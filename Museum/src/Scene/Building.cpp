#include "Building.h"

#include "Model.h"

Building::Building() {
	wallsModel = std::make_shared<Model>("res/models/museum/Walls.obj");
	wallsModel->InsertTexture("res/textures/marble/marble2_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	wallsModel->InsertTexture("res/textures/marble/marble2_specular.jpg", TEX_TYPE::TEX_SPECULAR);
	wallsModel->InsertTexture("res/textures/marble/marble2_normal.jpg", TEX_TYPE::TEX_NORMAL);
	wallsModel->transform.SetScale(0.01f);
	wallsModel->transform.PutOnGround();
	wallsModel->tiling = glm::vec2(5.0f, 0.5f);
	wallsModel->castShadows = false;

	floorModel = std::make_shared<Model>("res/models/museum/Floor.obj");
	floorModel->InsertTexture("res/textures/wood/wood_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	floorModel->InsertTexture("res/textures/wood/wood_specular.jpg", TEX_TYPE::TEX_SPECULAR);
	floorModel->InsertTexture("res/textures/wood/wood_normal.jpg", TEX_TYPE::TEX_NORMAL);
	floorModel->transform.SetScale(0.01f);
	floorModel->tiling = glm::vec2(5.0f, 5.0f);
	floorModel->castShadows = false;

	roofModel = std::make_shared<Model>("res/models/museum/Roof.obj");
	roofModel->InsertTexture("res/textures/marble/marble1_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	roofModel->InsertTexture("res/textures/marble/marble1_specular.jpg", TEX_TYPE::TEX_SPECULAR);
	roofModel->InsertTexture("res/textures/marble/marble1_normal.jpg", TEX_TYPE::TEX_NORMAL);
	roofModel->SetTiling(4.0f, 4.0f);
	roofModel->transform.SetScale(0.01f);
	roofModel->transform.PutOnGround();
	roofModel->transform.Translate(0.0f, 4.0f, 0.0f);
	roofModel->castShadows = false;

	tubeModel = std::make_shared<Model>("res/models/museum/Tube.obj");
	tubeModel->InsertTexture("res/textures/fabric/denim1_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	tubeModel->InsertTexture("res/textures/fabric/denim1_specular.jpg", TEX_TYPE::TEX_SPECULAR);
	tubeModel->InsertTexture("res/textures/fabric/denim1_normal.jpg", TEX_TYPE::TEX_NORMAL);
	tubeModel->SetTiling(4.0f, 4.0f);
	tubeModel->transform.SetScale(0.01f);
	tubeModel->castShadows = false;

	tubeSCModel = std::make_shared<Model>("res/models/museum/Tube.obj");
	tubeSCModel->transform.SetScale(0.0105f);
	tubeSCModel->transform.Translate(0.0f, -0.07f, 0.0f);
	tubeSCModel->castShadows = true;

	panelModel1 = std::make_shared<Model>("res/models/museum/Panel.obj");
	panelModel1->InsertTexture("res/models/museum/Panel_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	panelModel1->InsertTexture("res/models/museum/Panel_specular.jpg", TEX_TYPE::TEX_SPECULAR);
	panelModel1->InsertTexture("res/models/museum/Panel_normal.jpg", TEX_TYPE::TEX_NORMAL);
	panelModel1->transform.SetScale(0.01f);
	panelModel1->transform.Translate(0.0f, -0.1f, 0.0f);
	panelModel1->SetTiling(16.0f, 16.0f);
	panelModel1->ReveiceShadows(false);
	panelModel1->castShadows = false;
	panelModel1->transparent = true;

	panelModel2 = std::make_shared<Model>("res/models/museum/Panel.obj");
	panelModel2->InsertTexture("res/models/museum/Panel_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	panelModel2->InsertTexture("res/models/museum/Panel_specular.jpg", TEX_TYPE::TEX_SPECULAR);
	panelModel2->InsertTexture("res/models/museum/Panel_normal.jpg", TEX_TYPE::TEX_NORMAL);
	panelModel2->transform.SetScale(0.01f);
	panelModel2->transform.Translate(0.0f, 0.06f, 0.0f);
	panelModel2->SetTiling(16.0f, 16.0f);
	panelModel2->ReveiceShadows(false);
	panelModel2->castShadows = false;
	panelModel2->transparent = true;

	lamps[0].bodyModel->transform.Translate(  5.0f, 0.0f,  5.0f);
	lamps[1].bodyModel->transform.Translate( -5.0f, 0.0f,  5.0f);
	lamps[2].bodyModel->transform.Translate(  5.0f, 0.0f, -5.0f);
	lamps[3].bodyModel->transform.Translate( -5.0f, 0.0f, -5.0f);

	for (size_t i = 0; i < 8; ++i) {
		footerModels[i] = std::make_shared<Model>("res/models/museum/Footer.obj");
		footerModels[i]->InsertTexture("res/textures/wood/wood2_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
		footerModels[i]->transform.SetScale(0.01f);
		footerModels[i]->transform.PutOnGround();
		footerModels[i]->castShadows = false;
		footerModels[i]->ReveiceShadows(false);
	}
	
	float moveX = 10.0f - footerModels[0]->transform.size.x / 2;
	float moveY = 4.0f - footerModels[0]->transform.size.y;
	footerModels[0]->transform.Translate(moveX, 0.0f, 0.0f);
	footerModels[0]->transform.Rotate(0.0f, 0.0f, 0.0f);

	footerModels[1]->transform.Translate(-moveX, 0.0f, 0.0f);
	footerModels[1]->transform.Rotate(0.0f, 180.0f, 0.0f);

	footerModels[2]->transform.Translate(0.0f, 0.0f, moveX);
	footerModels[2]->transform.Rotate(0.0f, -90.0f, 0.0f);

	footerModels[3]->transform.Translate(0.0f, 0.0f, -moveX);
	footerModels[3]->transform.Rotate(0.0f, 90.0f, 0.0f);

	footerModels[4]->transform.Translate(moveX, moveY, 0.0f);
	footerModels[4]->transform.Rotate(180.0f, 0.0f, 0.0f);

	footerModels[5]->transform.Translate(-moveX, moveY, 0.0f);
	footerModels[5]->transform.Rotate(180.0f, 180.0f, 0.0f);

	footerModels[6]->transform.Translate(0.0f, moveY, moveX);
	footerModels[6]->transform.Rotate(180.0f, 90.0f, 0.0f);

	footerModels[7]->transform.Translate(0.0f, moveY, -moveX);
	footerModels[7]->transform.Rotate(180.0f, -90.0f, 0.0f);


}