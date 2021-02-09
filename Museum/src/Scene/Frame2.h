#pragma once

#include <iostream>

class Model;

struct Frame2 {
	Frame2(const std::string& texture);

	std::shared_ptr<Model> frameModel;
	std::shared_ptr<Model> paintingModel;
};