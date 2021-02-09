#include "Display4.h"

#include "Frame2.h"
#include "Model.h""

Display4::Display4() {
	
	painting1 = std::make_shared<Frame2>("res/textures/art/art4_1.jpg");
	painting1->frameModel->transform.Translate(9.99f, .5f, 0.0f);
	painting1->frameModel->transform.Rotate(0.0f, 180.0f, 0.0f);
	painting1->frameModel->transform.Scale(1.0f, 3.0f, 7.0f);

	painting2 = std::make_shared<Frame2>("res/textures/art/art4_2.jpg");
	painting2->frameModel->transform.Translate(9.99f, .4f, 4.0f);
	painting2->frameModel->transform.Rotate(0.0f, 180.0f, 0.0f);
	painting2->frameModel->transform.Scale(1.0f, 2.0f, 4.2f);
	
	painting3 = std::make_shared<Frame2>("res/textures/art/art4_3.jpg");
	painting3->frameModel->transform.Translate(9.99f, .5f, -4.0f);
	painting3->frameModel->transform.Rotate(0.0f, 180.0f, 0.0f);
	painting3->frameModel->transform.Scale(1.0f, 3.0f, 4.2f);

	
}