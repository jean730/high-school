#include <SFML/System.hpp>
#include <thread>
#include "global.h"
#include <libnotify/notify.h>
#include <mpv/client.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <mysql/mysql.h>
bool fav=false;
bool shit=false;

void mysql_shitcallback(MYSQL *database){
    MYSQL_RES *result = mysql_store_result(database);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) 
    { 
		if(strcmp(row[3],"0")==0){
			printf("Shitted : %s\n",row[0]);
			shit=true;
		}
		else{
			printf("Unshitted : %s\n",row[0]);
			shit=false;
		}
    }
	mysql_free_result(result);
}
void mysql_favcallback(MYSQL *database){
    MYSQL_RES *result = mysql_store_result(database);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) 
    { 
		if(strcmp(row[2],"0")==0){
			printf("Favorited : %s\n",row[0]);
			fav=true;
		}
		else{
			printf("Unfavorited : %s\n",row[0]);
			fav=false;
		}
    }
	mysql_free_result(result);
}

static int shitcallback(void *unused, int argc, char **argv, char **column){
    std::string cmp = argv[3];
    if(cmp=="0"){
        printf("Shitted : %s\n",argv[0]);
        shit=true;
    }
    else{
        printf("Unshitted : %s\n",argv[0]);
        shit=false;
    }
        return 0;
}
static int favcallback(void *unused, int argc, char **argv, char **column){
    std::string cmp = argv[2];
    if(cmp=="0"){
        printf("Favorited : %s\n",argv[0]);
        fav=true;
    }
    else{
        printf("Unfavorited : %s\n",argv[0]);
        fav=false;
    }
        return 0;
}

