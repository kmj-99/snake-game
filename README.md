# snake-game
c++언어를 사용하고 ncurses라이브러리를 사용하여서 게임을 만드는 프로젝트.

# 프로젝트 설명


![Snake_GameImage](https://user-images.githubusercontent.com/76093968/177235737-68e7c783-f0b3-431e-a88f-fc6620d94a6a.png)

**Immune Wall**: Gate로 변할 수 없는 Wall

**Snake Body**: Snake의 몸

**Gate B && Gate A**: Snake가 통과할 수 있는 Gate(Gate A로 들어가면 Gate B로 나온다.)

**Growth Item**: Snake Body의 길이를 1 증가시켜주는 Item

**Wall**: Gate로 변할 수 있는 Wall

**Poison Item**: Snake Body의 길이를 1 감소시키는 Item
<br/><br/>
전체적인 구조는 위와 같이 구성되어 있다.
<br/><br/><br/>
해당 프로젝트는 총 6단계로 나누어서 구현을 한다.

### 1단계
NCurses Library를 이용하여 Snake 게임을 할 수 있는 Map을 만든다.
<br/><br/>
### 2단계
1단계에서 만든 Map위에서 Snake를 표시하고 방향키로 Snake를 움직이도록 만든다.
<br/><br/>
### 3단계
Map위에 Growth Item과 Poison Item을 출현시켜서 2단계에서 만든 Snake가 Item을 먹을때
적절한 액션을 취할 수 있도록 한다.  
(참고:Snake Game의 구조)
<br/><br/>
### 4단계
Map의 Wall의 임의의 위치에서 한 쌍에 Gate가 출현할 수 있도록 하고,각 Gate에 Snake가 통과할 수 있도록 한다.  
(참고: Immune Wall은 Gate가 될 수 없다.)
<br/><br/>
### 5단계
우측에 게임 점수를 표시하는 화면을 구성한다. 또한 Mission을 달성하면 다음 Map으로 진행하도록 프로그램을 완성한다.  
(참고: Stage는 최소 4개로 구성하고, 각 Stage의 Map은 서로 다르다.)
<br/><br/>
### 6단계(추가구현)
다음 Map으로 넘어갈 때마다 Snake의 색깔이 바뀌고 Snake의 속도는 더 빠르게 하여 난이도를 높인다. 벽이나 Snake의 Body에 닿으면 GameOver화면을 띄우고 방향키를 누르면 첫 번째 Map부터 다시 시작하도록 한다.


# 목차
1. [개발&nbsp;환경](#1.개발-환경)
2. [개발&nbsp;내용&nbsp;및&nbsp;결과물](#2.개발-내용-및-결과물)
3. [프로젝트&nbsp;구조](#3.프로젝트-구조)
4. [실행 방법](#4.실행-방법)
5. [참고 문헌](#4.참고-문헌)



# 1.개발&nbsp;환경
**언어**: C++

**라이브러리**: 외부 라이브러리로 텍스트 기반 사용자 인터페이스를 제어할 수 있는 ncurses

```
$sudo apt-get install libncurses5-dev libncursesw5-dev 
```



**에디터**: Atom

**운영체제**: ubuntu 18.04 (64bit)

**소스코드 관리**: Git

**협업툴**: Slack


# 2.개발&nbsp;내용&nbsp;및&nbsp;결과물

### 1단계
- Ncurses의 screen과 window를 이용해 맵과 미션보드, 스코어보드를 출력한다.
- 실제 플레이 맵은 배열을 이용해 1은 벽 0은 빈 공간으로 색을 다르게 구현한다

### 2단계
- snake 객체를 만들고 맵의 배열에 2는 snake head, 3은 snake body로 할당해 준 뒤 출력한다.
- 키보드 입력을 이용해 뱀의 움직임을 구현하고 맵을 업데이트시키며 출력을 해서 맵의 랜더링 구현한다.
- snake head가 snake body에 닿으면 게임이 종료되도록 구현한다.
- snake head가 벽에 닿으면 게임이 종료되도록 구현한다.
- snake의 크기가 3보다 작아지거나 10보다 커지면 게임이 종료되도록 구현한다.

### 3단계
- poison과 growth 두가지 중 한가지 속성을 갖는 item객체 생성
- item은 정해진 주기마다 맵에 랜덤으로 생성된다.
- poison item은 맵의 배열에 5로 growth item은 4로 표기된다.
- 생성된 item들은 itemContainer에 저장되며 생명주기를 확인해 만료된 item들은 삭제된다.
- growth item을 먹은 snake는 body에 새로운 꼬리부분이 추가되며, poison item을 먹은 snake는 꼬리부분을 상실한다.
- item들은 맵의 빈공간에만 생성된다.

### 4단계
-	맵의 wall에서만 나타나는 한 쌍의 gate구현, gate가 나타나지 않는 immune wall은 맵의 배열에 6으로 표기된다.
-	gate는 정해진 주기마다 맵에 랜덤으로 생성된다. gate는 맵의 배열에 10으로 표기된다. 
-	gate는 정해진 시간동안 열려 있으며 snake가 통과하는 동안은 닫히지 않는다.
-	gate를 통과하는 snake의 진행방향은 정해진 규칙에 따라 결정된다.
-	gate는 한번에 한 쌍만 생성된다.

### 5단계
-	맵의 오른쪽에 게임 점수와 수행해야 할 미션을 출력해주는 미션보드, 스코어보드를 출력해준다.
-	기호 구성
- 기호 구성
  - B : snake의 길이
  - '+' : growth item을 먹은 횟수
  - '-' : poison item을 먹은 횟수
  - G : gate 사용 횟수
-	미션은 달성 할 경우 () -> (V)로 체크된다.
-	미션을 모두 달성 할 경우 맵이 바뀐다.

### 6단계(추가구현)
-	4개의 map을 만들어서 level을 적용하여 level_1,level_2,level_3,level_4로 구성하여 level별로 난이도를 다르게 구현한다
-	Level이 올라갈수록 스네이크의 속도는 점점 빨라진다.
-	벽이나 스네이크의 body에 닿으면 게임오버 화면을 띄우고 방향키를 누르면 level_1부터 다시 시작하도록 한다.
-	Level이 바뀔 때 마다 스네이크의 색깔이 바뀐다.





