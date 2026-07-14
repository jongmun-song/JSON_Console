# JSON 파일 저장

## 개요

메모리 상의 회원 데이터 목록을 JSON 형식으로 직렬화하여 파일에 저장하는 기능.
[nlohmann/json](https://github.com/nlohmann/json)을 사용해 직렬화하며,
Create/Update/Delete로 데이터가 변경될 때마다 호출되어 변경 사항을 영구 반영한다.

## 동작

- 회원 데이터 모델 목록을 `nlohmann::json` 배열로 직렬화한다. 모델 구조체에 정의한
  `to_json` 사용자 정의 변환 함수(또는 `NLOHMANN_DEFINE_TYPE_INTRUSIVE` 매크로)를
  활용한다.
- `nlohmann::json`의 `dump(indent)`로 보기 좋게 들여쓴 문자열을 생성한다.
- 직렬화된 내용을 `std::ofstream`으로 지정된 경로의 파일에 쓴다.
- 저장 도중 오류(디스크 쓰기 실패 등)가 발생하면 기존 파일 내용을 훼손하지 않도록,
  임시 파일에 먼저 쓴 뒤 원본 파일을 교체하는 방식을 사용한다.
- 매 CRUD 변경 동작(Create/Update/Delete) 직후 저장을 호출해 파일과 메모리 상태를
  항상 일치시킨다.

## 관련 기능

- [json-parsing](json-parsing.md): 저장된 파일을 다시 읽어올 때 사용.
- [create](create.md), [update](update.md), [delete](delete.md): 데이터 변경 후 저장을 트리거.
