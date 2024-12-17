// Task.cpp
#include "Task.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

Task::Task(string t, string d, string due)
    : title(t), description(d), dueDate(due), isCompleted(false), accumulatedTime(0) {}

void Task::displayTask() {
    cout << "����: " << title << endl;
    cout << "����: " << description << endl;
    if (isCompleted) {
        auto duration = duration_cast<seconds>(endTime - startTime).count(); //�ð����� �� ���� ��ȯ �� .count -> �ð� ���̰� ��������
        long totalSeconds = accumulatedTime + duration;

        long hours = totalSeconds / 3600;
        long minutes = (totalSeconds % 3600) / 60;
        long seconds = totalSeconds % 60;

        cout << "�ҿ� �ð�: " << hours << "�� " << minutes << "�� " << seconds << "��\n";
    }
    else {
        cout << "����: ���� ��\n";
    }
}

string Task::getTitle() { return title; }
string Task::getDescription() { return description; }
string Task::getDueDate() { return dueDate; }
bool Task::getStatus() { return isCompleted; }

void Task::startTask() {
    if (!isCompleted) {
        startTime = system_clock::now();
    }
}

void Task::completeTask() {
    endTime = system_clock::now();
    isCompleted = true;
    accumulatedTime += duration_cast<minutes>(endTime - startTime).count();
}

long Task::getTimeSpent() {
    if (isCompleted) {
        auto duration = duration_cast<minutes>(endTime - startTime);
        return accumulatedTime + duration.count();
    }
    else {
        // �۾��� ���� ���� ���, ���� �ð����� ���� �ð������� ���̸� ���Ѵ�.
        auto now = system_clock::now();
        auto duration = duration_cast<minutes>(now - startTime);
        return accumulatedTime + duration.count();
    }
}

void Task::resumeTask() {
    if (!isCompleted) {
        startTime = system_clock::now();
    }
}

void Task::addTime(long minutes) {
    if (!isCompleted) {
        // �۾��� �Ϸ���� ���� ���¿����� �߰� �ð��� ������
        accumulatedTime += minutes;
    }
}

void Task::saveToFile(ofstream& outFile) {
    outFile << title << '\n' << description << '\n' << dueDate << '\n'
        << isCompleted << '\n' << accumulatedTime << '\n';
}

void Task::loadFromFile(ifstream& inFile) {
    getline(inFile, title);
    getline(inFile, description);
    getline(inFile, dueDate);
    inFile >> isCompleted;
    inFile >> accumulatedTime;
    inFile.ignore();
}
