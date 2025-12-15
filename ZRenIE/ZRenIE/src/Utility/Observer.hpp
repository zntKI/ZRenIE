#pragma once

#include "Event.hpp"

class Observer
{
public:
	virtual ~Observer() {}
	virtual void OnNotify(Event event) = 0;
};