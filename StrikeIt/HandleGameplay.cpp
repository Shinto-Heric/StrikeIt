#include "HandleGameplay.h"
namespace strikeit
{
	HandleGameplay::HandleGameplay()
	{
		gameplayProgress = true;

		//currentState Variables
		up = false;
		down = false;
		xVelocityBall = BALL_X_VELOCITY;
		yVelocityBall = BALL_Y_VELOCITY;
		yVelocityPad = new float[PAD_COUNT];
		for (int index = 0; index < PAD_COUNT; index++)
		{
			yVelocityPad[index] = 0; /// to set start veleocity
		}
	}

	HandleGameplay::~HandleGameplay()
	{
	}

	void HandleGameplay::CreateGameObject()
	{
	}

	void HandleGameplay::HandleKeyEvents(sf::Event event)
	{
		//Event type is window closed
		if (event.type == sf::Event::Closed)
		{
			//Set play to false in order to stop the game loop
			gameplayProgress = false;
		}

		//Key pressed
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up ||
			event.key.code == sf::Keyboard::W))
		{
			up = true;
		}

		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Down ||
			event.key.code == sf::Keyboard::S))
		{
			down = true;
		}

		//Key released
		if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Up ||
			event.key.code == sf::Keyboard::W))
		{
			up = false;
		}

		if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Down ||
			event.key.code == sf::Keyboard::S))
		{
			down = false;
		}
	}

	void HandleGameplay::SetPadVelocities(int padnum)
	{
		if (up == true)
		{
			yVelocityPad[padnum] = MAX_PAD_VELOCITY * -1;
		}

		if (down == true)
		{
			yVelocityPad[padnum] = MAX_PAD_VELOCITY;
		}

		if (up == true && down == true)
		{
			yVelocityPad[padnum] = MIN_PAD_VELOCITY;
		}

		if (up == false && down == false)
		{
			yVelocityPad[padnum] = MIN_PAD_VELOCITY;
		}
	}

	float HandleGameplay::GetPadVelocity(int padnum)
	{
		return yVelocityPad[padnum];
	}

	float HandleGameplay::GetXBallVelocity()
	{
		return xVelocityBall;
	}

	void HandleGameplay::SetXBallVelocity(float velocity)
	{
		xVelocityBall = velocity;
	}
	float HandleGameplay::GetYBallVelocity()
	{
		return yVelocityBall;
	}

	void HandleGameplay::SetYBallVelocity(float velocity)
	{
		yVelocityBall = velocity;
	}

}