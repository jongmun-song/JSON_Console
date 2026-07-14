#include "ConsoleApp.h"

#include <iostream>
#include <stdexcept>
#include <string>

ConsoleApp::ConsoleApp(MemberRepository& repo) : repo_(repo) {}

void ConsoleApp::printMenu() const {
    std::cout << "\n===== 회원 관리 =====\n";
    std::cout << "1. Create\n";
    std::cout << "0. 종료\n";
    std::cout << "선택: ";
}

void ConsoleApp::handleCreate() {
    Member input;

    // name은 필수 항목이다. 빈 값이 입력되면 오류를 안내하고 재입력을 요구한다.
    while (true) {
        std::cout << "이름: ";
        if (!std::getline(std::cin, input.name)) {
            std::cout << "입력이 취소되었습니다.\n";
            return;
        }
        if (!input.name.empty()) {
            break;
        }
        std::cout << "이름은 필수 항목입니다. 다시 입력해 주세요.\n";
    }

    std::cout << "전화번호: ";
    if (!std::getline(std::cin, input.phone)) {
        std::cout << "입력이 취소되었습니다.\n";
        return;
    }

    std::cout << "이메일: ";
    if (!std::getline(std::cin, input.email)) {
        std::cout << "입력이 취소되었습니다.\n";
        return;
    }

    try {
        Member created = repo_.create(input);
        std::cout << "회원이 생성되었습니다. (id: " << created.id
                   << ", 이름: " << created.name << ")\n";
    } catch (const std::exception& e) {
        std::cout << "회원 생성에 실패했습니다: " << e.what() << "\n";
    }
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

        if (line == "1") {
            handleCreate();
            continue;
        }

        std::cout << "잘못된 선택입니다. 다시 입력해 주세요.\n";
    }
}
