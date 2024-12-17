// Task.h
#pragma once
#include <string>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

class Task {
private:
    string title;
    string description;
    string dueDate;
    bool isCompleted;
    long accumulatedTime; // 시간을 누적할 변수
    system_clock::time_point startTime;
    system_clock::time_point endTime;

public:
    Task(string t, string d, string due);
    
    void displayTask();
    string getTitle();
    string getDescription();
    string getDueDate();
    bool getStatus();
    
    void startTask();
    void completeTask();
    long getTimeSpent();
    void resumeTask();
    void addTime(long minutes); // 추가된 시간 더하기 기능 선언
    
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
};
