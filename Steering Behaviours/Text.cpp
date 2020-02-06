#include "Text.h"
#include <iostream>
#include <fstream> 
#include <exception>


Text::Text(const std::string& font_path, int font_size, std::string message_text, const SDL_Color& color)
{
	TTF_Init();
	//printf("TTF_OpenFont: %s\n", TTF_GetError());
	message = message_text;
	_font_path = font_path;
	_font_size = font_size;
	_color = color;
	_text_texture = LoadFont(font_path, font_size, message, color);
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
}

void Text::Display(int x, int y)
{
	_text_rect.x = x;
	_text_rect.y = y;
	SDL_RenderCopy(Platform::renderer, _text_texture, nullptr, &_text_rect);
}

SDL_Texture* Text::LoadFont(const std::string& font_path, int font_size, std::string message_text, const SDL_Color& color)
{
	TTF_Font* font = NULL;
	try
	{
		font = TTF_OpenFont(font_path.c_str(), font_size);
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << '\n';
	}
	if (!font)
	{
		std::cerr << "failed to load font \n";
	}

	auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
	if (!text_surface)
	{
		std::cerr << "failed to create text surface\n";
	}
	auto text_texture = SDL_CreateTextureFromSurface(Platform::renderer, text_surface);
	if (!text_texture)
	{
		std::cerr << "Failed to create text texture\n";
	}

	TTF_CloseFont(font);
	font = NULL;
	SDL_FreeSurface(text_surface);
	return text_texture;
}

void Text::Update(std::string message_text)
{
	message = message_text;
	_text_texture = LoadFont(_font_path, _font_size, message, _color);
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
}

Text::~Text()
{
}