#include <Windows.h>

#include "ConsoleApp.h"
#include "MemberRepository.h"

int main() {
    // 콘솔 입출력을 UTF-8로 맞춰 한글이 깨지지 않도록 한다.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    MemberRepository repo("members.json");
    repo.load();

    ConsoleApp app(repo);
    app.run();

    return 0;
}
