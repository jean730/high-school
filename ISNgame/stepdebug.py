class StepDebug:
    steps = 0
    state = 0
    prefix = ""
    def step(self):
        self.steps+=1
        if self.state == True or self.state == 1 :
            print(self.prefix,"Step",self.steps)
    def resetsteps(self):
        self.steps=0
    def enabled(self,state):
        self.state = state

