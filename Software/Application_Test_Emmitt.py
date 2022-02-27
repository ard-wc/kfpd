from tkinter import *
import multiprocessing
import tkinter
import pyglet, os
pyglet.font.add_file('Garamond Regular.ttf')
from win32gui import SetWindowLong, GetWindowLong, SetLayeredWindowAttributes
from win32con import WS_EX_LAYERED, WS_EX_TRANSPARENT, GWL_EXSTYLE
from win32api import RGB






root = Tk()
keyboard = root.winfo_id()
root.title("Keyboard")
root.geometry("1000x1000")
root.resizable(TRUE, TRUE)
root.wm_attributes('-topmost', True)
root.config(bg = '#000000')
root.attributes('-transparentcolor', '#000000', '-topmost', 1)
root.attributes('-alpha', 0.5)
root.overrideredirect(True)
styles = GetWindowLong(keyboard, GWL_EXSTYLE)
styles = WS_EX_LAYERED | WS_EX_TRANSPARENT
SetWindowLong(keyboard, GWL_EXSTYLE, styles)
SetLayeredWindowAttributes(keyboard, RGB(0,0,0), 255, 0x00000001)

Row1 = ['`', '1', '2', '3','4','5','6','7','8','9','0','-','=',"BACKSPACE"]
Row2 = ['TAB','q','w','e','r','t','y','u','i','o','p','[',']','\\']
Row3 = ['CAPS LOCK', 'a', 's', 'd', 'f', 'g','h','j','k','l',';','\'', "ENTER"]
Row4 = ["SHIFT", 'z','x','c','v','b','n','m',',','.','/','SHIFT']
def printletter(letter):
    print(letter)

def test(event):
    print("Press")


keys = []


def keypressfunction(x):
    print(x)
    if(keys[x].cget('relief') == RAISED):
        keys[x].configure(relief = SUNKEN)
    else:
        keys[x].configure(relief = RAISED)
def setWhite():
    for i in range(len(keys)):
        keys[i].configure(bg = 'White', fg = '#000001')

def setBlack():
    for i in range(len(keys)):
        keys[i].configure(bg = '#000001', fg = 'White')

def SetContrast(option):
    if option == "White on Black":
        print("White on Black")
        setWhite()
    elif option == "Black on White":
        print("Black on White")
        setBlack()
    else:
        print("Error")
            

selected = StringVar()
for i in range(14):
    if(i == 13):  
        TempKey = Label(text = Row1[i], relief=RAISED, bd = 8, width= 10, height = 2, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
    else:
        TempKey = Label(text = Row1[i], relief=RAISED, bd = 8, width= 4, height = 2, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
    TempKey.place(x = i*90, y = 0)
    keys.append(TempKey)
for i in range(14):
    if(i == 0):
        TempKey = Label(text = Row2[i], relief=RAISED, bd = 8, width= 8, height = 2, bg = 'White', fg = '#000001', font = ('Garamond', 24))
        TempKey.place(x = 0, y = 90)
        keys.append(TempKey)
    else:
        TempKey = Label(text = Row2[i], relief=RAISED, bd = 8, width= 4, height = 2, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = i*90 +70, y = 90)
        keys.append(TempKey)
for i in range(13):
    if(i == 0):
        TempKey = Label(text = Row3[i], relief=RAISED, bd = 8, width= 10, height = 2, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = 0, y = 180)
        keys.append(TempKey)
    elif(i == 12):
        TempKey = Label(text = Row3[i], relief=RAISED, bd = 8, width= 10, height = 2, bg = 'White', fg = '#000001', font = ('Arial', 24))
        TempKey.place(x = i * 90 + 100, y = 180)
        keys.append(TempKey)
    else:
        TempKey = Label(text = Row3[i], relief=RAISED, bd = 8, width= 4, height = 2, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = i*90 + 100, y = 180)
        keys.append(TempKey)
for i in range(12):
    if(i == 0):
        TempKey = Label(text = Row4[i], relief=RAISED, bd = 8, width= 12, height = 2, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = 0, y = 270)
        keys.append(TempKey)
    elif(i == 11):
        TempKey = Label(text = Row4[i], relief=RAISED, bd = 8, width= 12, height = 2, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = i*90 + 135, y = 270)
        keys.append(TempKey)
    else:
        TempKey = Label(text = Row4[i], relief=RAISED, bd = 8, width= 4, height = 2, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = i*90 + 135, y = 270)
        keys.append(TempKey)


ContrastTheme = OptionMenu(root, selected, "White on Black", "Black on White"
    ,command= SetContrast).place(x = 500, y = 360)

def close():
    root.destroy()

butt = Button(root, text = " TERMINATE ", bg = 'Red', bd = 50, command = close)
butt.place(x = 600, y = 350)
root.mainloop()
