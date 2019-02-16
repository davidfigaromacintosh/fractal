#include <iostream>
#include <chrono>
#include <cstring>
#include <math.h>
#include <float.h>
#include <SDL2/SDL.h>

#ifdef _WIN32
#include <windows.h>
#endif

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

//SDL_Surface *surf;
//SDL_Texture *tex;
//SDL_Rect rect;

//TTF_Font *font;
//SDL_Color font_color = { 128, 0, 0 };

class z {	//This class defines complex numbers
			//Ta klasa definiuje liczby zespolone

	double re, im;

public:

	z() {
		re = 0;
		im = 0;
	}
	z(double _re, double _im) {
		re = _re;
		im = _im;
	}

	//Returns the RE value of Z
	//Zwraca wartość RE liczby Z
	double r() {
		return this->re;
	}
	//Returns the IM value of Z
	//Zwraca wartość IM liczby Z
	double i() {
		return this->im;
	}

	//Addition
	//Dodawanie
	z operator+ (const double _d) {
		return z(this->re + _d, this->im);
	}
	z operator+ (const z _z) {
		return z(this->re + _z.re, this->im + _z.im);
	}

	//Substracion
	//Odejmowanie
	z operator- (const double _d) {
		return z(this->re - _d, this->im);
	}
	z operator- (const z _z) {
		return z(this->re - _z.re, this->im - _z.im);
	}

	//Multiplication
	//Mnożenie
	z operator* (const double _d) {
		return z(this->re * _d, this->im * _d);
	}
	z operator* (const z _z) {
		return z((this->re * _z.re - this->im * _z.im),	//(ac - bd)
			(this->re * _z.im + this->im * _z.re));	//(ad + bc)i
	}

	//Division
	//Dzielenie
	z operator/ (const double _d) {
		return z(this->re / _d, this->im / _d);
	}
	z operator/ (const z _z) {
		return z((this->re * _z.re + this->im * _z.im) / (_z.re * _z.re + _z.im * _z.im),	//(ac + bd) / (c2 + d2)
			(this->im * _z.re - this->re * _z.im) / (_z.re * _z.re + _z.im * _z.im));	//(bc - ad)i / (c2 + d2)
	}

	//Print number Z using ostream
	//Drukowanie liczby Z przy użyciu ostream
	friend std::ostream& operator<<(std::ostream& os, const z& _z) {
		char str_re[256] = { 0 };
		char str_im[256] = { 0 };

		sprintf(str_re, "%.15g", _z.re);
		sprintf(str_im, "%.15g", _z.im);

		os << str_re;
		if (!(_z.re < 0)) os << '+';
		os << str_im << 'i';

		return os;
	}
};

//This returns number Z as a string
//Ta funkcja zwraca łańcuch znaków przedstawiający liczbę zespoloną
/*
char* zdisp(z _z) {
	static char temp[256] = { 0 };
	sprintf_s(temp, sizeof(temp), "(%.15g, %.15g)", _z.r(), _z.i() );
	return temp;
}
*/

//Conjecture
//Sprzężenie zespolone
z conj(z _z) {
	return z(_z.r(), -_z.i());
}

//Absolute value
//Moduł (wartość bezwzględna)
double abs(z _z) {
	return sqrt(_z.r() * _z.r() + _z.i() * _z.i());
}

/*===========================================================================================*/

#define WIDTH 640
#define HEIGHT 640

#define BORDER 2

