#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>
std::string cwd(){
	char wd[1024];
	getcwd(wd,1024);
	return std::string(wd);
}
void ls(char* str,bool l,bool a){
  DIR *d;
  struct dirent *dir;
  d = opendir(str);
  if (d) {
    if(l==1){
      while ((dir = readdir(d)) != NULL) {
	if(a==1 || (a==0 && dir->d_name[0]!='.')){
          std::cout << dir->d_name << std::endl;
	}
      }
    }
    else{
      while ((dir = readdir(d)) != NULL) {
	if(a==1 || (a==0 && dir->d_name[0]!='.')){
          std::cout << dir->d_name << " ";
	}
      }
      std::cout << std::endl;
    }
    closedir(d);
  }
}
int main(){
	while(true){
	std::string unsplit;
	std::vector<std::string> split;
	unsplit = readline(("[jean@portable "+std::string(cwd())+"]$ ").c_str());
	add_history(unsplit.c_str());
	bool word=0;
	for(unsigned int i=0;i<unsplit.length();i++){
		if(word==0){
			std::string character = "";
			character += unsplit[i];
			split.push_back(character);
			word=1;
		}
		else{
			if(unsplit[i] != ' '){
				split[split.size()-1]+=unsplit[i];
			}
			else{
				word=0;
			}
		}
	}
	for(unsigned int i=0;i<split.size();i++){
		std::cout << "[" << i << "]" << split[i] << " ";
	}
	std::cout << std::endl;
	if(split.size()>0)
	{
		if(split[0] == "exit"){
			exit(0);
		}
		else if(split[0] == "pwd"){
			std::cout << cwd() << std::endl;
		}
		else if(split[0] == "mkdir"){
			for(unsigned int i=1;i<split.size();i++){
				std::cout << "--[Creating Folder " << split[i] << "]--" << std::endl;
				mkdir((char*)split[i].c_str(),S_IRWXU | S_IRWXG | S_IRWXO);
			}
		}
		else if(split[0] == "rm"){
			for(unsigned int i=1;i<split.size();i++){
				std::cout << "--[Deleting File " << split[i] << "]--" << std::endl;
				unlink((char*)split[i].c_str());
			}
		}
		else if(split[0] == "rmdir"){
			for(unsigned int i=1;i<split.size();i++){
				std::cout << "--[Deleting Folder " << split[i] << "]--" << std::endl;
				rmdir((char*)split[i].c_str());
			}
		}
		else if(split[0] == "clear"){
			for(int i=0;i<30;i++){
				std::cout << std::endl;
			}
		}
		else if(split[0] == "rand"){
			for(int i=0;i<100000;i++){
				std::string character = "";
				character += 32+rand()%94;
				std::cout << character;
			}
		std::cout << std::endl;
		}
		else if(split[0] == "cd"){
			if(split.size()==1){
				chdir((char*)"/documents");

			}
			else if(split.size()==2){
				chdir((char*)split[1].c_str());
			}
			else{
				std::cout << "Expected 1 parameter but got " << split.size() - 1 << std::endl;
			}
		}
		else if(split[0] == "cat"){
			for(unsigned int i=1;i<split.size();i++){
				std::ifstream file((char*)split[i].c_str());
				std::cout << "--[Reading " << split[i] << "]--" << std::endl;
				std::string line;
				while(std::getline(file,line)){
					std::cout << line << std::endl;
				}
			}
		}
		else if(split[0] == "cp" && split.size()==3){
			std::ifstream filein((char*)split[1].c_str());
			std::ofstream fileout((char*)split[2].c_str());
			std::cout << "--[Copying " << split[1] << " to " << split[2] << "]--" << std::endl;
			std::string line;
			while(std::getline(filein,line)){
				fileout << line << std::endl;
			}
		}
		else if(split[0] == "mv" && split.size()==3){
			rename((char*)split[1].c_str(),(char*)split[2].c_str());
		}
		else if(split[0] == "ls"){
			bool l = false;
			bool a = false;
			for(unsigned int i=1;i<split.size();i++){
				if(split[i] == "-l"){
					l=true;
					split.erase(split.begin()+i);
					i--;
				}
				if(split[i] == "-a"){
					a=true;
					split.erase(split.begin()+i);
					i--;
				}

			}
			unsigned int count = 0;
			for(unsigned int i=1;i<split.size();i++){
				count+=1;
				std::cout << "           --[List " << split[i] << "]--" << std::endl;
				ls((char*)split[i].c_str(),l,a);
					
			}
			if(count==0){
			std::cout << "           --[List .]--" << std::endl;
				ls((char*)".",l,a);
			}
		}
		else{
			char* args[split.size()+1];
			for(unsigned int i=0;i<split.size();i++){
				args[i] = (char*)split[i].c_str();
				std::cout << args[i]<< std::endl;
			}
			args[split.size()]=NULL;
			int status;
			if(fork()==0){
				std::cout << execvp((char*)split[0].c_str(),args) << std::endl;
			}
			else{
				wait(&status);
			}
			perror("");
		}

	}
	}
	return(0);
}
