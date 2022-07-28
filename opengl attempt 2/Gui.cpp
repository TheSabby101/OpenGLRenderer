#include "Gui.h"

MyGui::MyGui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430 core");

}

MyGui::~MyGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void MyGui::Render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	MakeWindow();
	ImGui::Render();
}

void MyGui::MakeWindow()
{
	static int x = 0.0f;
	static int y = 0.0f;
	static int z = 0.0f;
	static int ObjectNumber = 0;
	
	ImGui::Begin("Placement");                          

	ImGui::Text("Wouldnt it be great if this worked");     
	ImGui::SliderInt("X", &x, -100, 100);  
	ImGui::SliderInt("Y", &y, -100, 100);
	ImGui::SliderInt("Z", &z, -100, 100); 
	ImGui::SliderInt("LoadShape", &LoadShape, -0, Objectlist.size()-2);
	ImGui::ColorEdit3("clear color", (float*)&clear_color);

	if (ImGui::Button("Place"))                            
	{
		Objectlist[LoadShape]->AddToList(x, y, z);
	}
	
	
	
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	X = x;
	Y = y;
	Z = z;
}

void MyGui::RenderEnder()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MyGui::AddToList(Object* obj)
{
	
	Objectlist[ObjectCount] = obj;
	Objectlist.emplace_back();
	ObjectCount++;
}
