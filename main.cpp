#include <SFML/Graphics.hpp>
#include<iostream>


using namespace sf;


float offsetX = 0, offsetY = 0;

int ground = 500;
bool first = true;
bool eyeLeft;

const int H = 20;
const int W = 160;


String TileMap[H] = {

	"w                                                                                                                                                              w",
	"w                                                                                                                                                              w",
	"w                                                                                                                                                              w",
	"w                                                                                                                                                              w",
	"w                                                                                                                                                              w",
	"w                                                                                                                                                              w",
	"w                                 qqqq       q         qqqqqq     qq    q       q         q         qq    q   qqqqqq q   q   qqqqqq    e                       w",
	"w                                 q   q     q q        q    q     q q   q      q q       q q        q q   q  q        q  q  q                                  w",
	"w                                 qqqq     q   q       q    q     q  q  q     q   q     q   q       q  q  q q          q q q               e                   w",
	"w                                 qqqq    qqqqqqq   qqqqqqqqqqqq  q   q q    q     q   q     q      q   q q q           qq q                                   w",
	"w     0        000    0           q   q  q       q  q          q  q    qq   q       q q       q     q    qq  q           q  q                   e              w",
	"w     0       0   0   0           qqqq  q         q q          q  q     q  q         q         q    q     q   qqqqqq     q   qqqqqq                            w",
	"w     0       0   0   0                                                                                                                              e         w",
	"w     00000    000    00000                                                                                                                                    w",
	"w                                                                                                                                                         ee   w",
	"w                                                                                                               r                                              w",
	"w                                                                                                                                                              w",
	"w                                                                                                                                                              w",
	"w                                                                                         r                                                                   ew",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBrrrBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBrrrrrrrrrrBBBBBBBBBBBBBBBBBBBBBBBBB",

};





class player {
public:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;
	float currentFrameJump;
	
	

	player(Texture &image){
		sprite.setTexture(image);
		sprite.setTextureRect(IntRect(0, 0, 48, 100));
		rect = FloatRect(0, 0, 48, 100);


		dx = 10;
		dy = 0;
		currentFrame = 6;
		currentFrameJump = 0;
	}


	void update(float time){
		rect.left += dx * 10;
		CollisionX();

		if (!onGround) dy = dy + 0.0006*time;

		rect.top += dy*time;

		onGround = false;
		CollisionY();

		if (rect.top > ground) { rect.top = ground; dy = 0; onGround = true; }

		

		if (rect.top != 500){
			currentFrameJump += 0.003*time;

			if (currentFrameJump >= 7) { currentFrameJump -= 7; }
			sprite.setTextureRect(IntRect(50 * int(currentFrameJump), 430, 48, 100));
			if (50 * int(currentFrameJump) > 150 && 50 * int(currentFrameJump) <= 200){
				sprite.setTextureRect(IntRect(200, 430, 41, 75));
			}
			if (50 * int(currentFrameJump) > 200 && 50 * int(currentFrameJump) <= 250){
				sprite.setTextureRect(IntRect(240, 430, 41, 75));
			}
			if (50 * int(currentFrameJump) > 250 && 50 * int(currentFrameJump) <= 300){
				sprite.setTextureRect(IntRect(281, 430, 41, 75));
			}
			if (50 * int(currentFrameJump) > 300 && 50 * int(currentFrameJump) <= 350){
				sprite.setTextureRect(IntRect(328, 430, 41, 75));
			}
		}

		if (rect.top != 500 && dx < 0 || rect.top != 500 && eyeLeft){
			currentFrameJump += 0.003*time;

			if (currentFrameJump >= 7) { currentFrameJump -= 7; }
			sprite.setTextureRect(IntRect(50 * int(currentFrameJump)+48, 430, -48, 100));
			if (50 * int(currentFrameJump) > 150 && 50 * int(currentFrameJump) <= 200){
				sprite.setTextureRect(IntRect(200 + 41, 430, -41, 75));
			}
			if (50 * int(currentFrameJump) > 200 && 50 * int(currentFrameJump) <= 250){
				sprite.setTextureRect(IntRect(240 + 41, 430, -41, 75));
			}
			if (50 * int(currentFrameJump) > 250 && 50 * int(currentFrameJump) <= 300){
				sprite.setTextureRect(IntRect(281 + 41, 430, -41, 75));
			}
			if (50 * int(currentFrameJump) > 300 && 50 * int(currentFrameJump) <= 350){
				sprite.setTextureRect(IntRect(328 + 41, 430, -41, 75));
			}
		}
		

		if (dy == 0 && eyeLeft){
			sprite.setTextureRect(IntRect(48, 0, -48, 100));
		}

		if (dy == 0 && !eyeLeft){
			sprite.setTextureRect(IntRect(0, 0, 48, 100));
		}

		//std::cout << eyeLeft << std::endl;


		currentFrame -= 0.004*time;
		if (currentFrame < 0) { currentFrame += 6; }

		if (dy == 0 && dx > 0) sprite.setTextureRect(IntRect(50 * int(currentFrame), 215, 48, 100));
		if (dy == 0 && dx < 0) sprite.setTextureRect(IntRect(50 * int(currentFrame) + 48, 215, -48, 100));
	
		
			sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
							
		
		dx = 0;
	}

