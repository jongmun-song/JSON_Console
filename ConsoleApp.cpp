#include "ConsoleApp.h"

#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

ConsoleApp::ConsoleApp(MemberRepository& repo) : repo_(repo) {}

void ConsoleApp::printMenu() const {
    std::cout << "\n========================================\n";
    std::cout << "                회원 관리\n";
    std::cout << "========================================\n";
    std::cout << "  1. Create\n";
    std::cout << "  2. 전체 목록 보기\n";
    std::cout << "  3. ID로 검색\n";
    std::cout << "  4. Update\n";
    std::cout << "  5. Delete\n";
    std::cout << "  0. 종료\n";
    std::cout << "========================================\n";
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

    std::cout << "총 " << members.size() << "명의 회원이 있습니다.\n";
    for (const Member& member : members) {
        printMember(member);
    }
}

std::optional<int> ConsoleApp::readId(const std::string& prompt) const {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cout << "입력이 취소되었습니다.\n";
        return std::nullopt;
    }

    try {
        return std::stoi(line);
    } catch (const std::exception&) {
        std::cout << "올바른 숫자를 입력해 주세요.\n";
        return std::nullopt;
    }
}

void ConsoleApp::handleReadById() {
    std::optional<int> idOpt = readId("검색할 ID: ");
    if (!idOpt.has_value()) {
        return;
    }
    int id = idOpt.value();

    std::optional<Member> found = repo_.findById(id);
    if (!found.has_value()) {
        std::cout << "해당 ID의 회원을 찾을 수 없습니다.\n";
        return;
    }

    printMember(found.value());
}

void ConsoleApp::handleUpdate() {
    std::optional<int> idOpt = readId("수정할 ID: ");
    if (!idOpt.has_value()) {
        return;
    }
    int id = idOpt.value();

    std::optional<Member> found = repo_.findById(id);
    if (!found.has_value()) {
        std::cout << "해당 ID의 회원을 찾을 수 없습니다.\n";
        return;
    }

    std::cout << "수정 대상:\n";
    printMember(found.value());

    std::cout << "수정할 필드를 선택하세요 (1: 이름, 2: 전화번호, 3: 이메일): ";
    std::string fieldLine;
    if (!std::getline(std::cin, fieldLine)) {
        std::cout << "입력이 취소되었습니다.\n";
        return;
    }

    if (fieldLine != "1" && fieldLine != "2" && fieldLine != "3") {
        std::cout << "잘못된 선택입니다.\n";
        return;
    }

    std::string newValue;
    if (fieldLine == "1") {
        // 이름은 필수 항목이다. 빈 값이 입력되면 오류를 안내하고 재입력을 요구한다.
        while (true) {
            std::cout << "새 이름: ";
            if (!std::getline(std::cin, newValue)) {
                std::cout << "입력이 취소되었습니다.\n";
                return;
            }
            if (!newValue.empty()) {
                break;
            }
            std::cout << "이름은 필수 항목입니다. 다시 입력해 주세요.\n";
        }
    } else if (fieldLine == "2") {
        std::cout << "새 전화번호: ";
        if (!std::getline(std::cin, newValue)) {
            std::cout << "입력이 취소되었습니다.\n";
            return;
        }
    } else {
        std::cout << "새 이메일: ";
        if (!std::getline(std::cin, newValue)) {
            std::cout << "입력이 취소되었습니다.\n";
            return;
        }
    }

    try {
        bool updated = repo_.update(id, [&](Member& member) {
            if (fieldLine == "1") {
                member.name = newValue;
            } else if (fieldLine == "2") {
                member.phone = newValue;
            } else {
                member.email = newValue;
            }
        });

        if (updated) {
            std::cout << "회원 정보가 수정되었습니다.\n";
        } else {
            std::cout << "해당 ID의 회원을 찾을 수 없습니다.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "회원 정보 수정에 실패했습니다: " << e.what() << "\n";
    }
}

void ConsoleApp::handleDelete() {
    std::optional<int> idOpt = readId("삭제할 ID: ");
    if (!idOpt.has_value()) {
        return;
    }
    int id = idOpt.value();

    std::optional<Member> found = repo_.findById(id);
    if (!found.has_value()) {
        std::cout << "해당 ID의 회원을 찾을 수 없습니다.\n";
        return;
    }

    std::cout << "삭제 대상:\n";
    printMember(found.value());

    std::cout << "정말 삭제하시겠습니까? (Y/N): ";
    std::string confirm;
    if (!std::getline(std::cin, confirm)) {
        std::cout << "입력이 취소되었습니다.\n";
        return;
    }

    if (confirm != "Y" && confirm != "y") {
        std::cout << "삭제가 취소되었습니다.\n";
        return;
    }

    try {
        bool removed = repo_.remove(id);
        if (removed) {
            std::cout << "회원이 삭제되었습니다.\n";
        } else {
            std::cout << "해당 ID의 회원을 찾을 수 없습니다.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "회원 삭제에 실패했습니다: " << e.what() << "\n";
    }
}

void ConsoleApp::printMember(const Member& member) const {
    std::cout << "----------------------------------------\n";
    std::cout << "  ID       : " << member.id << "\n";
    std::cout << "  이름     : " << member.name << "\n";
    std::cout << "  전화번호 : " << member.phone << "\n";
    std::cout << "  이메일   : " << member.email << "\n";
    std::cout << "----------------------------------------\n";
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

        if (line == "4") {
            handleUpdate();
            continue;
        }

        if (line == "5") {
            handleDelete();
            continue;
        }

        std::cout << "잘못된 선택입니다. 다시 입력해 주세요.\n";
    }
}
