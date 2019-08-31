import threading
import time
import sys
import sdl2.ext
import sdl2.sdlttf
import sdl2.surface
import sdl2.sdlmixer
import os
import copy
import ctypes
import json
import math
import random
from objet import *
from rectangle import *
#Les informations partagées entre les Threads se trouvent dans game.py et player.py
class render(threading.Thread):
    editmode=False
    editmenu=False
    editmenu_offset=-300
    editmenu_offset_Y=0
    editselection="fire_0.png"
    editcursor=None
    menuSprites={}
    def __init__(self,gameObject):
        threading.Thread.__init__(self)
        self.gameObject = gameObject
    def run(self):
        FPS=0
        RESOURCES = sdl2.ext.Resources(__file__,"resources")
        sdl2.ext.init()
        window = sdl2.ext.Window("Wormblocks",size=(1280,720))
        window.show()
        spriteFactory = sdl2.ext.SpriteFactory(sdl2.ext.SOFTWARE)
        spriteRenderer = spriteFactory.create_sprite_render_system(window)
        sdl2.sdlttf.TTF_Init()
        ttffont=sdl2.sdlttf.TTF_OpenFont("resources/font.ttf".encode(),40)
        fpssprite=spriteFactory.from_color(sdl2.SDL_Color(0,0,0,0),(200,50))
        fpssprite.position=10,0
        sdl2.SDL_Init(sdl2.SDL_INIT_AUDIO)
        sdl2.sdlmixer.Mix_OpenAudio(44100, sdl2.sdlmixer.MIX_DEFAULT_FORMAT, 2, 1024)
        opensound=sdl2.sdlmixer.Mix_LoadWAV("resources/open.wav".encode())
        for root,directories,files in os.walk("resources"):
            for i in files:
                try:
                    name=""
                    if os.name == 'nt':
                        name=i.split("\\")[len(i.split("\\"))-1]
                    else:
                        name=i.split("/")[len(i.split("/"))-1]
                    self.gameObject.Textures[name]=\
                            spriteFactory.from_image(RESOURCES.get_path(name))
                    temp=sdl2.surface.SDL_CreateRGBSurface(0,50,50,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff)
                    sdl2.surface.SDL_BlitScaled(self.gameObject.Textures[name].surface,None,temp,sdl2.surface.SDL_Rect(0,0,50,50))
                    self.menuSprites[name]=self.gameObject.Textures[name].subsprite((0,0,50,50))
                    self.menuSprites[name].surface=temp
                    #print(temp)
                    #print(type(temp))
                    #print("Loaded Texture : ",name)
                except Exception as e:
                    print(e)
                    #not a texture
                    pass
        for i in self.gameObject.Rectangles:
            if i.Texture!=None:
                i.Sprite=self.gameObject.Textures[i.Texture].subsprite((0,0,self.gameObject.Textures[i.Texture].size[0],self.gameObject.Textures[i.Texture].size[1]))
        for j in self.gameObject.Players:
            for i in j.Units:
                if i.Texture!=None:
                    i.Sprite=self.gameObject.Textures[i.Texture].subsprite((0,0,self.gameObject.Textures[i.Texture].size[0],self.gameObject.Textures[i.Texture].size[1]))
                    temp=sdl2.surface.SDL_CreateRGBSurface(0,50,50,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff)
                    sdl2.surface.SDL_BlitScaled(self.gameObject.Textures[i.Texture].surface,None,temp,sdl2.surface.SDL_Rect(0,0,50,50))
                    i.Sprite.surface=temp
        for i in self.gameObject.localPlayer.Units:
            if i.Texture!=None:
                i.Sprite=self.gameObject.Textures[i.Texture].subsprite((0,0,self.gameObject.Textures[i.Texture].size[0],self.gameObject.Textures[i.Texture].size[1]))
                temp=sdl2.surface.SDL_CreateRGBSurface(0,50,50,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff)
                sdl2.surface.SDL_BlitScaled(self.gameObject.Textures[i.Texture].surface,None,temp,sdl2.surface.SDL_Rect(0,0,50,50))
                i.Sprite.surface=temp
        for i in self.gameObject.Interface:
            j=self.gameObject.Interface[i]
            if j.Texture!=None:
                j.Sprite=self.gameObject.Textures[j.Texture].subsprite((0,0,self.gameObject.Textures[j.Texture].size[0],self.gameObject.Textures[j.Texture].size[1]))
        temp=sdl2.surface.SDL_CreateRGBSurface(0,50,50,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff)
        self.editcursor=self.gameObject.Textures[self.editselection].subsprite((0,0,32,32))
        sdl2.surface.SDL_BlitScaled(self.gameObject.Textures[self.editselection].surface,None,temp,sdl2.surface.SDL_Rect(0,0,32,32))
        sdl2.surface.SDL_SetSurfaceAlphaMod(temp,150)
        self.editcursor.surface=temp
        while self.gameObject.Running:
            #evenements
            Clock = time.time()
            ttftext=sdl2.sdlttf.TTF_RenderText_Solid(ttffont, (str(int(FPS))+" FPS").encode(), sdl2.SDL_Color(255,230,0));
            fpssprite.surface=sdl2.surface.SDL_CreateRGBSurface(0,200,50,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff)
            sdl2.surface.SDL_BlitSurface(ttftext,None,fpssprite.surface,None);
            mouse_X=ctypes.c_int(0)
            mouse_Y=ctypes.c_int(0)
            sdl2.mouse.SDL_GetMouseState(ctypes.byref(mouse_X),ctypes.byref(mouse_Y))
            mx=mouse_X.value
            my=mouse_Y.value
            events = sdl2.ext.get_events()
            for i in self.gameObject.RenderInStream.split(";"):
                if i != "":
                    if i.split(",")[0]=="d":
                        print("Delete")
                        for j in self.gameObject.Rectangles:
                            mX,mY=int(i.split(",")[1]),int(i.split(",")[2])
                            search_X,search_Y=j.getPos()
                            if mX==search_X and mY==search_Y:
                                del self.gameObject.Rectangles[self.gameObject.Rectangles.index(j)]
                    elif i.split(",")[0]=="c":
                        mX,mY,tex=int(i.split(",")[1]),int(i.split(",")[2]),i.split(",")[3]
                        self.gameObject.Rectangles.append(Rectangle(mX,720 - 32 - mY, 0, 32, 32))
                        self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].ID=len(self.gameObject.Rectangles)
                        self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].setTexture(tex)
                        self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].Sprite=self.gameObject.Textures[tex].subsprite((0,0,32,32))
                        self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].setPos(mX,mY)
                        self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].X=mX
                        self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].Y=mY
                        self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].Type=["r",[32,32]]
                    elif i.split(",")[0]=="cb":
                        mX,mY,tex,ang=int(i.split(",")[1]),int(i.split(",")[2]),i.split(",")[3],float(i.split(",")[4])
                        self.gameObject.Bullets.append(Objet(len(self.gameObject.Bullets)))
                        self.gameObject.Bullets[len(self.gameObject.Bullets)-1].setType("Bullet")
                        self.gameObject.Bullets[len(self.gameObject.Bullets)-1].setTexture(tex)
                        self.gameObject.Bullets[len(self.gameObject.Bullets)-1].setDirection(ang)
                        self.gameObject.Bullets[len(self.gameObject.Bullets)-1].Sprite=self.gameObject.Textures[tex].subsprite((0,0,32,32))
                        self.gameObject.Bullets[len(self.gameObject.Bullets)-1].setPos(mX,mY)
                        self.gameObject.Bullets[len(self.gameObject.Bullets)-1].rayon = 16
                        self.gameObject.Bullets[len(self.gameObject.Bullets)-1].setVelocity(0.5)
            self.gameObject.RenderInStream=""
            for event in events:

                if event.type == sdl2.SDL_KEYDOWN:
                    if event.key.keysym.sym == sdl2.SDLK_l:
                        Save = copy.copy(self.gameObject.Rectangles)
                        savefile = 0
                        if os.name == 'nt':
                            savefile=open("saves\\"+str(random.randint(1,10000000))+".json","w")
                        else:
                            savefile=open("saves/"+str(random.randint(1,10000000))+".json","w")
                        jsave = json.loads(json.dumps(Save,default=lambda obj: obj.__dict__))
                        for element in jsave:
                            del element['Sprite']
                        savefile.write(json.dumps(jsave))
                        savefile.close()
                        print("World saved as",savefile)
                    editmenunow=self.editmenu
                    if event.key.keysym.sym == sdl2.SDLK_r and self.editmode==True:
                        if self.editmenu==True:
                            self.editmenu=False
                        else:
                            self.editmenu=True
                    if event.key.keysym.sym == sdl2.SDLK_e:
                        if self.editmode==True:
                            self.editmode=False
                            self.editmenu=False
                        else:
                            self.editmode=True
                            self.editmenu=True
                    elif event.key.keysym.sym == sdl2.SDLK_UP:
                        self.gameObject.Key_up=1
                    elif event.key.keysym.sym == sdl2.SDLK_DOWN:
                        self.gameObject.Key_down=1
                    elif event.key.keysym.sym == sdl2.SDLK_RIGHT:
                        self.gameObject.Key_right=1
                    elif event.key.keysym.sym == sdl2.SDLK_LEFT:
                        self.gameObject.Key_left=1
                    elif event.key.keysym.sym == sdl2.SDLK_a:
                        self.gameObject.Key_action=1
                    if editmenunow!=self.editmenu:
                        sdl2.sdlmixer.Mix_PlayChannel(-1, opensound, 0)
                elif event.type == sdl2.SDL_KEYUP:
                    if event.key.keysym.sym == sdl2.SDLK_UP:
                        self.gameObject.Key_up=0
                    elif event.key.keysym.sym == sdl2.SDLK_DOWN:
                        self.gameObject.Key_down=0
                    elif event.key.keysym.sym == sdl2.SDLK_RIGHT:
                        self.gameObject.Key_right=0
                    elif event.key.keysym.sym == sdl2.SDLK_LEFT:
                        self.gameObject.Key_left=0
                    elif event.key.keysym.sym == sdl2.SDLK_a:
                        self.gameObject.Key_action=0
                    elif event.key.keysym.sym == sdl2.SDLK_ESCAPE:
                        self.gameObject.Running=False
                elif event.type == sdl2.SDL_MOUSEBUTTONUP:
                    if event.button.button==sdl2.SDL_BUTTON_LEFT:
                        if self.editmenu==True and mx<300:
                            print("MenuClick !")
                            X=0
                            Y=0
                            for i in self.menuSprites:
                                j=self.menuSprites[i]
                                search_x=25+X*60+self.editmenu_offset
                                search_y=30+Y*60+self.editmenu_offset_Y
                                X+=1
                                if X>3:
                                    X=0
                                    Y+=1
                                if mx<=search_x+50 and mx>=search_x and my<=search_y+50 and my>=search_y:
                                    self.editselection=i
                                    temp=sdl2.surface.SDL_CreateRGBSurface(0,50,50,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff)
                                    self.editcursor=self.gameObject.Textures[self.editselection].subsprite((0,0,32,32))
                                    sdl2.surface.SDL_BlitScaled(self.gameObject.Textures[self.editselection].surface,None,temp,sdl2.surface.SDL_Rect(0,0,32,32))
                                    sdl2.surface.SDL_SetSurfaceAlphaMod(temp,150)
                                    self.editcursor.surface=temp

                        elif self.editmode==True:
                            print("PlaceBlock !")
                            self.gameObject.Rectangles.append(Rectangle(int(mx/32)*32, 720-32 - int((my-16)/32)*32+16, 0, 32, 32))
                            self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].setTexture(self.editselection)
                            self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].ID=len(self.gameObject.Rectangles)
                            self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].Sprite=self.gameObject.Textures[self.editselection].subsprite((0,0,32,32))
                            self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].Type=["r",[32,32]]
                            self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].setPos(int(mx/32)*32,int((my-16)/32)*32+16)
                            self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].X=int(mx/32)*32
                            self.gameObject.Rectangles[len(self.gameObject.Rectangles)-1].Y=int((my-16)/32)*32+16
                            self.gameObject.RenderOutStream+="c,"+str(int(mx/32)*32)+","+str(int((my-16)/32)*32+16)+","+self.editselection+";"
                        else:
                            print("Fire !")
                            self.gameObject.Bullets.append(Objet(len(self.gameObject.Bullets)))
                            self.gameObject.Bullets[len(self.gameObject.Bullets)-1].setType("Bullet")
                            self.gameObject.Bullets[len(self.gameObject.Bullets)-1].setTexture(self.gameObject.localPlayer.selectedweapon)
                            self.gameObject.Bullets[len(self.gameObject.Bullets)-1].Sprite=self.gameObject.Textures[self.gameObject.localPlayer.selectedweapon].subsprite((0,0,32,32))
                            pos=[]
                            pos.append(self.gameObject.localPlayer.Units[self.gameObject.localPlayer.selectedUnit].getPos()[0]+25)
                            pos.append(self.gameObject.localPlayer.Units[self.gameObject.localPlayer.selectedUnit].getPos()[1]+25)
                            dx=mx-pos[0]
                            dy=my-pos[1]
                            hyp=math.sqrt(dx*dx+dy*dy)
                            sin=(dy/hyp)
                            angle=math.acos(dx/hyp)*360/(2*math.pi)
                            if (sin<0 and angle<0) or (sin>0 and angle>0):
                                angle=-angle
                            if angle<0:
                                angle+=360
                            print(angle)
                            angle=math.radians(angle)
                            pos[0]-=16
                            pos[1]-=16
                            self.gameObject.Bullets[len(self.gameObject.Bullets)-1].setPos(int(pos[0]),int(pos[1]))
                            self.gameObject.Bullets[len(self.gameObject.Bullets)-1].setDirection(angle)
                            self.gameObject.Bullets[len(self.gameObject.Bullets)-1].rayon = 16
                            self.gameObject.Bullets[len(self.gameObject.Bullets)-1].setVelocity(0.5)
                            self.gameObject.RenderOutStream+="cb,"+str(int(pos[0]))+","+str(int(pos[1]))+","+"dragon_fireball.png"+","+str(angle)+";"

                    if event.button.button==sdl2.SDL_BUTTON_RIGHT:
                        if self.editmode and not (self.editmenu==True and mx<300):
                            print("Deletion !")
                            X=0
                            Y=0
                            for i in self.gameObject.Rectangles:
                                mX=int(mx/32)*32
                                mY=int((my-16)/32)*32+16
                                search_X,search_Y=i.getPos()
                                if mX==search_X and mY==search_Y:
                                    print("Clicked on",i.Texture)
                                    del self.gameObject.Rectangles[self.gameObject.Rectangles.index(i)]
                                    self.gameObject.RenderOutStream+="d,"+str(mX)+","+str(mY)+";"
                    if event.button.button==sdl2.SDL_BUTTON_MIDDLE:
                        if self.editmode and not (self.editmenu==True and mx<300):
                            print("Selection !")
                            X=0
                            Y=0
                            for i in self.gameObject.Rectangles:
                                mX=int(mx/32)*32
                                mY=int((my-16)/32)*32+16
                                search_X,search_Y=i.getPos()
                                if mX==search_X and mY==search_Y:
                                    print("Selected:",i.Texture)
                                    temp=sdl2.surface.SDL_CreateRGBSurface(0,50,50,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff)
                                    self.editselection=i.Texture
                                    self.editcursor=self.gameObject.Textures[self.editselection].subsprite((0,0,32,32))
                                    sdl2.surface.SDL_BlitScaled(self.gameObject.Textures[self.editselection].surface,None,temp,sdl2.surface.SDL_Rect(0,0,32,32))
                                    sdl2.surface.SDL_SetSurfaceAlphaMod(temp,150)
                                    self.editcursor.surface=temp

            sdl2.ext.fill(spriteRenderer.surface, sdl2.ext.Color(0, 0, 0))
            sprites=[]
            #Rectangles et joueurs
            for i in self.gameObject.Rectangles:
                i.Sprite.position=i.X,i.Y
                sprites.append(i.Sprite)
            for i in self.gameObject.Bullets:
                i.Sprite.position=i.X,i.Y
                sprites.append(i.Sprite)
            for j in self.gameObject.Players:
                for i in j.Units:
                    if i.Sprite == None:
                        if i.Texture!=None:
                            i.Sprite=self.gameObject.Textures[i.Texture].subsprite((0,0,self.gameObject.Textures[i.Texture].size[0],self.gameObject.Textures[i.Texture].size[1]))
                            temp=sdl2.surface.SDL_CreateRGBSurface(0,50,50,32,0xff000000,0x00ff0000,0x0000ff00,0x000000ff)
                            sdl2.surface.SDL_BlitScaled(self.gameObject.Textures[i.Texture].surface,None,temp,sdl2.surface.SDL_Rect(0,0,50,50))
                            i.Sprite.surface=temp
                    i.Sprite.position=i.Unit_X,i.Unit_Y
                    sprites.append(i.Sprite)
            for i in self.gameObject.localPlayer.Units:
                i.Sprite.position=i.Unit_X,i.Unit_Y
                sprites.append(i.Sprite)
            #Interface
            if self.editmenu:
                if self.editmenu_offset<0:
                    self.editmenu_offset+=20
                    self.gameObject.Interface["editmenu"].Sprite.position=self.editmenu_offset,0
            else:
                if self.editmenu_offset>-300:
                    self.editmenu_offset-=20
                    self.gameObject.Interface["editmenu"].Sprite.position=self.editmenu_offset,0
            if self.editmenu_offset>-300:
                sprites.append(self.gameObject.Interface["editmenu"].Sprite)
                X=0
                Y=0
                if mx<300:
                    if my>690:
                        self.editmenu_offset_Y-=my-690
                    elif my<30:
                        self.editmenu_offset_Y+=30-my
                    length=len(self.menuSprites)
                    if self.editmenu_offset_Y>0:
                        self.editmenu_offset_Y=0
                    elif self.editmenu_offset_Y<-int(60*length/4)+660:
                        self.editmenu_offset_Y=-int(60*length/4)+660
                for i in self.menuSprites:
                    j=self.menuSprites[i]
                    j.position=25+X*60+self.editmenu_offset,30+Y*60+self.editmenu_offset_Y
                    if j.position[0]>0 and j.position[0]<1280:
                        sprites.append(j)
                    X+=1
                    if X>3:
                        X=0
                        Y+=1
            if self.editmode==True and not (self.editmenu and mx<300):
                self.editcursor.position=int(mx/32)*32,int((my-16)/32)*32+16
                sprites.append(self.editcursor)
            sprites.append(fpssprite)
            spriteRenderer.render(sprites)
            try:
                FPS=1/(time.time()-Clock)
                time.sleep(0.0166-time.time()+Clock)
            except:
                pass
