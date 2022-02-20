from tkinter import *
import pyglet, os
import tkinter #For widget craftign
import serial #For reading the serial port

serialPort = serial.Serial(port = "COM3", baudrate = 9600, bytesize = 8, timeout = 2, stopbits = serial.STOPBITS_ONE) #Set up Serial port
serialString = ""#String to read into

pyglet.font.add_file('GARA.TTF')

root = Tk()
root.title("Keyboard")
root.geometry("1000x1400") #Create the "root" window for the widgets to be placed on

root.wm_attributes('-topmost', True) #Whether it stays on top
root.wm_attributes('-alpha', 0.9) #Transparency value from 0 (transparent) to 1 (opaque)

Row1 = ['`', '1', '2', '3','4','5','6','7','8','9','0','-','=',"BACKSPACE"]
Row2 = ['TAB','q','w','e','r','t','y','u','i','o','p','[',']','\\']
Row3 = ['CAPS LOCK', 'a', 's', 'd', 'f', 'g','h','j','k','l',';','\'', "ENTER"]
Row4 = ["SHIFT", 'z','x','c','v','b','n','m',',','.','/','SHIFT'] #Arrays containing all keys in the 4 rows in proper 

def printletter(letter):
    print(letter) #Prints the key's letter to the screen

keys = []  #Empty array to hold keys

def keypressfunction(x):  #Call when key is pressed
    print(x) #PRint the key being puhed to the terminal. Mostly for testing purposes
    if(keys[x].cget('relief') == RAISED):
        keys[x].configure(relief = SUNKEN)#If the key is raised, sink it
    else:#Otherwise
        keys[x].configure(relief = RAISED)#The key will be sunken, so raise it

def setWhite(): #Set black-on-white keyboard function
    for i in range(len(keys)): #Run through every key in the list
        keys[i].configure(bg = 'White', fg = 'Black')#Set a white background, black foreground
    
def setBlack(): #Set White-on-Black keyboard function
    for i in range(len(keys)):
        keys[i].configure(bg = 'Black', fg = 'White') #Same as previous, but black background white foreground

def SetContrast(option): #For the drop-down contrast menu
    if option == "White on Black": #If you select white on black
        print("White on Black")
        setWhite()#Call appropriate function (defined above)
    elif option == "Black on White":
        print("Black on White")#Else, if you selceted black on white
        setBlack()#Call appropriate function (defined above)
    else:
        print("Error") #For debugging. Won't come up.

value = int

def Read():  #Serial port reading code
    value = 0#Value will keep track of which key is being accessed
    if(serialPort.in_waiting > 0): #If there is a new input waiting to be read
        serialString = serialPort.readline()#Read it
        serialString = serialString.decode('Ascii')#Decode it into readable text
        #print(serialString) #Print for diagnostic purposes
        if(serialString[1] != 'd' and serialString[1] != 'x'):#Ignore diagnostic code we positioned in the arduino
            if(serialString[0] == 'A'):#Character 0 says which sensor it's reading on
             value = 29 #Set the value of value to align with the correct segment of keys
            elif(serialString[0] == 'C'):
              value = 42
            else:
                print("ERROR") #Error if no known boards are referenced
            value2 = int(serialString[2])#Character 2 is the pin number being touched
            value = value + value2#Add to value to go to the correct key
            if(serialString[4] == '0'): #Character 4 says if the key is touched or not
                keys[value].configure(relief = RAISED) #Raise the key if 0 for released
            elif(serialString[4] == '1'):
                keys[value].configure(relief = SUNKEN) #Lower the key if 1 for touched
            else:
                print("ERROR 2")  #If any other value, an error has occured
    root.after(1,Read) #Wait 1 ms, and repeat

selected = StringVar() #Define a string called "selected" for use in contrasttheme code

