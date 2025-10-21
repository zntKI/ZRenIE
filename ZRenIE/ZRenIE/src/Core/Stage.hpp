#pragma once

// Abstract representation of a game stage or level/menu
// TODO: Think about applying the correct design pattern here (TypeObject/Prototype/Subclass Sandbox)
class Stage
{
public:
	void Update();

private:
	// World* m_World; TODO: implement World class? Handles all game objects
};