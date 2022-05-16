#include "Save_game.h"
#include "Player.h"
using namespace std;

int Save_game::load_files (int &lv)
{
    // Open a file for reading
    std::ifstream load ("game_save.txt");

    //If the file loaded
    if(load )
    {

    //Set the position
        load >> lv;

        //Skip past the end of line
        load.ignore();

        //Get the next line
     //   getline(load, level_name);

        //If an error occurred while trying to read the data
        if( load.fail() == true )
        {
            return false;
        }

        //Close the file
        load.close();
    }
    //If everything loaded successfully
    return lv;
}

void Save_game:: clean_up(int lv)
{
    //Free the surface
   // SDL_FreeSurface(Player1);

    //Open a file for writing
     //std::ofstream save;
    //save.open("game_save.txt", std::ofstream::out | std::ofstream::trunc);
         std::ofstream save ("game_save.txt");
    //Write player's position to the file
    //save << "Player1";
    //save << " ";
    save << lv;
    save << "\n";
    //Close the file
    save.close();

    //Quit SDL
    SDL_Quit();
}


