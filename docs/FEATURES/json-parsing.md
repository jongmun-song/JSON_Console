# JSON 파싱

## 개요

디스크에 저장된 JSON 파일을 읽어 메모리 상의 회원 데이터 구조(모델)로 변환하는 기능.
외부 라이브러리인 [nlohmann/json](https://github.com/nlohmann/json)을 사용해 파일 내용을
파싱한다(직접 파서를 구현하지 않는다).

## 라이브러리 연동

- 헤더 온리 라이브러리인 `nlohmann/json`(`nlohmann/json.hpp`)을 사용한다.
- vcpkg 또는 NuGet으로 설치 후 `PoC.vcxproj`의 include 경로에 연결한다.
  - vcpkg 사용 시: `vcpkg install nlohmann-json` 후 `PoC.vcxproj`에 vcpkg 통합(툴셋 연결) 적용.
  - NuGet 사용 시: `nlohmann.json` 패키지를 프로젝트에 추가.
- 소스에서는 `#include <nlohmann/json.hpp>` 후 `nlohmann::json` 타입으로 JSON 값을 다룬다.

## 동작

- 지정된 경로의 JSON 파일을 `std::ifstream`으로 읽는다.
- `nlohmann::json::parse()`로 파일 스트림을 파싱하여 `nlohmann::json` 값(객체/배열)으로 변환한다.
- JSON 배열의 각 요소를 회원 데이터 모델로 매핑한다. `nlohmann::json`의
  `get<T>()` 또는 `from_json`/`to_json` 사용자 정의 변환 함수를 활용해 모델 구조체와
  상호 변환한다.
- 파일이 존재하지 않을 경우 빈 목록으로 취급한다.
- 파싱 중 문법 오류가 발생하면(`nlohmann::json::parse_error` 예외) 오류를 알리고 상위 CRUD
  동작(Create/Read/Update/Delete)을 중단시켜, 손상된 데이터로 잘못된 처리가 이어지지 않도록
  한다.

## 관련 기능

- [json-file-storage](json-file-storage.md): 파싱된 데이터를 다시 파일로 저장할 때 사용.
- [read](read.md): 파싱 결과를 목록 조회/검색에 사용.
