#pragma once

/// <summary>
/// ImGui UI window abstraction abstract class
/// </summary>
class Panel
{
protected:
	virtual void checkForInput() = 0;
};