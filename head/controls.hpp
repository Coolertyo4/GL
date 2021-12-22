#ifndef _controls
#define _controls

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "constants.hpp"


#define BASE_SPEED 3.0f
#define BOOST_SPEED 9.0f
#define MOUSE_SPEED 0.005f
#define MOUSE_BOUND 0



void computeMatricesFromInputs();

glm::mat4 getProjectionMatrix();

glm::mat4 getViewMatrix();


#endif