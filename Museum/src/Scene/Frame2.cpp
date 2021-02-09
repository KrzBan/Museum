#include "Frame2.h"

#include "Model.h"

Frame2::Frame2(const std::string& texture) {

	frameModel= std::make_shared<Model>("res/models/museum/paintings/painting2.fbx", false);
	frameModel->InsertTexture("res/models/museum/paintings/painting2_diffuse.png", TEX_TYPE::TEX_DIFFUSE);
	frameModel->InsertTexture("res/models/museum/paintings/painting2_specular.png", TEX_TYPE::TEX_SPECULAR);
	frameModel->InsertTexture("res/models/museum/paintings/painting2_normal.png", TEX_TYPE::TEX_NORMAL);
	frameModel->transform.SetScale(0.01f);
	frameModel->transform.PutOnGround();
	frameModel->transform.Translate(0.0f, 1.0f, 0.0f);

	paintingModel = std::make_shared<Model>("res/models/prim/plane.obj");
	paintingModel->InsertTexture(texture, TEX_TYPE::TEX_DIFFUSE);
	paintingModel->transform.SetParent(&frameModel->transform);
	paintingModel->transform.SetScale(1.0f, 0.16f, 0.09f);
	paintingModel->transform.Translate(0.5f, 1.1f, 0.0f);
	paintingModel->SetTiling(1.0f, -1.0f);

}