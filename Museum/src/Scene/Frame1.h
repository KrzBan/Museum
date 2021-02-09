#pragma once

#include <iostream>

class Model;

struct Frame1 {
	Frame1(const std::string& texture);

	std::shared_ptr<Model> frameModel;
	std::shared_ptr<Model> paintingModel;
};