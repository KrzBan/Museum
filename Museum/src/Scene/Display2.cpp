#include "Display2.h"

#include "Frame1.h"
#include "Model.h""

Display2::Display2() {
	
	painting1 = std::make_shared<Frame1>("res/textures/art/art2_1.png");
	painting1->frameModel->transform.Translate(-9.99f, 0.0f, 0.0f);

	painting2 = std::make_shared<Frame1>("res/textures/art/art2_2.jpg");
	painting2->frameModel->transform.Translate(-9.99f, -1.0f, 3.0f);
	painting2->frameModel->transform.Scale(1.0f, 1.4f, 0.6f);

	painting3 = std::make_shared<Frame1>("res/textures/art/art2_3.jpeg");
	painting3->frameModel->transform.Translate(-9.99f, -0.8f, -3.0f);
	painting3->frameModel->transform.Scale(1.0f, 1.1f, 0.9f);

	
}