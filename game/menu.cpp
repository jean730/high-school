void menuInGamedraw (int winw,int winh,RenderWindow& jeu, Text& menu,View& view,int& carte,string nomcartes[],int nombrecartes,bool& editor,RectangleShape& rectangle){

                jeu.clear(Color(40, 20, 45));
                rectangle.setOrigin(rectangle.getLocalBounds().width / 2, 0);
                rectangle.setPosition(winw / 2,0);
                rectangle.setFillColor(Color(40, 40, 70));
                rectangle.setSize(sf::Vector2f(winw/3, winh));
                jeu.draw(rectangle);
                rectangle.setSize(sf::Vector2f(winw/3, winh/15));
                for (int i = -2; i <= nombrecartes; i++) {
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
                        if (i == nombrecartes) {
                            menu.setString("Editeur " + stbool(editor));
                        }
                        else {
                            menu.setString(nomcartes[i]);
                        }
                    }
                    else if (i == -1) {
                        menu.setString("continuer");
                    }
                    else if (i == -2) {
                        menu.setString("quitter");
                    }
                    rectangle.setOrigin(rectangle.getLocalBounds().width / 2, rectangle.getLocalBounds().height / 2);
                    rectangle.setPosition(winw / 2,  winh / 2 + (i - carte) * 50 * winh/600 +12*winh/768);
                    menu.setOrigin(menu.getLocalBounds().width / 2, menu.getLocalBounds().height / 2);
                    menu.setPosition(winw / 2, winh / 2 + (i - carte) * 50 * winh/600);
                    view.setCenter(winw / 2, winh / 2);
                    jeu.setView(view);
                    jeu.draw(rectangle);
                    jeu.draw(menu);
                }

                jeu.display();
}
void menuInGameevent (RenderWindow& jeu,int nombrecartes,string cartes[],int& carte, Keyboard& keyboard,bool& editor,Map1& map,int compteur,int& inMenu,Perso& perso,int spriw,int sprih,int winh){

                Event event;
                while (jeu.pollEvent(event)) {

                    if (event.type == Event::Closed || keyboard.isKeyPressed(Keyboard::Key::Escape)) {

                        inMenu = 0;
                    }
                    if (event.type == Event::KeyPressed && keyboard.isKeyPressed(Keyboard::Key::Return)) {
                        if (carte >= -1) {
                            if(carte<nombrecartes){
                            inMenu = 0;
                            }
                            if (carte >= 0) {
                                if (editor) {
                                    printMap(map);
                                }
                                if (carte == nombrecartes) {
                                    if(editor){
		                                printMap(map);
                                    }
                                    map.set(map.mapFile);
                                    editor = !editor;
                                    inMenu = 1;
                                }
                                else {
                                    map.set(cartes[carte]);
                                    perso.setspawn(map.spawnx,map.spawny);
                                    perso.respawn(spriw, sprih, winh);
                                    compteur = 0;
                                }
                            }
                        }

                        else {
                            if (editor) {
                                printMap(map);
                            }
                            jeu.close();
                        }
                    }
                    if (event.type == Event::KeyPressed && keyboard.isKeyPressed(Keyboard::Key::Up)) {
                        if (carte > -2) {
                            carte--;
                        }
                        else {
                            carte = nombrecartes;
                        }
                    }
                    if (event.type == Event::KeyPressed && keyboard.isKeyPressed(Keyboard::Key::Down)) {
                        if (carte < nombrecartes) {
                            carte++;
                        }
                        else {
                            carte = -2;
                        }
                    }
                }

}
