#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "cellular.hpp"
using namespace sf;
int main(){
	float winh=700;
	float winw=700;
	float size=50;
	float gridSize = 0.8;
	float antiGrid = (1-gridSize)/2;
	RenderWindow jeu(VideoMode(winw,winh,24),"Conway's game of life");
	RectangleShape rect(Vector2f(winw/size*gridSize,winh/size*gridSize));
	cellular Cell[(int)size][(int)size];
	bool Pause = false;




	Clock clock;
	while(jeu.isOpen()){
	Event event;
	while(jeu.pollEvent(event)){
		if(event.type == Event::Closed){
			jeu.close();
		}
		if(event.type == Event::MouseButtonPressed){
			float mx = Mouse::getPosition(jeu).x;
                        float my = Mouse::getPosition(jeu).y;
			mx/=winw;
			mx*=size;
			my/=winh;
			my*=size;
			Cell[(int)mx][(int)my].nextState=!Cell[(int)mx][(int)my].isActive;

		}
               if(event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Space){
                        Pause = !Pause;
//td::cout << event.key.code << std::endl;
              }
	}
	if(clock.getElapsedTime().asMilliseconds()>=100){
		jeu.clear(Color(200,200,200));


		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				rect.setPosition(i*(winw/size)+winw/size*antiGrid,j*(winh/size)+winh/size*antiGrid);
				Cell[i][j].isActive = Cell[i][j].nextState;
				if(Cell[i][j].isActive){
					
rect.setFillColor(Color(100,100,100));
				}
				else{
                                        rect.setFillColor(Color(250,250,250));
				}
				jeu.draw(rect);
			}
		}
		if(!Pause){
                for(int i=0;i<size;i++){
                        for(int j=0;j<size;j++){
				int left=i-1;
				int right=i+1;
				if(left<0)left=size-1;
				if(right>size-1)right=0;
                                int up=j-1;
                                int down=j+1;
                                if(up<0)up=size-1;
                                if(down>size-1)down=0;
				int sum =
					Cell[left][up].isActive+
					Cell[left][j].isActive+
					Cell[left][down].isActive+
					Cell[i][up].isActive+
					Cell[i][down].isActive+
					Cell[right][up].isActive+
					Cell[right][j].isActive+
					Cell[right][down].isActive;
				if(sum==3 && Cell[i][j].isActive==false){
					Cell[i][j].nextState = true;
				}
				if(sum==1 | sum==0 | sum>=4){
					Cell[i][j].nextState = false;
				}

                        }
                }
		}





	
		clock.restart();
		jeu.display();
	}
	};
	return 0;
}
