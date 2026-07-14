# Create

## 개요

새로운 회원 데이터를 입력받아 JSON 파일에 저장하는 기능.

## 동작

- 콘솔에서 사용자로부터 회원 정보(이름, 연락처 등 필드)를 입력받는다.
- 입력값의 형식/필수 항목 여부를 검증한다.
- 신규 데이터에 고유 ID(또는 키 값)를 부여한다. 이미 사용 중인 ID와 중복되지 않도록 확인한다.
- 검증을 통과한 데이터를 회원 데이터 모델 구조체로 구성하여 메모리 상의 회원 목록에 추가한다.
  이 모델은 [nlohmann/json](json-file-storage.md)을 통해 JSON으로 직렬화될 수 있도록
  `to_json`/`from_json` 변환 함수(또는 대응하는 매크로)를 정의해둔다.
- [json-file-storage](json-file-storage.md)를 호출해 변경된 목록을 JSON 파일에 저장한다.

## 관련 기능

- [json-file-storage](json-file-storage.md): 저장된 결과를 파일에 반영.
- [read](read.md): 추가된 데이터를 이후 조회할 때 사용.
