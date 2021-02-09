#pragma once

#include <iostream>

#include "Object.h"

class Model;
class Transform;

class Lamp  {
public:
	Lamp();

	std::shared_ptr<Model> bodyModel;
	std::shared_ptr<Model> lightModel;

};