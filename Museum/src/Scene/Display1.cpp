#include "Display1.h"

#include "Model.h"

Display1::Display1() {
	column.columnModel->transform.Translate(7.0f, 0.0f, 7.0f);
	column.columnModel->transform.Rotate(0.0f, 15.0f, 0.0f);

	decahedronModel = std::make_shared<Model>("res/models/museum/display1/decahedron.obj");
	decahedronModel->InsertTexture("res/models/museum/display1/decahedron_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	decahedronModel->InsertTexture("res/models/museum/display1/decahedron_metalness.jpg", TEX_TYPE::TEX_SPECULAR);
	decahedronModel->InsertTexture("res/models/museum/display1/decahedron_normal.jpg", TEX_TYPE::TEX_NORMAL);
	decahedronModel->transform.SetScale(8.0f);
	decahedronModel->transform.SetParent(&column.columnModel->transform);
	decahedronModel->transform.Translate(0.0f, 98.0f, 0.0f);

	
	laoconModel = std::make_shared<Model>("res/models/museum/display1/laocon.obj", false);
	laoconModel->InsertTexture("res/models/museum/display1/laocon_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	laoconModel->InsertTexture("res/models/museum/display1/laocon_gloss.jpg", TEX_TYPE::TEX_SPECULAR);
	laoconModel->InsertTexture("res/models/museum/display1/laocon_normal.jpg", TEX_TYPE::TEX_NORMAL);
	laoconModel->transform.Rotate(-90.0f, 0.0f, -130.0f);
	laoconModel->transform.SetScale(0.11f);
	laoconModel->transform.PutOnGround();
	laoconModel->transform.Translate(7.8f, -0.8f, -7.8f);


	eagleModel = std::make_shared<Model>("res/models/museum/display1/model.obj", false);
	eagleModel->InsertTexture("res/models/museum/display1/model_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	eagleModel->transform.Rotate(-90.0f, 0.0f, 135.0f);
	eagleModel->transform.SetScale(0.11f);
	eagleModel->transform.PutOnGround();
	eagleModel->transform.Translate(-7.2f, 2.8f, 6.85f);

	horseModel = std::make_shared<Model>("res/models/museum/display1/horse.obj", false);
	horseModel->InsertTexture("res/models/museum/display1/horse_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	horseModel->transform.Rotate(-45.0f, 0.0f, 0.0f);
	horseModel->transform.SetScale(0.18f);
	horseModel->transform.PutOnGround();
	horseModel->transform.Translate(-6.9f, 1.4f, -6.9f);

	carpetModel = std::make_shared<Model>("res/models/museum/display1/carpet.glb");
	carpetModel->InsertTexture("res/models/museum/display1/carpet_diffuse.jpeg", TEX_TYPE::TEX_DIFFUSE);
	carpetModel->InsertTexture("res/models/museum/display1/carpet_roughness.jpeg", TEX_TYPE::TEX_SPECULAR);
	carpetModel->InsertTexture("res/models/museum/display1/carpet_normal.jpeg", TEX_TYPE::TEX_NORMAL);
	carpetModel->transform.Scale(0.012f);
	carpetModel->transform.Translate(-7.5f, 0.01f, -8.2f);
	carpetModel->transform.Rotate(0.0f, -20.0f, 0.0f);
	carpetModel->castShadows = false;
}