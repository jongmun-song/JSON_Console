#include "ConsoleApp.h"

#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

ConsoleApp::ConsoleApp(MemberRepository& repo) : repo_(repo) {}

void ConsoleApp::printMenu() const {
    std::cout << "\n===== 회원 관리 =====\n";
    std::cout << "1. Create\n";
    std::cout << "2. 전체 목록 보기\n";
    std::cout << "3. ID로 검색\n";
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

void ConsoleApp::handleReadAll() {
    const std::vector<Member>& members = repo_.all();

    if (members.empty()) {
        std::cout << "등록된 회원이 없습니다.\n";
        return;
    }

    for (const Member& member : members) {
        printMember(member);
    }
}

void ConsoleApp::handleReadById() {
    std::cout << "검색할 ID: ";
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cout << "입력이 취소되었습니다.\n";
        return;
    }

    int id = 0;
    try {
        id = std::stoi(line);
    } catch (const std::exception&) {
        std::cout << "올바른 숫자를 입력해 주세요.\n";
        return;
    }

    std::optional<Member> found = repo_.findById(id);
    if (!found.has_value()) {
        std::cout << "해당 ID의 회원을 찾을 수 없습니다.\n";
        return;
    }

    printMember(found.value());
}

void ConsoleApp::printMember(const Member& member) const {
    std::cout << "id: " << member.id
               << ", 이름: " << member.name
               << ", 전화번호: " << member.phone
               << ", 이메일: " << member.email << "\n";
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

        if (line == "2") {
            handleReadAll();
            continue;
        }

        if (line == "3") {
            handleReadById();
            continue;
        }

        std::cout << "잘못된 선택입니다. 다시 입력해 주세요.\n";
    }
}
