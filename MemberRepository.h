#pragma once

#include <filesystem>
#include <vector>

#include "Member.h"

// JSON 파일을 통해 회원 데이터를 읽고 쓰는 리포지토리 계층.
class MemberRepository {
public:
    explicit MemberRepository(std::filesystem::path jsonPath);

    // 파일 -> memberList_. 파일이 없으면 빈 목록으로 둔다.
    // 파싱 오류(nlohmann::json::parse_error)는 예외를 상위로 전달한다.
    void load();

    // memberList_ -> 파일. 임시 파일에 먼저 쓰고 원본으로 교체한다.
    void save() const;

    const std::vector<Member>& all() const;

private:
    std::filesystem::path jsonPath_;
    std::vector<Member> memberList_;
};
