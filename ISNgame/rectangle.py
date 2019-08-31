#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 28 15:57:15 2019

"""
from objet import *
from rectangle import *
from math import *

class Rectangle(Objet):

  #constructeur
  def __init__(self, x0, y0, a, l, h):

    self.l = l
    self.h = h
    self.pO = [x0, y0]
    self.a = a

    #changement de repere des points du rectangle
    self.maj(x0, y0, a)

    #calcul de l'encombrement du rectangle
    self.MinMax()

  #changement de repere des points du rectangle
  def maj(self, x, y, a):

    self.pO = [x,y]
    self.a = a

    #coordonnees dans le rep. global en fonction des coordonnees dans le rep. local
    self.point = [self.changement_repere([0,0]), \
                  self.changement_repere([self.l,0]), \
                  self.changement_repere([self.l,self.h]), \
                  self.changement_repere([0,self.h])]
    #calcul de l'encombrement
    self.MinMax()

  #encombrement du rectangle
  def MinMax(self):

    self.xmin = self.point[0][0]
    self.xmax = self.point[0][0]
    self.ymin = self.point[0][1]
    self.ymax = self.point[0][1]

    for p in self.point[1:]:
      #ieme point
      if p[0] < self.xmin:
        self.xmin = p[0]

      if p[0] > self.xmax:
        self.xmax = p[0]

      if p[1] < self.ymin:
        self.ymin = p[1]

      if p[1] > self.ymax:
        self.ymax = p[1]

  #changement de repere d'un point
  def changement_repere(self, p):

    # v1 = v1' . cos(a) - v2' . sin(a)
    # v2 = v1' . sin(a) + v2' . cos(a)

    pg = [0,0]
    pg[0] = self.pO[0] + p[0] * cos(self.a) - p[1] * sin(self.a)
    pg[1] = self.pO[1] + p[0] * sin(self.a) + p[1] * cos(self.a)

    return pg

      #Ajouter le rectangle a un Canvas tk
  def Dessiner(self, canv, h, color):

    #liste des points du rectangle
    l = []
    for p in self.point:
      l.append(p[0])
      l.append(h - p[1])

    canv.create_polygon(l, outline=color, fill='', width=2)
    #canv.create_polygon(l, fill=color)

