#include "Player.h"
#include "OtherObj.h"
Player::Player()
{
	frame = 0;
	xpos = 332;
	ypos = 664;
	xval = 0;
	yval = 0;
	widthframe = 0;
	heightframe = 0;
	status = -1;
	onground = false;
	input_type.left = 0;
	input_type.right = 0;
	input_type.stayleft = 0;
	input_type.stayright = 0;
	input_type.jump = 0;
	pinkfishcount = 0;
}
Player::~Player() {
	Free();
}
bool Player::LoadImg(string path, SDL_Renderer* renderer) {
	bool check = BaseObj::LoadImg(path, renderer);

	if (check == true) {
		widthframe = 24;
		heightframe = 24;
	}
	return check;
}

void Player::show1(SDL_Renderer* des) {
	rect.x = xpos;
	rect.y = ypos;
	SDL_Rect renderQuad = {rect.x,rect.y,widthframe*3,heightframe*3 };

	if (currentclip != NULL)
	{
		renderQuad.w = 3*currentclip->w;
		renderQuad.h = 3*currentclip->h;
	}
	SDL_RenderCopy(des, texture, currentclip, &renderQuad);
}

void Player::handleEvent1(SDL_Event e,SDL_Renderer* renderer,Mix_Chunk* sound[5]) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_d:
			status = WALK_RIGHT;
			input_type.stayleft = 0;
			input_type.stayright = 0;
			input_type.right = 1;
			input_type.left = 0;

			UpdateImgPlayer1(renderer);
			break;

		case SDLK_a:
			status = WALK_LEFT;
			input_type.stayleft = 0;
			input_type.stayright = 0;
			input_type.left = 1;
			input_type.right = 0;

			UpdateImgPlayer1(renderer);

			break;
		case SDLK_w:
			status = JUMP;
			if (onground) {
				Mix_PlayChannel(-1, sound[0], 0);
				input_type.jump = 1;
				input_type.stayleft = 0;
				input_type.stayright = 0;
			}
			break;
		default:

			break;
		}
	}
	else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_d:
			status = STAY_RIGHT;
			if (onground == true) {
				input_type.stayright = 1;
				input_type.right = 0;
				input_type.stayleft = 0;
			}
			input_type.right = 0;
			input_type.stayleft = 0;

			UpdateImgPlayer1(renderer);

			break;
		case SDLK_a:
			status = STAY_LEFT;
			if (onground == true) {
				input_type.stayleft = 1;
				input_type.left = 0;
				input_type.stayright = 0;
			}
			input_type.left = 0;
			input_type.stayright = 0;

			UpdateImgPlayer1(renderer);

			break;
		default:
			break;
		}
	}
}
void Player::handleEvent2(SDL_Event e, SDL_Renderer* renderer, Mix_Chunk* sound[5])
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			status = WALK_RIGHT;
			input_type.stayleft = 0;
			input_type.stayright = 0;
			input_type.right = 1;
			input_type.left = 0;

			UpdateImgPlayer2(renderer);
			break;

		case SDLK_LEFT:
			status = WALK_LEFT;
			input_type.stayleft = 0;
			input_type.stayright = 0;
			input_type.left = 1;
			input_type.right = 0;

			UpdateImgPlayer2(renderer);

			break;
		case SDLK_UP:
			if (onground) {
				Mix_PlayChannel(-1, sound[0], 0);
				input_type.jump = 1;
				input_type.stayleft = 0;
				input_type.stayright = 0;
			}
			break;
		default:
			break;
		}
	}
	else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			status = STAY_RIGHT;
			if (onground == true) {
				input_type.stayright = 1;
				input_type.right = 0;
				input_type.stayleft = 0;
			}
			input_type.right = 0;
			input_type.stayleft = 0;

			UpdateImgPlayer2(renderer);

			break;
		case SDLK_LEFT:
			status = STAY_LEFT;
			if (onground == true) {
				input_type.stayleft = 1;
				input_type.left = 0;
				input_type.stayright = 0;
			}
			input_type.left = 0;
			input_type.stayright = 0;

			UpdateImgPlayer2(renderer);

			break;
		default:
			break;
		}
	}
}
void magicBox::DoPlayer(Map& mapdata) {
	xval = 0;
	yval += GRAVITY_SPEED;

	if (yval >= MAX_FALL_SPEED) {
		yval = MAX_FALL_SPEED;
	}
	if (input_type.left == 1) {
		xval -= PLAYER_SPEED;
	}
	if (input_type.right == 1) {
		xval += PLAYER_SPEED;
	}
	if (input_type.jump == 1) {
		if (onground==true) {
			yval -= JUMP_VAL;
		}
		onground = false;

		input_type.jump = 0;
	}

	CheckToMap(mapdata);

}
void Player::CheckToMap(Map& mapdata) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;


	//check horizontal
	int height_min = (heightframe * 3 < TILE_SIZE ? heightframe * 3 : TILE_SIZE);

	x1 = (xpos+xval+10)/TILE_SIZE;
	x2 = (xpos + xval + widthframe*3 -10)/ TILE_SIZE;

	y1 = (ypos+30) / TILE_SIZE;
	y2 = (ypos + height_min +20) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (xval > 0) {

			if (mapdata.tile[y1][x2] == PINK_FISH) {
				mapdata.tile[y1][x2] = 0;
				IncreasePowerPlayer1();
			}
			else if (mapdata.tile[y2][x2] == PINK_FISH) {
				mapdata.tile[y2][x2] = 0;
				IncreasePowerPlayer1();
			}

			else {
				if ((mapdata.tile[y1][x2] != BLANK_TILE || mapdata.tile[y2][x2] != BLANK_TILE)) {
					xpos = (x2)*TILE_SIZE;
					xpos -= widthframe * 3 - 10;
					xval = 0;
				}
			}
		}
		else if (xval < 0) {

			if (mapdata.tile[y2][x1] == PINK_FISH) {
				mapdata.tile[y2][x1] = 0;
				IncreasePowerPlayer1();
			}
			else if (mapdata.tile[y1][x1] == PINK_FISH) {
				mapdata.tile[y1][x1] = 0;
				IncreasePowerPlayer1();
			}
			else {
				if (mapdata.tile[y1][x1] != BLANK_TILE || mapdata.tile[y2][x1] != BLANK_TILE) {
					xpos = (x1)*TILE_SIZE + 20;
					xval = 0;
				}
			}
		}
	}
	//check vertical
	int width_min = widthframe*3< TILE_SIZE ? widthframe*3 : TILE_SIZE;
	x1 = (xpos+25) / TILE_SIZE;
	x2 = (xpos + width_min+40) / TILE_SIZE;

	y1 = (ypos + yval) / TILE_SIZE;
	y2 = (ypos + yval + heightframe*3 -17) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (yval > 0) {
			if (mapdata.tile[y2][x2] == PINK_FISH) {
				mapdata.tile[y2][x2] = 0;
				IncreasePowerPlayer1();
			}
			else if (mapdata.tile[y2][x1] == PINK_FISH) {
				mapdata.tile[y2][x1] = 0;
				IncreasePowerPlayer1();
			}
			else {
				if (mapdata.tile[y2][x1] != BLANK_TILE || mapdata.tile[y2][x2] != BLANK_TILE) {
					ypos = y2 * TILE_SIZE;
					ypos -= heightframe * 3 - 17;
					yval = 0;
					onground = true;
				}
			}
		}
		else if (yval < 0) {

			if (mapdata.tile[y1][x2] == PINK_FISH) {
				mapdata.tile[y1][x2] = 0;
				IncreasePowerPlayer1();
			}
			else if (mapdata.tile[y1][x1] == PINK_FISH) {
				mapdata.tile[y1][x1] = 0;
				IncreasePowerPlayer1();
			}
			else{
			if (mapdata.tile[y1][x1] != BLANK_TILE || mapdata.tile[y1][x2] != BLANK_TILE) {
				ypos = (y1)*TILE_SIZE+5;
				yval = 0;
				}
			}
		}
	}


	xpos += xval;
	ypos += yval;
	if (xpos < 0) {
		xpos = 0;
	}
	else if ((xpos + widthframe*3) > mapdata.maxx) {
		xpos = mapdata.maxx - widthframe*3 -1;
	}

	if (ypos < 0) {
		ypos = 0;
	}

}

void Player::IncreasePowerPlayer1() {
	pinkfishcount++;
}
