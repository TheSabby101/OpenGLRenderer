#include "Gui.h"

MyGui::MyGui(GLFWwindow* window, unsigned int& Width, unsigned int& Height)
	:windowref(window), width(Width), height(Height)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430 core");

	
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	
	io.ConfigWindowsResizeFromEdges = true;
	//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	ImGui::GetMouseCursor();

	
	
	SetStyle();
}

MyGui::~MyGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void MyGui::Init()
{
	ImGui_ImplOpenGL3_NewFrame();

	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	
}

void MyGui::render()
{
	ImGui::Render();
}

void MyGui::MakeWindow()
{
	
	//ImGui::SetNextWindowBgAlpha(0.9f);
	
	
	static int x = 0.0f;
	static int y = 0.0f;
	static int z = 0.0f;

	static float w = 1.0f;
	static float h = 1.0f;
	static float d = 1.0f;

	static int ObjectNumber = 0;
	bool truetho = true;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.2, 0.2, 0.2, 0.7f });
	ImGui::Begin("Placement");
	ImGui::PopStyleColor(0);
	ImGui::Text("Wouldnt it be great if this worked");     
	ImGui::SliderInt("X", &x, -100, 100);  
	ImGui::SliderInt("Y", &y, -100, 100);
	ImGui::SliderInt("Z", &z, -100, 100); 

	ImGui::SliderFloat("W", &w, 0.1, 100);
	ImGui::SliderFloat("H", &h, 0.1, 100);
	ImGui::SliderFloat("D", &d, 0.1, 100);

	for (int i = 0; i < Objectlist.size()-1; i++)
	{
		ImGui::Checkbox(Objectlist[i]->OBJName, &Objectlist[i]->ShaderRef->LinkStatusbool);
		for (int i = 0; i < Objectlist.size() - 1; i++)
		{
			//ImGui::Text("%i Passed", Objectlist[i]->any_samples_passed);

		}

	}

	ImGui::SliderInt("LoadShape", &LoadShape, -0, Objectlist.size()-2);
	
	
	if (ImGui::Button("Place"))                            
	{
		Objectlist[LoadShape]->AddToList(x, y, z,w,h,d);
	}
	
	X = x;
	Y = y;
	Z = z;
	
	W = w;
	H = h;
	D = d;
	
	
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
	///
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::PopStyleColor(0);
}

void MyGui::MakeViewport()
{

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.2f, 0.2f, 0.2f, 0.7f });
	ImGui::PopStyleColor(0);
	ImGui::Begin("Scene Window");
	ImGui::ShowStyleEditor();
	ImGui::End();
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::PopStyleColor(0);
}

void MyGui::RenderEnder()
{

	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MyGui::AddToList(Object* obj)
{
	
	Objectlist[ObjectCount] = obj;
	Objectlist.emplace_back();
	ObjectCount++;
}

void MyGui::Docking()
{
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

void MyGui::SetStyle()
{
	ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f });
	//ImGui::PopStyleColor(0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 12.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 12.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 12.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, 7.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
	//ImGui::PopStyleVar(0);
}
