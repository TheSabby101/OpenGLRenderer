#pragma once
#include "Header.h"
#include "Camera.h"
#include "Object.h"


class MyGui
{

	bool show_demo_window = false;
	bool show_another_window = false;
	//ImVec4 clear_color = ImVec4(1.0f, 0.55f, 1.0f, 1.0f);

	int LoadShape = 0;
	bool draw = false;
	//ImGuiIO& io = ImGui::GetIO();
	//ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	GLFWwindow* windowref;

	inline static int ObjectIndex = 0;
	inline static int ObjectNumber = 0;

	//enum condition { begin, end };
	void Highlight();

	float* prevSelect;
	float* currentSelect;
	bool first = true;
	int prevshape, currshape = 0;



public:
	float X, Y, Z = 0.0f;
	float W, H, D = 1.0f;

	unsigned int& width;
	unsigned int& height;

	inline static float FPS;

	MyGui(GLFWwindow* window, unsigned int& Width, unsigned int& Height);
	~MyGui();

	void render();
	void Init();
	void MakeWindow();
	void MakeViewport();
	void RenderEnder();
	void Docking();
	void SetStyle();
};