void GAME_THREAD(_GAME &GAME){
	int shm = shm_open(("/playershm-"+std::to_string(getuid())).c_str(),O_CREAT|O_RDWR,ACCESSPERMS);
	ftruncate(shm,128);
	void *mem = mmap(NULL, 128, PROT_READ|PROT_WRITE, MAP_SHARED, shm, 0);
	char *str = (char*)"0";
	memcpy(mem,str,1);
	while(GAME.Active){
		sf::Clock clock;
                int sleepLength = 100;
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepLength));
		if(GAME.audio_ready==true){
			if(memcmp(mem,"0",1)!=0){
				if(memcmp(mem,"p",1)==0){
					const char* com[] = {"cycle","pause",NULL};
					mpv_command(GAME.mpv,com);
					printf("Toggle Pause\n");
				}
				else if(memcmp(mem,">",1)==0){
					const char* com[] = {"playlist-next",NULL};
					mpv_command(GAME.mpv,com);
					printf("Next\n");
				}
				else if(memcmp(mem,"<",1)==0){
					const char* com[] = {"playlist-prev",NULL};
					mpv_command(GAME.mpv,com);
					printf("Previous\n");
				}
				else if(memcmp(mem,"f",1)==0){
					std::string query=mpv_get_property_string(GAME.mpv,"filename");
					query="select * from musics where lien like '%"+query+"%'";
//					printf("SQL : %s\n",query.c_str());
					if(GAME.backend=="sqlite"){
						int result = sqlite3_exec(GAME.database,query.c_str(),favcallback,NULL,NULL);
						printf("%d \n",result);
					}
					else if(GAME.backend=="mysql"){
						mysql_query(GAME.database_2, query.c_str());
						mysql_favcallback(GAME.database_2);
					}
					if(fav==true){
						NotifyNotification* notif = notify_notification_new("Favorited",
							mpv_get_property_string(GAME.mpv,"media-title"),0);
						notify_notification_set_timeout(notif,1000);
						notify_notification_show(notif,0);
						query=mpv_get_property_string(GAME.mpv,"filename");
						query="update musics set favorite=1 where lien like '%"+query+"%'";
						if(GAME.backend=="sqlite"){
							sqlite3_exec(GAME.database,query.c_str(),NULL,NULL,NULL);
							printf("%s \n",sqlite3_errmsg(GAME.database));
						}
						else if(GAME.backend=="mysql"){
							mysql_query(GAME.database_2, query.c_str());
						}
					}
					else{
						NotifyNotification* notif = notify_notification_new("Unfavorited",
							mpv_get_property_string(GAME.mpv,"media-title"),0);
						notify_notification_set_timeout(notif,1000);
						notify_notification_show(notif,0);
						query=mpv_get_property_string(GAME.mpv,"filename");
						query="update musics set favorite=0 where lien like '%"+query+"%'";
						if(GAME.backend=="sqlite"){
							sqlite3_exec(GAME.database,query.c_str(),NULL,NULL,NULL);
							printf("%s \n",sqlite3_errmsg(GAME.database));
						}
						else if(GAME.backend=="mysql"){
							mysql_query(GAME.database_2, query.c_str());
						}
					}
				}
				else if(memcmp(mem,"s",1)==0){
					std::string query=mpv_get_property_string(GAME.mpv,"filename");
					query="select * from musics where lien like '%"+query+"%'";
				//	printf("SQL : %s\n",query.c_str());
					if(GAME.backend=="sqlite"){
						sqlite3_exec(GAME.database,query.c_str(),shitcallback,NULL,NULL);
					}
					else if(GAME.backend=="mysql"){
						mysql_query(GAME.database_2, query.c_str());
						mysql_shitcallback(GAME.database_2);
					}
					notify_init("Player");
					if(shit==true){
						NotifyNotification* notif = notify_notification_new("Shitted",
								mpv_get_property_string(GAME.mpv,"media-title"),0);
						notify_notification_set_timeout(notif,1000);
						notify_notification_show(notif,0);
						query=mpv_get_property_string(GAME.mpv,"filename");
						query="update musics set shit=1 where lien like '%"+query+"%'";
						if(GAME.backend=="sqlite"){
							sqlite3_exec(GAME.database,query.c_str(),NULL,NULL,NULL);
						}
						else if(GAME.backend=="mysql"){
							mysql_query(GAME.database_2, query.c_str());
						}
					}
					else{
						NotifyNotification* notif = notify_notification_new("Unshitted",
								mpv_get_property_string(GAME.mpv,"media-title"),0);
						notify_notification_set_timeout(notif,1000);
						notify_notification_show(notif,0);
						query=mpv_get_property_string(GAME.mpv,"filename");
						query="update musics set shit=0 where lien like '%"+query+"%'";
						if(GAME.backend=="sqlite"){
							sqlite3_exec(GAME.database,query.c_str(),NULL,NULL,NULL);
						}
						else if(GAME.backend=="mysql"){
							mysql_query(GAME.database_2, query.c_str());
						}
					}
				}
				else if(memcmp(mem,"c",1)==0){ // switch favorite first
					if(GAME.favorite_first=="yes"){
						GAME.favorite_first="no";
					}
					else{
						GAME.favorite_first="yes";
					}
					GAME.reload_songs();
				}
				else if(memcmp(mem,"w",1)==0){ // Set waypoint
					GAME.set_waypoint();
				}
				else if(memcmp(mem,"l",1)==0){ // Load waypoint
					GAME.load_waypoint();
				}
				str=(char*)"0";
				memcpy(mem,str,1);
			}
			mpv_event *event = mpv_wait_event(GAME.mpv, 0);
			const char *event_name=mpv_event_name(event->event_id);
			if(strcmp(event_name,"none")!=0){
//					printf("event: %d %s\n",strcmp(mpv_event_name(event->event_id),"file-loaded"),
//						mpv_event_name(event->event_id));
				if(GAME.Vid=="yes" && GAME.video_ready==true){
					GAME.window->setTitle(mpv_get_property_string(GAME.mpv,"media-title"));
				}
				if( strcmp(event_name,"file-loaded") == 0){
						printf("Playing : %s\n",mpv_get_property_string(GAME.mpv,"media-title"));
				}
				else if( strcmp(event_name,"start-file") == 0){
						printf("Loading : %s\n",mpv_get_property_string(GAME.mpv,"media-title"));
				}
				else if (event->event_id == MPV_EVENT_SHUTDOWN){
					break;
				}
			}
		}
	}
}
