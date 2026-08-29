/*
 * Menu.cpp
 * Keeps a list of relative coordinates to the buttons of the menu screens.
 * Determines which menu image is displayed when navigating the menu. It also
 * takes hovering above a button into account.
 *  Created on: 24-apr.-2016
 *      Author: Kwinten
 */

#include <menu/Menu.h>
#include "menu/MenuButton.h"
using namespace frogger;

Menu::Menu(Window* win, char* gameMode, int* amountOfPlayers, char* difficulty) :
		win(win), gameMode(gameMode), amountOfPlayers(amountOfPlayers), difficulty(
				difficulty)
{
	BST = new MenuButton(0.24719,0.4052,0.50843,0.09294, win); //start game button
	BH = new MenuButton(0.2809,0.56506,0.46348,0.0855, win); //high score button
	BQ = new MenuButton(0.39888,0.72119,0.19944,0.09665, win); //quit button
	BHE = new MenuButton(0.02247,0.84387,0.10674,0.13383, win); //help button
	BS = new MenuButton(0.83989,0.829,0.13764,0.15985, win); //setting button
	S1 = new MenuButton(0.43258,0.50558,0.05618,0.05576, win); //1 player setting
	S2 = new MenuButton(0.43258,0.5948,0.05618,0.05576, win); //2 players setting
	S3 = new MenuButton(0.43258,0.69517,0.05618,0.05576, win); //3 players setting
	SEN = new MenuButton(0.03933,0.50558,0.19663,0.05576, win); //endless mode button
	SC = new MenuButton(0.03652,0.5948,0.18539,0.05204, win); //classic mode button
	SE = new MenuButton(0.73315,0.49442,0.1264,0.05576, win); //easy mode button
	SM = new MenuButton(0.73315,0.5948,0.19663,0.05576, win); //medium mode button
	SH = new MenuButton(0.73315,0.69517,0.1264,0.05576, win); //hard mode button

	back=new MenuButton(0.38483,0.86617,0.22753,0.08178,win);

	selectedMode = SEN;
	selectedNumberOfPlayers = S1;
	selectedDifficulty = SE;
}

Menu::~Menu()
{
	delete(BST);
	delete(BH);
	delete(BQ);
	delete(BHE);
	delete(BS);
	delete(S1);
	delete(S2);
	delete(S3);
	delete(SEN);
	delete(SC);
	delete(SE);
	delete(SM);
	delete(SH);
	delete(back);
}

