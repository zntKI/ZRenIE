//#include "StageManager.hpp"
//#include "../Utility/Utils.hpp"
//
//StageManager::StageManager()
//{
//	Utils::logMessage("Initializing Stage...");
//	//m_CurrentStage = new Stage();
//	m_Stages.push(m_CurrentStage);
//}
//
//StageManager::~StageManager()
//{
//	clearStages();
//}
//
//void StageManager::Update()
//{
//	m_CurrentStage->Update();
//}
//
//void StageManager::Render()
//{
//	m_CurrentStage->Render();
//}
//
//void StageManager::clearStages()
//{
//	while (!m_Stages.empty())
//	{
//		delete m_Stages.top();
//		m_Stages.pop();
//	}
//	m_CurrentStage = nullptr;
//}