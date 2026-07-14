#include "MemberRepository.h"

#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

MemberRepository::MemberRepository(std::filesystem::path jsonPath)
    : jsonPath_(std::move(jsonPath)) {}

void MemberRepository::load() {
    memberList_.clear();

    if (!std::filesystem::exists(jsonPath_)) {
        return;
    }

    std::ifstream input(jsonPath_);
    if (!input.is_open()) {
        return;
    }

    // 파싱 오류(nlohmann::json::parse_error)는 상위로 전달한다.
    nlohmann::json root = nlohmann::json::parse(input);
    memberList_ = root.get<std::vector<Member>>();
}

void MemberRepository::save() const {
    nlohmann::json root = memberList_;

    std::filesystem::path tempPath = jsonPath_;
    tempPath += ".tmp";

    {
        std::ofstream output(tempPath, std::ios::trunc);
        if (!output.is_open()) {
            throw std::runtime_error("Failed to open temporary file for writing: " + tempPath.string());
        }
        output << root.dump(4);
    }

    std::filesystem::rename(tempPath, jsonPath_);
}

const std::vector<Member>& MemberRepository::all() const {
    return memberList_;
}

int MemberRepository::nextId() const {
    int maxId = 0;
    for (const Member& member : memberList_) {
        if (member.id > maxId) {
            maxId = member.id;
        }
    }
    return maxId + 1;
}

Member MemberRepository::create(const Member& input) {
    if (input.name.empty()) {
        throw std::invalid_argument("Member name must not be empty.");
    }

    Member created = input;
    created.id = nextId();

    memberList_.push_back(created);

    try {
        save();
    } catch (...) {
        memberList_.pop_back();
        throw;
    }

    return created;
}
