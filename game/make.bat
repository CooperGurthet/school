gcc .\src\*.c -lpdcurses -I.\include\ -o rogue
@REM compiles all .c files in src folder and includes all .h files in include folder to include library
rogue.exe
@REM runs the newly created executable
Del rogue.exe
@REM deletes the executable after quitting the game

@REM gcc -g C:\Users\coope\Documents\code\arduino\game\src\main.c -lpdcurses -IC:\Users\coope\Documents\code\arduino\game\include\ -o rogue
@REM https://u.osu.edu/cstutorials/2018/09/28/how-to-debug-c-program-using-gdb-in-6-simple-steps/