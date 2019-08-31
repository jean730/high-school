#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <ctime>
#include <fstream>
#include <X11/Xlib.h>
#include <math.h>
#include "map.cpp"
#include "misc.cpp"
#include "personnage.cpp"
#include "physics.cpp"
#include "menu.cpp"
#include "render.cpp"
using namespace sf;





int main(int argc, char** argv)
{
    XInitThreads();

    Keyboard keyboard;
    int winw = VideoMode::getDesktopMode().width;
    int winh = VideoMode::getDesktopMode().height;
    int sprix;
    int spriy;
    bool editor = false;
    int compteur = 0;
    int selected = 65;
    int state = 1;
    string cartes[100];
    string nomcartes[100];
    int carte = 0;
    int nombrecartes = 0;
    int reste = 1;
    ifstream fluxi("maps/maps.list");
    while (reste == 1) {
        getline(fluxi, cartes[nombrecartes]);
        if (cartes[nombrecartes] == "") {
            reste = 0;
        }
        else {
            nombrecartes++;
        }
    }
    for (reste = 0; reste < nombrecartes; reste++) {
        ifstream fluxi(cartes[reste]);
        getline(fluxi, nomcartes[reste]);
        std::cout << nomcartes[reste] << " => " << cartes[reste] << "\n";
    }
    int inMenu = 1;
    sf::Font font;
    font.loadFromFile("Fonts/font.ttf");
    Text menu;
    menu.setFont(font);
    menu.setCharacterSize(winh/ 15);

    menu.setFillColor(Color(200, 200, 200));
    menu.setString("Pieces " + std::to_string(compteur));
    menu.setOutlineThickness(4);
    RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(winw/3, winh/15));
    rectangle.setPosition(10, 20);
    RenderWindow jeu(VideoMode(winw, winh, 64), "jeu", Style::Fullscreen);
    View view = jeu.getDefaultView();
    jeu.setFramerateLimit(60);
    bool Open = true;
    while (jeu.isOpen() && inMenu == 1) {
        Event event;
        while (jeu.pollEvent(event)) {

            if (event.type == Event::KeyPressed && keyboard.isKeyPressed(Keyboard::Key::Return)) {
                if (carte >= 0) {
                    inMenu = 0;
                }
                else {
                    jeu.close();
                }
            }
            if (event.type == Event::KeyPressed && keyboard.isKeyPressed(Keyboard::Key::Up)) {
                if (carte > -1) {
                    carte--;
                }
                else {
                    carte = nombrecartes - 1;
                }
            }
            if (event.type == Event::KeyPressed && keyboard.isKeyPressed(Keyboard::Key::Down)) {
                if (carte < nombrecartes - 1) {
                    carte++;
                }
                else {
                    carte = -1;
                }
            }
        }
        jeu.clear(Color(40, 20, 45));
            rectangle.setOrigin(rectangle.getLocalBounds().width / 2, 0);
            rectangle.setPosition(winw / 2,0);
            rectangle.setFillColor(Color(40, 40, 70));
            rectangle.setSize(sf::Vector2f(winw/3, winh));
            jeu.draw(rectangle);
            rectangle.setSize(sf::Vector2f(winw/3, winh/15));
        for (int i = -1; i < nombrecartes; i++) {
            if (i == carte) {
                menu.setFillColor(Color(200, 200, 200));
                menu.setOutlineColor(Color(50, 50, 50));
                rectangle.setFillColor(Color(20, 20, 70));
            }
            else {
                menu.setFillColor(Color(240, 240, 20));
                menu.setOutlineColor(Color(20, 50, 250));
                rectangle.setFillColor(Color(20, 20, 20));
            }
            if (i >= 0) {
                menu.setString(nomcartes[i]);
            }
            else if (i == -1) {
                menu.setString("quitter");
            }
            rectangle.setOrigin(rectangle.getLocalBounds().width / 2, rectangle.getLocalBounds().height / 2);
            rectangle.setPosition(winw / 2,  winh / 2 + (i - carte) * 50 * winh/600 +12*winh/768);
            menu.setOrigin(menu.getLocalBounds().width / 2, menu.getLocalBounds().height / 2);
            menu.setPosition(winw / 2,  winh / 2 + (i - carte) * 50 * winh/600);
            jeu.draw(rectangle);
            jeu.draw(menu);

        }

        jeu.display();
    }

    if (jeu.isOpen()) {

        Map1 map(cartes[carte]);
        int spriw = map.tileWidth * map.scale;
        int sprih = map.tileHeight * map.scale;
        int wsh = winh - sprih;
        Mouse mouse;
        Perso perso;
        perso.setspawn(map.spawnx,map.spawny);
        perso.respawn(spriw, sprih, winh);
        Texture persotex;
        persotex.loadFromFile(perso.sprite);
        Sprite persosprite(persotex);
        persosprite.setScale(perso.scale, perso.scale);
        persosprite.setOrigin(perso.xSize / 2, perso.ySize / 2);
        Image tileset;
        tileset.loadFromFile(map.TileSet);
        Texture tex;
        tex.loadFromImage(tileset, tileRect(0, state));
        Sprite tiles(tex);
        Music coin;
        coin.openFromFile("Sounds/coin.wav");
        Music jump;
        jump.openFromFile("Sounds/jump.wav");
        Music diesound;
        diesound.openFromFile("Sounds/die.wav");
        tiles.setScale(map.scale, map.scale);

        Text score;
        score.setFont(font);
        score.setCharacterSize(winw / 20);
        score.setPosition(20, 50);
        score.setFillColor(Color(255, 255, 50));
        score.setString("Pieces " + std::to_string(compteur));
        jeu.setActive(false);
        std::thread th1(physics, std::ref(perso), std::ref(Open), std::ref(map), winh,
            std::ref(state), std::ref(compteur), std::ref(coin),
            std::ref(jump), std::ref(diesound), std::ref(selected), winw, std::ref(inMenu), std::ref(editor),std::ref(persosprite), std::ref(carte), nombrecartes, cartes,std::ref(mouse),std::ref(jeu),std::ref(keyboard));
        th1.detach();
        
   
        std::thread rend(render, std::ref(perso), std::ref(Open),std::ref(map), winh,std::ref(state),
    std::ref(compteur), std::ref(selected),
    winw,std::ref(inMenu),std::ref(editor),std::ref(persosprite),std::ref(jeu),std::ref(view),std::ref(tex),std::ref(score),std::ref(tiles),std::ref(tileset),std::ref(carte),nomcartes,nombrecartes,std::ref(menu),std::ref(rectangle));
        rend.detach();
        int mx;
        int my;
        carte = -1;
        while (jeu.isOpen()) {


            if (inMenu == 1) {
                menuInGameevent(std::ref(jeu),nombrecartes,cartes,std::ref(carte),std::ref(keyboard),std::ref(editor),std::ref(map),compteur,std::ref(inMenu),std::ref(perso),spriw,sprih,winh);
            }
            if(inMenu==0){
                
                
                Event event;
                while (jeu.pollEvent(event)) {

                    if (event.type == Event::Closed || keyboard.isKeyPressed(Keyboard::Key::Escape)) {
                        inMenu = 1;
                    }

                    if (event.type == Event::KeyPressed && keyboard.isKeyPressed(Keyboard::Key::J)) {
                        if(editor){
                        printMap(map);
                        }
                        map.set(map.mapFile);
                        
                        editor = !editor;


                    }
                    if (editor) {

                        mx = perso.x + sf::Mouse::getPosition().x - winw / 2;
                        my = sf::Mouse::getPosition().y;
                        if (mouse.isButtonPressed(Mouse::Button::Middle)) {

                            for (int i = 0; i < map.Lines; i++) {
                                for (int j = 0; j < map.Columns; j++) {
                                    sprix = spriw * j;
                                    spriy = wsh - sprih * (map.Lines - 1 - i);
                                    if (collide(sprix, spriy, spriw, sprih, mx, my, 1, 1)) {

                                        map.mapCollide[i][j] = !map.mapCollide[i][j];
                                    }
                                }
                            }
                        }
                        if (mouse.isButtonPressed(Mouse::Button::Left)) {

                            for (int i = 0; i < map.Lines; i++) {
                                for (int j = 0; j < map.Columns; j++) {
                                    sprix = spriw * j;
                                    spriy = wsh - sprih * (map.Lines - 1 - i);
                                    if (collide(sprix, spriy, spriw, sprih, mx, my, 1, 1)) {


                                            map.map[i][j] = selected;
                                            if(selected!=65){
                                            map.mapCollide[i][j] = 1;
                                            }
                                            else{
                                            map.mapCollide[i][j] = 0;
                                            }
                                            
                                            
                                    }
                                }
                            }
                        }

                        if (mouse.isButtonPressed(Mouse::Button::Right)) {
                            for (int i = 0; i < map.Lines; i++) {
                                for (int j = 0; j < map.Columns; j++) {
                                    sprix = spriw * j;
                                    spriy = wsh - sprih * (map.Lines - 1 - i);
                                    if (collide(sprix, spriy, spriw, sprih, mx, my, 1, 1)) {
                                        map.map[i][j] = 34;

                                        map.mapCollide[i][j] = 0;
                                    }
                                }
                            }
                        }

                        if (event.type == Event::KeyPressed && keyboard.isKeyPressed(Keyboard::Key::Left)) {
                            selected--;
                            if (selected == -1) {
                                selected = 65;
                            };
                        }
                        if (event.type == Event::KeyPressed && keyboard.isKeyPressed(Keyboard::Key::Right)) {
                            selected++;
                            if (selected == 66) {
                                selected = 0;
                            };
                        }
                    }
                }

              
            }
        }
    }
    Open = false;
    return 0;
}
