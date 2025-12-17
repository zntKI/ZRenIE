#pragma once

/// <summary>
/// ImGui UI window abstraction abstract class
/// </summary>
class Panel
{
public:
	virtual void render() = 0;
	virtual void processInput() = 0;
};