#include"time.h"
#include<iostream>
namespace imatics {
	Time::Time() {
		m_alarmbusy = false;
		m_holdtime = 0;
	}
	bool Time::Alarm(double timeins) {
		if (!m_alarmbusy) {
			m_alarmbusy = true;
			m_holdtime = glfwGetTime();
			return false;
		}
		else {
			double currenttime = glfwGetTime();
			if ((currenttime - m_holdtime) < timeins) {
				return false;
			}
			m_alarmbusy = false;
			return true;
		}

	}
}