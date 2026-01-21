#include "UIContext.hpp"

#include "../Framebuffers/Framebuffer.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <cassert>

bool UIContext::s_isInstantiated = false;

UIContext::UIContext()
	: m_GLFWWindow(nullptr),
	m_StagePanel(nullptr), m_HierarchyPanel(nullptr)
{
	assert(!s_isInstantiated);
	s_isInstantiated = true;
}

void UIContext::InitUIContext(std::shared_ptr<Window> GLFWWindow)
{
	m_GLFWWindow = GLFWWindow;

	m_StagePanel = std::make_unique<StagePanel>(m_GLFWWindow);
	m_HierarchyPanel = std::make_unique<HierarchyPanel>();

	initImGui();
}

void UIContext::initImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_GLFWWindow->GetWindowPtr(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
}

UIContext::~UIContext()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	s_isInstantiated = false;
}

void UIContext::PreRenderUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::Begin("DockSpaceRoot", nullptr,
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus
	);

	ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
	ImGui::DockSpace(dockspace_id);

	ImGui::End();
}

void UIContext::RenderStagePanel()
{
	m_StagePanel->Render();
}

void UIContext::RenderHierarchyPanel()
{
	m_HierarchyPanel->Render();
}

void UIContext::PostRenderUI()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIContext::ProcessInput()
{
	m_StagePanel->ProcessInput();

}

void UIContext::AddObserverToStagePanel(std::shared_ptr<Observer> observer)
{
	if (auto framebuffer = std::dynamic_pointer_cast<Framebuffer>(observer);
		framebuffer != nullptr)
	{
		m_StagePanel->AssignFramebuffer(framebuffer);
	}
	m_StagePanel->AddObserver(observer);
}

void UIContext::AssignWorldToHierarchyPanel(std::shared_ptr<World> worldPtr)
{
	m_HierarchyPanel->AssignWorldPtr(worldPtr);
}