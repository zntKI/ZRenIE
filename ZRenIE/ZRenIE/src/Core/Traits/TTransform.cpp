#include "TTransform.hpp"

TTransform::TTransform()
	: m_Position(0.0f, 0.0f, 0.0f),
	  m_Rotation(0.0f, 0.0f, 0.0f),
	  m_Scale(1.0f, 1.0f, 1.0f)
{
}

void TTransform::Update()
{
}