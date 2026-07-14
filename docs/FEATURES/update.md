# Update

## 개요

기존 회원 데이터를 선택하여 특정 필드를 수정하는 기능.

## 동작

- 사용자로부터 수정할 대상의 ID(또는 키 값)를 입력받아 [read](read.md) 검색 기능으로 대상을 찾는다.
- 대상이 존재하지 않으면 수정 불가를 알리고 종료한다.
- 대상이 존재하면 수정할 필드와 새 값을 입력받는다.
- 새 값에 대해 형식/필수 항목 검증을 수행한다(Create와 동일한 검증 규칙 적용).
- 검증을 통과하면 메모리 상의 해당 데이터(회원 모델 구조체)의 필드를 갱신한다.
  모델은 [nlohmann/json](json-file-storage.md)의 `to_json`/`from_json` 변환 함수를
  통해 언제든 JSON으로 직렬화 가능한 상태를 유지한다.
- [json-file-storage](json-file-storage.md)를 호출해 변경된 목록을 JSON 파일에 저장한다.

## 관련 기능

- [read](read.md): 수정 대상을 찾을 때 사용.
- [json-file-storage](json-file-storage.md): 수정 결과를 파일에 반영.
