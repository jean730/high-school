#!/bin/python3
import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk
import random
import time
def openAbout(a):
    About.show()
    about.show()
def addData(Current,Next,Chain):
    try :
        Chain[Current].append(Next)
    except KeyError:
        Chain[Current]=[]
        Chain[Current].append(Next)
    return Chain
def getNextWord(Word,Chain):
    try:
        index = random.randint(0,len(Chain[Word])-1)
        return Chain[Word][index]
    except KeyError:
        return "End"

def generate(a):
    text=TextEntry.get_buffer().props.text
    if len(text.split(" ")) < 25:
        Generated.set_label("Texte trop court")
    else:
        print(text)
        Chain={}
        splitText = text.split(" ")
        for i in range(0,len(splitText)-1):
            Chain = addData(splitText[i],splitText[i+1],Chain)
        Word=""
        while Word!=Word.capitalize() or Word == "":
            Word=random.choice(list(Chain))
        Text=""
        Text.join(Word)
        Writing = 1
        while Writing == 1 :
            Text+=Word+" "
            Word=getNextWord(Word,Chain)
            if len(Word.split("."))!=1 or len(Word.split("\n"))!=1 or len(Word.split("?"))!=1 or len(Word.split("!"))!=1:
                Writing = 0
        Generated.set_label(Text)
        if len(Text.split(" "))<8 or len(Text.split(" "))>15:
            generate(0)
            time.sleep(0.1) # Pour une jolie animation jusqu'a trouver une phrase de taille convenable.
window = Gtk.Window()
window.resizable=True
window.resize(800,600)
about = Gtk.Dialog(title="About",parent=window,modal=True)
About=Gtk.Label()
About.set_label("This program, made by jean bisel analyses the text put in the textview and pass it to a markov chain.\nThe said markov chain is then used to generate sentences.")
about.get_content_area().pack_end(About,True,False,10)
scroll=Gtk.ScrolledWindow()
scroll2=Gtk.ScrolledWindow()
Generated = Gtk.Label()
TextEntry=Gtk.TextView()
TextEntry.set_wrap_mode(Gtk.WrapMode.WORD_CHAR)
bar = Gtk.HeaderBar(title="Sentence Generator",subtitle="Generate sentences with markov chains.")
bar.set_show_close_button(True)
aboutButton = Gtk.Button.new_from_icon_name("help-about",Gtk.IconSize.LARGE_TOOLBAR)
aboutButton.connect("clicked", openAbout)
bar.pack_start(aboutButton)
aboutButton.show()
bar.show()
generateButton = Gtk.Button.new_with_label("Generate")
generateButton.connect("clicked", generate)
vbox = Gtk.VBox()
vbox.pack_start(scroll,True,True,0)
scroll.add(TextEntry)
TextEntry.show()
scroll.show()
vbox.pack_start(scroll2,False,False,10)
scroll2.add(Generated)
Generated.show()
scroll2.show()
vbox.pack_start(generateButton,False,False,0)
generateButton.show()
window.add(vbox)
vbox.show()
window.set_titlebar(bar)
window.show()
window.connect("destroy", Gtk.main_quit)
Gtk.main()
