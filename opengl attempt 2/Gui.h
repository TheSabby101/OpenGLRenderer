#pragma once
#include "Header.h"
#include "Object.h"
#include "Camera.h"



class MyGui
{

	bool show_demo_window = false;
	bool show_another_window = false;
	//ImVec4 clear_color = ImVec4(1.0f, 0.55f, 1.0f, 1.0f);
	int ObjectCount = 0;
	int LoadShape = 0;
	bool draw = false;
	//ImGuiIO& io = ImGui::GetIO();
	//ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	GLFWwindow* windowref;
	
	
public:
	float X, Y, Z = 0.0f;

	float W, H, D = 1.0f;
	unsigned int& width;
	unsigned int& height;

	//Object* Objectlist[50];
	std::vector<Object*> Objectlist{0};


	MyGui(GLFWwindow* window, unsigned int& Width, unsigned int& Height);
	~MyGui();

	void render();
	void Init();
	void MakeWindow();
	void MakeViewport();
	void RenderEnder();
	void AddToList(Object* obj);
	void Docking();
	void SetStyle();
};

