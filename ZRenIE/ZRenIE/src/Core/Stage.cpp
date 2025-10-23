#include "Stage.hpp"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Update()
{
	m_World.Update();
}

void Stage::Render()
{
	m_Renderer.Render(&m_World);
}