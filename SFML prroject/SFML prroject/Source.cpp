# include < SFML/Graphics.hpp>
#include <Windows.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<vector>
#include <ctime>
using namespace sf;
using namespace std;
static const float VIEW_WIDTH = 800;
static const float VIEW_HEIGHT = 600;
enum movingStates {
	IDLE, MOVING_UP, MOVING_DOWN, MOVING_LEFT, MOVING_RIGHT
};
struct positionRock
{

	double arraystorex[82];
	double arraystorey[82];
	int indexrockx;
	int indexrocky;




}rockposition[82];
bool walkfinish;
void gameover() {
	RenderWindow gameOver(sf::VideoMode(259, 194), "Game Over", Style::Close);
	sf::RectangleShape shape(Vector2f(259, 194));
	Texture game;
	game.loadFromFile("jim.jpg");
	shape.setTexture(&game);



	/////////////sound gameover

	while (gameOver.isOpen())
	{
		sf::Event event;
		while (gameOver.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				gameOver.close();
		}

		gameOver.clear();
		gameOver.draw(shape);
		gameOver.display();
	}



};

void win() {
	RenderWindow win(sf::VideoMode(300, 168), "HORRAY", Style::Close);
	sf::RectangleShape shape(Vector2f(300, 168));
	Texture won;
	won.loadFromFile("download(2).jpg");
	shape.setTexture(&won);

	/////////////////sound horrray


	while (win.isOpen())
	{
		sf::Event event;
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				win.close();
		}

		win.clear();
		win.draw(shape);
		win.display();
	}



};
void control(RenderWindow& window, bool& up, bool& down, bool& right, Sprite& spriteJim, Sprite arrayBarrier[]) {

	for (int i = 0; i < 2; i++)
	{

		if (spriteJim.getGlobalBounds().intersects(arrayBarrier[i].getGlobalBounds()) && spriteJim.getPosition().x > 80)
		{
			if (down) {
				//if (spriteJim.getPosition().y <245){


				/////////////sound electric
				spriteJim.setPosition(spriteJim.getPosition().x, 220);//downspriteJim.getPosition().y + 1
				/*if (right)
				{
					if (spriteJim.getPosition().x==80)
					spriteJim.setPosition(80, spriteJim.getPosition().y);

					if (spriteJim.getPosition().x == 120)
						spriteJim.setPosition(120, spriteJim.getPosition().y);

				}*/

			}
			else
			{//////////////////sound electric


				spriteJim.setPosition(spriteJim.getPosition().x, 360);//spriteJim.getPosition().y - 1

			}

		}

	}

	if (right)
	{
		if (spriteJim.getPosition().x <= 45 && (spriteJim.getPosition().y < 360 && spriteJim.getPosition().y > 240))
		{
			spriteJim.setPosition(40, spriteJim.getPosition().y);
			//spriteJim.getPosition().x <= 50 &&
		}
	}


};
void boundaries(RenderWindow& window, Sprite& spriteJim) {
	if (spriteJim.getPosition().x < 40) {

		spriteJim.setPosition(40, spriteJim.getPosition().y);
	}
	if (spriteJim.getPosition().y < 40) {

		spriteJim.setPosition(spriteJim.getPosition().x, 40);
	}

	if (spriteJim.getPosition().x + spriteJim.getGlobalBounds().width > 1160) {

		spriteJim.setPosition(1160 - spriteJim.getGlobalBounds().width, spriteJim.getPosition().y);
	}

	if (spriteJim.getPosition().y + spriteJim.getGlobalBounds().height > 760) {//down

		spriteJim.setPosition(spriteJim.getPosition().x, 760 - spriteJim.getGlobalBounds().height);
	}

};

void intersectdiamond(RenderWindow& window, int& score, Sprite& spriteJim, Sprite arrayDiamond[30][20], Sprite arayRock[30][20]) {
	bool first = false;

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++) {

			if (arrayDiamond[i][j].getPosition() == arayRock[i][j].getPosition())
				continue;


			//else if (.intersects(arrayDiamond[i][j].getGlobalBounds())) 
			int intersectx = spriteJim.getPosition().x;
			int intersectdiamondx = (arrayDiamond[i][j].getPosition().x);
			int intersecty = spriteJim.getPosition().y;
			int intersectDiamondy = (arrayDiamond[i][j].getPosition().y);

			if (spriteJim.getGlobalBounds().intersects(arrayDiamond[i][j].getGlobalBounds()) && intersectx == intersectdiamondx && intersecty == intersectDiamondy) {



				arrayDiamond[i][j].setScale(sf::Vector2f(0.f, 0.f));
				score += 10;



				//cout << "score =" << score;
			}

			window.draw(arrayDiamond[i][j]);

		}

	}
};

