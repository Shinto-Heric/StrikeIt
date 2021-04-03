#pragma once




#ifndef HANDLEGAMEPLAY_H_
#define HANDLEGAMEPLAY_H_

#include <SFML/Graphics.hpp>


#define MAX_PAD_VELOCITY 10
#define MIN_PAD_VELOCITY 0
#define PAD_COUNT 2
#define PAD1 0
#define PAD2 1
#define X 0
#define Y 1
#define AUTOMACTIC_PAD_VELOCITY 8
#define BALL_X_VELOCITY -8
#define BALL_Y_VELOCITY -6
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PAD_WIDTH 50
#define PAD_HEIGHT 100
#define BALL_WIDTH 50
#define FORCE_WIN_POINT 20
const float PAD1_DEFAULT_POSITON[] = { 50 , PAD_HEIGHT * 2 }; // paddle 1 will be 50pixel away from left side of the window
const float PAD2_DEFAULT_POSITON[] = { SCREEN_WIDTH - 100 , PAD_HEIGHT * 2 }; // paddle 2 will be 50pixel away from right side of the window since 0,0 of the pad will be the bottom left corner of the texture
const float BALL_DEFAULT_POSITON[] = { SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 };
namespace strikeit
{
	class HandleGameplay
	{
	public:
		float *yVelocityPad;
		bool gameplayProgress;

		HandleGameplay();
		~HandleGameplay();
		void CreateGameObject();
		void HandleKeyEvents(sf::Event);
		void SetPadVelocities(int padnum);
		float GetPadVelocity(int padnum);
		float GetXBallVelocity();
		void SetXBallVelocity(float);
		float GetYBallVelocity();
		void SetYBallVelocity(float);

	private:
		bool up;
		bool down;
		//Variables to handle velocity
		int xVelocityBall; //X velocity of the ball
		int yVelocityBall; //Y velocity of the ball

	};
}
#endif /* HANDLEGAMEPLAY_H_ */


