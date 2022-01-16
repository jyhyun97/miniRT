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
   * 해상도 setting
   * 각 도형 별로 setting
2. cam
3. 도형 구현
4. phone 모델
