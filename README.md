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
2. [프로젝트&nbsp;구조](#2.프로젝트-구조)
3. [개발&nbsp;내용&nbsp;및&nbsp;결과물](#3.개발-내용-및-결과물)
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
<br/><br/>

# 2.프로젝트&nbsp;구조
![project_structure](https://user-images.githubusercontent.com/76093968/177243203-4f667a80-0f3b-42be-8c13-35af78bf3cd9.png)
<br/><br/>

# 3.개발&nbsp;내용&nbsp;및&nbsp;결과물

### 1단계
-	Ncurses의 window를 이용해서 게임을 진행할 공간을 만들어 주었다. 배경을 위한 main_window를 먼저 만들어주고 그 위에 snake가 움직일 main_board, 점수가 표현될 score_board, 미션의 수행 여부를 표시해 줄 mission_board를 만들어준다.
-	게임을 전체적으로 관리할 GameController class를 만들고 게임이 시작하면 위의 window들을 출력해줄 BoardController class를 만들어준다.
-	GameController class의 생성자가 불리면 BoardController class의 생성자도 실행되면서 초기 게임화면이 출력된다.
- main_board는 맵 배열 안 값에 따라 각각 다른 색과 모양으로 출력해준다.  
  - 0 : empty space – 흰색 블록 
  - 1 : wall – 검은색 블록
  - 2 : snake head – 빨간 M
  - 3 : snake body – 빨간 O
  - 4 : growth item – 빨간 G
  - 5 : poison item – 빨간 P
  - 6 : immune wall – 검은색 블록
  - 10 : gate – 빨간 1
-	wrefresh를 이용해 터미널에 출력한다.
- 색을 사용할 때에는 start_color(), init_color()을 이용해 미리 색을 준비해 두고 사용하였다.
-	맵의 배열값에 따라 화면에 출력해주며 게임의 변화를 실시간으로 계속 보여주는 랜더링 작업이 필요하다.
  -	<signal.h>, <unistd.h>를 이용해 alarm을 활용한 랜더링을 void game_run()함수에서 구현했다. Signal함수를 이용해 정해진 시간마다 프로세스에 정해진 시그널을 전달해준다. 시그널을 받으면 전역함수인 bool _signal을 false로 바꿔주는데 이 값이 유효한 동안 while문 내에서 키보드 입력을 기다리게 한다. 이 입력값을 snake에 전달해 snake를 움직이고 맵을 다시 refresh해준다. 이 과정을 반복하면서 게임이 진행되고 화면에 게임이 출력된다.
  -	맵을 refresh하는 과정은 render_map()함수에서 구현했다. 배열내의 snake를 나타내는 부분을 다시 0으로 초기화하고 snake객체의 vector내부의 값을 다시 배열에 표시한다음 main_board, score_board, mission_board를 배열에 맞게 wrefresh()해서 새로 출력해준다.


### 2단계
-	Snake class를 만들고 snake의 머리와 몸통의 x, y좌표를 vector<vector<int>> body에 저장해준다. vector의 0번 값이 머리를 나타낸다. Snake의 움직임과 크기에 관련된 메소드들을 구현한다.
-	snake가 움직일 때 각 몸통은 바로 앞 몸통의 이동방향을 따라 가야하기 때문에 snake의 머리부분만 옮겨준 뒤 iterator를 이용해 몸통 부분이 따라가도록 구현해준다.
-	몸통이 커져야 하는 경우 몸통의 마지막 부분에 새로운 몸통이 생겨야 하는데 이 꼬리 또한 이 전 몸통의 이동방향과 일치하는 방향으로 생성되야 하므로 vector<int> empty_body에 항상 보이지 않는 꼬리를 저장 해 두며 뱀이 움직일 때 같이 움직여준다. 몸통이 커지는 상황이 벌어질 때 이 투명한 꼬리를 vector에 push해줌으로써 정확한 위치에 몸통이 추가된다. 게임화면에 출력되는 snake는 vector<vector<int>> body이다.
-	snake의 움직임은 키보드 입력 값을 이용해서 방향키의 해당하는 값을 입력받으면 그 방향으로 머리를 이동시켜준다. 
-	snake가 움직인 후 snake head가 맵의 배열내에서 다양한 값에 접근할 때 그에 맞는 처리를 해준다.  
  -	wall, immune wall, snake body을 만나면 게임이 종료된다.
  -	growth item을 만나면 size_up()을 한다.
  -	poison item을 만나면 size_down()을 한다.
  -	gate를 만나면 다른 gate로 이동한다.
  -	body vector의 크기에 따라 3보다 작거나 10보다 크면 게임이 종료된다.
-	매 snake의 움직임 마다 맵의 배열을 최신화 해주며 맵을 출력해준다.
-	snake class의 생성자에서 기본으로 vector body에 3개의 vector을 넣어주어 크기를 3으로 만들어 주고 시작한다.
-	snake 객체를 만들고 맵의 배열에 2는 snake head, 3은 snake body로 할당해 준 뒤 출력한다.


### 3단계
-	배열내 좌표와 lifetime, itemType을 갖는 Item class를 생성한다.
-	두가지 종류의 itemType을 갖기 때문에 bool타입으로 만들어 true와 false로 growth인지 poison인지를 구별해주었다.
-	GameController class에서 이 item을 담아 둘 vector<Item> itemContainer을 만들고 정해진 시간마다 Item객체를 만들어 push해 주었다. 이 itemContainer안에 들어있는 Item객체들을 맵에 표시해준다.
-	lifeTime을 이용해 item의 만료조건을 만들었는데, 게임이 진행되면서 game_run()함수에서 while루프를 돌때마다 lifeTime값을 감소시켜주고 매번 lifeTime을 확인해서 0인 Item들은 itemContainer에서 없애준다.


### 4단계
-	Map , Snake의 상태를 보고 Gate를 생성해야 하기 때문에 GameController에서 Gate클래스를 생성할 때 참조연산자로 Map과 Snake를 받는다.
-	게이트를 랜덤으로 생성하기 위해 게이트를 나타내는 gate1,gate2를 참조연산자로 받는다
-	 Snake가 게이트1으로 들어가면 게이트2로 나오는 기능을 구현하기 위해 Snake를 움직이는 변수인 command를 참조연산자로 받는다.
-	Snake가 미션에서 주어진 게이트 사용횟수를 채울 때 체크표시를 하기 위해 goal_gateCount를 참조연산자로 받는다.
-	syncMap()을 통해서 Map에서 게이트가 될 수 있는 위치를 받아서 저장한다.  
  -	IMMUNE_WALL은 게이트가 될 수 없고 WALL만 게이트가 될 수 있기에 WALL의 위치를 파싱해서 저장한다.
-	gateRefresh()를 통해서 Map에서 게이트가 랜덤으로 나타나게 한다.
-	gateSensor()를 통해서 Snake가 게이트에 들어갔는 지를 감지해서 다른 게이트로 나오게 만든다.
-	GameController클래스의 game_run()함수를 통해서 GateController클래스의 gateRefresh()로 Map에서 게이트가 랜덤으로 나타나게 하고 GateController클래스의 gateSensor()로 Snake가 게이트에 들어갔는 지를 감지하도록 한다.


### 5단계
-	맵의 오른쪽에 게임 점수와 수행해야 할 미션을 출력해주는 미션보드, 스코어보드를 출력해준다.
- 기호 구성
  - B : snake의 길이
  - '+' : growth item을 먹은 횟수
  - '-' : poison item을 먹은 횟수
  - G : gate 사용 횟수
-	미션은 달성 할 경우 () -> (V)로 체크된다.
-	미션을 모두 달성 할 경우 맵이 바뀐다.
-	GameController class에서 미션보드와 스코어보드에 출력해줄 string들을 만들어 놓고, game_run()함수에서 각 게임의 진행상황에 맞게 매번 최신화해서 출력해준다.

### 6단계(추가구현)
-	speed변수를 하나 선언해서 level이 높아질 때마다 스네이크의 속도를 더 빠르게 만든다.
-	Main.cpp 안에 init_pair을 만들어서 level마다 달라지는 스네이크의 색깔을 정의를 한다. 그리고 snakeColor변수를 선언해서 level마다 snakeColor에 값을 다르게 할당을 하여서 level마다 스네이크의 색깔을 다르게 나타나도록 만든다.
-	ending_board라는 window를 하나 만들어서 벽에 부딪히거나 body에 부딪히면 ending_board를 띄우도록 한다.






