This program allows you to make shortcuts for Windows applications in the run prompt.  For example, configuring the characters 'ch' to represent 'chrome' or 'ie' to represent iexplore, will come in handy for the lazy typer!

Additionally, you can pass optional command line parameters, (should the application in question accept it). For example, Google Chrome has the ability to be launched with the --new-window <URL> option which opens <URL> in a new window. You can create a shortcut for this, such as "SO", that opens google chrome to the stackoverflow.com website.

To use, either compile the source or run the .exe that's already built ( Requires Visual C++ 2012 Redistributable x86 or later). Since it requires access to the registry, please run under elevated permissions.  You will be presented with a command line utility prompting you for the shortcut name ("ch", "ie", "py", "note"), etc. Hit enter.

Following this, you will be prompted to input the location of the executable (you can and should enable edit-mode by right clicking on the command prompt window so you can paste in long directory paths). 

Finally, you will have the opportunity to pass in additional parameters/switches to the program. Alluding to the example in the 2nd paragraph, here is where you would pass --new-window stackoverflow.com ( or any other switch for that matter).

Hit enter and you should see a successfull "Done!" message. Now, you can Windows+R (or however you used to get to the run prompt), and type in the new command shortcut you created in the 1st step!

Enjoy!!