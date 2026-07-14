#pragma once

#include <optional>
#include <string>

#include "MemberRepository.h"

// 메뉴 출력, 사용자 입력 처리를 담당하는 콘솔 UI 계층.
class ConsoleApp {
public:
    explicit ConsoleApp(MemberRepository& repo);

    // 메뉴 출력 -> 입력 처리 -> 종료 시까지 반복한다.
    void run();

private:
    void printMenu() const;
    void handleCreate();
    void handleReadAll();
    void handleReadById();
    void handleUpdate();
    void handleDelete();
    void printMember(const Member& member) const;

    // prompt를 출력하고 한 줄을 읽어 정수 ID로 파싱한다.
    // 입력 취소(EOF) 또는 숫자 변환 실패 시 안내 메시지를 출력하고 std::nullopt을 반환한다.
    std::optional<int> readId(const std::string& prompt) const;

    MemberRepository& repo_;
};
