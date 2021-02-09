#include "App.h"

#include "Utility.h"
#include "src/Time.h"
#include "src/Scene.h"
#include "src/ResourceManager.h"

//Initialization
App::App(int screenWidth, int screenHeight):
	m_ScreenWidth{ screenWidth }, m_ScreenHeight{ screenHeight }
{
	mainCamera = std::make_unique<CameraController>( static_cast<float>(screenWidth) / screenHeight );
	mainCamera->camera.position = glm::vec3(0.0f, 1.8f, -7.0f);

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	float ambientStrength = 1;

	pointLights.push_back(PointLight{ 1, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(252.0f, 212.0f, 64.0f) / 255.0f , 0.2 }); //sun

	pointLights.push_back(PointLight{ 1, glm::vec3( 5.0f, 3.9f,  5.0f), lightColor, ambientStrength });
	pointLights.push_back(PointLight{ 1, glm::vec3(-5.0f, 3.9f,  5.0f), lightColor, ambientStrength });
	pointLights.push_back(PointLight{ 1, glm::vec3( 5.0f, 3.9f, -5.0f), lightColor, ambientStrength });
	pointLights.push_back(PointLight{ 1, glm::vec3(-5.0f, 3.9f, -5.0f), lightColor, ambientStrength });

	//After the lights are made
	shadowMap = std::make_shared<ShadowMap>(1024, 1024, PointLight::GetShadowCasters());
	hdr = std::make_shared<HDR>(m_ScreenWidth, m_ScreenHeight);

	shaderModel = std::make_shared<Shader>("model", "res/shaders/model_vert.glsl", "res/shaders/model_frag.glsl");
	shaderShadow = std::make_shared<Shader>("shadow", "res/shaders/shadow_vert.glsl", "res/shaders/shadow_frag.glsl", "res/shaders/shadow_geo.glsl");
	shaderHDR = std::make_shared<Shader>("shadow", "res/shaders/hdr_vert.glsl", "res/shaders/hdr_frag.glsl");

	//set uniforms that dont really change
	shaderModel->Bind();
	shaderModel->SetInt("textureDepth", 6);
	shaderModel->SetFloat("u_Material.shininess", 32.0f);
}

void App::Idle()
{
	Time::UpdateTime();
	float deltaTime = Time::DeltaTimeF();

	std::string title = "Museum, " + std::to_string(Time::FPS()) + " FPS";
	glutSetWindowTitle(title.c_str());

	//process scripts...
	mainCamera->OnUpdate(deltaTime);
	solarSystem.OnUpdate(deltaTime);

	pointLights[0].position = solarSystem.sunModel->transform.position;

	if (Input::GetKey(27)) {
		//exit(1);
		glutLeaveMainLoop();
	}
	if (Input::GetKeyDown('x')) {
		m_DrawShadows = !m_DrawShadows;
	}
	if (Input::GetKeyDown('z')) {
		m_UseLights = !m_UseLights;
	}
	if (Input::GetKeyDown('c')) {
		m_SoftShadows = !m_SoftShadows;
	}
	if (Input::GetKeyDown('b')) {
		m_UseHDR = !m_UseHDR;
	}
	if (Input::GetKey('m')) {
		m_Exposure += 1 * deltaTime;
	}
	if (Input::GetKey('n')) {
		m_Exposure -= 1 * deltaTime;
	}
	if (Input::GetKeyDown('v')) {
		m_GenerateShadows = !m_GenerateShadows;
	}

	if (Input::GetKeyDown(GLUT_LEFT_BUTTON)) {
		std::cout << "X: " << Input::GetMousePosX();
		std::cout << ", Y: " << Input::GetMousePosY() << '\n';
	}

	//reset input state
	Input::ResetKeyState();

	glutPostRedisplay();
}

void App::Draw()
{	
	Scene::GetTransform().UpdateTransform();	//Updates Scene::Transform and, recursively, its' children

	static int i = 0;
	if (m_DrawShadows && m_GenerateShadows) {
			RenderShadows();	
	}

	Render();

	AddHDR();

	glFlush();
	glutSwapBuffers();
}

void App::Render() {
	hdr->BindFramebuffer();
	SetFrameSize(m_ScreenWidth, m_ScreenHeight);
	
	 std::shared_ptr<Shader> currentShader = shaderModel;
	
	//Models
	currentShader->Bind();
	currentShader->SetFloat("u_FarPlane", farPlane);
	currentShader->SetFloat3("u_ViewPos", mainCamera->camera.position);
	currentShader->SetMat4f("u_ViewProj", mainCamera->camera.GetViewProjMatrix());

	currentShader->SetFloat("u_Transparency", 1.0f);

	//lights
	currentShader->SetBool("u_DrawShadows", m_DrawShadows);
	currentShader->SetBool("u_SoftShadows", m_SoftShadows);
	currentShader->SetBool("u_UseLights", m_UseLights);
	if(m_UseLights)
		BindLights(pointLights, currentShader);

	//Draw models
	for (auto& model : ResourceManager::GetModels()) {
		if(model->transparent == false)
			model->Draw(currentShader);
	}
	
	//render all transparent objects here, sorted by camera distance(TODO)
	glDepthMask(GL_FALSE);
	currentShader->SetFloat("u_Transparency", 0.4f);
	for (auto& model : ResourceManager::GetModels()) {
		if (model->transparent == true)
			model->Draw(currentShader);
	}
	//restore the depth mask
	glDepthMask(GL_TRUE);

	hdr->UnbindFramebuffer();
}

void App::RenderShadows() {
	shadowMap->Bind();

	float aspect = static_cast<float>(shadowMap->m_Width) / static_cast<float>(shadowMap->m_Height);
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), aspect, nearPlane, farPlane);

	std::vector<glm::mat4> shadowTransforms;
	shadowTransforms.reserve(PointLight::GetShadowCasters() * static_cast<size_t>(6));
	for (auto& light : pointLights) {
		if (light.castsShadows == false) continue;
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(light.position, light.position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(light.position, light.position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(light.position, light.position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(light.position, light.position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(light.position, light.position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(light.position, light.position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
	}
		
	shaderShadow->Bind();
	shaderShadow->SetFloat("u_FarPlane", farPlane);
	for (unsigned int i = 0; i < 6*PointLight::GetShadowCasters(); ++i)
		shaderShadow->SetMat4f("u_ShadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
	int i = 0;
	for (auto& light : pointLights) {
		if (light.castsShadows == false) continue;
		shaderShadow->SetFloat3("u_LightPos[" + std::to_string(i++) + "]", light.position);
	}
	
	//Draw all models(not transparent, havent figured how, yet)
	for (auto& model : ResourceManager::GetModels()) {
		if (model->castShadows && model->transparent == false)
			model->Draw(shaderShadow);
	}
	shadowMap->Unbind();
}

void App::AddHDR() {
	ClearScreen();
	shaderHDR->Bind();
	shaderHDR->SetBool("u_UseHDR", m_UseHDR);
	shaderHDR->SetFloat("u_Exposure", m_Exposure);
	hdr->BindTexture(shaderHDR);

	RenderQuad();
}

void App::Resize(int width, int height) {
	m_ScreenWidth = width;
	m_ScreenHeight = height;

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetFrameSize(m_ScreenWidth, m_ScreenHeight);

	mainCamera->camera.UpdateAspectRatio((GLfloat)m_ScreenWidth / (GLfloat)m_ScreenHeight);
	//Just re-create hdr, results in memory spike during re-sizing after which it slowly falls down, but at least it's easy...
	hdr = std::make_shared<HDR>(width, height);

	glutPostRedisplay();
}