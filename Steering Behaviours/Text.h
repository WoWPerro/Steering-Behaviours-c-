#pragma once
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL.h"
#include <string>
#include "Platform.h"

class Text
{
public:
	Text(const std::string& font_path, int font_size, std::string message_text, const SDL_Color& color);

	void Display(int x, int y);

	static SDL_Texture* LoadFont(const std::string& font_path, int font_size, std::string message_text, const SDL_Color& color);
	void Update(std::string message_text);
	~Text();

private:
	SDL_Texture* _text_texture = nullptr;
	mutable SDL_Rect _text_rect;
	std::string message;
	std::string _font_path;
	int _font_size;
	SDL_Color _color;
};
