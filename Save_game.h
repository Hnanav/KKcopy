#pragma once

#include "CommonFunction.h"
#include "Player.h"
#include "OtherObj.h"

class Save_game{
public:
    int load_files (int&lv);
    void clean_up(int lv);
};
