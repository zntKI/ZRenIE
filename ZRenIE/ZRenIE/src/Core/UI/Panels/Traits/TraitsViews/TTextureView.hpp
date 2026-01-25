#pragma once

#include <imgui.h>
#include <imfilebrowser/imfilebrowser.h>

#include <string>
#include <vector>

class TTextureView
{
public:
    TTextureView();

    bool Render(unsigned int currentTextureId, std::string& currentTextureDirectory);

private:
    ImGui::FileBrowser m_FileDialog;
};