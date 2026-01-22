#pragma once

struct TransformProperties;

class TTransformView
{
public:
	/// <summary>
	/// Render Transform properties through ImGui UI
	/// </summary>
	/// <param name="localTransform">Reference to Transform's local transform properties
	/// member variable</param>
	/// <returns>true if changes occurred</returns>
	bool Render(TransformProperties& localTransform);
};