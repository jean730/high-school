class Objet:
    def __init__(self,ID):
        self.ID=ID
    X=0
    Y=0
    Direction = 0
    Poids=None
    Vitesse=0
    Actif=False
    Texture=None
    Sprite=None
    rayon = 25
    ID=1
    Type=None #["nom",rayon ou [largeur,longueur]]

    def getPos(self):
        x,y = self.X,self.Y
        return x,y
    def setPos(self,x,y):
        self.X=x
        self.Y=y
    def getVelocity(self):
        return self.Vitesse
    def setVelocity(self,v):
        self.Vitesse=v
    def getType(self):
        return self.Type
    def setType(self,Type):
        self.Type=Type
    def getActif(self):
        return self.Actif
    def setActif(self,Actif):
        self.Actif=Actif
    def getPoids(self):
        return self.Poids
    def setPoids(self,Poids):
        self.Poids=Poids
    def getDirection(self):
        return self.Direction
    def setDirection(self,Direction):
        self.Direction=Direction
    def setTexture(self,tex):
        self.Texture=tex
