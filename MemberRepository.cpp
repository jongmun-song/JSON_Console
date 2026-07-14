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
