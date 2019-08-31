#!/bin/python3
import math
import turtle
class vertex(object):
    x=0
    y=0
    def __init__(self,x,y):
        self.x=x
        self.y=y
class Line(object):
    x1 = 0
    x2 = 0
    y1 = 0
    y2 = 0
    dx = 0
    dy = 0

    def __init__(self, x1, y1, x2, y2):
        self.x1 = x1
        self.x2 = x2
        self.y1 = y1
        self.y2 = y2
        self.dx=(x2-x1)
        self.dy=(y2-y1)
class Rect(object):
    x=0
    y=0
    sx=0
    sy=0
    lines=[]
    def __init__(self,x,y,sx,sy):
        self.x=x
        self.y=y
        self.sx=sx
        self.sy=sy
        lines.append(Line(x,y,x+sx,y))
        lines.append(Line(x,y+sy,x+sx,y+sy))
        lines.append(Line(x,y,x,y+sy))
        lines.append(Line(sx+x,y,x+sx,y+sy))
        
class Ray(object):
    x = 0
    dx = 0
    y = 0
    dy = 0

    def __init__(self, x, y, angle):
        self.x = x
        self.dx = math.cos(math.radians(angle))
        self.y = y
        self.dy = math.sin(math.radians(angle))
lines=[]
rects=[]
rects.append(Rect(-250,-250,500,500))
for i in range(0,10):
    rects.append(Rect(140*math.sin(i*math.pi/5)-20,140*math.cos(i*math.pi/5)-20,40,40))
rects.append(Rect(-40,-20,80,40))
for k in rects:
    for i in k.lines:
        lines.append(i)
t=turtle.Turtle()
turtle.bgcolor("black")
t.speed(0)
t.hideturtle()
angle=0
posX,posY=2,-2
time=0
turtle.tracer(0, 0)
while True:
    t.color("cyan")
    t.pensize(4)
    for i in lines:
        t.penup()
        t.setpos(i.x1,i.y1)
        t.pendown()
        t.setpos(i.x2,i.y2)
    turtle.update()
    t.clear()
    rays=[]
    angles=[]
    t.penup()
    time+=0.05
    vertices=[];
    posY=math.sin(time)*100
    posX=math.cos(time)*100
    for k in lines:
        
        angles.append(math.degrees(math.atan2(k.y1-posY,k.x1-posX))-0.0001)
        angles.append(math.degrees(math.atan2(k.y1-posY,k.x1-posX)))
        angles.append(math.degrees(math.atan2(k.y1-posY,k.x1-posX))+0.0001)
        angles.append(math.degrees(math.atan2(k.y2-posY,k.x2-posX))-0.0001)
        angles.append(math.degrees(math.atan2(k.y2-posY,k.x2-posX)))
        angles.append(math.degrees(math.atan2(k.y2-posY,k.x2-posX))+0.0001)
    angles.sort()
    for i in angles:
        rays.append(Ray(posX,posY,i))
    for i in rays:
        minT1=0
        minT2=0
        for j in lines:
            if (j.dx*i.dy - j.dy*i.dx) != 0:
                T2 = (i.dx*(j.y1-i.y) + i.dy*(i.x-j.x1))/(j.dx*i.dy - j.dy*i.dx)
            else:
                T2=0.5
            T1 = (j.x1+j.dx*T2-i.x)/i.dx
            if abs(T1)<abs(minT1) or minT1==0:
                if T1>0 and T2<1 and T2>0:# and T2>=0 and T2<=1:
                    minT1=T1
                    minT2=T2
        t.setpos(i.x,i.y)
        if minT1>0 and minT2<1 and minT2>0:# and T2>=0 and T2<=1:
            vertices.append(vertex(i.x+i.dx*minT1,i.y+i.dy*minT1))
    t.begin_fill()
    t.setpos(vertices[0].x,vertices[0].y)
    for i in range(0,len(vertices)):
        t.fillcolor(1,1,0.9)
        t.setpos(vertices[i].x,vertices[i].y)
        if i!=len(vertices)-1 :
            t.setpos(vertices[i+1].x,vertices[i+1].y)
        else:
            t.setpos(vertices[0].x,vertices[0].y)
    t.end_fill()
    t.setpos(posX,posY)
    t.pendown()
    t.color("red")
    t.pensize(10)
    t.setpos(posX,posY)
    t.penup()
input("press enter")
