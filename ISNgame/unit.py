class Unit:
    def __init__(self,ID):
        self.ID=ID
        self.V_object = 3 #m/s
    Unit_X=0
    Unit_Y=0
    Texture=None
    Sprite=None
    Direction = 0
    Poids=None
    Vitesse_X=None
    Vitesse_Y=None
    Actif=True
    rayon=25
    Type=None
    OffsetX=25
    OffsetY=25
    LengthX=26
    LengthY=44

   
    def getPos(self):
        x,y = self.Unit_X,self.Unit_Y
        return x,y
    def setPos(self,x,y):
        self.Unit_X=x
        self.Unit_Y=y
    def getVelocity(self):
        x,y = self.Vitesse_X,self.Vitesse_Y
        return x,y
    def setVelocity(self,x,y):
        self.Vitesse_X=x
        self.Vitesse_Y=y
    def getRayon(self):
        return self.Rayon
    def setType(self,Type):
        self.Type=Type
    def getType(self):
        return self.Type
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
