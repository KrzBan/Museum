#include "Frame1.h"

#include "Model.h"

Frame1::Frame1(const std::string& texture) {

	frameModel= std::make_shared<Model>("res/models/museum/paintings/painting1.obj", false);
	frameModel->InsertTexture("res/models/museum/paintings/painting1_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	frameModel->InsertTexture("res/models/museum/paintings/painting1_specular.jpg", TEX_TYPE::TEX_SPECULAR);
	frameModel->InsertTexture("res/models/museum/paintings/painting1_normal.jpg", TEX_TYPE::TEX_NORMAL);
	frameModel->transform.PutOnGround();
	frameModel->transform.Translate(0.0f, 1.0f, 0.0f);
	frameModel->transform.SetScale(2.0f);
	frameModel->ReveiceShadows(false);
	

	paintingModel = std::make_shared<Model>("res/models/prim/plane.obj");
	paintingModel->InsertTexture(texture, TEX_TYPE::TEX_DIFFUSE);
	paintingModel->transform.SetParent(&frameModel->transform);
	paintingModel->transform.SetScale(1.0f, 0.0013f, 0.0033f);
	paintingModel->transform.Translate(0.025, 1.12f, -0.12f);
	paintingModel->SetTiling(1.0f, -1.0f);
	paintingModel->ReveiceShadows(false);
	paintingModel->castShadows = false;

}