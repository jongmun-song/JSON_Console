# CLAUDE.md

이 파일은 Claude Code(claude.ai/code)가 이 저장소에서 작업할 때 참고할 가이드를 제공한다.

## 프로젝트 개요

`PoC`는 회원 정보에 대한 CRUD를 수행하는 Windows 콘솔 애플리케이션(C++20)이며,
데이터베이스 없이 JSON 파일(또는 일반 파일)을 영구 저장소로 사용한다.
현재는 순수 MSBuild 스켈레톤 상태로, `main.cpp`는 비어 있고 소스 구조가 아직
존재하지 않는다. 아래 아키텍처 항목은 의도된 설계 방향이며, 실제 모듈이
추가되면 함께 갱신해야 한다.

## 빌드

CMake가 아닌 Visual Studio / MSBuild C++ 프로젝트이다 — `CMakeLists.txt`는 없다.

- 솔루션 파일: `PoC.slnx`, 프로젝트 파일: `PoC.vcxproj`
- 플랫폼 툴셋: `v145`, C++ 표준: `stdcpp20`, 문자 집합: Unicode
- 구성: `Debug`/`Release` x `Win32`/`x64`

Visual Studio Developer Command Prompt / PowerShell에서 `msbuild`가 PATH에
등록된 상태로 빌드한다:

```powershell
msbuild PoC.slnx /p:Configuration=Debug /p:Platform=x64
msbuild PoC.slnx /p:Configuration=Release /p:Platform=x64
```

또는 `PoC.slnx`를 Visual Studio에서 열어 F5 / Ctrl+F5로 빌드·실행한다.

아직 테스트 프로젝트나 테스트 러너가 구성되어 있지 않고, 린터 설정도 없다
(`.clang-format`, `.clang-tidy`, EditorConfig 없음).

## 아키텍처 노트

- `_CONSOLE` 서브시스템의 `Application`을 타깃으로 하므로(`PoC.vcxproj` 참고),
  진입점은 `main.cpp`의 표준 `main()`이며 GUI 프레임워크는 사용하지 않는다.
- 영속화 방식이 DB가 아닌 JSON/파일 기반이므로, 최종적으로는 다음과 같이
  구조를 분리할 것을 예상한다: (1) 회원 데이터 모델/구조체, (2) JSON 파일을
  읽고 쓰는 리포지토리/저장소 계층, (3) CRUD 동작을 이끄는 콘솔 UI/메뉴 루프.
  이 PoC의 목적 자체가 이러한 계층 분리를 검증하는 것이므로, 하나의 파일에
  몰아넣지 말고 별도의 translation unit으로 유지한다.
- JSON 파싱/직렬화는 [nlohmann/json](https://github.com/nlohmann/json)을 사용하기로
  결정되어 있다(자체 파서를 구현하지 않는다). 프로젝트에는 아직 라이브러리가
  포함/참조되어 있지 않으므로, 이 프로젝트는 vcpkg나 CMake 패키지 관리를 사용하지
  않는 만큼 vcpkg 통합 또는 NuGet 패키지로 설치 후 `PoC.vcxproj`에 연결해야 한다.
  자세한 사용 방식은 `docs/FEATURES/json-parsing.md`, `docs/FEATURES/json-file-storage.md`
  참고.

## 문서 안내

- `docs/pre.md`: 기능 요구사항 원본.
- `docs/FEATURES/`: 요구사항별(Create/Read/Update/Delete, JSON 파싱/저장) 상세 명세.
- `docs/PLAN.md`: phase별 목표를 세운 계획 문서. 각 phase는 빌드·실행 가능한
  콘솔 애플리케이션을 산출물로 남긴다.
- `docs/design/`: phase별 설계 문서. 클래스/모듈 구조(`Member`, `MemberRepository`,
  `ConsoleApp`)와 각 phase에서 추가되는 인터페이스를 구체적으로 정의한다.
  - [`phase0-foundation.md`](docs/design/phase0-foundation.md) — 뼈대 + JSON 라이브러리 연동
  - [`phase1-create.md`](docs/design/phase1-create.md) — Create
  - [`phase2-read.md`](docs/design/phase2-read.md) — Read
  - [`phase3-update.md`](docs/design/phase3-update.md) — Update
  - [`phase4-delete.md`](docs/design/phase4-delete.md) — Delete
- `.claude/agents/`: manager(총감독)/developer/reviewer/tester subagent 정의. phase별
  구현은 이 파이프라인을 통해 진행한다.

## 보안 주의사항

이 저장소의 `.mcp.json`에는 현재 평문 GitHub Personal Access Token이 들어 있다.
해당 토큰은 폐기(rotate)하고 환경 변수로 옮겨야 하며, 앞으로도 추적 대상 파일에
비밀 정보를 추가하지 않는다.
