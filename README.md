# HOW TO USE

1. You must have a windows machine with [gcc](https://sourceforge.net/projects/mingw-w64/) installed.

2. Clone the project.
```
git clone https://github.com/Silme94/Tcp-Reverse-Shell
cd Tcp-Reverse-Shell
```
3. Compile the source code using Makefile.
```
cd bin
mingw32-make
```
4. Start a server, you can use netcat as server :
```
ncat -nlvp 1234
```
5. Execute the file, and the shell should be opened in the server side.

![App Screenshot](https://github.com/Silme94/Tcp-Reverse-Shell/blob/main/screenshot.png)
