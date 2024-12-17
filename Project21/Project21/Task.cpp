// Task.cpp
#include "Task.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

Task::Task(string t, string d, string due)
    : title(t), description(d), dueDate(due), isCompleted(false), accumulatedTime(0) {}

void Task::displayTask() {
    cout << "과목: " << title << endl;
    cout << "설명: " << description << endl;
    if (isCompleted) {
        auto duration = duration_cast<seconds>(endTime - startTime).count(); //시간차이 초 단위 변환 후 .count -> 시간 차이값 가져오기
        long totalSeconds = accumulatedTime + duration;

        long hours = totalSeconds / 3600;
        long minutes = (totalSeconds % 3600) / 60;
        long seconds = totalSeconds % 60;

        cout << "소요 시간: " << hours << "시 " << minutes << "분 " << seconds << "초\n";
    }
    else {
        cout << "상태: 진행 중\n";
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
        // 작업이 진행 중인 경우, 현재 시간에서 시작 시간까지의 차이를 더한다.
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
        // 작업이 완료되지 않은 상태에서만 추가 시간이 누적됨
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
