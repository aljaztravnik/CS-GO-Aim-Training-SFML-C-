#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <unistd.h>
#include <sstream>

//std::cout << "Program tece: " << int_ms.count() << " milisekund\n";

int setTime(auto);

int main()
{
	int width = 800;
	int height = 600;
	int hit = 1;
	int size = 50;
	float posX, posY;
	int count = 0;
	int countMax = 0;

	sf::Vector2i mousePos;
	sf::RenderWindow window(sf::VideoMode(width, height), "Aim Training", sf::Style::Close | sf::Style::Resize);
	sf::RectangleShape hitbox;
	hitbox.setSize(sf::Vector2f(size, size));
	hitbox.setPosition(size/2, size/2);
	hitbox.setOrigin(size/2, size/2);

	sf::Font font;
	sf::Text countdown;
	sf::Text highscore;
	sf::Text score;
	font.loadFromFile("ARIAL.TTF");
	if(!font.loadFromFile("ARIAL.TTF")) std::cout << "Could not load font file.\n";
	countdown.setFont(font);
	countdown.setCharacterSize(20);
	countdown.setFillColor(sf::Color::Red);
	countdown.setStyle(sf::Text::Bold);
	countdown.setPosition(20, 10);
	score.setFont(font);
	score.setCharacterSize(20);
	score.setFillColor(sf::Color::Green);
	score.setStyle(sf::Text::Bold);
	score.setPosition(220, 10);
	highscore.setFont(font);
	highscore.setCharacterSize(20);
	highscore.setFillColor(sf::Color::White);
	highscore.setStyle(sf::Text::Bold);
	highscore.setPosition(420, 10);
	auto t1 = std::chrono::high_resolution_clock::now();
	auto t2 = std::chrono::high_resolution_clock::now();
	auto intms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	auto tImE = 0;
	unsigned int sleepFor = 30000;

	/*sf::Texture playerTexture;
	playerTexture.loadFromFile("nekej.jpeg");
	player.setTexture(&playerTexture);
	player.setFillColor(sf::Color::Red);
	player.setOrigin(50.0f, 50.0f);*/
 
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
			}
		}
		if(hit == 1)
		{
			tImE = setTime(t1);
			if(tImE < 0)
			{
				countMax = (count > countMax) ? count : countMax;
				count = 0;
				t1 = std::chrono::high_resolution_clock::now();
			}
			srand(time(NULL));
			size = (rand() % 40 + 20);
			posX = (rand() % (width-size) + 1);
			posY = (rand() % (height-size) + 1);
			hitbox.setOrigin(size/2, size/2);
			hitbox.setSize(sf::Vector2f(size, size));
			hitbox.setPosition(posX, posY);
			hit = 0;
		}
		else
		{
			tImE = setTime(t1);
			if(tImE < 0)
			{
				countMax = (count > countMax) ? count : countMax;
				count = 0;
				t1 = std::chrono::high_resolution_clock::now();
			}
			else if (hitbox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    		{
    			hit = 1;
    			count++;
    		}
		}

		std::stringstream sa;
        sa << tImE;
        countdown.setString(sa.str());
		
		std::stringstream sb;
        sb << count;
        score.setString(sb.str());

        std::stringstream sc;
        sc << countMax;
        highscore.setString(sc.str());

		window.clear();
		window.draw(hitbox);
		window.draw(countdown);
		window.draw(score);
		window.draw(highscore);
		window.display();
		usleep(sleepFor); //microseconds
	}

	return 0;
}

int setTime(auto x1)
{
	auto x2 = std::chrono::high_resolution_clock::now();
	auto razlikaMillis = std::chrono::duration_cast<std::chrono::milliseconds>(x2 - x1);
	int zeit = 10 - (razlikaMillis.count() / 1000);
	return zeit;
}