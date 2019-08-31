import threading
import rectangle
import time
from player import *
from math import *
from tkinter import *
#Les informations partagées entre les Threads se trouvent dans game.py et player.py
class physics(threading.Thread):
    def __init__(self,gameObject):
        threading.Thread.__init__(self)
        self.gameObject = gameObject
        self.h_fenetre = 720

    def run(self):

        #creation de la fenetre tk
        fenetre = Tk()
        fenetre.title("Test collision")
        fenetre.geometry("1280x720")
        self.h_fenetre = 720
        self.canv = Canvas(fenetre, width=1280, height=self.h_fenetre)

        a=1
        exectime = 0
        while self.gameObject.Running:
            clock = time.time()
            fenetre.update_idletasks()
            fenetre.update()

            self.passif = []

            for i in self.gameObject.Rectangles:
                self.passif.append(i)

            if 1:

                self.canv.delete("all")


                #rectangles passifs




                """
                #rectangles potentiellement en collision avec l'actif
                for r in y:
                    r.Dessiner(self.canv, self.h_fenetre, "green")

                #rectangle actif
                actif.Dessiner(self.canv, self.h_fenetre, "red")

                #points+points tangent
                r = 2
                for rec in Ptangent:
                    for p in range(1, len(rec)):
                        rec[p][1] += rayon
                        Pt = actif.changement_repere(rec[p])

                        #self.canv.create_oval(rec[p][0]-r, self.h_fenetre-rec[p][1]-r, rec[p][0]+r, self.h_fenetre-rec[p][1]+r, fill="yellow")
                        self.canv.create_oval(Pt[0]-r, self.h_fenetre-Pt[1]-r, Pt[0]+r, self.h_fenetre-Pt[1]+r, fill="yellow")

                r = 3
                d = actif.changement_repere([d[1][0],d[1][1]])
                self.canv.create_oval(d[0]-r, self.h_fenetre-d[1]-r, d[0]+r, self.h_fenetre-d[1]+r, fill="purple")

                #cercle actif
                r = rayon
                self.canv.create_oval(centre[0]-r, self.h_fenetre-centre[1]-r, centre[0]+r, self.h_fenetre-centre[1]+r, fill="", outline="blue")
                """
                self.canv.pack()




            for i in self.gameObject.Bullets:
                pos=i.getPos()
                if pos[0]<0 or pos[0]>1280 or pos[1]<0 or pos[1]>720:
                    del self.gameObject.Bullets[self.gameObject.Bullets.index(i)]
                else:
                    if i.getVelocity()!=0:
                        self.deplacement(i,i.getVelocity(),i.getDirection(),exectime)
                    else:
                        i.setVelocity(1)
                        i.setDirection(i.getDirection()+pi)
                    print(i.Texture)
                    if i.Texture == "dragon_fireball.png":
                        distance=sqrt((pos[0]-self.gameObject.localPlayer.Units[0].getPos()[0])**2+((pos[1]-self.gameObject.localPlayer.Units[0].getPos()[1])**2)**2)
                        print(distance)
            if self.gameObject.Key_down==1:
                for i in self.gameObject.localPlayer.Units:
                    self.deplacement(i,1,3*pi/2,exectime)
                    self.gameObject.PhysicsOutStream+="pos,"+str(i.getPos()[0])+","+str(i.getPos()[1])+";"
            if self.gameObject.Key_up==1:
                for i in self.gameObject.localPlayer.Units:
                    self.deplacement(i,1,pi/2,exectime)
                    self.gameObject.PhysicsOutStream+="pos,"+str(i.getPos()[0])+","+str(i.getPos()[1])+";"
            if self.gameObject.Key_left==1:
                for i in self.gameObject.localPlayer.Units:
                    self.deplacement(i,1,pi,exectime)
                    self.gameObject.PhysicsOutStream+="pos,"+str(i.getPos()[0])+","+str(i.getPos()[1])+";"
            if self.gameObject.Key_right==1:
                for i in self.gameObject.localPlayer.Units:
                    self.deplacement(i,1,0,exectime)
                    self.gameObject.PhysicsOutStream+="pos,"+str(i.getPos()[0])+","+str(i.getPos()[1])+";"
            exectime = 0.001
            print(len(self.gameObject.localPlayer.Units))
            for r in self.passif:
                ##print("dessin :",r)
                r.Dessiner(self.canv, self.h_fenetre, "black")
                ##print("point : ",r.point)
            for i in self.gameObject.PhysicsInStream.split(";"):
                if i!="":
                    NoPlayer=1
                    X = int(i.split(":")[1].split(",")[1])
                    Y = int(i.split(":")[1].split(",")[2])
                    for j in self.gameObject.Players:
                        if j.Name == i.split(":")[0] and j.Name != self.gameObject.localPlayer.Name:
                            j.Units[0].setPos(X,Y)
                            print(j.Units[0].getPos())
                            NoPlayer=0
                    if NoPlayer==1:
                        self.gameObject.Players.append(Player(i.split(":")[0]))
                        self.gameObject.Players[len(self.gameObject.Players)-1].Units.append(Unit(0))
                        for i in self.gameObject.Players[len(self.gameObject.Players)-1].Units:
                            i.setTexture("test.png")
                            i.setPos(X,Y)
            self.gameObject.PhysicsInStream=""
            time.sleep(0.01)
            ##print("Physics ",self.gameObject)

    def deplacement(self,objet,V_objet,direction,exectime):

        #deplacement en fonction de exectime
        V_objet = 3
        d = V_objet*exectime #*10000
        d = 6
        ##print("Move",direction,d)

        x,y = objet.getPos()
        y = self.h_fenetre - y

        #print("x = ", x, ", y = ", y)

        Fx,Fy = int(x + (cos(direction)*d)), int(y + (sin(direction)*d))
        ##print("direction :",direction," d : ",d,"/V_objet :",V_objet,"/Fx,FY:",Fx,"-->",x,"///",Fy,"-->",y)

        y = self.h_fenetre - y

        T = str(type(objet))
        if T == "<class 'unit.Unit'>":
            x += 25
            y -= 5

        else:
            y -= objet.rayon
            x += objet.rayon

        y = self.h_fenetre - y

        ##print(Fx,Fy)

        #if objet.getType() != "Bullet":
        #   Fx, Fy = self.collision(objet,Fx,Fy)
        #("passif : ",self.passif)
        actif = self.CalculRectangleActif([x,y], objet.rayon, direction, d)
        actif.Dessiner(self.canv, self.h_fenetre, "blue")
        ##print("actif : ",actif)
        pcollision = self.CollisionEncombrement(actif, self.passif)
        #print("Encombrement : ", pcollision)
        pcollision_loc = self.Reperelocal([x,y], actif, pcollision)
        #print("local : ", pcollision_loc)
        pcollision_3 = self.PointsTangents(actif, objet.rayon, d, pcollision_loc)

        Ptcollision = self.PointCollision(actif, [x,y], objet.rayon, d, pcollision_3)
        #print("PtCollision : ", Ptcollision)

        x,y = objet.getPos()
        y = self.h_fenetre - y

        if Ptcollision != [100000]:
            d = Ptcollision[0]
            Fx,Fy = int(x + (cos(direction)*(d-2))), int(y + (sin(direction)*(d-2)))
            #Fx,Fy = x,y
            objet.setPos(Fx, self.h_fenetre - Fy)
            if objet.getType()=="Bullet":
                objet.setVelocity(0)
            #Appel physique
        else:
            objet.setPos(Fx, self.h_fenetre - Fy)
            #Appel physique


    #premiere phase de verification de collision
    def CollisionEncombrement(self, actif, objets):

      pcollision = []

      #boucle de verification
      for r in objets:

        #recherche de l'intersection en x
        if ((r.xmin <= actif.xmax) and (r.xmax >= actif.xmin))\
        or ((actif.xmin <= r.xmin) and (r.xmax <= actif.xmax)):

          #recherche de l'intersection en x
          if ((r.ymin <= actif.ymax) and (r.ymax >= actif.ymin))\
          or ((actif.ymin <= r.ymin) and (r.ymax <= actif.ymax)):
            pcollision.append(r)

      #liste des rectangles potentiellement en collision
      return pcollision
    def Reperelocal(self, centre, actif, pCollision):

        #cos et sin de l'angle dans le repere global du rectangle actif pour changer
        #les coordonnees des points global en local du rectangle passif
        CAlpha = cos(actif.a)
        SAlpha = sin(actif.a)
        PointsPossibles = []

        #Centre cercle actif dans le repere tourné dans l'angle de l'actif
        OC = [centre[0]*CAlpha + centre[1]*SAlpha, -centre[0]*SAlpha + centre[1]*CAlpha]

        i = 0
        #Boucle pour chaque liste [R,p1,p2,p3,...]
        for r in pCollision:

            PointsPossibles.append([r])

            #boucle pour chaque point de la liste
            for p in r.point:

                #point du passif dans le repere tourné dans l'angle de l'actif
                OP = [p[0]*CAlpha + p[1]*SAlpha, -p[0]*SAlpha + p[1]*CAlpha]

                # P dans le repere local du cercle actif
                CP = [OP[0]-OC[0], OP[1]-OC[1]]

                PointsPossibles[i].append(CP)

            i += 1

        return PointsPossibles
    def PointsTangents(self, actif, rayon, distance, Potentielles):

        #initialisation des variables
        R2 = rayon**2
        signe = 1

        #indice de la liste Potentielles
        i = 0

        #liste des indices des points p+1
        finale = [0,2,3,4,1]

        #boucle pour chaque rectangle passif
        for r in Potentielles:

            #boucle pour chaque segment du rectangle passif
            for p in range(1, len(r)):

                #print(p)

                # Calcul de Yt
                #=============

                Y21 = (r[finale[p]][1] - r[p][1])
                ##print("Y21:",Y21)

                #Si Y21 = 0 --> le segment est parallele au abscisse donc pas de tangente
                if Y21 == 0:
                    ##print("Y21 == 0")
                    continue
                ##print("Y21 != 0")

                X21 = r[finale[p]][0] - r[p][0]
                X21_2 = X21**2
                ##print("X21",X21)


                #Change le signe de Yt
                # (Xt-xD) . x21 + Yt . y21 = 0
                #
                # (Xt-xD) > 0 par hyp.
                # x21 > 0, y21 > 0 => Yt < 0
                # x21 < 0, y21 > 0 => Yt > 0
                # x21 < 0, y21 < 0 => Yt < 0
                # x21 > 0, y21 < 0 => Yt > 0

                if Y21 < 0:

                    if X21 < 0:
                        signe = -1
                    else :
                        signe = 1

                elif Y21 > 0:

                    if X21 >= 0:
                        signe = -1
                    else:
                        signe = 1


                Yt = signe * sqrt(  (R2 * X21_2) / (X21_2 + Y21**2)  )
                ##print("Yt:",Yt)

                #parametre de l'equation de droite du point du rectangle passif
                k = (Yt - r[p][1]) / Y21
                ##print("k:",k)

                #point en dehors du rectangle actif
                if Yt< -rayon or Yt>rayon:
                    continue

                #point en dehors du segment
                if k<0 or k>1:
                    continue

                Xt = r[p][0] + k * X21
                ##print("Xt:",Xt)


                #point en dehors du rectangle actif
                if Xt<0 or Xt>distance+rayon:
                    continue


                #ajoute le point tangent potentielle
                Potentielles[i].append([Xt,Yt])

        #incremente indice liste Potentielles
        i += 1

        return Potentielles

    def PointCollision(self, actif, centre, rayon, distance, Potentielles):

        #initialisation des variables
        d = [100000]
        R_2 = rayon**2

        #boucle pour chaque rectangle
        for r in Potentielles:

            #boucle pour chaque point du rectangle
            for p in range(1, len(r)):

                #Si le point est en dehors du rectangle actif
                if r[p][1] > rayon or r[p][1] < -rayon:
                    continue

                if r[p][0] > rayon + distance or r[p][0] < 0:
                    continue

                #calcul de la longueur interieur au cercle
                L_2 = R_2 - r[p][1]**2

                #calcul de la distance separant le cercle du point
                testd = r[p][0] - sqrt(L_2)

                if testd < d[0]:
                    Normal = [(centre[0] + testd) - r[p][0], -r[p][1]]
                    d = [testd, r[p], Normal, r[0]]
        return d

    def CalculRectangleActif(self, centre, rayon, direction, d):

        p = [centre[0] + rayon*sin(direction), centre[1] - rayon*cos(direction)]
        rec = rectangle.Rectangle(p[0], p[1], direction, d+rayon, 2*rayon)
        return rec
    


