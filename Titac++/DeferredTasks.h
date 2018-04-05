#pragma once

#include <functional>
#include <vector>

class DeferredTasks
{
public:
	void addTask(std::function<void()> lambaTask);
	void executeTasks();

private:
	std::vector<std::function<void()>> m_tasks;
};