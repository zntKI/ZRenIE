#pragma once

#include "Event.hpp"
#include "Observer.hpp"

#include <memory>
#include <vector>
#include <queue>

class Sender
{
protected:
	std::vector<std::shared_ptr<Observer>> m_Observers;

	std::queue<Event> m_eventQueue;

public:
	void AddObserver(std::shared_ptr<Observer> observer);
	//void RemoveObserver(std::shared_ptr<Observer> observer);

protected:
	void emptyQueue();
};