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
   * 구 -> (1/20 -> 구현은 됬지만 표현이 안됨)
   * 평면 -> (1/21 -> 구현 성공)
   * 원기둥
   * Error 어안렌즈 효과?
4. phong 모델
   * 주변광
   * 난반사
   * 경면광
   * 그림자

## 주차별 과정
* 1.17[1주차]
   - [ x ] 파싱 {1.17 ~ 1.18}
   - [ x ] 카메라 {1.18 ~ 1.19}
      - [ x ] 창 띄우기
      - [ x ] mlx관련 함수 만들기
      - [ x ] 벡터 함수
      - [ x ] mlx_hook
* 1.24[2주차]
   - [ x ] 도형
      - [ x ] 구
      - [ x ] 평면
      - [ x ] 원기둥
* 1.31[3주차]
   - [ x ] phong 모델
      - [ x ] ambient
      - [ x ] diffuse
      - [ x ] specular
   - [ ] shadow
      - [ ] Noise 제거 필요
* 2.7[4주차]
   - [ ] 리펙


## Ray와 구의 교점 찾기
   직선의 방정식과 구의 방정식 사이의 교점(P(t))이 있는지 확인하고 싶은 것!
   
   ```
   P(t) = A + Bt // 직선의 방정식
   (x - a)^2 + (y - b)^2 + (z - c)^2 = r^2 // 구의 방정식 (변수 X)

   A는 ray.origin(정해진 수)
   B는 ray.normal(정해진 수)
   C는 구의 중심 좌표(정해진 수)
   C(a, b, c) => 구의 중심 좌표
   t는 임의의 변수

   y = 기울기 * x + 상수
   P(t) => A + Bt // 직선의 방정식에서의 임의의 점 => P(t)

   직선 위 임의의 점(임의의 P(t))과 구의 좌표 사이의 거리가 r이라고 가정
   왜? r이라고 가정했을때 적절한 t값을 찾기 위해서

   만약 t의 값이 1개라면 구와 접하는 것
   t의 값이 2개라면 구를 통과해서 교점이 2개인 것
   t의 값이 존재하지 않는다면 구를 지나지 않는 것

   r = P(t) - C (점과 점 사이의 거리)
    
   임의의 점P(t)과 C 사이의 거리
   r^2 = (P(t) - C)^2 = (A + Bt - C)^2 = (Bt + (A - C))^2
   r^2 = BBt^2 + 2B(A - C)t + (A - C)^2
   BBt^2 + 2B(A - C)t + (A - C)^2 - r^2 = 0

   at^2 + bt + c = 0

   (-b +- sqrt(b^2 - 4ac))/ 2a
   (-2 +- sqrt(2^2 - ac)) / a
   (-(b/2) +- sqrt((b/2)^2 - ac)) / a
   ```

## Ray와 평면의 교점 찾기
   ```
   직선의 방정식 : P(t) = v1 + t * vDir = A + Bt
   P(t) : 직선상의 모든 점.
   v1 : 직선상의 임의의 한 점.
   t : v1로부터 떨어진 거리.
   vDir : 직선의 방향(벡터).

   가정 -> 임의의 직선 위의 점 P(t) = A + Bt = P1

   평면의 방정식 : pN • (P0 - P1) = 0 = pl.normal dot (pl.point - P(t))
   pN : 평면에 수직방향인 벡터. pl.normal
   P0 : 평면상의 임의의 한 점.(평면의 중심) pl.point
   P1 : 평면상의 임의의 한 점. -> (P1을 P(t)로 가정하고 진행)
   (P0-P1) : 평면위의 선분(벡터).

   a • b = |a||b|cos(theta) = 0
   PN • (P0 - P1) = |PN||P0-P1|cos(theta) = 0

   P(t) = A + Bt = P1(가정)
   PN • (P0 - P1) = 0 => PN • (P0 - A + Bt) = 0
   PN • (Bt + (P0 - A)) = 0
   PN•Bt + PN•(P0 - A) = 0

   t = PN • (P0 - A) / PN • B
   ```


