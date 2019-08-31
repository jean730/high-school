
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
using namespace sf;

int main(){
	int rframe=0;
	int frame=0;
	int secrets=0;
	Texture texture;
	texture.loadFromFile("sprites/robot/frame_0_delay-0.04s.png");
	Sprite sprite(texture);
	sprite.setScale(Vector2f(-1,1));
	double enemylevel = 20;
	Font font;
	font.loadFromFile("font/font.ttf");
	Text score;
	score.setFont(font);
	int ilevel;
	Keyboard keyboard;
	int secret = 0;
        double winh;
	double winw;
	winw=VideoMode::getDesktopMode().width;
	winh=VideoMode::getDesktopMode().height;

	score.setCharacterSize(winw/20);
	score.setPosition(20,50);


	double level = 0;
	ilevel = level;
	score.setString("Score "+ std::to_string(ilevel));

	//	Définition du décor
	RectangleShape topRect(Vector2f(winw,(winh/1000)*15));
	topRect.setPosition(Vector2f(0,0));
	RectangleShape bottomRect(Vector2f(winw,(winh/1000)*15));
	bottomRect.setPosition(Vector2f(0,winh-(winh/1000)*15));
	RectangleShape centerRect(Vector2f(winw/90,winh/20));
	centerRect.setOrigin((winw/90)/2,winh/20/2);
	//

	//	Définition de la balle
	double ballSize = 15;
	double ballx = 500;
	double bally = 500;
	int ballSpeed= 3;
	srand (time(NULL));
	double ballyVelocity;
	double ballxVelocity;
	if(std::rand() % 10-5 < 0){
		ballxVelocity = -1;
	}
	else{
		ballxVelocity = 1;
	}
	if(std::rand() % 10-5 < 0){
		ballyVelocity = -1;
	}
	else{
		ballyVelocity = 1;
	}

	RectangleShape ball(Vector2f(ballSize/1000*winw,ballSize/1000*winw));
	ball.setOrigin((ballSize/1000*winw)/2,(ballSize/1000*winw)/2);
	ball.setPosition(Vector2f(ballx/1000*winw,bally/1000*winh));
	//
	int Robot = 1;
	//	Définition du palet 1
	double pall1Size = 10;
	double pall1Sizey = 200;
	double pall1x = 50;
	double pall1y = 500;
	int pall1Speed= 15;
	int up1 = 0;
	int down1 = 0;

	RectangleShape pall1(Vector2f(pall1Size/1000*winw,pall1Sizey/1000*winh));
	pall1.setOrigin((pall1Size/1000*winw)/2,(pall1Sizey/1000*winh)/2);
	pall1.setPosition(Vector2f(pall1x/1000*winw,pall1y/1000*winh));
	//
	//	Définition du palet 2
	double pall2Size = 10;
	double pall2Sizey = 200;
	double pall2x = 950;
	double pall2y = 500;
	int pall2Speed= 15;
	int up2 = 0;
	int down2 = 0;

	RectangleShape pall2(Vector2f(pall2Size/1000*winw,pall2Sizey/1000*winh));
	pall2.setOrigin((pall2Size/1000*winw)/2,(pall2Sizey/1000*winh)/2);
	pall2.setPosition(Vector2f(pall2x/1000*winw,pall2y/1000*winh));
	//


	Music lose;
	lose.openFromFile("sounds/lose.ogg");
	Music wallHit;
	wallHit.openFromFile("sounds/wall.ogg");
	Music Hit;
	Hit.openFromFile("sounds/pong.ogg");
	lose.play();
	RenderWindow jeu(VideoMode(winw,winh,64),"Pong", Style::Fullscreen);
	View view = jeu.getDefaultView();
	jeu.setMouseCursorVisible(false);
	

	jeu.setFramerateLimit(60);
	Mouse::setPosition(Vector2i(winw/2, winh/2), jeu);
	while(jeu.isOpen()){








		Event event;
		while(jeu.pollEvent(event)){
			if(event.type == Event::Closed){
			
				jeu.close();
			}
		}



		jeu.clear();



	// Touches
		if(keyboard.isKeyPressed(Keyboard::Key::Escape)){
			jeu.close();
		}
		if(keyboard.isKeyPressed(Keyboard::Key::LControl)){
			down1=1;
			Robot = 0;
		}
                else{
			down1=0;
                }
		if(keyboard.isKeyPressed(Keyboard::Key::LShift)){
			up1=1;
			Robot = 0;
		}
                else{
			up1=0;
                }

		if(keyboard.isKeyPressed(Keyboard::Key::Down)){
			down2=1;
		}
                else{
			down2=0;
                }
		if(keyboard.isKeyPressed(Keyboard::Key::Up)){
			up2=1;
		}
                else{
			up2=0;
                }

		//if(Mouse::isButtonPressed(Mouse::Right) && !Mouse::isButtonPressed(Mouse::Left)){
		//	view.move(winw/2-Mouse::getPosition(jeu).x,winh/2-Mouse::getPosition(jeu).y);

		//}


	//
	//	Décor
		jeu.draw(topRect);				
		jeu.draw(bottomRect);
		
		for(int i=0;i<=10;i++){
			centerRect.setPosition(Vector2f(winw/2,winh/20*i*2));
			jeu.draw(centerRect);
		}

	//




	//	Collisions
		if(bally<15+(ballSize/2)){
			bally=15+(ballSize/2);
			ballyVelocity = -ballyVelocity;
			wallHit.play();
		}
		else if(bally>985-(ballSize/2)){
			bally=985-(ballSize/2);
			ballyVelocity = -ballyVelocity;
			wallHit.play();
		}
		if(ballx<-20+(ballSize/2)){
			ballx=500;
			ballxVelocity = -ballxVelocity;
			lose.play();
		}
		else if(ballx>1020-(ballSize/2)){
			ballx=500;
			ballxVelocity = -ballxVelocity;

			lose.play();
		}
		double uppall1 = pall1y-(pall1Sizey/2);
		double uppall2 = pall2y-(pall2Sizey/2);
		double downpall1 = pall1y+(pall1Sizey/2);
		double downpall2 = pall2y+(pall2Sizey/2);
		if(bally-ballSize/2 <= downpall1 && bally+ballSize/2 >= uppall1 && ballx <60 && ballx >40){
			ballx=60;
			ballxVelocity = -ballxVelocity;	
			ballyVelocity = ballSpeed * (bally-pall1y)/100;
			Hit.play();
			pall1Sizey*=0.99;
			pall2Sizey*=0.99;
			pall1.setSize(Vector2f(pall1Size/1000*winw,pall1Sizey/1000*winh));
			pall1.setOrigin((pall1Size/1000*winw)/2,(pall1Sizey/1000*winh)/2);
			pall1.setPosition(Vector2f(pall1x/1000*winw,pall1y/1000*winh));
			pall2.setSize(Vector2f(pall2Size/1000*winw,pall2Sizey/1000*winh));
			pall2.setOrigin((pall2Size/1000*winw)/2,(pall2Sizey/1000*winh)/2);
			pall2.setPosition(Vector2f(pall2x/1000*winw,pall2y/1000*winh));
			if(Robot == 0){
				level++;
			}
			else if(enemylevel>0 && enemylevel <40){
				enemylevel+=2;
			}
			ilevel=level;
			score.setString("Score "+ std::to_string(ilevel));
		}
		if(bally-ballSize/2 <= downpall2 && bally+ballSize/2 >= uppall2 && ballx >1000-60 && ballx <1000-40){
			ballx=1000-60;
			ballxVelocity = -ballxVelocity;	
			ballyVelocity = ballSpeed * (bally-pall2y)/100;
			Hit.play();
			pall1Sizey*=0.99;
			pall2Sizey*=0.99;
			pall1.setSize(Vector2f(pall1Size/1000*winw,pall1Sizey/1000*winh));
			pall1.setOrigin((pall1Size/1000*winw)/2,(pall1Sizey/1000*winh)/2);
			pall1.setPosition(Vector2f(pall1x/1000*winw,pall1y/1000*winh));
			pall2.setSize(Vector2f(pall2Size/1000*winw,pall2Sizey/1000*winh));
			pall2.setOrigin((pall2Size/1000*winw)/2,(pall2Sizey/1000*winh)/2);
			pall2.setPosition(Vector2f(pall2x/1000*winw,pall2y/1000*winh));
			level++;
			if(Robot==1 && enemylevel>0){
				enemylevel-=2;
			}
			ilevel=level;
			score.setString("Score "+ std::to_string(ilevel));
		}
		if(secret==0 && level >5){
			secret=1;

			
		}
		else if(secret==1){
			if(secrets>2000){
				secret=2;
			}
			else{
				secrets+=2;
				if(frame == 1){
					if(rframe<25){
						rframe++;
					}
					else{
						rframe=0;
					}
					frame=0;
				}
				else{
					frame++;
				}
				texture.loadFromFile("sprites/robot/frame_"+std::to_string(rframe)+"_delay-0.04s.png");
				sprite.setPosition(secrets-150,winh-260);
			}

			jeu.draw(sprite);

		}

	//


	
// Cheat mode	//if(Mouse::isButtonPressed(Mouse::Left)){
		//	ballx=(Mouse::getPosition(jeu).x/winw)*1000;
		//	bally=(Mouse::getPosition(jeu).y/winh)*1000;
		//}
		//else{
//	Mouvement et dessin de la balle
//			Mouse::setPosition(Vector2i(winw/2, winh/2), jeu);
			if(level < 60){
				ballx+=ballxVelocity*ballSpeed*(1+(level/30));
				bally+=ballyVelocity*ballSpeed*(1+(level/30));
			}
			else{
				ballx+=ballxVelocity*ballSpeed*(1+(60/30));
				bally+=ballyVelocity*ballSpeed*(1+(60/30));
			}

		//}
			ball.setPosition(Vector2f(ballx/1000*winw,bally/1000*winh));



		jeu.draw(ball);

	//
	//	Dessin et mouvement des Palets

		if(pall2y < 985-(pall2Sizey/2) && down2==1){
			pall2y+=pall2Speed*down2+(level/6);
		}
		if(pall2y > 15+(pall2Sizey/2)  && up2==1){
			pall2y-=pall2Speed*up2+(level/6);
		}


		pall2.setPosition(Vector2f(pall2x/1000*winw,pall2y/1000*winh));
		pall1.setPosition(Vector2f(pall1x/1000*winw,pall1y/1000*winh));

			if(up2 && down2){

				pall2.setFillColor(Color(std::rand() % 255,std::rand() % 255,std::rand() % 255));
			}
			else{
				pall2.setFillColor(Color(255, 255, 255));
			}
		jeu.draw(pall1);

	//	Robot
		if(Robot == 1){

			// ancienne intelligence artificielle(plus simple a battre mais se comporte bizarrement)
			//if(pall1y<=bally+55 && pall1y <  890){
			//	pall1y+=pall1Speed;
			//}
			//if(pall1y>=bally-55 && pall1y > 110){
			//	pall1y-=pall1Speed;
			//}

			pall1y+=(-pall1y+bally)/(enemylevel+1);
			if(pall1y > 985-(pall2Sizey/2)){
				pall1y = 985-(pall2Sizey/2);
			}
			else if(pall1y < 15+(pall2Sizey/2)){
				pall1y = 15+(pall2Sizey/2);
			}
		}
		else{
			if(up1 && down1){

				pall1.setFillColor(Color(std::rand() % 255,std::rand() % 255,std::rand() % 255));
			}
			else{
				pall1.setFillColor(Color(255, 255, 255));
			}
			if(pall1y <  985-(pall2Sizey/2) && down1==1){
				pall1y+=pall1Speed*down1+(level/6);

			}
			if(pall1y > 15+(pall2Sizey/2)  && up1==1){
				pall1y-=pall1Speed*up1+(level/6);

			}
		}

		jeu.draw(pall2);
		jeu.draw(score);
	//
				jeu.setView(view);
		jeu.display();
	}
	return 0;
}