for i in range(14): #Run through row 1, which has 14 entries
    if(i == 13):  #All keys but "Backspace" are the same size, so Backspace needs it's own constructor
        TempKey = Label(text = Row1[i], relief=RAISED, bd = 8, width= 10, height = 2, bg = 'White', fg = 'Black', font = 'Arial 20 bold')
        #The backspace key has text from the array, is raised by default, has border size 8, width of 10, height of 2, a white background and black text, with Arial 20 bold font
    else:
        TempKey = Label(text = Row1[i], relief=RAISED, bd = 8, width= 4, height = 2, bg = 'White', fg = 'Black', font = 'Arial 20 bold')
        #Other keys are the same, but with a width of 4 instead of 10
    TempKey.place(x = i*90, y = 0) #plaace each key at an x-coordinate determined by how far into the array they are and a y-coordinate based on their row
    keys.append(TempKey)#Put that key in keys for adjustment purposes (mainly binding and contrast changes for now)
for i in range(14): #Same general procedure for all other rows of keys.  The ifs are for the abnormally sized keys
    if(i == 0):
        TempKey = Label(text = Row2[i], relief=RAISED, bd = 8, width= 8, height = 2, bg = 'White', fg = 'Black', font = 'Arial 20 bold')
        TempKey.place(x = 0, y = 90)
        keys.append(TempKey)
    else:
        TempKey = Label(text = Row2[i], relief=RAISED, bd = 8, width= 4, height = 2, bg = 'White', fg = 'Black', font = 'Arial 20 bold')
        TempKey.place(x = i*90 +70, y = 90)
        keys.append(TempKey)
for i in range(13):
    if(i == 0):
        TempKey = Label(text = Row3[i], relief=RAISED, bd = 8, width= 10, height = 2, bg = 'White', fg = 'Black', font = 'Arial 20 bold')
        TempKey.place(x = 0, y = 180)
        keys.append(TempKey)
    elif(i == 12):
        TempKey = Label(text = Row3[i], relief=RAISED, bd = 8, width= 10, height = 2, bg = 'White', fg = 'Black', font = 'GARA 20 bold')
        TempKey.place(x = i * 90 + 100, y = 180)
        keys.append(TempKey)
    else:
        TempKey = Label(text = Row3[i], relief=RAISED, bd = 8, width= 4, height = 2, bg = 'White', fg = 'Black', font = 'Arial 20 bold')
        TempKey.place(x = i*90 + 100, y = 180)
        keys.append(TempKey)
for i in range(12):
    if(i == 0):
        TempKey = Label(text = Row4[i], relief=RAISED, bd = 8, width= 12, height = 2, bg = 'White', fg = 'Black', font = 'Arial 20 bold')
        TempKey.place(x = 0, y = 270)
        keys.append(TempKey)
    elif(i == 11):
        TempKey = Label(text = Row4[i], relief=RAISED, bd = 8, width= 12, height = 2, bg = 'White', fg = 'Black', font = 'Arial 20 bold')
        TempKey.place(x = i*90 + 135, y = 270)
        keys.append(TempKey)
    else:
        TempKey = Label(text = Row4[i], relief=RAISED, bd = 8, width= 4, height = 2, bg = 'White', fg = 'Black', font = 'Arial 20 bold')
        TempKey.place(x = i*90 + 135, y = 270)
        keys.append(TempKey)

for i in range(len(keys)):  #Bind all keys to, when clicked with mouse1, call their keypressfunction (Defined above) to raise/lower them
    keys[i].bind("<Button-1>", lambda event, x = i: keypressfunction(x))

ContrastTheme = OptionMenu(root, selected, "White on Black", "Black on White" #Create the option menu for contrasttheme
    ,command= SetContrast).place(x = 500, y = 360)#And put it in a location not yet taken

root.after(1,Read)#1 ms after keyboard creation is finished, startreading the serialport

root.mainloop()#root.mainloop() is what makes the widget run. It's basically a while loop that say 'keep updatingt the widgets'