int main()

{
	int score = 0;
	Time second = seconds(0.01);
	//Time millisecond = milliseconds(0.001);

	// grid lines setting
	float gridSize = 100.0f;//must be global
	unsigned GridSize = 100.f;
	float dt = 0.f;
	RenderWindow window(sf::VideoMode(800, 600), "Digging Jim", Style::Close);
	window.setFramerateLimit(360);

	//window.SetFramerateLimit(360);
	//view
	View view;
	view.setSize(VIEW_WIDTH, VIEW_HEIGHT);
	//center of view
	view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);//float
	float viewSpeed = 60.f;
	// grid rectangle
	RectangleShape shape(Vector2f(gridSize, GridSize));
	//clock
	Clock clock;

	sf::Clock clockview;
	int countdown = 30;
	Texture textureJim;
	textureJim.loadFromFile("jim project.png");
	Sprite spriteJim;
	spriteJim.setTexture(textureJim);
	spriteJim.setPosition(80, 80);

	// >> wooden walll

	Texture textureBarrier;
	textureBarrier.loadFromFile("scorebar3.png");

	Sprite arrayBarrier[2];

	for (int i = 0; i < 2; i++)
		arrayBarrier[i].setTexture(textureBarrier);

	arrayBarrier[0].setPosition(80, 300);
	arrayBarrier[1].setPosition(560, 300);

	//iron wall

	Texture wallvtext;
	wallvtext.loadFromFile("iron.png");
	Sprite spriteWall;
	spriteWall.setTexture(wallvtext);
	//soil

	Texture textureSoil;
	textureSoil.loadFromFile("sand.png");
	Sprite arraySoil[30][20];
	bool Nothing[30][20];
	//vector<int>vectorSoilX;
	//vector<int>vectorSoilY;
	int	widthSoil, hightSoil;
	//vector<int>vectorWidthSoil;
