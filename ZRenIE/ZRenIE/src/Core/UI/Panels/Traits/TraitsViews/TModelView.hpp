#pragma once

#include <imgui.h>
#include <imfilebrowser/imfilebrowser.h>

#include <string>
#include <vector>

class TModelView
{
public:
    TModelView();

    bool Render(std::string& currentModelName, std::string& currentModelDirectory);

private:
    ImGui::FileBrowser m_FileDialog;
};