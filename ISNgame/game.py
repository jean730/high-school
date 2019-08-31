from player import *
from objet import *
from rectangle import *
import json
class GAME:
    def __init__(self):
        self.localPlayer.Name = input("Pseudo :")
        self.localPlayer.createUnits(1)

        for i in self.localPlayer.Units:
            i.setTexture("test.png")
            i.setPos(1100-self.localPlayer.Units.index(i)*60, 500)

        savename=input("Map ? ")
        try:
            save=open("saves/"+savename+".json")
        except:
            save=open("saves/default.json")
        rawObjects = json.loads(save.read())

        for i in rawObjects:

            rect = Rectangle(i["X"], 720 - i["Y"], 0, 32, 32)
            rect.ID = i["ID"]
            self.Rectangles.append(rect)
            index = len(self.Rectangles)-1

            if 'X' in i:
                self.Rectangles[index].X=i['X']
            if 'Y' in i:
                self.Rectangles[index].Y=i['Y']
            if 'Direction' in i:
                self.Rectangles[index].Direction=i['Direction']
            if 'Poids' in i:
                self.Rectangles[index].Poids=i['Poids']
            if 'Vitesse_X' in i:
                self.Rectangles[index].Vitesse_X=i['Vitesse_X']
            if 'Vitesse_Y' in i:
                self.Rectangles[index].Vitesse_Y=i['Vitesse_Y']
            if 'Actif' in i:
                self.Rectangles[index].Actif=i['Actif']
            if 'Texture' in i:
                self.Rectangles[index].Texture=i['Texture']
            if 'Type' in i:
                self.Rectangles[index].Type=i['Type']
            else:
                self.Rectangles[index].Type=["r",[32,32]]


        self.Interface["editmenu"]=Objet(0)
        self.Interface["editmenu"].setTexture("edit_menu.png")

        addr = input("Addresse du serveur (localhost si vide) :")
        if addr == "":
            self.Address = "127.0.0.1"
        else:
            self.Address = addr

        port = input("Port du serveur (9996 si vide) :")
        if port == "":
            self.Port = 9996
        else:
            self.Port = int(port)
    #EVENTS
    #------
    Key_up = 0
    Key_down = 0
    Key_right = 0
    Key_left = 0
    Key_action = 0

    #VARIABLES D'INTIALISATIONS
    localPlayer=Player("PlaceHolder")
    Players=[]
    Objets=[]
    Rectangles=[]
    Bullets=[]
    Interface={}
    Running=True
    Address="127.0.0.1"
    Port=9996

    #Flux de données
    RenderInStream=""
    RenderOutStream=""
    PhysicsInStream=""
    PhysicsOutStream=""

    #Resources
    Textures={}

    def kill():
        self.Running=False

