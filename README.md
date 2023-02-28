# miniRT

<img width="1020" alt="miniRT_0" src="https://user-images.githubusercontent.com/72776427/221765804-29ffdb6c-9a65-4032-a5e6-4d1e8fe26dc6.png">
<img width="1022" alt="miniRT_1" src="https://user-images.githubusercontent.com/72776427/221765820-47362fea-3e06-44ed-b711-38ca8b8892d2.png">

## 실행

make && ./miniRT .rt파일
(.rt파일은 scene 디렉토리에 있음)

## 요구사항

openGL기반으로 한 그래픽 라이브러리 MiniLibX를 사용.

레이트레이싱을 구현하는 것이 목표.

구, 평면, 원기둥 세 가지 입체도형, phong 조명 모델, 그림자를 구현한다.

.rt파일에 입체 도형의 크기와 벡터, 광원, 주변광, 등이 주어진다.

## 구현 과정 요약

.rt 파일을 파싱하고 값을 검증한다.

카메라와 레이 구현.

각 입체도형의 교점을 찾는 방정식을 통해 교점과 교점 거리를 알아내어 도형 출력.

phong 모델 구현을 위해 주변광, 난반사, 반사광 처리.

광원과 도형에 부딪혀 반사되는 벡터에 도형이 있는지 판단해 그림자 구현하기.

## 참고자료

[https://raytracing.github.io/books/RayTracingInOneWeekend.html](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
