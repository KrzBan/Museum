#include "Display3.h"

#include "Frame1.h"
#include "Frame2.h"
#include "Model.h""

Display3::Display3() {
	
	painting1 = std::make_shared<Frame2>("res/textures/art/art3_1.jpg");
	painting1->frameModel->transform.Translate(0.0f, .5f, 9.99f);
	painting1->frameModel->transform.Rotate(0.0f, 90.0f, 0.0f);
	painting1->frameModel->transform.Scale(1.0f, 3.0f, 4.0f);

	painting2 = std::make_shared<Frame2>("res/textures/art/art3_2.jpg");
	painting2->frameModel->transform.Translate(3.0f, .5f, 9.99f);
	painting2->frameModel->transform.Rotate(0.0f, 90.0f, 0.0f);
	painting2->frameModel->transform.Scale(1.0f, 2.0f, 4.2f);
	
	painting3 = std::make_shared<Frame2>("res/textures/art/art3_3.jpg");
	painting3->frameModel->transform.Translate(-3.0f, .5f, 9.99f);
	painting3->frameModel->transform.Rotate(0.0f, 90.0f, 0.0f);
	painting3->frameModel->transform.Scale(1.0f, 2.0f, 3.2f);

	painting4 = std::make_shared<Frame1>("res/textures/art/art3_4.jpg");
	painting4->frameModel->transform.Translate(5.0f, -1.4f, 9.99f);
	painting4->frameModel->transform.Rotate(0.0f, 90.0f, 0.0f);
	painting4->frameModel->transform.Scale(1.0f, 1.4f, 0.4);
}