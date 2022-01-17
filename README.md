# miniRT

## 일정

평일 오전 9시부터 시작
주말, 스케줄에 따라 변동 가능

   
## 목표기간

### 1.17 ~ 2.21
   
## Subject 관련 사항

* miniLibX 사용하여 과제 수행한다.
* Window를 움직일 때 부드러운 움직임을 보여주어야 한다.(ex. 화면 전환, 최소화, 등)
* 적어도 세 가지 object를 만들어야 한다.(plane, sphere, cylinder)
* object의 정보를 변경할 수 있어야 한다.
* cam, light, object의 회전과 변화에 따른 처리를 해야한다.
* spot brightness, hard shadows, ambiance lighting 처리를 해야한다.
* 주변광, 분산광은 반드시 수행해야 한다.(참고 https://nobilitycat.tistory.com/entry/Ambient-and-Diffuse-Lighting)
* ESC를 누르면 프로그램이 완벽히 종료되어야 한다.
* 왼쪽 위 닫기 버튼을 누르면 완벽히 종료되어야 한다.
* minilibX의 images를 사용하길 강력히 추천한다.
* .rt의 확장자를 가진 파일을 불러와야 한다.
   * 첫 인자는 화면에 대한 정보를 갖고 있어야 한다.
   * object의 요소들은 하나 이상의 space로 구분된다.
   * object는 하나 이상의 개행으로 구분된다.
   * 대문자로 정의된 요소는 장면당 하나씩 정의할 수 있다.
   
## 절차

1. 파싱
   * .rt 파일 불러오기
      * gnl 수정
      * char -> double func(atof)
   * 해상도 setting
      * 에러체크
   * 각 도형 별로 setting
      * 구조체(object) 생성
      * 구조체에 담으면서 에러체크
2. cam
   * 벡터 함수(사칙연산, 내적, 외적)
   * 화면 띄우기
   * hook 구현
3. 도형 구현
   * 구
   * 평면
   * 원기둥
4. phong 모델
   * 주변광
   * 난반사
   * 경면광
   * 그림자

## 주차별 과정
* 1.17[1주차]
   - [ ] 파싱
   - [ ] 카메라
* 1.24[2주차]
   - [ ] 도형
* 1.31[3주차]
   - [ ] phong 모델
* 2.7[4주차]
   - [ ] 리펙


Makefile
scene/ .rt
include/ 헤더
mlx/
src/ 파싱/ 렌더링/