int main(int argc, char **argv) {

    #ifdef __linux__
	std::cout << "\033]0;(= OwO =)\007";
	#elif _WIN32
    SetConsoleTitleA("(= OwO =)");
	#endif


	char tempstr[256];

	//Initiate SDL
	//Inicjacja SDL
	std::cout << "Initializing SDL...";
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::cout << "Oops, couldn't init SDL :(\n" << SDL_GetError() << std::endl;
		exit(0xF19A20);
	}
	std::cout << " Done!\n";

	//std::cout << "Initializing TTF...";
	//if (TTF_Init() == -1) {
	//	std::cout << "Oops, couldn't init TTF :(\n" << TTF_GetError() << std::endl;
	//	exit(0xF19A20);
	//}
	//std::cout << " Done!\n";

	//Creating the SDL window
	//Tworzymy okno w SDL
	std::cout << "Creating a window...";
	if ((window = SDL_CreateWindow("(= OwO =)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN)) == NULL) {
		std::cout << "Oops, couldn't create a window :(\n" << SDL_GetError() << std::endl;
		exit(0xF19A20);
	}
	std::cout << " Done!\n";

	//Creating the SDL window
	//Tworzymy okno w SDL
	std::cout << "Creating a renderer...";
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		std::cout << "Oops, couldn't create a renderer :(\n" << SDL_GetError() << std::endl;
		exit(0xF19A20);
	}
	std::cout << " Done!\n";

	//Coordinations
	//Współrzędne
	double X = 0, Y = 0, R = 1;

	//Complex
	//Zespolone
	z Z, C;

	//Iterations
	//Iteracje
	unsigned long long int it = 10;

	//What fractal?
	//Jaki fraktal?
	unsigned short int type = 0;

	_START:

    #ifdef __linux__
	system("clear");
	#elif _WIN32
    system("cls");
	#endif
	
	std::cout << std::flush;

	std::cout << "Choose a fractal!\n0 = Mandelbrot 2\n1 = Mandelbrot 3\n2 = Mandelbrot 4\n3 = Burning Ship\n>>> ";
	std::cin >> type;

	std::cout << "\nEnter the X coordinate (double, from -2 to +2)\n>>> ";
	std::cin >> X;
	if (X < -2) { X = -2; }
	if (X > 2) { X = 2; }

	std::cout << "\nEnter the Y coordinate (double, from -2 to +2)\n>>> ";
	std::cin >> Y;
	if (Y < -2) { Y = -2; }
	if (Y > 2) { Y = 2; }

	std::cout << "\nEnter the zoom ratio (double, must be greater than DBL_MIN and smaller than 2)\n>>> ";
	std::cin >> R;
	if (R < DBL_MIN) { R = DBL_MIN; }
	if (R > 2) { R = 2; }

	std::cout << "\nEnter the iteration count (unsigned long long int, not smaller than 1)\n>>> ";
	std::cin >> it;
	if (it < 1) { it = 1; }

	//Sets the title of the window
	//Ustawia tytuł okna
	switch (type) {
		case 1: {
			strcpy(tempstr, "Mandelbrot 3");
			break;
		}
		case 2: {
			strcpy(tempstr, "Mandelbrot 4");
			break;
		}
		case 3: {
			strcpy(tempstr, "The Burning Ship");
			break;
		}
		default: {
			strcpy(tempstr, "Mandelbrot 2");
			break;
		}
	}
	sprintf(tempstr, "%s:   X: %.16g   Y: %.16g   R: %.16g   Iterations: %llu", tempstr, X, Y, R, it);
	SDL_SetWindowTitle(window, tempstr);

	//Shows the window
	//Pokazuje okno
	SDL_ShowWindow(window);

	std::cout <<
		"\nRenderer information:"	<< std::endl <<
		"F = " << type				<< std::endl <<
		"X = " << X					<< std::endl <<
		"Y = " << Y					<< std::endl <<
		"R = " << R					<< std::endl <<
		"I = " << it				<< std::endl <<
	std::endl;

	//if ((font = TTF_OpenFont("ariblk.ttf", 18)) == NULL) {
	//	std::cout << "Oops, couldn't load a font :(\n" << TTF_GetError() << std::endl;
	//	exit(0xF19A20);
	//}
	//surf = TTF_RenderText_Solid(font, tempstr, font_color);
	//tex = SDL_CreateTextureFromSurface(renderer, surf);

	//rect.x = 5;
	//rect.y = 5;
	//rect.w = surf->w;
	//rect.h = surf->h;

	auto start = std::chrono::steady_clock::now();

	std::cout << "Rendering..." << std::endl;

	for (int j = 0; j < HEIGHT; j++) {	//Y coord

		for (int i = 0; i < WIDTH; i++) {	//X coord

			Z = z(0, 0);
			C = z(

				R * ( -BORDER + ((double)i / WIDTH ) * BORDER*2 ) + X,
				R * ( -BORDER + ((double)j / HEIGHT) * BORDER*2 ) - Y

			);

			//std::cout << "C = " << C;

			for (int k = 0; k <= it; k++) {

				switch (type) {
					case 1: {	//The Mandelbrot Set 3 formula: Z -> Z3 + C
						Z = Z * Z * Z;
						Z = Z + C;
						break;
					}
					case 2: {	//The Mandelbrot Set 4 formula: Z -> Z4 + C
						Z = Z * Z * Z * Z;
						Z = Z + C;
						break;
					}
					case 3: {	//The Burning ship formula: Z -> ( Re(Z) + Im(Z)i )2 + C
						Z = z(abs(Z.r()), abs(Z.i())) * z(abs(Z.r()), abs(Z.i()));
						Z = Z + C;
						break;
					}
					default: {	//The Mandelbrot Set 2 formula: Z -> Z2 + C
						Z = Z * Z;
						Z = Z + C;
						break;
					}
				}

				//If Z crosses the border, stop calculating
				//Jeżeli Z przekroczy granicę, nie licz dalej
				if (!(abs(Z) < 2)) {
					SDL_SetRenderDrawColor(renderer,
						128 * (0.5 + sin(0.5*(double)k / M_PI) / 2),
						255 * (0.5 + sin(0.5*(double)k / M_PI) / 2),
						255,
						255
					);
					SDL_RenderDrawPoint(renderer, i, j);
					//std::cout << " Failed!" << std::endl;
					break;
				}

				//If the point belongs to the set, colour it black
				//Jeżeli punkt należy do zbioru, pokoloruj go na czarno
				if (k == it) {
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderDrawPoint(renderer, i, j);
					//std::cout << " Passed!" << std::endl;
					break;
				}

			}

		}
	}

	auto end = std::chrono::steady_clock::now();
	double diff = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / 1000000000;

	//SDL_RenderCopy(renderer, tex, NULL, &rect);
	SDL_RenderPresent(renderer);

	//TTF_CloseFont(font);
	//SDL_FreeSurface(surf);
	//SDL_DestroyTexture(tex);

	printf("Done! Took %f seconds!\n", diff);
	std::cout << "Close the window to render another fractal or close the console to exit!";

	while (1) {

		while (SDL_PollEvent(&event)) {
			switch (event.type) {

				case SDL_QUIT: {
					//SDL_DestroyWindow(window);
					//SDL_Quit();
					//TTF_Quit();
					//return 0;
					SDL_HideWindow(window);
					goto _START;
				}

			}
		}

	}

	return 0;
}
