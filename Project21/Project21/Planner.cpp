#include "Planner.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>

Planner::Planner(string date) : currentDate(date) {}

void Planner::addTask(string title, string description) {
    Task newTask(title, description, currentDate);  // 새로운 Task 객체 생성
    tasks.push_back(newTask);  // 할 일 목록에 추가
}


void Planner::displayAllTasks() {
    if (tasks.empty()) {
        cout << currentDate << "에 할 일이 없습니다.\n";
        return;
    }
    cout << currentDate << "의 할 일 목록:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << "할 일 " << i + 1 << ":\n";
        tasks[i].displayTask();  // 각 할 일의 정보를 출력
        cout << endl;
    }
}


void Planner::deleteTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);  // 해당 인덱스의 할 일 삭제
        cout << "할 일 " << index + 1 << "이 삭제되었습니다.\n";
    }
    else {
        cout << "유효하지 않은 할 일 번호입니다!\n";  // 잘못된 인덱스일 경우 오류 메시지 출력
    }
}


Task& Planner::getTask(int index) {
    return tasks[index];  // 지정된 인덱스의 Task 객체 반환
}


bool Planner::hasTasks() {
    return !tasks.empty();  // 할 일이 존재하는지 확인
}


void Planner::saveTasksToFile() {
    string filename = "tasks_" + currentDate + ".txt";  // 파일 이름 생성
    ofstream outFile(filename);  // 파일 열기
    if (!outFile) {
        cout << "파일 저장 중 오류가 발생했습니다!\n";
        return;
    }

    outFile << tasks.size() << '\n';  // 할 일 개수 저장
    for (auto& task : tasks) {
        task.saveToFile(outFile);  // 각 Task의 정보를 파일에 저장
    }
    outFile.close();  // 파일 닫기
}


void Planner::loadTasksFromFile() {
    string filename = "tasks_" + currentDate + ".txt";
    ifstream inFile(filename);
    if (!inFile) {
        cout << currentDate << "에 저장된 할 일이 없습니다.\n";
        return;
    }

    size_t taskCount;
    inFile >> taskCount;
    inFile.ignore();

    for (size_t i = 0; i < taskCount; ++i) {
        Task newTask("", "", "");
        newTask.loadFromFile(inFile);
        tasks.push_back(newTask);
    }
    inFile.close();
}

string Planner::getTodayDate() {
    auto now = system_clock::now();
    time_t t = system_clock::to_time_t(now);
    tm tmStruct;
    localtime_s(&tmStruct, &t);

    stringstream ss;
    ss << tmStruct.tm_year + 1900 << "-" << tmStruct.tm_mon + 1 << "-" << tmStruct.tm_mday;
    return ss.str();
}

string Planner::getCurrentDate() {
    return currentDate;
}
