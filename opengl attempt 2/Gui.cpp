#include "Gui.h"

MyGui::MyGui(GLFWwindow* window, unsigned int& Width, unsigned int& Height)
	:windowref(window), width(Width), height(Height)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450 core");

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
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void MyGui::Highlight()
{
//	This old code checks if the value has changed before changing it, but it was determined to be slower than just changing the value anyway;

//	if (!Stop)
//	{
//		if (Object::Objectlist[LoadShape]->MeshInstances > 0)
//		{
//			Resets object back to original size
//			if(changed)
//			Object::Objectlist[LoadShape]->InstanceCoordinates[a].w = 1.0;
//			a = ObjectIndex - 1;
//
//			Sets object size
//			ImGui::SliderInt("DrawlistSelect", &ObjectIndex, 1, Object::Objectlist[LoadShape]->MeshInstances);
//			Object::Objectlist[LoadShape]->InstanceCoordinates[ObjectIndex - 1].w = 0.8;
//			b = ObjectIndex - 1;
//			//std::cout << a  << " " <<  b << std::endl;
//
//		}
//	}
//	if (a != b)
//	{
//		changed = true;
//		std::cout << "changed";
//	}
//	else
//		changed = false;


	
		if (Object::Objectlist[LoadShape]->MeshInstances > 0)
		{
//			Resets object back to original size
			if(!first)
//			Resets the previous selection, then sets the new previous for the next frame
			*prevSelect = 1.0;
			prevSelect = &Object::Objectlist[LoadShape]->InstanceCoordinates[ObjectIndex - 1].w;
			
			
			
//			Sets object size
			ImGui::SliderInt("DrawlistSelect", &ObjectIndex, 1, Object::Objectlist[LoadShape]->MeshInstances);
			Object::Objectlist[LoadShape]->InstanceCoordinates[ObjectIndex - 1].w = 0.8;
			
			//only reset the previous selection if there was a previous selection
			first = false;
		}
	
}


void MyGui::MakeWindow()
{

	//ImGui::SetNextWindowBgAlpha(0.9f);

	static int x = 0;
	static int y = 0;
	static int z = 0;

	static float w = 1.0f;
	static float h = 1.0f;
	static float d = 1.0f;

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.2, 0.2, 0.2, 0.7f });
	ImGui::Begin("Placement");
	ImGui::PopStyleColor(0);
	ImGui::Text("I Cant Believe its Not Butter");
	ImGui::SliderInt("X", &x, -100, 100);
	ImGui::SliderInt("Y", &y, -100, 100);
	ImGui::SliderInt("Z", &z, -100, 100);

	ImGui::SliderFloat("W", &w, 0.1f, 100.0f);
	ImGui::SliderFloat("H", &h, 0.1f, 100.0f);
	ImGui::SliderFloat("D", &d, 0.1f, 100.0f);
	ImGui::NewLine();

	ImGui::SliderFloat("FOV", &Camera::fov, 20.0f, 120.0f);
	
	

//	for (int i = 0; i < Object::Objectlist.size() - 1; i++)
//	{
//		ImGui::Checkbox(Object::Objectlist[i]->OBJName, &Object::Objectlist[i]->ShaderRef->LinkStatusbool);
//		for (int i = 0; i < Object::Objectlist.size() - 1; i++)
//		{
//			ImGui::Text("%i Passed", Objectlist[i]->any_samples_passed);
//
//		}
//
//	}


	ImGui::SliderInt("LoadShape", &LoadShape, 0, Object::Objectlist.size() - 2);
	ImGui::NewLine();

	ImGui::Text(Object::Objectlist[LoadShape]->OBJName);

	if(ObjectIndex > Object::BatchDrawIndex[LoadShape]->MeshInstances)
	ObjectIndex = Object::BatchDrawIndex[LoadShape]->MeshInstances;

	
	if (ObjectIndex == 0 )
		ObjectIndex = 1;
	if (Object::Objectlist[LoadShape]->MeshInstances > 0)
	{
		ImGui::Text("%f X", Object::BatchDrawIndex[LoadShape]->InstanceCoordinates[ObjectIndex-1].x);
		ImGui::Text("%f Y", Object::BatchDrawIndex[LoadShape]->InstanceCoordinates[ObjectIndex-1].y);
		ImGui::Text("%f Z", -Object::BatchDrawIndex[LoadShape]->InstanceCoordinates[ObjectIndex-1].z);
	}
	

//	Increases the size of the object by 20% to make it clear what you have selected
	Highlight();
	

//	Places and removes selected objects based on their index
	if (ImGui::Button("Place"))
	{
	//	Object::Objectlist[LoadShape]->AddToList(x, y, z, w, h, d);
		Object::Objectlist[LoadShape]->BatchAddToList(x, y, z,w,h,d);
	}
	if (ImGui::Button("Remove"))
	{
		if(ObjectIndex !=0)
		Object::Objectlist[LoadShape]->BatchRemove(ObjectIndex-1);
		//if(ObjectIndex > Object::Objectlist[LoadShape]->DrawIndex.size() - 1)
		//ObjectIndex -= 1;
	}
	
	X = x;
	Y = y;
	Z = z;

	W = w;
	H = h;
	D = d;

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	FPS = 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate;
	ImGui::End();
	
	//ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::PopStyleColor(1);

}

void MyGui::MakeViewport()
{

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.2f, 0.2f, 0.2f, 0.7f });
	
	ImGui::Begin("Scene Window");
	ImGui::PopStyleColor(0);
	ImGui::ShowStyleEditor();
	ImGui::End();
	//ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f });
	//ImGui::PopStyleColor(0);
}

void MyGui::RenderEnder()
{
	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void MyGui::Docking()
{
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

void MyGui::SetStyle()
{
	ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f });
#ifdef NDEBUG


	
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 12.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 12.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 12.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, 7.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
	//ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
	//ImGui::SetNextItemWidth(ImGui::GetFontSize() * 80);
	
#endif // release
	//ImGui::PopStyleColor(0);
}