## Ray와 평면의 교점 찾기
   ```
   원기둥의 축을 나타내는 방정식 [P(t1)]
      P(t1) = P0 + Vt1 = cy.point + cy.normal * t1
   원기둥의 축과 거리가 r인 임의의 ray[R(t2)]는 원기둥과 교점이 있다고 본다.
      R(t2) = A + Bt2 = ray.origin + ray.normal * t2

   if. R(t2)는 원기둥의 표면을 지난다고 가정하자.
   그럼 R(t2) - P0는 분명 원기둥 내의 어떤 점일것이다.
   여기서 원기둥의 normal 벡터와 외적한 값은 반지름이 될것이다.

   ((R(t2) - P0) x V)^2 = r^2
   ((ray - cy.point) x cy.normal)^2 = 반지름^2

   A x B = |A| |B| sin(theta)
   (ray - cy.point) x cy.normal = |(ray - cy.point)| |cy.normal| sin(theta) = Vector(r)

   ((A + Bt - P0) x V)^2 = r^2
   ((Bt + (A - P0)) x V)^2 = r^2
   ((B x V)t + ((A - P0) X V))^2 = r^2
   
   (B x V)^2 * t^2 + 2(B x V)((A - P0) X V)t + ((A - P0) X V)^2 - r^2 = 0

   (B x V)^2 * t^2 + 2(B x V)•((A - P0) x V)t + ((A - P0) x V)^2 = r^2
   (B x V)^2 * t^2 + 2(B x V)•((A - P0) x V)t + ((A - P0) x V)^2 - r^2 = 0

   a = (B x V)^2
   b_half = (B x V)•((A - P0) x V)
   c = ((A - P0) x V)^2 - r^2
   
   ray = A + Bt
   ray.point = A
   ray.normal = B
   cy.point = P0
   cy.normal = V

   a = (ray.normal x cy.normal)^2
   b_half = (ray.normal x cy.normal)((ray.point - cy.point) x cy.normal)
   c = ((ray.point - cy.point) x cy.noral)^2 - cy.radius^2
   
   at^2 + (2b_half)t + c = 0
   
   근의 공식!!! = (-b +- sqrt(b^2 - ac)) / a
   점화식 =   b^2 - ac > 0 [근이 두개]
            b^2 - ac = 0 [근이 한개]
            b^2 - ac < 0 [근이 없음]
   dis = b * b - a * c
   if (dis < 0)
      return (-1);
   t1 = (-b + sqrt(dis)) / a;
   t2 = (-b - sqrt(dis)) / a;
   
   if (작은 값 < 큰 값)
      t = 작은 값
   {
      t1 알고있는 값
      R(t1) = A + Bt1 => 좌표(원기둥 표면의 점)

      P0(원기둥의 중심)

      V1(원기둥 중심부터 표면의 점까지의 벡터) = R(t1) - P0

      V0(원기둥의 normal)
   }
   0 <= V1 • V0 =< h (원기둥의 측면만 고려한 상황) 

   t_vec ray = ray.origin + ray.normal * t; (무한한 원기둥과 Ray의 교점까지의 벡터)

   t_vec RO = cy.point - ray; (교점과 원기둥의 중심까지의 벡터)

   double   h = R0 • cy.normal;

   if (0 <= h && h <= cy.height)
      return (t);
   else
   {
      double   t`;
      if (h < 0)
         t`= (cy.normal • (cy.point - A)) / (cy.normal • B);
      else
         t`= (cy.normal • (cy.point + (h * cy.normal) - A)) / (cy.normal • B);
      
      if (t` > r)
         return (-1);
      return (t`);
   }

   OT` = (R(t`) - cy.point) = A + Bt` - cy.point
   
   OT` • cy.normal = 0
   (Bt` + (A - cy.point)) • cy.normal = cy.normal • Bt` + cy.normal • (A - cy.point) = 0
   cy.normal • Bt` = cy.normal • (cy.point - A)
   t`= (cy.normal • (cy.point - A)) / (cy.normal • B)

   OT` = R(t`) - (cy.point + (h * cy.normal))
   t`= (cy.normal • (cy.point + (h * cy.normal) - A)) / (cy.normal • B)


   ```

## Hard shadows
   ```
      shadow ray의 origin은 curr_ob.point
      normal은 light.Point - curr_ob.point
      hit_object(info, shadowray)

   ```