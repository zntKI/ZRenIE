#include "Sender.hpp"

void Sender::AddObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.push_back(observer);
}

void Sender::emptyQueue()
{
	while (!m_eventQueue.empty())
	{
		for (auto& observer : m_Observers)
		{
			observer->OnNotify(m_eventQueue.front());
		}
		m_eventQueue.pop();
	}
}