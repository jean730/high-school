#include "global.h"
int _GAME::entityFromUid(int uid){
	for(int i=0;i<(int)this->Entities.size();i++){
		if(this->Entities[i].uid==uid){
		return i;
		}
	}
	return -1;
}

