#include "CameraControl.h"
#include <GLFW/glfw3.h>

void gp::gui::CameraControl::moveCamera(GLFWwindow* window, gp::gui::ScenarioControl& scenarioControl, gp::graphics::Camera& camera)
{
  if (scenarioControl.interactsWithMouse()) {
    return;
  }

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
		m_xrot += (xpos-m_lastXPos) / (0.1f * camera.width());
		m_yrot += (ypos-m_lastYPos) / (0.1f * camera.height());
	}
  glfwGetCursorPos(window, &m_lastXPos, &m_lastYPos);

  int W = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) ? 1 : 0;
  int A = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) ? 1 : 0;
  int S = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) ? 1 : 0;
  int D = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) ? 1 : 0;
  int E = (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) ? 1 : 0;
  int Q = (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) ? 1 : 0;

  float speed = 0.05f;
  camera.translateCC(glm::vec3( (A-D) * speed, (Q-E) * speed, (W-S) * speed ));

  glm::vec3 yAxis = glm::vec3(0.0, 1.0, 0.0);
  glm::vec3 xAxis = glm::vec3(1.0, 0.0, 0.0);
	glm::quat rot1 = glm::rotate(glm::quat(), m_yrot, xAxis);
	glm::quat rot2 = glm::rotate(rot1, m_xrot, yAxis);
	camera.setRotation(rot2);
}

void gp::gui::CameraControl::reset()
{
  m_lastXPos = 0.0;
  m_lastYPos = 0.0;
  m_xrot = 0.0f;
  m_yrot = 0.0f;
}
