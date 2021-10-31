/*
 * Author: Dennis Lövkvist
 * Version: 1.0 (2021-05-12)
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;


int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game Of Life Shader");
	sf::Shader shader_game_of_life;
	shader_game_of_life.loadFromFile("shader_game_of_life.frag", sf::Shader::Fragment);

	sf::Texture tex_input;
	tex_input.loadFromFile("input.jpg");

	sf::Sprite sprite_input;
	sprite_input.setTexture(tex_input);

	sf::RenderTexture textures[2];
	textures[0].create(SCREEN_WIDTH, SCREEN_HEIGHT);
	textures[1].create(SCREEN_WIDTH, SCREEN_HEIGHT);
	textures[0].draw(sprite_input);

	sf::Sprite sprites[2];

	sprites[0].setTexture(textures[0].getTexture());
	sprites[1].setTexture(textures[1].getTexture());


    sf::RenderTexture final_textures[2];
	final_textures[0].create(SCREEN_WIDTH, SCREEN_HEIGHT);
	final_textures[1].create(SCREEN_WIDTH, SCREEN_HEIGHT);

	sf::Sprite final_sprites[2];
	final_sprites[0].setTexture(final_textures[0].getTexture());
	final_sprites[1].setTexture(final_textures[1].getTexture());

	final_textures[0].clear(sf::Color::Black);
    final_textures[1].clear(sf::Color::Black);


	sf::Clock clock;
	float dt = 1.f / 12.f;
	float accumulator = 0.f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		while (accumulator >= dt)
		{
			accumulator -= dt;

			textures[1].clear(sf::Color::Transparent);
			shader_game_of_life.setUniform("screen_width", SCREEN_WIDTH);
            shader_game_of_life.setUniform("screen_height", SCREEN_HEIGHT);
            shader_game_of_life.setUniform("tex_input", textures[0].getTexture());
            textures[1].draw(sprites[0], &shader_game_of_life);

            textures[0].draw(sprites[1]);

            window.clear(sf::Color::Black);
            window.draw(sprites[0]);
            window.display();
		}

		accumulator += clock.getElapsedTime().asSeconds();
		clock.restart();

	}

	return 0;
}
