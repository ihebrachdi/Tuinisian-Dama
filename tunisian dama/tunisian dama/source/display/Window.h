#pragma once

#include<glfw3.h>
#include"../game_core/board.h"


#define DEFAULT_WIDTH 1080
#define DEFAULT_HEIGHT 720

//destructor

namespace imatics {
	class Window {
	public:
		unsigned short m_width = DEFAULT_WIDTH;
		unsigned short m_height = DEFAULT_HEIGHT;
		const char* m_title = NULL;
		GLFWwindow* m_window;

		bool m_isresize = false;
		bool m_mouse_pressed = false;
		bool m_mouse_pressing = false;
		bool m_mouse_release = true;



	private:
		GLFWimage* icon = NULL;
		/**********************this need to be proccess when the window is resized */
		struct port {
			board* portboard = nullptr;
		};
	public:
		port m_resizeport;

	public:
		Window(const char* title, unsigned short width, unsigned short height);
		void updatewindow(bool swap)const;
		bool windowclosed();
		void configport(board* boardport) {
			m_resizeport.portboard = boardport;
		}
	private:
		void windowcallback();
		bool windowinit();
	};
}