#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <Arduino.h>

// Function pointer type for tasks
typedef void (*VoidFunction)();

#define MAX_TASKS 10

/**
 * @brief Structure representing a single task.
 */
struct Task {
  VoidFunction func;
  unsigned long interval;
  unsigned long lastRun;
  bool active;
};

/**
 * @brief A cooperative scheduler to run multiple functions periodically.
 */
class TaskManager
{
  private:
    Task _tasks[MAX_TASKS];
    int _taskCount;

  public:
    TaskManager();

    /**
     * @brief Adds a function to the scheduler.
     * @param callback The void function to call.
     * @param interval How often to call it (in milliseconds).
     */
    void addTask(VoidFunction callback, unsigned long interval);

    /**
     * @brief Main loop runner. Must be called inside loop().
     */
    void run();
};

#endif