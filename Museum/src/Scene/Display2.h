#pragma once

#include "Column.h"

struct Frame1;

struct Display2 {
	Display2();

	std::shared_ptr<Frame1> painting1;
	std::shared_ptr<Frame1> painting2;
	std::shared_ptr<Frame1> painting3;
};