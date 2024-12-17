#include <iostream>
#include <string>
#include <conio.h> // _getch�� ����ϱ� ���� ��� �߰�
#include "Planner.h"

using namespace std;

int navigateMenu(const vector<string>& options, Planner& myPlanner) {
    int currentSelection = 0;
    char key;

    while (true) {
        system("cls");  // ȭ���� �����
        myPlanner.displayAllTasks();  // �� �� ����� ���

        cout << "\n����Ʈ �÷��� �޴�:\n";
        for (size_t i = 0; i < options.size(); ++i) {  // �޴� �ɼ� ���
            if (i == currentSelection) {
                cout << " > " << options[i] << " < \n";  // ���� ���õ� �׸� ����
            }
            else {
                cout << "   " << options[i] << "\n";
            }
        }

        key = _getch();  // Ű �Է��� ����
        if (key == '\r') return currentSelection;  // Enter Ű�� ������ ���õ� �׸� ��ȯ
        else if (key == 72) currentSelection = (currentSelection - 1 + options.size()) % options.size();  // �� ����Ű
        else if (key == 80) currentSelection = (currentSelection + 1) % options.size();  // �Ʒ� ����Ű
    }
}


int main() {
    string todayDate;
    cout << "���� ��¥�� �Է��ϼ��� (YYYY-MM-DD) �Ǵ� Enter�� ���� ���� ��¥�� ���: ";
    getline(cin, todayDate);

    if (todayDate.empty()) {
        todayDate = Planner::getTodayDate();
    }

    Planner myPlanner(todayDate);
    myPlanner.loadTasksFromFile();

    vector<string> menuOptions = { "�� �� �߰�", "�� �� ����", "�� �� ����/�簳", "����" };

    Task* selectedTask = nullptr;  // Task ��ü�� ����ų ������ ����

    while (true) {
        int choice = navigateMenu(menuOptions, myPlanner);
        string title;
        string description;

        switch (choice) {
        case 0:  // �� �� �߰�
            cout << "�� �� ���� �Է�: ";
            getline(cin, title);  // Use getline for string input
            cout << "�� �� ���� �Է�: ";
            getline(cin, description);  // Use getline for string input
            myPlanner.addTask(title, description);
            break;
        case 1:  // �� �� ����
            size_t indexToDelete;
            cout << "������ �� �� ��ȣ �Է� (1���� ����): ";
            cin >> indexToDelete;
            cin.ignore();  // Ignore the newline character left by cin
            myPlanner.deleteTask(static_cast<int>(indexToDelete) - 1);
            break;
        case 2:  // �� �� ����/�簳
            if (!myPlanner.hasTasks()) {
                cout << "�����ϰų� �簳�� �� ���� �����ϴ�!" << endl;
                cin.get();  // Wait for user input instead of using system("pause")
                break;
            }

            size_t indexToStart;
            cout << "����/�簳�� �� �� ��ȣ �Է� (1���� ����): ";
            cin >> indexToStart;
            cin.ignore();  // Ignore the newline character left by cin

            // 'selectedTask'�� case 2 �������� ����
            selectedTask = &myPlanner.getTask(static_cast<int>(indexToStart) - 1);  // �ּ� �Ҵ�

            
                selectedTask->startTask();
                cout << "�� ���� ���۵Ǿ����ϴ�! �Ϸ� �� Enter Ű�� ��������.\n";
                cin.get();
                selectedTask->completeTask();
                cout << "�� ���� �Ϸ�Ǿ����ϴ�!\n";
        
            break;
        case 3:  // ����
            myPlanner.saveTasksToFile();
            cout << "�÷��ʸ� �����մϴ�..." << endl;
            return 0;  // Exit the program
        default:
            cout << "�߸��� �����Դϴ�! �ٽ� �õ��ϼ���.\n";
            break;
        }
    }

    return 0;
}
