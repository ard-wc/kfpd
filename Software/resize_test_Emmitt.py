from tkinter import *
import multiprocessing
import tkinter
import pyglet, os
pyglet.font.add_file('Garamond Regular.ttf')




root = Tk()
keyboard = root.winfo_id()
root.title("Keyboard")
root.geometry("1400x550")
root.wm_attributes('-topmost', True)
root.attributes('-alpha', 1.0)

Row1 = ['`', '1', '2', '3','4','5','6','7','8','9','0','-','=',"BACKS"]
Row2 = ['TAB','q','w','e','r','t','y','u','i','o','p','[',']','\\']
Row3 = ['CAPS LOCK', 'a', 's', 'd', 'f', 'g','h','j','k','l',';','\'', "ENTER"]
Row4 = ["SHIFT", 'z','x','c','v','b','n','m',',','.','/','SHIFT']
def printletter(letter):
    print(letter)

def test(event):
    print("Press")


keys = []

size = 1.30


size2 = int(size/100)
print(size2)
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
        TempKey = Label(text = Row1[i], compound=CENTER, image = PhotoImage(), relief=RAISED, bd = 8, width = 145 * size, height = 75 * size, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
    else:
        TempKey = Label(text = Row1[i], compound=CENTER, image = PhotoImage(), relief=RAISED, bd = 8, width = 75 * size, height = 75 * size, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
    TempKey.place(x = size *i*90 , y = size * 0)
    keys.append(TempKey)
for i in range(14):
    if(i == 0):
        TempKey = Label(text = Row2[i], compound=CENTER, image = PhotoImage(), relief=RAISED, bd = 8, width = 145 * size, height = 75 * size, bg = 'White', fg = '#000001', font = ('Garamond', 24))
        TempKey.place(x = size *0, y = size * 90)
        keys.append(TempKey)
    else:
        TempKey = Label(text = Row2[i], compound=CENTER, image = PhotoImage(), relief=RAISED, bd = 8, width = 75 * size, height = 75 * size, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = size *i*90 + 70, y = size * 90)
        keys.append(TempKey)
for i in range(13):
    if(i == 0):
        TempKey = Label(text = Row3[i], compound=CENTER, image = PhotoImage(), relief=RAISED, bd = 8, width = 175 * size, height = 75 * size, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = size *0, y = size * 180)
        keys.append(TempKey)
    elif(i == 12):
        TempKey = Label(text = Row3[i], compound=CENTER, image = PhotoImage(), relief=RAISED, bd = 8, width = 135 * size, height = 75 * size, bg = 'White', fg = '#000001', font = ('Arial', 24))
        TempKey.place(x = size *i * 90 + 100, y = size * 180)
        keys.append(TempKey)
    else:
        TempKey = Label(text = Row3[i], compound=CENTER, image = PhotoImage(), relief=RAISED, bd = 8, width = 75 * size, height = 75 * size, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = size *i*90 + 100, y = size * 180)
        keys.append(TempKey)
for i in range(12):
    if(i == 0):
        TempKey = Label(text = Row4[i], compound=CENTER, image = PhotoImage(), relief=RAISED, bd = 8, width = 210 * size, height = 75 * size, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = size *0, y = size * 270)
        keys.append(TempKey)
    elif(i == 11):
        TempKey = Label(text = Row4[i], compound=CENTER, image = PhotoImage(), relief=RAISED, bd = 8, width = 190 * size, height = 75 * size, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = size *i*90 + 135, y = size * 270)
        keys.append(TempKey)
    else:
        TempKey = Label(text = Row4[i], compound=CENTER, image = PhotoImage(), relief=RAISED, bd = 8, width = 75 * size, height = 75 * size, bg = 'White', fg = '#000001', font = ('Garamond Regular', 24))
        TempKey.place(x = size *i*90 + 135, y = size * 270)
        keys.append(TempKey)


ContrastTheme = OptionMenu(root, selected, "White on Black", "Black on White"
    ,command= SetContrast).place(x = size *500, y = 360)

def close():
    root.destroy()

butt = Button(root, text = " TERMINATE ", bg = 'Red', bd = 50, command = close)
butt.place(x = size *600, y = size * 350)
root.mainloop()
