#include <vector>
#include <string>
#include "Task.h"

using namespace std;

class Planner {
private:
    vector<Task> tasks;
    string currentDate;

public:
    Planner(string date);

    void addTask(string title, string description);
    void displayAllTasks();
    void deleteTask(int index);
    Task& getTask(int index);
    bool hasTasks();
    void saveTasksToFile();
    void loadTasksFromFile();

    static string getTodayDate();
    string getCurrentDate();
};
