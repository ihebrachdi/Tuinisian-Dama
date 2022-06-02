#include<glew.h>
#include"Window.h"
#include"..\Log.h"

namespace imatics {

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	Window* entity = (Window*)glfwGetWindowUserPointer(window);
	entity->m_width = width;
	entity->m_height = height;
	entity->m_isresize = true;
	/*if (entity->m_resizeport.portboard)
	{
		//entity->m_resizeport.portboard->redimensionBoard(width, height);
		//Log("resizeing  "<< entity->m_resizeport.portboard->m_vecteurw);
	}*/
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	Window* entity = (Window*)glfwGetWindowUserPointer(window);
	double xpos, ypos;
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			entity->m_mouse_pressed = true;
			entity->m_mouse_pressing = true;
			glfwGetCursorPos(entity->m_window, &xpos, &ypos);
			
		}
		else if (action == GLFW_RELEASE) {
			entity->m_mouse_pressed = false;
			entity->m_mouse_pressing = false;
			entity->m_mouse_release = true;
			
		}
	}

}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
}

	Window::Window(const char* title, unsigned short width, unsigned short height) :m_width(width), m_height(height), m_title(title) {
		if (!windowinit()) {
			glfwSetWindowShouldClose(m_window, GLFW_TRUE);
		}
		else {
			//glClearColor(1.0f, 0.0f, 0.75f, 1.0f);
			glfwSetWindowUserPointer(m_window, this);
			windowcallback();
		}
	}
	bool Window::windowinit() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

#if 0
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
#endif

		if (!glfwInit()) {
			Log("fail to initialize");
			return false;
		}
		m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
		if (!m_window) {
			Log("failed to create window");
			glfwTerminate();
			return false;
		}
		else {
			glfwMakeContextCurrent(m_window);
			Log("window created succesfuly");
		}
		if (glewInit() != GLEW_OK) {
			Log("glew init pb");
			return false;
		}
		
		glfwSwapInterval(1);
		return true;
	}

	void Window::updatewindow(bool swap) const {
		if (swap)
			glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	bool Window::windowclosed() {
		if (glfwWindowShouldClose(m_window)) {
			return true;
		}
		return false;
	}

	void Window::windowcallback() {
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);
	}
}