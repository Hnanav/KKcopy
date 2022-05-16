
#pragma once
#include "CommonFunction.h"
#include "BaseObj.h"
#inclue "Player.h"

class magicBox : public Player
{
public:
    magicBox();
    ~magicBox();
    bool LoadImg(string path, SDL_Renderer* renderer);
	void show(SDL_Renderer* des);
	void handleEvent1(SDL_Event e, SDL_Renderer* renderer,Mix_Chunk* sound[5]);
	void setclip();

	void DoPlayer(Map& mapdata);

	void CheckToMap(Map& mapdata);

	void CheckToPlayer();

private:
	float xval;
	float yval;

	float xpos;
	float ypos;

	int widthframe;
	int heightframe;

	SDL_Rect FRAME_;

	Input input_type;
};
