#!/bin/python3
import random
text="""Bonjour je m'appelle jean, je suis un enfant marrant et j'ai un chien jaune et blanc. Je suis né le 15 novembre 2001 et j'ai 17 ans. J'ai des amis et je suis gentil."""
fichier=open("input","r")
text=fichier.read()
Chain={}

def addData(Current,Next):
    try :
        Chain[Current].append(Next)
    except KeyError:
        Chain[Current]=[]
        Chain[Current].append(Next)
def getNextWord(Word):
    try:
        index = random.randint(0,len(Chain[Word])-1)
        return Chain[Word][index]
    except KeyError:
        return "End"

splitText = text.split(" ")
for i in range(0,len(splitText)-1):
    addData(splitText[i],splitText[i+1])
#print(Chain)

Word=random.choice(list(Chain))
#while Word!=Word.capitalize() or Word == "":
#    Word=random.choice(list(Chain))
Text=""
Text.join(Word)
while len(Word.split("."))==1 and len(Word.split("\n"))==1 and len(Word.split("?"))==1 and len(Word.split("!"))==1:
    Text+=Word+" "
    Word=getNextWord(Word)
print(Text)
