#Front Page Dev:
#1)Must Provide a welcome message at the top of the screen
#2)** may Provide an image/logo(not currently available) to go below the welcome message **
#3)Prompt user to enter Email below the image logo
#4)Prompt user to enter Password below Email prompt
#5)Button to log in below the password prompt
#6)Must Have a new user register button below the Log in button
#7)Must have a 'Forgot Password' button beside the new user register button

#importing the used libraries
import tkinter as tk
window=tk.Tk()
#Displaying title of the proposed app
window.title(" Keyboard Display App ")
#Adjusting size of the app front page
window.geometry("600x400")

newlabel = tk.Label(text = " Welcome to the Keyboard Display app ")
tk.title(" Kindly login ")

#Title to begin obtaining Email from User
newlabel = tk.EmailPrompt(text = " Email ")
newlabel.grid(column=0,row=0)