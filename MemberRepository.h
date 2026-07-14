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

    // 신규 회원을 생성한다.
    // 1. nextId()로 고유 id를 부여한다(입력값의 id는 무시).
    // 2. 필수 필드(name)가 비어 있으면 std::invalid_argument를 던진다.
    // 3. memberList_에 추가한다.
    // 4. save()를 호출해 JSON 파일에 반영한다.
    // 반환값: 생성된 Member(부여된 id 포함)
    Member create(const Member& input);

private:
    int nextId() const;   // memberList_ 내 최댓값 id + 1 (없으면 1)

    std::filesystem::path jsonPath_;
    std::vector<Member> memberList_;
};
