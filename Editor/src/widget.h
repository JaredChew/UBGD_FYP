#pragma once

#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Widget {

protected:
	std::string name;
	bool allowCloseButton;

	virtual void action() = 0;

public:

	Widget() {

		this->name = "widget";
		this->allowCloseButton = true;
	}
	Widget(std::string name, bool allowCloseButton) {
		this->name = name;
		this->allowCloseButton = allowCloseButton;
	}

	void drawWidget()
	{
		//ImGui::SetNextWindowSize(ImVec2(300, 600));
		//if (this->allowCloseButton) return;

		if (ImGui::Begin(name.c_str(), &this->allowCloseButton))
		{
			this->action();
			ImGui::End();
		}
		else 
		{
			ImGui::End();
			return;
		}

	}

};