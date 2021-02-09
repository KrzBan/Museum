#pragma once

#include <iostream>

struct Frame1;
struct Frame2;

struct Display3 {
	Display3();

	std::shared_ptr<Frame2> painting1;
	std::shared_ptr<Frame2> painting2;
	std::shared_ptr<Frame2> painting3;

	std::shared_ptr<Frame1> painting4;
};