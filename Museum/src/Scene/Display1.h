#pragma once

#include "Column.h"

struct Display1 {
	Display1();

	Column column;

	std::shared_ptr<Model> decahedronModel;

	std::shared_ptr<Model> laoconModel;

	std::shared_ptr<Model> eagleModel;

	std::shared_ptr<Model> horseModel;

	std::shared_ptr<Model> carpetModel;

};