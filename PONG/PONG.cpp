#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(sf::VideoMode(800, 600), "PONG");
	//setting the frame limit
	window.setFramerateLimit(60);

	//FONT
	Font font;
	if (!font.loadFromFile("Fonts/OrkneyBold.otf"))  return 1;
	Text score;
	score.setFont(font);
	score.setCharacterSize(30);
	score.setFillColor(Color(255, 0, 0, 255));
	score.setPosition(380, 10);
	score.setString("0 : 0");


	//Images
	Texture player_tex;
	if(!player_tex.loadFromFile("Textures/playerTile.png"))  return -1;
	Texture ball_tex;
	if (!ball_tex.loadFromFile("Textures/ball.png"))  return -1;
	Texture background_tex;
	if (!background_tex.loadFromFile("Textures/back.png"))  return -1;

	//Sounds
	/*
	SoundBuffer buff_hit;
	if (!hit.loadFromFile("Audio/hit.wav")) return -1;


	Sound hit;
	hit.setBuffer(buff_hit);
	*/
	//STATES
	bool upButton = 0, downButton = 0;

	//VARIABLES
	int yVelPlayer = 0;
	int yVelOpp = 0;
	float xball = -5;
	float yball = -3.3;
	int playerscore = 0, oppscore = 0;

	//SHAPES
	RectangleShape background;
	background.setSize(Vector2f(800, 600));
	background.setPosition(0, 0);
	background.setFillColor(Color(150, 150, 150, 255));
	background.setTexture(&background_tex);

	RectangleShape player1;
	player1.setSize(Vector2f(20, 100));
	player1.setPosition(30, 200);
	player1.setFillColor(Color(200, 40, 40, 255));
	player1.setTexture(&player_tex);

	RectangleShape player2;
	player2.setSize(Vector2f(20, 100));
	player2.setPosition(750, 400);
	player2.setFillColor(Color(200, 40, 40, 255));
	player2.setTexture(&player_tex);

	RectangleShape ball;
	ball.setSize(Vector2f(20, 20));
	ball.setPosition(400, 300);
	ball.setFillColor(Color(40, 255, 40, 255));
	ball.setTexture(&ball_tex);



	while (window.isOpen())
	{
		Event event;
		//Events
		while (window.pollEvent(event))
		{
			//window close event
			if (event.type == Event::Closed)
			{
				window.close();
			}


			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up) upButton = true;
				if (event.key.code == sf::Keyboard::Down) downButton = true;
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Up) upButton = false;
				if (event.key.code == sf::Keyboard::Down) downButton = false;
			}

		}
		///////////////////////////////
		///////////////Logic///////////
		///////////////////////////////
		yVelPlayer = (downButton - upButton) * 5;

		//MOVE
		player1.move(0, yVelPlayer);
		ball.move(xball, yball);

		//outofbounds player 1
		if (player1.getPosition().y < 0)
			player1.setPosition(30, 0);
		if (player1.getPosition().y > 500)
			player1.setPosition(30, 500);

		//player2AI
		if (ball.getPosition().y < player2.getPosition().y) yVelOpp = -3.8;
		if (ball.getPosition().y + 20 > player2.getPosition().y + 100) yVelOpp = 3.8;
		player2.move(0, yVelOpp);

		//outofbound ball and reflect
		if (ball.getPosition().y < 0) yball = -yball;
		if (ball.getPosition().y > 580) yball = -yball;

		if (ball.getPosition().x < -20)
		{
			oppscore++;
			ball.setPosition(600, 400);
		}
		if (ball.getPosition().x > 800)
		{
			playerscore++;
			ball.setPosition(300, 200);
		}

		//collisonWith Player
		if (ball.getGlobalBounds().intersects(player1.getGlobalBounds()))
		{
			xball = -xball;
			//hit.play(); //sound
		}
		if (ball.getGlobalBounds().intersects(player2.getGlobalBounds()))
		{
			xball = -xball;
			//hit.play(); //sound
		}


		///////////////////////////
		//////////RENDERING////////
		///////////////////////////
		window.clear();


		//drawing the shapes
		window.draw(background);
		window.draw(player1);
		window.draw(player2);
		window.draw(ball);

		//Score
		stringstream text;
		text << playerscore << " : " << oppscore;
		score.setString(text.str());
		window.draw(score);


		window.display();
	}
	return 0;
}
