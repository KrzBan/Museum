#pragma once

#include <iostream>

class Model;

class Column {
public:
	Column();

	std::shared_ptr<Model> columnModel;
};