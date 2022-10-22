Farzan Mosayyebi -400522175-

"Conway's Game Of Life"

Needed files for compilation:

  Libraries:
	lib/libbfd.a
	lib/libopcodes.a
	lib/libsfml-graphics-s.a
	lib/libsfml-system-s.a
	lib/libsfml-window-s.a
	lib/libsfml-graphics.a
	lib/libsfml-main.a
	lib/libsfml-system.a
	lib/libsfml-window.a

  Include Files:
	All of the files in include/SFML folder are needed.

  dll files:
	libgcc_s_seh_64-1.dll
	libstdc++_64-6.dll
	openal32.dll
	sfml-graphics-2.dll
	sfml-system-2.dll
	sfml-window-2.dll


Needed files for opening the executable file (TheGameOfLife.exe):

	libgcc_s_seh_64-1.dll
	libstdc++_64-6.dll
	openal32.dll
	sfml-graphics-2.dll
	sfml-system-2.dll
	sfml-window-2.dll


This program is developed in "DEV C++".
Shown below are the compilers with which the program is tested:
	TDM-GCC 9.2.0 64-bit
	TDM-GCC 4.9.2 64-bit

After running the program, it will start and proceed to the next level by itself.

The program is set to continue up to 10 levels by default.
And The Frame rate limit is set to 1 FPS.

You can change the above mentioned items in the program (each item is indicated with " /***/ "):

	- The nubmer of levels --> line 79.
	- Frame rate limit --> line 83.

	- Range of random number of alive cells in the first level --> line 31.
	(maximum size is 10000) 