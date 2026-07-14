#pragma once

#include "MemberRepository.h"

// 메뉴 출력, 사용자 입력 처리를 담당하는 콘솔 UI 계층.
class ConsoleApp {
public:
    explicit ConsoleApp(MemberRepository& repo);

    // 메뉴 출력 -> 입력 처리 -> 종료 시까지 반복한다.
    void run();

private:
    void printMenu() const;

    MemberRepository& repo_;
};
