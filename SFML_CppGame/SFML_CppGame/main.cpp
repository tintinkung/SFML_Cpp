#include <iostream>
#include "Game.h"

/*  --- ORG Include path ---
 * 
 *  #include "../External/include/SFML/Graphics.hpp"
 *  #include "../External/include/SFML/System.hpp"
 *  #include "../External/include/SFML/Window.hpp"
 *  #include "../External/include/SFML/Audio.hpp"
 *  #include "../External/include/SFML/Network.hpp"
 * 
 --- contained string reference of main.cpp: 
 * "../SFML_CppGame/SML_CppGame/SFML_CppGame.vcxproj", 
 * "../SFML_CppGame/SML_CppGame/SFML_CppGame.vcxproj.filters"
 */ 

/// <summary>
/// main.cpp : 
/// This file contains the 'main' function. Program execution begins and ends there.
/// </summary>
/// <returns>0</returns>
int main()
{
    // --- Initialize srand ---
    srand(static_cast<unsigned>(time(NULL)));

    // --- Init Game Engine ---
    Game game;



    // --- MAIN GAME LOOP ---
    /*
     * Main Game Loop goes here.
     * As long as render window is open, game loop is on.
     * basically Unity Update() function.
     */
    while (game.running()/* && !game.gameIsEnded() */)
    {
        // --- Update ---
        game.update();

        // --- Render ---
        game.render();
        
    }

    // === End of Application. ===
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
