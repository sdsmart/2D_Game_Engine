2D Game Engine Built With Allegro
---------------------------------
This project is a 2D Game Engine built with the Allegro c++ library.

It is meant to be a starting platform to build and customize 2D games.

The engine uses Allegro to run through the game loop at a constant 60 fps
independent of personal computer hardware.

The engine is ready to extend by adding classes to manage sprites and render
them on the screen.

The Allegro API can be found here: [Allegro API](http://liballeg.org/a5docs/trunk)

Build Instructions
------------------
This project was originally built within Visual Studio Community 2016.

You can install Allegro using Visual Studio's built in Nuget Package Manager.
More information on this can be found here: [Allegro Nuget Package](https://www.nuget.org/packages/Allegro/)

Alternatively you can install Allegro manually and link the library with
the project to build it.
[Allegro Wiki](https://wiki.allegro.cc/index.php?title=Getting_Started)

Run Instructions
----------------
To run this project, simply run the project in Visual Studio or run the executable created after compiling.

While running, a black screen should appear. If f1 is pressed, statistics
for the engine's running status should appear on screen to ensure everything
is working properly.
