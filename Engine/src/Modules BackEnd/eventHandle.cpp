#include "eventHandle.h"

Event::Event()
{
	funcPtr = NULL;
	name = "";

}
Event::Event(void* func, const std::string& funcName)
{
	this->bind(func, funcName);

}

void Event::bind(void* func, const std::string& funcName)
{
	funcPtr = static_cast<BlankVoidFunc>(func);
	name = funcName;

}
void Event::invoke()
{
	((void(*)())funcPtr)();

}


// ------------------- |*     Event Handle     *| -------------------

EventHandle::EventHandle()
{
	this->event.clear();

}
EventHandle::EventHandle(const std::vector<Event>& event)
{
	this->event.clear();
	this->event = event;

}


void EventHandle::bindEvent(void* func, const std::string& functionName)
{
	for (int i = 0; i < event.size(); i++)
	{
		if (event[0].name.compare(functionName) == 0)
		{
			printf("Failed to bind an event \"%s\", because the name have be used!\n", functionName.c_str());
			return;
		}

	}

	Event newEvent(func, functionName);
	event.push_back(newEvent);

}
void EventHandle::invokeEvent(const std::string& functionName)
{
	for (int i = 0; i < event.size(); i++)
	{
		if (event[i].name.compare(functionName) == 0)
		{
			event[i].invoke();
			return;
		}

	}

	printf("Invalid invoke \"%s\" event - [ERROR Message : event not found!]\n", functionName.c_str());

}
std::vector<Event>::iterator EventHandle::findEvent(std::string functionName)
{
	for (std::vector<Event>::iterator i = event.begin(); i != event.end(); i++)
	{
		Event& temp = *i;
		if (i->name.compare(functionName) == 0)
		{
			return i;
		}
	}

	printf("The \"%s\" event not found!\n", functionName.c_str());
	return event.end();

}
void EventHandle::freeEvent(const std::string& functionName)
{
	for (std::vector<Event>::iterator i = event.begin(); i != event.end(); i++)
	{
		Event& temp = *i;
		if (i->name.compare(functionName) == 0)
		{
			event.erase(i);
			printf("Completed free the \"%s\" event.\n", functionName.c_str());
			return;
		}
	}

	printf("Failed to free the \"%s\" event!   [ERROR Message : Event Not Found]\n", functionName.c_str());

}