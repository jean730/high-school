from unit import *
class Player:
    def __init__(self,Name):
        self.Name=Name
        self.selectedweapon="slime_ball.png"
        self.selectedUnit=0
        self.Units=[]
    def setName(self,Name):
        self.Name=Name
    def createUnits(self,Number):
        for i in range(0,Number):
            self.Units.append(Unit(len(self.Units)))
