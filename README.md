# A simple C++ program that draws fractals!

The program can render following fractal sets:
* Julia Sets Z^2
* Julia Sets Z^3
* The Mandelbrot Set Z^2
* The Mandelbrot Set Z^3
* The Mandelbrot Set Z^4
* Inverse Mandelbrot
* Lambda Mandelbrot
* Tricorn
* The Burning Ship

#
## How to compile (Windows/Code::Blocks):
#### 1. Download SDL 2.0 MinGW Development Libraries:
<http://libsdl.org/download-2.0.php>

#### 2. Inside the downloaded tar archive, there should be a folder called SDL2-2.X.X. Inside that folder, there should be another folder called "i686-w64-mingw32". This folder contains 32-bit libraries. Extract these somewhere, e.g.:
`C:\dev\i686-w64-mingw32`
#### Note: If you want to use 64-bit libraries, they are included within the "x86_64-w64-mingw32" folder.

#### 3. Open Code::Blocks and create an empty project. Go to properties (Project -> Properties), select the "Project settings" tab and click the "Project's build options" button.

#### 4. Go to the "Search directories" tab then to the "Compiler" tab. Click the "Add" button and select the include folder located in the folder with our libraries, e.g.:
`C:\dev\i686-w64-mingw32\include`

#### 5. Go to the "Linker" tab and add a folder that contains archive libraries (.a files), e.g.:
`C:\dev\i686-w64-mingw32\lib`

#### 6. Now go to the "Linker settings" tab and in the "Other linker options" area type the following:
`-lmingw32 -lSDL2main -lSDL2`

#### 7. Go to the "Compiler settings" tab, go to the "Compiler flags" tab and make sure if the "Have g++ follow the C++11 ISO C++ language standard" is set.

#### 8. Click "OK"

#### 9. Go to the "Build targets" tab and select the "Console application" type.

#### 10. Build and run the program.

#
## How to compile (Linux):
#### 1. Make sure you have already installed the following libraries:
* libsdl2-2.0
* libsdl2-dev
* g++-multilib
#### You can install these with the following commands:
`sudo apt install libsdl2-2.0`

`sudo apt install libsdl2-dev`

`sudo apt install g++-multilib`

#### 2. Open the terminal and type in the following command:

`g++ main.cpp -o fractal -lstdc++ -lm -lSDL2`

#### 3. Run the program:

`./fractal`

#
## Images generated by the program:
![alt text][img0]
![alt text][img1]
![alt text][img2]
![alt text][img3]
![alt text][img4]
![alt text][img5]
![alt text][img6]

(C) 2019 David Macintosh

[img0]: https://github.com/dawid9554/fractal/blob/master/img/img0.png
[img1]: https://github.com/dawid9554/fractal/blob/master/img/img1.png
[img2]: https://github.com/dawid9554/fractal/blob/master/img/img2.png
[img3]: https://github.com/dawid9554/fractal/blob/master/img/img3.png
[img4]: https://github.com/dawid9554/fractal/blob/master/img/img4.png
[img5]: https://github.com/dawid9554/fractal/blob/master/img/img5.png
[img6]: https://github.com/dawid9554/fractal/blob/master/img/img6.png
