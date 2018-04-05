#include "DeferredTasks.h"

void DeferredTasks::addTask(std::function<void()> lambaTask)
{
	m_tasks.push_back(lambaTask);
}

void DeferredTasks::executeTasks()
{
	for (auto task : m_tasks)
		task();
	m_tasks.clear();
}
