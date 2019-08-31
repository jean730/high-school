void physics(Perso& perso, bool& open, Map1& map, int winh, int& state,
    int& compteur, Music& coin, Music& jump, Music& diesound, int& selected,
    int winw, int& inMenu, bool& editor, Sprite& persosprite,  int& carte, int nombrecartes, string cartes[],  Mouse& mouse,RenderWindow& jeu, Keyboard& keyboard)
{

    int mode = 0;
    int sprix;
    int spriy;
    int spriw = map.tileWidth * map.scale;
    int sprih = map.tileHeight * map.scale;
            int mx = perso.x + sf::Mouse::getPosition().x - winw / 2;
            int my = sf::Mouse::getPosition().y;
    int wsh = winh - sprih;
    bool Jump = false;
    int counter = 0;

    while (open) {
        if (inMenu == 0) {







            if (keyboard.isKeyPressed(Keyboard::Key::Space) && !Jump && perso.dead == 0) {
                if (perso.yVel >= -10) {
                    if (perso.yVel >= 0) {
                        perso.yVel = 0;
                        jump.play();
                    }
                    perso.yVel -= 1;
                }
                if (perso.yVel <= -10) {
                    Jump = true;
                }
            }
            else {
                perso.yVel += 0.3;
            }
            if (!perso.dead) {

                if (keyboard.isKeyPressed(Keyboard::Key::Q) && keyboard.isKeyPressed(Keyboard::Key::D) && perso.dead == 0) {
                    perso.xVel /= 1.1;
                }
                else if (keyboard.isKeyPressed(Keyboard::Key::D) && perso.dead == 0) {
                    if (perso.xVel <= 10) {
                        perso.xVel += 1;
                    }
                }
                else if (keyboard.isKeyPressed(Keyboard::Key::Q) && perso.dead == 0) {
                    if (perso.xVel >= -10) {
                        perso.xVel -= 1;
                    }
                }

                else {
                    perso.xVel /= 1.1;
                }
                if (keyboard.isKeyPressed(Keyboard::Key::LShift) && perso.dead == 0) {
                    mode = 1;
                }
                else {
                    mode = 0;
                }
                if (keyboard.isKeyPressed(Keyboard::Key::LControl) && perso.dead == 0) {
                    perso.die(std::ref(diesound), winh);
                }

                for (int i = 0; i < map.Lines; i++) {
                    for (int j = 0; j < map.Columns; j++) {
                        sprix = spriw * j;
                        spriy = wsh - sprih * (map.Lines - 1 - i);
                        if (map.mapCollide[i][j] == 1) {
                            if (collide(sprix, spriy, spriw, sprih,
                                    perso.x + perso.xVel - (perso.scale * perso.xSize) / 2,
                                    perso.y - (perso.scale * perso.ySize) / 2,
                                    perso.xSize * perso.scale, perso.ySize * perso.scale)) {
                                perso.xVel = 0;
                            }
                            else if (collide(sprix, spriy, spriw, sprih,
                                         perso.x - (perso.scale * perso.xSize) / 2,
                                         perso.y + perso.yVel - (perso.scale * perso.ySize) / 2,
                                         perso.xSize * perso.scale,
                                         perso.ySize * perso.scale)) {
                                if (perso.yVel > 0) {
                                    Jump = false;
                                }
                                perso.yVel = 0;
                            }
                        }
                        if (!editor) {
                            if (map.map[i][j] == 65 && mode == 0) {
                                if (collide(sprix + spriw / 4, spriy, spriw / 2, sprih,
                                        perso.x + perso.xVel - (perso.scale * perso.xSize) / 2,
                                        perso.y - perso.ySize * perso.scale,
                                        perso.xSize * perso.scale, perso.ySize * perso.scale)) {
                                    map.map[i][j] = 34;
                                    compteur++;
                                    coin.play();
                                }
                            }
                            else if (map.map[i][j] == 34 && mode == 1 && compteur > 0) {
                                if (collide(sprix + spriw / 4, spriy, spriw / 2, sprih,
                                        perso.x + perso.xVel - (perso.scale * perso.xSize) / 2,
                                        perso.y - perso.ySize * perso.scale,
                                        perso.xSize * perso.scale, perso.ySize * perso.scale)) {
                                    map.map[i][j] = 65;
                                    compteur--;
                                    coin.play();
                                }
                            }
                        }
                    }
                }
            }
            perso.x += perso.xVel;
            perso.y += perso.yVel;
            persosprite.rotate(perso.xVel * 0.5);
            if (perso.y > winh + perso.ySize && perso.dead == 0) {
                perso.die(std::ref(diesound), winh);
            }
            if (perso.dead == 1 && perso.yVel > 0 && perso.y > winh + perso.ySize + 6000) {
                perso.respawn(spriw, sprih, winh);
            }
            counter++;
            if (counter == 13) {
                counter = 0;
                if (perso.lose > 0) {
                    if (compteur > 0) {
                        compteur--;
                    }
                    perso.lose--;
                }
                if (state < 6) {
                    state++;
                }
                else {
                    state = 1;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 120));
        }
    }
}

