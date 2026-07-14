#include "ConsoleApp.h"

#include <iostream>
#include <limits>
#include <string>

ConsoleApp::ConsoleApp(MemberRepository& repo) : repo_(repo) {}

void ConsoleApp::printMenu() const {
    std::cout << "\n===== 회원 관리 =====\n";
    std::cout << "0. 종료\n";
    std::cout << "선택: ";
}

void ConsoleApp::run() {
    while (true) {
        printMenu();

        std::string line;
        if (!std::getline(std::cin, line)) {
            break;
        }

        if (line == "0") {
            std::cout << "프로그램을 종료합니다.\n";
            break;
        }

        std::cout << "잘못된 선택입니다. 다시 입력해 주세요.\n";
    }
}
