#include "TaskManager.h"

TaskManager::TaskManager() {
  _taskCount = 0;
}

void TaskManager::addTask(VoidFunction callback, unsigned long interval) {
  if (_taskCount < MAX_TASKS) 
  {
    _tasks[_taskCount].func = callback;
    _tasks[_taskCount].interval = interval;
    _tasks[_taskCount].lastRun = 0;
    _tasks[_taskCount].active = true;
    _taskCount++;
  }
}

/**
 * @brief Main scheduler loop. Checks all tasks and runs them if due.
 */
void TaskManager::run() {
  unsigned long currentMillis = millis();
  int i;

  i = 0;
  while (i < _taskCount)
  {
    if (_tasks[i].active)
    {
      if (currentMillis - _tasks[i].lastRun >= _tasks[i].interval)
      {
        _tasks[i].lastRun = currentMillis;
        _tasks[i].func();
      }
    }
    i++;
  }
}