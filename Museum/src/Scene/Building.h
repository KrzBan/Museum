#pragma once

#include <iostream>

#include "Lamp.h"
#include "Display1.h"
#include "Display2.h"
#include "Display3.h"
#include "Display4.h"

#include "Frame1.h"

class Model;

class Building {
public:
	Building();

	std::shared_ptr<Model> wallsModel;
	std::shared_ptr<Model> floorModel;
	std::shared_ptr<Model> roofModel;

	std::shared_ptr<Model> tubeModel;
	std::shared_ptr<Model> tubeSCModel;

	std::shared_ptr<Model> panelModel1;
	std::shared_ptr<Model> panelModel2;

	std::shared_ptr<Model> footerModels[8];

	Lamp lamps[4];

	Display1 display1;
	Display2 display2;
	Display3 display3;
	Display4 display4;

};