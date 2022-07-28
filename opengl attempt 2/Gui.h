#pragma once
#include "Header.h"
#include "Object.h"




class MyGui
{
	bool show_demo_window = false;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	int ObjectCount = 0;
	int LoadShape = 0;
	bool draw = false;
public:
	float X = 0;
	float Y = 0;
	float Z = 0;

	//Object* Objectlist[50];
	std::vector<Object*> Objectlist{0};
	MyGui(GLFWwindow* window);
	~MyGui();

	void Render();
	void MakeWindow();
	void RenderEnder();
	void AddToList(Object* obj);
	

};

