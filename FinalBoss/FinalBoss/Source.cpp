/*Program by Eric Ashford*/

#include <iostream>
#include <string>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <ctime>			//time()
#include <cstdlib>			//srand() and rand()
#include <SFML/Audio.hpp>
#include <stdio.h>
#include "Source.h"


using namespace std;



char* Color(int color = 7, char* Message = "") {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);			//http://www.cplusplus.com/forum/beginner/77879/
	return Message;
}




#pragma region Colors
		/*  1: Blue
			2 : Green
			3 : Cyan
			4 : Red
			5 : Purple
			6 : Yellow(Dark)
			7 : Default white
			8 : Gray / Grey
			9 : Bright blue
			10 : Bright green
			11 : Bright cyan
			12 : Bright red
			13 : Pink / Magenta
			14 : Yellow
			15 : Bright white
		*/
#pragma endregion


#pragma region Player Data

class Player
{
public:
	string PName;
	int PHp;
	void AttackMenu(int Energy);
	int Energy;
};


void Player::AttackMenu(int Energy)
{	

	cout << Color(11, "\nSelect an action from below! You have 100 energy.") << endl;
	cout << "1) Slash	  - deals 25 damage. 50% chance double slash! -25 energy." << endl; 
	cout << "2) OverHead Slash - deals 75 damage. 20% chance of crit. -50 energy. " << endl;
	cout << "3) Parry	  - Chance to negate all damage. Depletes remaining energy." << endl;
	cout << "4) Recover	  - Recover 50 hp. -50 energy." << endl;
	cout << "5) Unleash   - Go all out... Requires 100 fury. -100 energy & fury!" << endl;

};
#pragma endregion

#pragma region Boss Data

class Boss
{
public:
	string BName;
	//string BWep = "Greatsword";
	int BossHp;
};

#pragma endregion




