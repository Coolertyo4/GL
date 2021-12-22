#include "controls.hpp"
#define LOGCONTROLS

extern GLFWwindow* window;

void log(const char* name, glm::vec3 l)
{
     printf("%s %f %f %f\n", name, l.x, l.y, l.z);
}


glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::vec3 position(0, 0, 5);

int mouseBound = MOUSE_BOUND;

float horizontalAngle = 0.0f;

float verticalAngle = 0.0f;

float initialFoV = 45.0f;

float speed = BASE_SPEED;

float mouseSpeed = MOUSE_SPEED;

double lastTime;

void computeMatricesFromInputs()
{
    // printf("%f\n", verticalAngle);
     

     double currentTime= glfwGetTime();
     float deltaTime = float(currentTime - lastTime);
     lastTime = currentTime;

     double xpos, ypos;
     if(mouseBound)
     {
	glfwGetCursorPos(window, &xpos, &ypos);
	//Compute orientation
	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * float( 768/2 - ypos );

     //reset
	glfwSetCursorPos(window, 1024/2, 768/2);

     //printf("%d\n", horizontalAngle);
     }
     //direction vector
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
     

     //right vector
     glm::vec3 right = glm::vec3(
          sin(horizontalAngle - 3.14f/2.0f),
          0,
          cos(horizontalAngle - 3.14f/2.0f)
     );

     glm::vec3 up = glm::cross(right, direction);
     //move forward
     if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS)
     {
          position += normalize(glm::vec3(direction.x, 0.0f, direction.z)) * deltaTime * speed;
     }
     //move backward
     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
     {
          position -= normalize(glm::vec3(direction.x, 0.0f, direction.z)) * deltaTime * speed;
     }
     //move right
     if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS)
     {
          position += normalize(right) * deltaTime * speed;
     }
     //move left
     if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS)
     {
          position -= normalize(right) * deltaTime * speed;
     }
     if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
     {
          position.y -= deltaTime * speed;
     }

     if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
     {
          position.y += deltaTime * speed;
     }

     if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
     {
          speed = BOOST_SPEED;
     } else
     {
          speed = BASE_SPEED;
     }
     if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
     {
          mouseBound = 0;
     }
     if(glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
     {
          mouseBound = 1;
     }
  

     //compute FoV
     float FoV = initialFoV;
     #ifdef LOGCONTROLS
     printf("%s %f %f %f %s %f %f %f %s %f %f %s %f %f \n", "UP: ", up.x, up.y, up.z, "DIRECTION: ", direction.x, direction.y, direction.z, "coss", cos(verticalAngle), cos(horizontalAngle), "Angles", verticalAngle, horizontalAngle);
  
     if(up.y < 0)
     {
          printf("Upside Down!\n");
     }
     #endif
     //Projection Matrix
     ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

     //View Matrix for Camera
     ViewMatrix = glm::lookAt(
          position, //Camera position
          position + direction, // Looks at position plus direction
          up // Where up is
     );

}

glm::mat4 getProjectionMatrix()
{
     return ProjectionMatrix;
}

glm::mat4 getViewMatrix()
{
     return ViewMatrix;
}