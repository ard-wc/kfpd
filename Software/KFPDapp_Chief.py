#Front Page Dev:
#1)Must Provide a welcome message at the top of the screen - DONE
#2)** may Provide an image/logo(not currently available) to go below the welcome message **
#3)Prompt user to enter Email below the image logo - DONE
#4)**Prompt user to enter Password below Email prompt**
#5)Button to log in below the Username / password prompt
#6)Must Have a new user 'register' button below the Log in button
#7)Must have a 'Forgot Password' button beside the new user register button

#importing the used libraries
from tkinter import * #imports tkinter objects
from functools import partial # Helps to reuse some functions through the code

tkwindow=Tk()
#Displaying title of the proposed app
tkwindow.title(" Keyboard Display App ")
#Adjusting size of the app front page
tkwindow.geometry("600x400")
newlabel = Label(text = " Welcome to the Keyboard Display app ")
#tk.title(" Kindly login ")

#Importing the image logo, if being used.

#Title to begin obtaining Email from User
#Using defensive programming to ensure the correct email format is used
def Login(username,password):
    print("Email entered: ", username.get())
    print("Password entered: ", password.get)
    return
#Email login text entry box
usernameLabel = Label(tkwindow, text = "Username").grid(row = 0, column = 0)
username = StringVar()
usernameIn = Entry (tkwindow, textvar = username).grid(row = 0, column = 1)
#Defensive programming code for email login
#username = input("Email: ")
#while "@" not in username:
   # username = input("Incorrect Email. Email does not contain the symbol '@' in it\n Kindly re-enter your email: ")
   # if "." not in username:
    #    username = input("Incorrect Email. Email does not contain the symbol '.' in it\n Kindly re-enter your email: ")
#print("The email is valid")

#Password login text entry box
passwordLabel = Label(tkwindow, text = "Password").grid(row = 1, column = 0)
password = StringVar()
passwordEntry = Entry(tkwindow, textvar = password, show = '*').grid(row = 1, column = 1)
#password = input ("Password: ")
#Defensive programming for password login
#If password does not match saved password for username account, throw error message indicating "Password mismatch"

#Button to login 
#validLogin = partial(validLogin, username , password)
#ButtonLogin = Button(tkwindow, text = "Login", command = validLogin)

#newlabel.grid(column=0,row=0)
tkwindow.mainloop() #End of program
