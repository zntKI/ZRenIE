#include "TTransformView.hpp"

#include "../../../../Traits/TTransform.hpp"

#include <imgui.h>

bool TTransformView::Render(TransformProperties& localTransform)
{
    ImGui::PushItemWidth(160.0f);

    bool changed = false;

    // Position
    ImGui::Text("Position");
    ImGui::SameLine(100.0f);
    float pos[3] = { localTransform.Position.x, localTransform.Position.y, localTransform.Position.z };
    changed |= ImGui::DragFloat3("##pos", pos, 0.1f, -FLT_MAX, FLT_MAX, "%.3f");

    // Rotation (degrees)
    ImGui::Text("Rotation");
    ImGui::SameLine(100.0f);
    float rot[3] = { localTransform.Rotation.x, localTransform.Rotation.y, localTransform.Rotation.z };
    changed |= ImGui::DragFloat3("##rot", rot, 0.5f, -360.0f, 360.0f, "%.2f");

    // Scale
    ImGui::Text("Scale");
    ImGui::SameLine(100.0f);
    float scl[3] = { localTransform.Scale.x, localTransform.Scale.y, localTransform.Scale.z };
    changed |= ImGui::DragFloat3("##scl", scl, 0.01f, 0.0f, FLT_MAX, "%.3f");

    ImGui::PopItemWidth();

    // Apply changes
    if (changed)
    {
        localTransform.Position = { pos[0], pos[1], pos[2] };
        localTransform.Rotation = { rot[0], rot[1], rot[2] }; // stored as degrees
        localTransform.Scale = { scl[0], scl[1], scl[2] };
    }

    return changed;
}