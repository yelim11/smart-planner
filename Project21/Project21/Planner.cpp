#include "Planner.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>

Planner::Planner(string date) : currentDate(date) {}

void Planner::addTask(string title, string description) {
    Task newTask(title, description, currentDate);  // ���ο� Task ��ü ����
    tasks.push_back(newTask);  // �� �� ��Ͽ� �߰�
}


void Planner::displayAllTasks() {
    if (tasks.empty()) {
        cout << currentDate << "�� �� ���� �����ϴ�.\n";
        return;
    }
    cout << currentDate << "�� �� �� ���:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << "�� �� " << i + 1 << ":\n";
        tasks[i].displayTask();  // �� �� ���� ������ ���
        cout << endl;
    }
}


void Planner::deleteTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);  // �ش� �ε����� �� �� ����
        cout << "�� �� " << index + 1 << "�� �����Ǿ����ϴ�.\n";
    }
    else {
        cout << "��ȿ���� ���� �� �� ��ȣ�Դϴ�!\n";  // �߸��� �ε����� ��� ���� �޽��� ���
    }
}


Task& Planner::getTask(int index) {
    return tasks[index];  // ������ �ε����� Task ��ü ��ȯ
}


bool Planner::hasTasks() {
    return !tasks.empty();  // �� ���� �����ϴ��� Ȯ��
}


void Planner::saveTasksToFile() {
    string filename = "tasks_" + currentDate + ".txt";  // ���� �̸� ����
    ofstream outFile(filename);  // ���� ����
    if (!outFile) {
        cout << "���� ���� �� ������ �߻��߽��ϴ�!\n";
        return;
    }

    outFile << tasks.size() << '\n';  // �� �� ���� ����
    for (auto& task : tasks) {
        task.saveToFile(outFile);  // �� Task�� ������ ���Ͽ� ����
    }
    outFile.close();  // ���� �ݱ�
}


void Planner::loadTasksFromFile() {
    string filename = "tasks_" + currentDate + ".txt";
    ifstream inFile(filename);
    if (!inFile) {
        cout << currentDate << "�� ����� �� ���� �����ϴ�.\n";
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