//	vector<int>vectorHightSoil;




	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++)
			arraySoil[i][j].setTexture(textureSoil);



	}


	//diamond

	Texture diamond;
	diamond.loadFromFile("diamond.png");
	Sprite arrayDiamond[30][20];

	//rocks

	Texture textureRocks;
	textureRocks.loadFromFile("rock.jpg");

	Sprite arayRock[30][20];

	Sprite arayRock2[30][20];
	//bool arrayRockIsThere[30][20];
	Sprite arayNewRock[30][20];

	bool arrayRockIsThere[30][20];

	/*for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++) {
			arrayRockIsThere[i][j] == false;
		}
	}*/
	int arraystorex[82];
	int arraystorey[82];
	int count2 = 0;
	int indexrockx[9];
	int indexrocky[9];






	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) {

			arayRock[i][j].setTexture(textureRocks);


			arayRock[i][j].setPosition(((rand() % 28) * 40) + 40, ((rand() % 18) * 40) + 40);


			arraystorex[count2] = arayRock[i][j].getPosition().x;
			arraystorey[count2] = arayRock[i][j].getPosition().y;
			indexrockx[count2] = i;
			indexrockx[count2] = j;
			rockposition[count2].arraystorex[count2] = arayRock[i][j].getPosition().x;
			rockposition[count2].arraystorey[count2] = arayRock[i][j].getPosition().y;
			rockposition[count2].indexrockx = i;
			rockposition[count2].indexrocky = j;




			count2++;
			/*x = arayRock[i][j].getPosition().x;
			y = arayRock[i][j].getPosition().y;
			arayRock2[x / 40][y / 40].setPosition(x, y);
			arrayRockIsThere[x / 40][y / 40] = 1;*/

		}
	}
	cout << count2 << "**" << endl;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			arrayDiamond[i][j].setTexture(diamond);
			arrayDiamond[i][j].setPosition(((rand() % 28) * 40) + 40, ((rand() % 18) * 40) + 40);

			if (arrayDiamond[i][j].getGlobalBounds().intersects(arrayBarrier[1].getGlobalBounds()) || arrayDiamond[i][j].getGlobalBounds().intersects(arrayBarrier[0].getGlobalBounds()))
			{
				arrayDiamond[i][j].setScale(0, 0);
			}

			if (arayRock[i][j].getGlobalBounds().intersects(arrayBarrier[1].getGlobalBounds()) || arayRock[i][j].getGlobalBounds().intersects(arrayBarrier[0].getGlobalBounds()))
				arayRock[i][j].setScale(0, 0);
			count2 = 0;
			while (count2 <= 82)
			{

				if (arraystorex[count2] == arrayDiamond[i][j].getPosition().x && arraystorey[count2] == arrayDiamond[i][j].getPosition().y) {

					arrayDiamond[i][j].setScale(0, 0);
				}


				count2++;
			}
		}
	}



	//door

	Texture Doortext;
	Doortext.loadFromFile("door.jpg");
	Sprite DOOR;
	DOOR.setTexture(Doortext);
	DOOR.setPosition(80, 80);

	//smash
	Texture smashTexture;
	smashTexture.loadFromFile("smash.png");
	Sprite smashSprite;
	smashSprite.setTexture(smashTexture);
	smashSprite.setPosition(80, 80);


	int count = 0;


	while (window.isOpen())
	{//update clock

		dt = clockview.restart().asSeconds();//to know how much a frame
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;

			}
		}
		//TIMER - 30 SECONDS
		int timer = clock.getElapsedTime().asSeconds();
		//std::cout << timer << std::endl;

		if (timer > 0) {
			countdown--;
			cout << countdown << endl;
			cout << "leeeeeeeeeeeeeeee" << endl;
			//	countdownString = convert.str();
				//timerText.setString(countdownString);
			clock.restart();
		}



		int dir, x = 80, y = 80;
		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;
		bool barrierup = false;


		//control
		if (sf::Keyboard::isKeyPressed(Keyboard::Key::Left))//left 
		{
			spriteJim.move(-0.01f, 0.0f);//float

			left = true;


			dir = 1;
			if ((view.getCenter().x < 400))
				view.setCenter(400, view.getCenter().y);
			else
				view.move(-viewSpeed * dt, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(Keyboard::Key::Right))
		{
			dir = 2;
			spriteJim.move(0.01f, 0.0f);

			right = true;
			if (view.getCenter().x >= 800)
				view.setCenter(800, view.getCenter().y);
			else
				view.move(viewSpeed * dt, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(Keyboard::Key::Up))
		{
			dir = 3;

			spriteJim.move(0.0f, -0.01f);// (x,y)
			up = true;


			if (view.getCenter().y <= 300)
				view.setCenter(view.getCenter().x, 300);

			view.move(0.f, -viewSpeed * dt);
		}
		else if (sf::Keyboard::isKeyPressed(Keyboard::Key::Down))
		{
			dir = 4;
			//spriteJim.setPosition(spriteJim.getPosition().x, spriteJim.getPosition().y + 4);
			spriteJim.move(0.0f, 0.01f);
			down = true;

			if (view.getCenter().y >= 500)
				view.setCenter(view.getCenter().x, 500);


			view.move(0.f, viewSpeed * dt);
		}
		//function for controlling barrier

		control(window, up, down, right, spriteJim, arrayBarrier);

		if (left)
		{
			int xl = spriteJim.getPosition().x;


			//spriteJim.move(-0.01f, 0.0f);//float


			while (xl % 40 != 0) {
				spriteJim.move(-0.01f, 0.0f);//float
				xl = spriteJim.getPosition().x;
			}
		}
		if (right)
		{
			int xr = spriteJim.getPosition().x;
			while (xr % 40 != 0) {
				spriteJim.move(0.01f, 0.0f);
				xr = spriteJim.getPosition().x;
			}
		}
		if (up)
		{
			int xu = spriteJim.getPosition().y;
			while (xu % 40 != 0) {
				spriteJim.move(0.0f, -0.01f);
				xu = spriteJim.getPosition().y;

			}
			up = false;
		}
		if (down)
		{
			int xd = spriteJim.getPosition().y;
			while (xd % 40 != 0) {
				spriteJim.move(0.00f, 0.01f);
				xd = spriteJim.getPosition().y;
			}
			down = false;
		}





		//screen boundries
		boundaries(window, spriteJim);

		Time elapsed = clockview.getElapsedTime();




		//collision with rock
		//collosion with rock
		for (int i = 0; i < 9; i++)//spriteJim.getPosition().x == arayRock[i][j].getPosition().x &&
		{//spriteJim.getPosition().y == arayRock[i][j].getPosition().y
			//&&( spriteJim.getPosition().x == arayRock[i][j].getPosition().x || spriteJim.getPosition().x >= arayRock[i][j].getPosition().x
			for (int j = 0; j < 9; j++)
			{


				if (spriteJim.getGlobalBounds().intersects(arayRock[i][j].getGlobalBounds()) &&
					(spriteJim.getPosition().y > arayRock[i][j].getPosition().y) && Keyboard::isKeyPressed(Keyboard::Key::Up) && spriteJim.getPosition().x >= arayRock[i][j].getPosition().x - 5 && spriteJim.getPosition().x <= arayRock[i][j].getPosition().x + 5)

				{
					cout << spriteJim.getPosition().x << endl;
					cout << arayRock[i][j].getPosition().x << endl;

					//spriteJim.setPosition(arayRock[i][j].getPosition().x, arayRock[i][j].getPosition().y + 40);


					spriteJim.setPosition(arayRock[i][j].getPosition().x, arayRock[i][j].getPosition().y + 40);

					// spriteJim.move(+0.0f, 0.5f);
					cout << "noooooooooooooo" << endl;




				}
				else if (spriteJim.getGlobalBounds().intersects(arayRock[i][j].getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::Key::Down) && spriteJim.getPosition().x >= arayRock[i][j].getPosition().x - 5 && spriteJim.getPosition().x <= arayRock[i][j].getPosition().x + 5)
				{




					spriteJim.setPosition(arayRock[i][j].getPosition().x, arayRock[i][j].getPosition().y - 40);
					// spriteJim.move(+0.0f, -0.5f);
					cout << "dowwwwwwwwwwwwwwwwwwwwwwwwn" << endl;


				}
				//left
				else  if (spriteJim.getGlobalBounds().intersects(arayRock[i][j].getGlobalBounds()) &&
					(spriteJim.getPosition().x < arayRock[i][j].getPosition().x) && Keyboard::isKeyPressed(Keyboard::Key::Right) && spriteJim.getPosition().y >= arayRock[i][j].getPosition().y - 5 && spriteJim.getPosition().y <= arayRock[i][j].getPosition().y + 5)
				{




					spriteJim.setPosition(arayRock[i][j].getPosition().x - 40, arayRock[i][j].getPosition().y);

					//spriteJim.move(-0.5f, 0.0f);
					cout << "hiiiiiiiiiiiii" << endl;
					cout << spriteJim.getPosition().x << "\t" << spriteJim.getPosition().y;

				}

				//right

				else if (spriteJim.getGlobalBounds().intersects(arayRock[i][j].getGlobalBounds()) &&
					(spriteJim.getPosition().x > arayRock[i][j].getPosition().x) && Keyboard::isKeyPressed(Keyboard::Key::Left) && spriteJim.getPosition().y >= arayRock[i][j].getPosition().y - 5 && spriteJim.getPosition().y <= arayRock[i][j].getPosition().y + 5)
				{


					// spriteJim.move(+0.5f, 0.0f);

					spriteJim.setPosition(arayRock[i][j].getPosition().x + 40, arayRock[i][j].getPosition().y);
					cout << "hiiiiiiiiiiiiiiii" << endl;
					cout << spriteJim.getPosition().x << "\t" << spriteJim.getPosition().y;

				}//down

			}
		}

		/*Time elapsed = clock.getElapsedTime();
float countdown =( float)elapsed;
/*count_le_down  -= clock.getElapsedTime();
if (count_le_down <= 0.f) {
	std::cout << count_le_down << std::endl;
}*/
/*count_le_down = count_le_down - elapsed;
if (count_le_down <= 0.f) {
	std::cout << "lol, the count down counted down!" << std::endl;*/




		window.clear();
		window.setView(view);
		int bag;
		int size = 40;
		int N = 30;
		int M = 20;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (i == 0) {
					spriteWall.setPosition(i * size, j * size);

					window.draw(spriteWall);
				}
				else if (i == 29)
				{
					spriteWall.setPosition(i * size, j * size);
					window.draw(spriteWall);
				}
				else if (j == 0)
				{
					spriteWall.setPosition(i * size, j * size);
					window.draw(spriteWall);
				}
				else if (j == 19)
				{
					spriteWall.setPosition(i * size, j * size);
					window.draw(spriteWall);
				}

				else

				{

					//	Nothing[i][j] = 1;
					//	arraySoil[i][j].setScale(0, 0);

					arraySoil[i][j].setPosition(i * size, j * size);

					int intersectx = spriteJim.getPosition().x;
					int intersectsoilx = (arraySoil[i][j].getPosition().x);
					int intersecty = spriteJim.getPosition().y;
					int intersectsoily = (arraySoil[i][j].getPosition().y);




					count2 = 0;





					if (intersectx == intersectsoilx && intersecty == intersectsoily)

					{
						//soilposition[count3].indexsoilx = i;
						//soilposition[count3].indexsoily = j;


						if (Keyboard::isKeyPressed(Keyboard::Key::Right))
						{
							intersectsoilx = spriteJim.getPosition().x - 40;


						}
						else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
						{
							intersectsoilx = spriteJim.getPosition().x + 40;


						}
						else
							intersectsoilx = spriteJim.getPosition().x;


						arraySoil[i][j].setScale(0, 0);
						/*while (count2 < 99)
						{
							if (rockposition[count2].arraystorex[count2] == intersectsoilx && rockposition[count2].arraystorey[count2] == intersectsoily - 40)
							{
								//cout << "horray " << endl;

								//arayRock[rockposition[count2].indexrockx][rockposition[count2].indexrocky].move(0, 0.2);

								arayRock[rockposition[count2].indexrockx][rockposition[count2].indexrocky].setPosition(intersectsoilx, intersectsoily);
								rockposition[count2].arraystorex[count2] = arayRock[rockposition[count2].indexrockx][rockposition[count2].indexrocky].getPosition().x;
								rockposition[count2].arraystorey[count2] = arayRock[rockposition[count2].indexrockx][rockposition[count2].indexrocky].getPosition().y;

							}
							count2++;
						}*/
					}
					window.draw(arraySoil[i][j]);

				}
			}
		}








		//left

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {



				window.draw(arayRock[i][j]);

			}
		}
		int intersectsoilx;
		bool no = false;
		//	count2 = 0;

			/*if (spriteJim.getPosition().y == arraySoil[i][j].getPosition().y && ((spriteJim.getPosition().x == arayRock[i][j].getPosition().x - 40 || spriteJim.getPosition().x == arayRock[i][j].getPosition().x + 40) || (spriteJim.getPosition().x == arayRock[i][j].getPosition().x && spriteJim.getPosition().y == arraySoil[i][j].getPosition().y))) {
				no = true;
				cout << "innnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn" << endl;

			}*/


		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (arraySoil[i][j].getGlobalBounds().height == 0)
				{

					//	cout << "hellllllllllllllo" << endl;
					for (int k = 0; k < 30; k++)
					{
						for (int z = 0; z < 20; z++)
						{
							if (arraySoil[i][j].getPosition().x == arayRock[k][z].getPosition().x && arraySoil[i][j].getPosition().y == arayRock[k][z].getPosition().y + 40)
							{

								arayRock[k][z].setPosition(arraySoil[i][j].getPosition().x, arraySoil[i][j].getPosition().y);
							}

						}

					}



				}


			}



		}

		intersectdiamond(window, score, spriteJim, arrayDiamond, arayRock);

		window.draw(spriteJim);
		/*	for (int i = 0; i < 30; i++)
			{
				for (int j = 0; j < 20; j++)


				{
					if (spriteJim.getPosition().x == (arayRock[i][j].getPosition().x - 40) && spriteJim.getPosition().y == (arayRock[i][j].getPosition().y ));

					spriteJim.setPosition(arayRock[i][j].getPosition().x - 20, spriteJim.getPosition().y);


				}


			}*/


		if (count < 600)
			window.draw(DOOR);
		cout << score << endl;

		if (score >= 400) {

			////////////////////sound door

			DOOR.setPosition(1000, 600);
			window.draw(DOOR);
			//if (spriteJim.getPosition().x == DOOR.getPosition().x && spriteJim.getPosition().y == DOOR.getPosition().y)
			//	win();

			//	if (spriteJim.setPosition(spriteJim.getPosition().x, spriteJim.getPosition().y) == DOOR.setPosition(DOOR.getPosition().x, DOOR.getPosition().y)) {
				//	spriteJim.setScale(0, 0);
	//}
		}

		/*
		if (spriteJim.setPosition(spriteJim.getPosition().x, spriteJim.getPosition().y) == DOOR.setPosition(DOOR.getPosition().x, DOOR.getPosition().y)) {
			delete spriteJim;

		}
		*/


		for (int i = 0; i < 2; i++)
		{
			window.draw(arrayBarrier[i]);
		}
		//window.draw(shape);
		window.setView(window.getDefaultView());


		/*	for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 20; j++) {

					arayRock2[i][j].setTexture(textureRocks);
					//Nothing[i][j] = 1;
					window.draw(arayRock2[i][j]);

				}
			}*/

			//	sf::sleep(sf::seconds(0.001));
		window.display();
		//view.setCenter(spriteJim.getPosition());//to make the player always in the middle

		count++;


		// sleep a minimum amount of time to ensure there's always at least some delta time (assuming very, very fast CPUs)

	}



	return 0;


}

	
