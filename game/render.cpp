void render(Perso& perso, bool& open, Map1& map, int winh, int& state,
    int& compteur,  int& selected,
    int winw, int& inMenu, bool& editor, Sprite& persosprite,RenderWindow& jeu,View& view,Texture& tex,Text& score,Sprite& tiles,Image& tileset,int& carte,string nomcartes[],int nombrecartes,Text& menu,RectangleShape& rectangle)
{
    jeu.setActive(true);
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
            jeu.clear(Color(140, 200, 255));
            int xmin = std::floor((view.getCenter().x - view.getSize().x/2)/spriw);
            int xmax = std::ceil((view.getCenter().x + view.getSize().x/2)/spriw);
            if(xmin<0){
                xmin=0;
            }
            else if(xmax>150){
                xmax=150;
            }
                for (int i = 0; i < map.Lines; i++) {
                    for (int j = xmin; j < xmax; j++) {
                        sprix = spriw * j;
                        spriy = wsh - sprih * (map.Lines - 1 - i);
                        if (collide(view.getCenter().x - view.getSize().x / 2,
                                view.getCenter().y - view.getSize().y / 2, view.getSize().x,
                                view.getSize().y, sprix, spriy, spriw, sprih)
                            && map.map[i][j] != 34) {
                            tex.loadFromImage(tileset, tileRect(map.map[i][j], state));

                            if (map.mapCollide[i][j] == 1 || !editor) {
                                tiles.setColor(Color(255, 255, 255));
                            }
                            else {
                                tiles.setColor(Color(255, 155, 155));
                            }
                            tiles.setPosition(sprix, spriy);
                            jeu.draw(tiles);
                        }
                    }
                }

                score.setString("Pieces " + std::to_string(compteur));

                jeu.draw(persosprite);
                jeu.draw(score);
                score.setPosition(perso.x - winw / 2.2, winh / 25);
                persosprite.setPosition(perso.x, perso.y);
                view.move((perso.x - view.getCenter().x), 0);
                // if(perso.zoom!=0){
                //      view.zoom(perso.zoom);
                //}
                if (editor) {
                    tex.loadFromImage(tileset, tileRect(selected, state));
                    int mx = perso.x + sf::Mouse::getPosition().x - winw / 2 - spriw / 2;
                    int my = sf::Mouse::getPosition().y - sprih / 2;
                    tiles.setPosition(mx, my);
                }
                jeu.draw(tiles);
                jeu.setView(view);
                jeu.display();
        }
        else{
        menuInGamedraw(winw,winh,std::ref(jeu), std::ref(menu),std::ref(view),std::ref(carte),nomcartes,nombrecartes,std::ref(editor),std::ref(rectangle));
        
        }
    }

}