char Menu::menuExecution(std::string keyDown, char state, int mXH, int mYH)
{
	switch (state)
	{
		case 'B':
			if (BST->col(mXH, mYH))
			{
				win->setBackground(1);
				if (keyDown == "MOUSEBUTTONDOWN")
					return 'E';
			}
			else if (BH->col(mXH, mYH))
			{
				win->setBackground(2);
				if (keyDown == "MOUSEBUTTONDOWN")
					return 'H';
			}
			else if (BQ->col(mXH, mYH))
			{
				win->setBackground(3);
				if (keyDown == "MOUSEBUTTONDOWN")
					return 'Q';
			}
			else if (BHE->col(mXH, mYH))
			{
				win->setBackground(5);
				if (keyDown == "MOUSEBUTTONDOWN")
					return 'A';
			}
			else if (BS->col(mXH, mYH))
			{
				win->setBackground(4);
				if (keyDown == "MOUSEBUTTONDOWN")
					return 'S';
			}
			else
			{
				win->setBackground(0);
					return state;
			}
			break;
		case 'H':
			if (back->col(mXH, mYH))
			{
				win->setBackground(7);
				if (keyDown == "MOUSEBUTTONDOWN")
					state = 'B';
			}
			else
			{
				win->setBackground(6);
					return state;
			}
			break;
		case 'S':
			if (S1->col(mXH, mYH) && keyDown == "MOUSEBUTTONDOWN")
			{
				*amountOfPlayers = 1;
				selectedNumberOfPlayers = S1;
				win->setBackground(8);
				win->drawLineUnder(selectedMode, selectedNumberOfPlayers,
						selectedDifficulty);
				return state;
			}
			else if (S2->col(mXH, mYH) && keyDown == "MOUSEBUTTONDOWN")
			{
				*amountOfPlayers = 2;
				selectedNumberOfPlayers = S2;
				win->setBackground(8);
				win->drawLineUnder(selectedMode, selectedNumberOfPlayers,
						selectedDifficulty);
				return state;
			}
			else if (S3->col(mXH, mYH) && keyDown == "MOUSEBUTTONDOWN")
			{
				*amountOfPlayers = 3;
				selectedNumberOfPlayers = S3;
				win->setBackground(8);
				win->drawLineUnder(selectedMode, selectedNumberOfPlayers,
						selectedDifficulty);
				return state;
			}
			else if (back->col(mXH, mYH))
			{
				win->setBackground(9);
				win->drawLineUnder(selectedMode, selectedNumberOfPlayers,
						selectedDifficulty);
				if (keyDown == "MOUSEBUTTONDOWN")
					return 'B';
			}
			else if (SEN->col(mXH, mYH) && keyDown == "MOUSEBUTTONDOWN")
			{
				*gameMode = 'E';
				selectedMode = SEN;
				win->setBackground(8);
				win->drawLineUnder(selectedMode, selectedNumberOfPlayers,
						selectedDifficulty);
				return state;
			}
			else if (SC->col(mXH, mYH) && keyDown == "MOUSEBUTTONDOWN")
			{
				*gameMode = 'C';
				selectedMode = SC;
				win->setBackground(8);
				win->drawLineUnder(selectedMode, selectedNumberOfPlayers,
						selectedDifficulty);
				return state;
			}
			else if (SE->col(mXH, mYH) && keyDown == "MOUSEBUTTONDOWN")
			{
				*difficulty = 'E';
				selectedDifficulty = SE;
				win->setBackground(8);
				win->drawLineUnder(selectedMode, selectedNumberOfPlayers,
						selectedDifficulty);
				return state;
			}
			else if (SM->col(mXH, mYH) && keyDown == "MOUSEBUTTONDOWN")
			{
				*difficulty = 'M';
				selectedDifficulty = SM;
				win->setBackground(8);
				win->drawLineUnder(selectedMode, selectedNumberOfPlayers,
						selectedDifficulty);
				return state;
			}
			else if (SH->col(mXH, mYH) && keyDown == "MOUSEBUTTONDOWN")
			{
				*difficulty = 'H';
				selectedDifficulty = SH;
				win->setBackground(8);
				win->drawLineUnder(selectedMode, selectedNumberOfPlayers,
						selectedDifficulty);
				return state;
			}
			else
			{
				win->setBackground(8);
				win->drawLineUnder(selectedMode, selectedNumberOfPlayers,
						selectedDifficulty);
				return state;
			}
			break;
		case 'G':
			if (back->col(mXH, mYH))
			{
				win->setBackground(13);
				if (keyDown == "MOUSEBUTTONDOWN")
					return 'B';
			}
			else if (keyDown!="")
			{
					return 'E';
			}
			else
			{
				win->setBackground(12);
				return state;
			}
			break;
		case 'V':
			if (back->col(mXH, mYH))
			{
				win->setBackground(11);
				if (keyDown == "MOUSEBUTTONDOWN")
					return 'B';
			}
			else if (keyDown!="")
			{
				return 'C';
			}
			else
			{
				win->setBackground(10);
				return state;
			}
			break;
		case 'A':
			if (back->col(mXH, mYH))
			{
				win->setBackground(15);
				if (keyDown == "MOUSEBUTTONDOWN")
					state = 'B';
			}
			else
			{
				win->setBackground(14);
				return state;
			}
			break;
	}
	return state;
}

