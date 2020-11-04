#pragma once

#include <string>
#include <vector>

class Event {

public:

	typedef void (*BlankVoidFunc)(void);

public:

	BlankVoidFunc funcPtr;
	std::string name;

public:

	Event();
	Event(void* func, const std::string& funcName);


	void bind(void* func, const std::string& funcName);
	void invoke();
	template<typename ReturnType, typename ... Args > ReturnType invoke(Args... arg)
	{
		//std::tuple<Args...> param(arg...);
		//std::tuple_element<0, Args...> a = std::get<0, Args...>(param);
		//int paramCount = std::tuple_size<std::tuple<Args...>>::value;
		//printf("Type = %s, param = %i\n", typeid(param).name(), paramCount);
		//int h = 1;
		//const size_t i = const_cast<const int&>(*&h);
		//printf("%i\n", i);
		//printf("first : %i\n", std::get<i, Args...>(std::tuple<Args...>(arg...)));

		return ((ReturnType(*)(Args...))funcPtr)(arg...);
	}

};


class EventHandle {

private:

	static EventHandle instance;

public:

	std::vector<Event> event;

public:

	static EventHandle& getInstance();

public:

	EventHandle();
	EventHandle(const std::vector<Event>& event);


	void bindEvent(void* func, const std::string& functionName);
	template<typename ReturnType, typename ... Args > ReturnType invokeEvent(const std::string& functionName, Args... arg)
	{
		for (int i = 0; i < event.size(); i++)
		{
			if (event[i].name.compare(functionName) == 0)
			{
				return event[i].invoke<ReturnType, Args...>(arg...);
			}

		}

		printf("Invalid invoke \"%s\" event!   [ERROR Message : Event Not Found]\n", functionName.c_str());
		return ReturnType();

	}
	void invokeEvent(const std::string& functionName);
	std::vector<Event>::iterator findEvent(std::string functionName);
	void freeEvent(const std::string& functionName);

};

// \  /
//  \/  Tips
/* 
EventHandle event;

static float getNumber(int i, float j, bool g) 
{ 
	printf("send : %i, %f, %s\n", i, j, g ? "true": "false"); 
	return i + 5; 
}
static void byeWorld() 
{ 
	printf("Bye World!\n");
}
static void sleep()
{
	printf("I can't now!\n");
}

// first param is the function which I call it [function pointer], second param is the string use for later find the event which I call it [keyword name].
event.bindEvent(getNumber, "getNumber");
event.bindEvent(byeWorld, "byeWorld");
event.bindEvent(sleep, "You need it");

// use the [keyword name] to erase the event in EventHandle.
event.freeEvent("You need it");

// invokeEvent<ReturnType, ...>, the first Type is always the return type of the function, 
// the second or continue type is the parameter type of the function, must follow the order.
// the first param is use the [keyword name] to find the event and invoke it,
// the second or continue param is what the event function parameter you want to pass, must follow the order parameter of the function.
printf("get getNumber : %f\n", event.invokeEvent<float, int, float, bool>("getNumber", 1, 2.0f, true));

printf("get getNumber : %f\n", ((float (*)(int, float, bool))event.findEvent("getNumber")->funcPtr)(5, 5.0f, true));

// only when the function you bind are (void return type) and (null parameter type) then just can use like this.
event.invokeEvent("byeWorld");

// but you also can use like this.
event.invokeEvent<void>("sleep");

*/