#include "Column.h"

#include "Model.h"

Column::Column() {
	columnModel = std::make_shared<Model>("res/models/museum/column/column.obj", false);
	columnModel->InsertTexture("res/models/museum/column/Column_diffuse.jpg", TEX_TYPE::TEX_DIFFUSE);
	columnModel->InsertTexture("res/models/museum/column/Column_normal.jpg", TEX_TYPE::TEX_NORMAL);
	columnModel->transform.SetScale(0.015f);
	columnModel->transform.PutOnGround();
}