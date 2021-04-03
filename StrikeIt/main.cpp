//Libraries
#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include "HandleGameplay.h"

//Namespaces
using namespace strikeit;


//Glboal variables, functions, classes

//main class functions
void CheckOutOfBounds(int);
void CheckAndMovePadAutomatically(HandleGameplay *);
void CheckOutofBoundForBall(HandleGameplay *);
void CheckCollision(HandleGameplay *);


//global variables
sf::RectangleShape pad[PAD_COUNT];
sf::RectangleShape ball;
sf::Sound hit;

int pad1Score = 0; //Score for pad1
int pad2Score = 0; //Score for pad2

int main()
{
	//Creating the window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "StrikeIt", sf::Style::Titlebar | sf::Style::Close);

	//Settign the framerate limit to 60 FPS
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);


	//Event object holding all events
	sf::Event event;

	//Font
	sf::Font font;	//Font object
	if (font.loadFromFile("Data/font.otf") == 0) //Safe way to load font
	{
		return 1;
	}

	//Text object for score
	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(30);
	score.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10);
	score.setString("0 : 0");

	//Images
	sf::Texture tex_pad; //Pad image/texutre
	sf::Texture tex_ball; //Ball texture

						  //Load the textures
	if (tex_pad.loadFromFile("Data/pad.png") == false)
	{
		return -1;
	}

	if (tex_ball.loadFromFile("Data/ball.png") == false)
	{
		return -1;
	}


	//Sounds
	sf::SoundBuffer buff_hit; //Hit sound

							  //Sound
	hit.setBuffer(buff_hit);

	//Load the sound
	if (buff_hit.loadFromFile("Data/hit.wav") == false)
	{
		return -1;
	}



	//Pad1


	pad[PAD1].setSize(sf::Vector2f(PAD_WIDTH, PAD_HEIGHT));
	pad[PAD1].setPosition(PAD1_DEFAULT_POSITON[X], PAD1_DEFAULT_POSITON[Y]);
	pad[PAD1].setTexture(&tex_pad);

	//Pad2
	pad[PAD2].setSize(sf::Vector2f(PAD_WIDTH, PAD_HEIGHT));
	pad[PAD2].setPosition(PAD2_DEFAULT_POSITON[X], PAD2_DEFAULT_POSITON[Y]);
	pad[PAD2].setTexture(&tex_pad);

	//Ball
	ball.setSize(sf::Vector2f(BALL_WIDTH, BALL_WIDTH));
	ball.setPosition(BALL_DEFAULT_POSITON[X], BALL_DEFAULT_POSITON[Y]);
	ball.setTexture(&tex_ball);

	HandleGameplay *gameplay = new HandleGameplay();

	//Game loop
	while (gameplay->gameplayProgress == true)
	{
		//EVENTS
		while (window.pollEvent(event))
		{
			gameplay->HandleKeyEvents(event);
		}

		////////////LOGIC
		////Pad1
		gameplay->SetPadVelocities(PAD1);

		//Move pad1
		pad[PAD1].move(0, gameplay->GetPadVelocity(PAD1));

		//Out of bounds check
		CheckOutOfBounds(PAD1);


		////Pad2
		//Check where the ball is and set the velocity

		CheckAndMovePadAutomatically(gameplay);


		/////Ball
		ball.move(gameplay->GetXBallVelocity(), gameplay->GetYBallVelocity());

		//Out of bounds check
		CheckOutofBoundForBall(gameplay);

		//Collision

		CheckCollision(gameplay);


		//RENDERING
		window.clear();

		//Drawing the shapes

		window.draw(pad[PAD1]);
		window.draw(pad[PAD2]);
		window.draw(ball);

		//Score
		std::stringstream text;
		text << pad1Score << " : " << pad2Score; //Create the text
		score.setString(text.str()); //Set the score text

		window.draw(score);

		window.display();
	}
	///////////

	//Clean up and close the window
	window.close();

	//Close the program
	return 0;
}

void CheckOutOfBounds(int padnum)
{
	if (pad[padnum].getPosition().y < 0)
	{
		pad[padnum].setPosition(PAD_WIDTH, 0);
	}

	if (pad[padnum].getPosition().y > SCREEN_HEIGHT - PAD_HEIGHT)
	{
		pad[padnum].setPosition(PAD_WIDTH, SCREEN_HEIGHT - PAD_HEIGHT);
	}
}

void CheckAndMovePadAutomatically(HandleGameplay *classObj)
{
	if (ball.getPosition().y < pad[PAD2].getPosition().y)
	{
		classObj->yVelocityPad[PAD2] = -1 * AUTOMACTIC_PAD_VELOCITY;
	}

	if (ball.getPosition().y > pad[PAD2].getPosition().y)
	{
		classObj->yVelocityPad[PAD2] = AUTOMACTIC_PAD_VELOCITY;
	}

	if (rand() % FORCE_WIN_POINT + 1 == FORCE_WIN_POINT)
	{
		classObj->yVelocityPad[PAD2] = 0;
	}

	if (pad[PAD2].getPosition().y < 0)
	{
		pad[PAD2].setPosition(SCREEN_WIDTH - PAD_WIDTH * 2, 0);
	}

	if (pad[PAD2].getPosition().y > SCREEN_HEIGHT - PAD_HEIGHT)
	{
		pad[PAD2].setPosition(SCREEN_WIDTH - PAD_WIDTH * 2, SCREEN_HEIGHT - PAD_HEIGHT);
	}	//Move pad2 
	pad[PAD2].move(0, classObj->yVelocityPad[PAD2]);
}

void CheckOutofBoundForBall(HandleGameplay *classObj)
{
	if (ball.getPosition().y < 0)
	{
		classObj->SetYBallVelocity(-1 * classObj->GetYBallVelocity());
	}

	if (ball.getPosition().y >  SCREEN_HEIGHT - BALL_WIDTH)
	{
		classObj->SetYBallVelocity(-1 * classObj->GetYBallVelocity());
	}

	//Left and right out of bounds check
	if (ball.getPosition().x < -1 * BALL_WIDTH)
	{
		pad2Score++; //Increase score
		ball.setPosition(BALL_DEFAULT_POSITON[X], BALL_DEFAULT_POSITON[Y]); //Move the ball back to middle
	}

	if (ball.getPosition().x > SCREEN_WIDTH)
	{
		pad1Score++;
		ball.setPosition(BALL_DEFAULT_POSITON[X], BALL_DEFAULT_POSITON[Y]);
	}
}

void CheckCollision(HandleGameplay *classObj)
{
	//Collision for pad1
	if (ball.getGlobalBounds().intersects(pad[PAD1].getGlobalBounds()) == true)
	{
		classObj->SetXBallVelocity(-1 * classObj->GetXBallVelocity());//Invert the x velocity of ball
		hit.play(); //Play sound
	}

	//Collision for pad2
	if (ball.getGlobalBounds().intersects(pad[PAD2].getGlobalBounds()) == true)
	{
		classObj->SetXBallVelocity(-1 * classObj->GetXBallVelocity());

		hit.play(); //Play sound
	}
}



