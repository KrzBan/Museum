#pragma once

#include <iostream>

struct Frame2;

struct Display4 {
	Display4();

	std::shared_ptr<Frame2> painting1;
	std::shared_ptr<Frame2> painting2;
	std::shared_ptr<Frame2> painting3;
};