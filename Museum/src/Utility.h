#pragma once

//GLUT
#include "GL\glew.h"
#include "GL\freeglut.h"

//GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp"

//ASSIMP
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

void ClearScreen();
void SetFrameSize(uint32_t width, uint32_t height);


//Quad primitive, straight from LearnOpenGL.com
void RenderQuad();