	void CollisionX(){
		for (int i = rect.top / 32; i < (rect.top + rect.height)/32; i++){
			for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++){
				if (TileMap[i][j] == 'B' || TileMap[i][j] == 'w' || TileMap[i][j] == 'q' || TileMap[i][j] == 'e'){
					if (dx > 0) rect.left = j * 32 - rect.width;
					if (dx < 0) rect.left = j * 32 + 32;
				}
				if (TileMap[i][j] == '0'){
					TileMap[i][j] = ' ';
				}
			}
		}
	}

	void CollisionY(){
		for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++){
			for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++){
				
				if (TileMap[i][j] == 'B' || TileMap[i][j] == 'w' || TileMap[i][j] == 'q' || TileMap[i][j] == 'e'){
					if (dy > 0) { rect.top = i * 32 - rect.height; dy = 0; onGround = true; }
					if (dy < 0) { rect.top = i * 32 + 32; dy = 0; }
					if (TileMap[i][j] == '0'){
						TileMap[i][j] = ' ';
					}
				}
			}
		}
	}

};


//////////////////////////////VADIM CODE//////////////////////////////////////////
void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("image/game.png");
	menuTexture3.loadFromFile("image/game.png");
	menuBackground.loadFromFile("image/k.png");
	Sprite menu1(menuTexture1), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu3.setPosition(100, 150);
	menuBg.setPosition(345, 0);


	//////////////////////////////MENU///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 3) { window.close(); isMenu = false; }
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}
//////////////////////////////VADIM CODE//////////////////////////////////////////]]]]


int main()
{
	
	RenderWindow window(VideoMode(1000, 600), "jesus!");



	Texture t;
	t.loadFromFile("image/sonic.png");



	float currentFrame = 0;

	Sprite s;
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 48, 100));
	s.setPosition(50,50);


	Texture mapTexture;
	mapTexture.loadFromFile("image/map.png");

	Sprite tile;
	tile.setTexture(mapTexture);
	

	player p(t);


	Clock clock;

	RectangleShape rectangle(Vector2f(32, 32));


	menu(window);
	while (window.isOpen()){
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 300;

		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed){
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)){
			eyeLeft = true;
			p.dx = -0.08;
		
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)){
			eyeLeft = false;
			p.dx = 0.08;

		}

		if (Keyboard::isKeyPressed(Keyboard::Up)){
			if (p.onGround) { p.dy = -0.4; p.onGround = false; }
		}

		p.update(time);

		offsetX = p.rect.left - 500;
		offsetY = p.rect.top- 300;
			
		window.clear(Color::White);

		for (int i = 0; i < H; i++){
			for (int j = 0; j < W; j++){
				if (TileMap[i][j] == 'B') { tile.setTextureRect(IntRect(457, 550, 32, 32)); tile.setPosition(j * 32 - offsetX, i * 32 - offsetY); }
				if (TileMap[i][j] == '0') { tile.setTextureRect(IntRect(400, 220, 32, 32)); tile.setPosition(j * 32 - offsetX, i * 32 - offsetY); }
				if (TileMap[i][j] == 'q') { tile.setTextureRect(IntRect(333, 290, 30, 30)); tile.setPosition(j * 32 - offsetX, i * 32 - offsetY); }
				if (TileMap[i][j] == 'w') { tile.setTextureRect(IntRect(400, 130, 30, 30)); tile.setPosition(j * 32 - offsetX, i * 32 - offsetY); }
				if (TileMap[i][j] == 'e') { tile.setTextureRect(IntRect(593, 380, 30, 30)); tile.setPosition(j * 32 - offsetX, i * 32 - offsetY); }
				if (TileMap[i][j] == 'r') { tile.setTextureRect(IntRect(174, 440, 25, 38)); tile.setPosition(j * 32 - offsetX, i * 32 - offsetY); }
				if (TileMap[i][j] == ' ') continue;

				  					
				 
				window.draw(tile);
			}
		}

		window.draw(p.sprite);
		window.display();
	}

	return 0;
} 

