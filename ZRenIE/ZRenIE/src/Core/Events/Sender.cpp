#include "Sender.hpp"

void Sender::AddObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.push_back(observer);
}

void Sender::emptyQueue()
{
	while (!s_eventQueue.empty())
	{
		for (auto& observer : m_Observers)
		{
			observer->OnNotify(s_eventQueue.front());
		}
		s_eventQueue.pop();
	}
}