#include "ray.h"
#include <math.h>
Ray::Ray(float x,float y,float angle){
	this->x=x;
	this->y=y;
	this->dx=cos(angle*M_PI/180);
	this->dy=sin(angle*M_PI/180);

}
