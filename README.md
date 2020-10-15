# C/C ++ Keylogger

A simple keylogger that records the key and the time in a .txt file. (If the file does not exist, the program (main.exe) will create one.)

The keylogger is called silently by a .bat file (run.bat) that runs a Chrome browser.
In addition, the .bat file is called whenever the .vbs is run.

That is, every time the .vbs file (or you can just add a shortcut (Google Chrome.lnk) and change the icon for a better trap) is executed, the keylogger is initialized, being possible to just interrupt it by terminating the process in the Task Manager or by restarting the system.

# How to avoid getting caught in a keylogger like this?

The most important thing is to check the shortcut properties of your usual program and see if the destination is a .vbs file. If so, DO NOT CLICK.
PS: This repository is for educational purposes. Spying on other people through a keylogger is a digital crime and I am NOT responsible for any attitude of those who use this program for other purposes.
