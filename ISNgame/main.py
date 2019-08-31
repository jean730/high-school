#!/bin/python3
from game import *
from renderthread import * 
from physicsthread import * 
from networkthread import *
#Creation de l'objet global
gameObject = GAME()
#Création des Threads
Threads = [render(gameObject),physics(gameObject),network(gameObject)]
#Lancement des Threads
for i in Threads:
    i.start()
