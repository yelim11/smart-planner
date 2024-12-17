#include <iostream>
#include <string>
#include <conio.h> // _getch를 사용하기 위한 헤더 추가
#include "Planner.h"

using namespace std;

int navigateMenu(const vector<string>& options, Planner& myPlanner) {
    int currentSelection = 0;
    char key;

    while (true) {
        system("cls");  // 화면을 지우고
        myPlanner.displayAllTasks();  // 할 일 목록을 출력

        cout << "\n스마트 플래너 메뉴:\n";
        for (size_t i = 0; i < options.size(); ++i) {  // 메뉴 옵션 출력
            if (i == currentSelection) {
                cout << " > " << options[i] << " < \n";  // 현재 선택된 항목 강조
            }
            else {
                cout << "   " << options[i] << "\n";
            }
        }

        key = _getch();  // 키 입력을 받음
        if (key == '\r') return currentSelection;  // Enter 키를 누르면 선택된 항목 반환
        else if (key == 72) currentSelection = (currentSelection - 1 + options.size()) % options.size();  // 위 방향키
        else if (key == 80) currentSelection = (currentSelection + 1) % options.size();  // 아래 방향키
    }
}


int main() {
    string todayDate;
    cout << "오늘 날짜를 입력하세요 (YYYY-MM-DD) 또는 Enter를 눌러 오늘 날짜를 사용: ";
    getline(cin, todayDate);

    if (todayDate.empty()) {
        todayDate = Planner::getTodayDate();
    }

    Planner myPlanner(todayDate);
    myPlanner.loadTasksFromFile();

    vector<string> menuOptions = { "할 일 추가", "할 일 삭제", "할 일 시작/재개", "종료" };

    Task* selectedTask = nullptr;  // Task 객체를 가리킬 포인터 선언

    while (true) {
        int choice = navigateMenu(menuOptions, myPlanner);
        string title;
        string description;

        switch (choice) {
        case 0:  // 할 일 추가
            cout << "할 일 제목 입력: ";
            getline(cin, title);  // Use getline for string input
            cout << "할 일 설명 입력: ";
            getline(cin, description);  // Use getline for string input
            myPlanner.addTask(title, description);
            break;
        case 1:  // 할 일 삭제
            size_t indexToDelete;
            cout << "삭제할 할 일 번호 입력 (1부터 시작): ";
            cin >> indexToDelete;
            cin.ignore();  // Ignore the newline character left by cin
            myPlanner.deleteTask(static_cast<int>(indexToDelete) - 1);
            break;
        case 2:  // 할 일 시작/재개
            if (!myPlanner.hasTasks()) {
                cout << "시작하거나 재개할 할 일이 없습니다!" << endl;
                cin.get();  // Wait for user input instead of using system("pause")
                break;
            }

            size_t indexToStart;
            cout << "시작/재개할 할 일 번호 입력 (1부터 시작): ";
            cin >> indexToStart;
            cin.ignore();  // Ignore the newline character left by cin

            // 'selectedTask'를 case 2 내에서만 선언
            selectedTask = &myPlanner.getTask(static_cast<int>(indexToStart) - 1);  // 주소 할당

            
                selectedTask->startTask();
                cout << "할 일이 시작되었습니다! 완료 시 Enter 키를 누르세요.\n";
                cin.get();
                selectedTask->completeTask();
                cout << "할 일이 완료되었습니다!\n";
        
            break;
        case 3:  // 종료
            myPlanner.saveTasksToFile();
            cout << "플래너를 종료합니다..." << endl;
            return 0;  // Exit the program
        default:
            cout << "잘못된 선택입니다! 다시 시도하세요.\n";
            break;
        }
    }

    return 0;
}
