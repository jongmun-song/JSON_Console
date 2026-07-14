#pragma once

#include <string>

#include <nlohmann/json.hpp>

// 회원 데이터 모델.
struct Member {
    int id = 0;
    std::string name;
    std::string phone;
    std::string email;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Member, id, name, phone, email)
};
