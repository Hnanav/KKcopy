#pragma once
#include "CommonFunction.h"
#include "BaseObj.h"



class Mushroom : public BaseObj
{
public:
	Mushroom();
	~Mushroom();
	bool LoadImg(string path, SDL_Renderer* renderer);
	void show(SDL_Renderer* des);
	void getNum(int _n);
	void setclip();

private:
	float xval;
	float yval;
	float xpos;
	float ypos;
	int widthframe;
	int heightframe;
	SDL_Rect FRAME_CLIP[5];
	int frame;
	int n ;

};


