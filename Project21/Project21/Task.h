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
    long accumulatedTime; // �ð��� ������ ����
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
    void addTime(long minutes); // �߰��� �ð� ���ϱ� ��� ����
    
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
};