int main(Player P, Boss B)
{
	B.BName = "Dark Lord";

	srand(time(NULL));
	cout << Color(11,"=======================================================================================================================\n=======================================================================================================================\n") << endl;
	cout << "                                                    Boss Battle\n                                            Text Based Battle Simulator\n                                  oo()xxxx[{::::::::::::::::::::::::::::::::::>\n" << endl;
	cout << "=======================================================================================================================\n=======================================================================================================================" << endl;
	cout << "What is your name?" << endl;
	cin >> P.PName;
	cout << endl;
	cout << "\nBase Stats\n-------------- \nName: " << P.PName << " \nClass: Infinity Blade \nAttack:  ??? \nDefense: ??? \n\nHp: 300 \nMax Energy: 100\n\n" << endl;
	Sleep(500);
	cout << "Loading . . ." << endl;
	Sleep(300);
	cout << "Incoming threat. . ."<< endl;

	sf::SoundBuffer buffer;
	buffer.loadFromFile("Duel.WAV");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	Sleep(3000);

	buffer.loadFromFile("BossIntro.wav");
	sound.play();

	cout << Color(4,"") << B.BName << " approaches into the arena.\nBoss Hp: 1000 \nPower Level : Lol what?" <<endl;
	Sleep(5000);


	sf::Music music;
	music.openFromFile("Unc.wav");
	music.play();


retry:
	
	P.PHp = 400;
	P.Energy = 100;
	int Fury = 0;
	int hits = 0;
	B.BossHp = 1000;
	bool isBlocking;
	int choice;

	do
	{
#pragma region Player Phase

		P.AttackMenu(P.Energy);
		buffer.loadFromFile("Go.wav");
		sound.play();
		do {
			
			
			int x;
			cout << P.Energy << Color(3, " energy remains. ") << Fury << " fury.\nHp Remaining: " << P.PHp << endl << endl;
			cin >> choice;
			switch (choice) {
				
			case 1: cout << endl << P.PName << " attacks " << B.BName << " with slash! +5 fury." << endl; P.Energy = P.Energy - 25;
				x = (1 + rand() % 2) * 25;
				B.BossHp = B.BossHp - x;
				if (x <= 25) { cout << B.BName << " has " << B.BossHp << " hp remaining." << endl; Fury = Fury + 5; buffer.loadFromFile("Hit.wav"); sound.play();}
				else { cout << "DOUBLE SLASH! +5 Bonus fury! \n" << B.BName << " has " << B.BossHp << " hp remaining." << endl; Fury = Fury + 10; buffer.loadFromFile("Attack1.wav");	sound.play();}
				isBlocking = false;
				break;

			case 2: cout << P.PName << " attacks " << B.BName << " dealing 75 damage! ";
				x = (1 + rand() % 3);
				P.Energy = P.Energy - 50;
				buffer.loadFromFile("OverHit.wav");
				sound.setPitch(0.7f);
				sound.play();
				sound.setPitch(1.0f);
				if (x <= 75) {  cout << B.BName << " has " << B.BossHp << " hp remaining." << endl; Fury = Fury + 10; B.BossHp = B.BossHp - 75;
				}
				else { cout << "Critical Hit! " << B.BName << " has " << B.BossHp << " hp remaining." << endl; Fury = Fury + 30; B.BossHp = B.BossHp - 150;
				}
				isBlocking = false;
				break;

			case 3: cout << P.PName << " attempts to parry " << B.BName << "'s next attack." << endl;
				x = ((rand() %2));
				P.Energy = 0;
				if (x >= 1) 
				{ isBlocking = true; }
				else { isBlocking = false; }
				break;

			case 4: cout << P.PName << " begins to bandage their wounds " << endl;
				if (P.Energy >= 50)
				{
					cout << P.PName << " heals for 50 hp. " << P.PHp << " remains." << endl;
					x = (1 + (rand() % 3));
					if (x < 1) { buffer.loadFromFile("Heal.wav"); }
					else { buffer.loadFromFile("Heal2.wav"); }
					sound.play();
					P.PHp = P.PHp + 50;
					P.Energy = P.Energy - 50;
					isBlocking = false;
				}
				else { cout << "Not enough energy. Select another Action." << endl; }
				break;

				case 5: cout << "Activating Unleash Mode... " << endl;
					if (P.Energy == 100 && Fury >= 100)
					{
						buffer.loadFromFile("AllOut.wav");
						sound.setPitch(0.8f);
						sound.play();
						Sleep(2500);
						cout << " Go all out! Mash X as fast as you can!" << endl;
						sound.setPitch(1.0f);
						sound.play();
						Sleep(2000);
						do
						{
							buffer.loadFromFile("Hit.wav");
							sound.play();
							Sleep(0100);
							x = _getch();
							x = tolower(x);
							Fury = Fury - 1;
							hits = hits + 1;
							
						}while ( Fury > 25 );
						cout << "You attacked "<< hits << " times." << endl;
						x = (hits * 6);
						B.BossHp = B.BossHp - x; P.Energy = P.Energy - 100;
						cout << B.BName << " has taken " << x << " damage!\n" << endl;
						Fury = 0;
						isBlocking = true;
					}
					else { cout << "Cannot Unleash..."; }
					break;
			}

		} while (P.Energy > 0);
#pragma endregion
#pragma region Boss Phase



		if (isBlocking == true)
		{
			cout << P.PName << " parries " << B.BName << " attack."<< endl;
			buffer.loadFromFile("Collide.wav");
			sound.play();
			Sleep(2000);
		}
		else {
			cout << "\n" << B.BName << Color(4, " attacks, dealing 100 dmg.\n") << endl;
			buffer.loadFromFile("Damaged.Wav");
			sound.play();
			P.PHp = P.PHp - 100;
			Sleep(2000);
		}
		P.Energy= P.Energy + 100;
#pragma endregion
	} while (P.PHp > 0 && B.BossHp > 0 );

#pragma region Endings


	if (B.BossHp <= 0)
	{
		music.stop();
		cout << P.PName << " beat " << B.BName << "! Sadly this was only phase 1 to the fight. But " << P.PName << " WINS!!!!\n \n\n\nTo Be Continued..." << endl;
		buffer.loadFromFile("Win.wav");
		sound.play();
	}
	else if (P.PHp <= 0)
	{
		string choice;

		cout << "The brave hero has failed." << endl;
		cout << "Would you like to retry?" << endl;
		cin >> choice;
		if (choice == "yes")
		{
			system("cls");
			goto retry;
		}
		else
		{
			return 0;
		}
	}

#pragma endregion

	int e;
	cin >> e;
	return 0;
}