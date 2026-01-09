#include "ImGuiFramebuffer.hpp"

void ImGuiFramebuffer::OnNotify(Event event)
{
	switch (event.eventType)
	{
	case EventType::ON_WINDOW_RESIZE:
	{
		unsigned int panelWidth = static_cast<unsigned int>(get<0>(event.eventData.twoValueChange));
		unsigned int panelHeight = static_cast<unsigned int>(get<1>(event.eventData.twoValueChange));

		if (!isInitialized())
		{
			Initialize(panelWidth, panelHeight);
		}
		else
		{
			Resize(panelWidth, panelHeight);
		}
		break;
	}
	default:
		break;
	}
}