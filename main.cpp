#include <GL/glew.h>
#include "engine.h"
#include "texture.h"
#include "config.h"

#define DRAW_DISTANCE 500.0F
#define SKYBOX_SIZE DRAW_DISTANCE / 2

float* cvar_width;
float* cvar_height;
float* cvar_vsync;
float* cvar_msaa;
float* cvar_sensitivity;
float* cvar_speed;
float* cvar_gravity;
float* cvar_bounce;
std::string* cvar_sky;

GLuint TexBox;
GLuint TexGround;
Uint32 gTexSkybox[6];

vec3_t Position(0.0F, 0.0F, 5.0F); // позиция камеры
vec2_t Rotation; // Вращение камеры

void drawcube(float size)
{
	glBindTexture(GL_TEXTURE_2D, TexBox);
	glBegin(GL_QUADS);
	glNormal3f(0.0F, 0.0F, 1.0F);
	glTexCoord2f(0.0F, 0.0F); glVertex3f(-size, -size, size);
	glTexCoord2f(1.0F, 0.0F); glVertex3f(size, -size, size);
	glTexCoord2f(1.0F, 1.0F); glVertex3f(size, size, size);
	glTexCoord2f(0.0F, 1.0F); glVertex3f(-size, size, size);
	glNormal3f(0.0F, 0.0F, -1.0F);
	glTexCoord2f(0.0F, 0.0F); glVertex3f(size, -size, -size);
	glTexCoord2f(1.0F, 0.0F); glVertex3f(-size, -size, -size);
	glTexCoord2f(1.0F, 1.0F); glVertex3f(-size, size, -size);
	glTexCoord2f(0.0F, 1.0F); glVertex3f(size, size, -size);
	glNormal3f(1.0F, 0.0F, 0.0F);
	glTexCoord2f(0.0F, 0.0F); glVertex3f(size, -size, size);
	glTexCoord2f(1.0F, 0.0F); glVertex3f(size, -size, -size);
	glTexCoord2f(1.0F, 1.0F); glVertex3f(size, size, -size);
	glTexCoord2f(0.0F, 1.0F); glVertex3f(size, size, size);
	glNormal3f(-1.0F, 0.0F, 0.0F);
	glTexCoord2f(0.0F, 0.0F); glVertex3f(-size, -size, -size);
	glTexCoord2f(1.0F, 0.0F); glVertex3f(-size, -size, size);
	glTexCoord2f(1.0F, 1.0F); glVertex3f(-size, size, size);
	glTexCoord2f(0.0F, 1.0F); glVertex3f(-size, size, -size);
	glNormal3f(0.0F, 1.0F, 0.0F);
	glTexCoord2f(0.0F, 0.0F); glVertex3f(-size, size, size);
	glTexCoord2f(1.0F, 0.0F); glVertex3f(size, size, size);
	glTexCoord2f(1.0F, 1.0F); glVertex3f(size, size, -size);
	glTexCoord2f(0.0F, 1.0F); glVertex3f(-size, size, -size);
	glNormal3f(0.0F, -1.0F, 0.0F);
	glTexCoord2f(0.0F, 0.0F); glVertex3f(-size, -size, -size);
	glTexCoord2f(1.0F, 0.0F); glVertex3f(size, -size, -size);
	glTexCoord2f(1.0F, 1.0F); glVertex3f(size, -size, size);
	glTexCoord2f(0.0F, 1.0F); glVertex3f(-size, -size, size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TexGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0F, 0.0F); glVertex3f(-10.0F, -size, 10.0F);
	glTexCoord2f(1.0F, 0.0F); glVertex3f(10.0F, -size, 10.0F);
	glTexCoord2f(1.0F, 1.0F); glVertex3f(10.0F, -size, -10.0F);
	glTexCoord2f(0.0F, 1.0F); glVertex3f(-10.0F, -size, -10.0F);
	glEnd();
}



void glDrawSkyBox()
{
	glDisable(GL_LIGHTING);

	float xn = Position.x - SKYBOX_SIZE,
		xm = Position.x + SKYBOX_SIZE,
		yn = Position.y - SKYBOX_SIZE,
		ym = Position.y + SKYBOX_SIZE,
		zn = Position.z - SKYBOX_SIZE,
		zm = Position.z + SKYBOX_SIZE;

	glBindTexture(GL_TEXTURE_2D, gTexSkybox[0]);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(xn, yn, zn);
	glTexCoord2i(1, 0); glVertex3f(xm, yn, zn);
	glTexCoord2i(1, 1); glVertex3f(xm, ym, zn);
	glTexCoord2i(0, 1); glVertex3f(xn, ym, zn);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, gTexSkybox[1]);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(xm, yn, zm);
	glTexCoord2i(1, 0); glVertex3f(xn, yn, zm);
	glTexCoord2i(1, 1); glVertex3f(xn, ym, zm);
	glTexCoord2i(0, 1); glVertex3f(xm, ym, zm);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, gTexSkybox[2]);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(xn, yn, zm);
	glTexCoord2i(1, 0); glVertex3f(xn, yn, zn);
	glTexCoord2i(1, 1); glVertex3f(xn, ym, zn);
	glTexCoord2i(0, 1); glVertex3f(xn, ym, zm);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, gTexSkybox[3]);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(xm, yn, zn);
	glTexCoord2i(1, 0); glVertex3f(xm, yn, zm);
	glTexCoord2i(1, 1); glVertex3f(xm, ym, zm);
	glTexCoord2i(0, 1); glVertex3f(xm, ym, zn);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, gTexSkybox[4]);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(xn, yn, zm);
	glTexCoord2i(1, 0); glVertex3f(xm, yn, zm);
	glTexCoord2i(1, 1); glVertex3f(xm, yn, zn);
	glTexCoord2i(0, 1); glVertex3f(xn, yn, zn);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, gTexSkybox[5]);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(xn, ym, zn);
	glTexCoord2i(1, 0); glVertex3f(xm, ym, zn);
	glTexCoord2i(1, 1); glVertex3f(xm, ym, zm);
	glTexCoord2i(0, 1); glVertex3f(xn, ym, zm);
	glEnd();

	glEnable(GL_LIGHTING);
}

void UpdateGame(float deltatime)
{
	static float movey = 0.0F;
	vec2_t movexz;

	if (GetKeyState(SDL_SCANCODE_W))
		movexz += rotate(Rotation.y);
	else if (GetKeyState(SDL_SCANCODE_S))
		movexz += rotate(Rotation.y + 180.0F);

	if (GetKeyState(SDL_SCANCODE_A))
		movexz += rotate(Rotation.y + 90.0F);
	else if (GetKeyState(SDL_SCANCODE_D))
		movexz += rotate(Rotation.y - 90.0F);

	if (GetKeyState(SDL_SCANCODE_SPACE) == 1)
	{
		if (Position.y <= 0.0F)
			movey = *cvar_bounce;
	}

	if (movexz.length() != 0.0F)
	{
		movexz = movexz.normalize();
		if (GetKeyState(SDL_SCANCODE_LSHIFT)) movexz *= 0.5F;
		Position.x -= movexz.x * *cvar_speed * deltatime;
		Position.z -= movexz.y * *cvar_speed * deltatime;
	}

	movey -= *cvar_gravity * deltatime;
	Position.y += movey * *cvar_speed * deltatime;

	if (Position.y < 0.0F) Position.y = movey = 0.0F;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Rotation -= GetRelativeMouse() * *cvar_sensitivity;

	Rotation.x = SDL_clamp(Rotation.x, -90.0F, 90.0F);
	if (Rotation.y < 0.0F) Rotation.y += 360.0F;
	else if (Rotation.y > 360.0F) Rotation.y -= 360.0F;

	glRotatef(-Rotation.x, 1.0, 0.0, 0.0);
	glRotatef(-Rotation.y, 0.0, 1.0, 0.0);

	glTranslatef(-Position.x, -Position.y, -Position.z);

	glDrawSkyBox();


	drawcube(1.0F);
}

void SetWindowTitle(SDL_Window* window, Uint32 ticks)
{
	static Uint32 frame = 1;
	static Uint32 preticks = 0;

	if (ticks - preticks >= 1000)
	{
		char title[22];
		sprintf(title, "3D %ix%i FPS: %i", (int)*cvar_width, (int)*cvar_height, frame);
		SDL_SetWindowTitle(window, title);

		preticks = ticks;
		frame = 1;
	}
	else frame++;
}

void ResizeWindow(int width, int height)
{
	glViewport(0, 0, width, height); // область просмотра
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)width / height, 0.1, DRAW_DISTANCE);
}

#define SDL_main main
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_OPENGL;
	Uint32 time, pretime = 0;
	float deltatime, dtrest;

	cvar_width = register_cvar("width", 800);
	cvar_height = register_cvar("height", 600);
	cvar_vsync = register_cvar("vsync", 0);
	cvar_msaa = register_cvar("msaa", 8);
	cvar_sensitivity = register_cvar("sensitivity", 0.2F);
	cvar_speed = register_cvar("speed", 10.0F);
	cvar_gravity = register_cvar("gravity", 10.0F);
	cvar_bounce = register_cvar("bounce", 3.0F);
	cvar_sky = register_cvar("sky", "sky");

	for (int i = 1; i < argc; i++)
	{
		char* a = &argv[i][2];
		if (argv[i][0] == '-') switch (argv[i][1])
		{
		case 'w': *cvar_width = (float)atof(a); break;
		case 'h': *cvar_height = (float)atof(a); break;
		case 'v': *cvar_vsync = (float)atof(a); break;
		case 'm': *cvar_msaa = (float)atof(a); break;
		case 't': flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN; break;
		}
	}

	if (*cvar_msaa > 1) // включаем MSAA
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, (int)*cvar_msaa);
	}

#define SDL_WIN_CENTERXY SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
	SDL_Window* window = SDL_CreateWindow("3D", SDL_WIN_CENTERXY, (int)*cvar_width, (int)*cvar_height, flags);

	SDL_SetRelativeMouseMode(SDL_TRUE); // скрытие курсора и непрерывное движение мыши
	SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval((int)*cvar_vsync);

	bool running = true;
	SDL_Event event;

	glEnable(GL_DEPTH_TEST); // тест глубины
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE); // убираем нелицевые грани
	glEnable(GL_TEXTURE_2D);

	if (*cvar_msaa > 1) // включаем MSAA
		glEnable(GL_MULTISAMPLE);

	ResizeWindow((int)*cvar_width, (int)*cvar_height);

	LoadTexture(TexBox, "texture/box.jpg");
	LoadTexture(TexGround, "texture/ground.jpg");




	LoadSkybox(gTexSkybox, (std::string("gamedir/material/skybox/") + *cvar_sky).c_str());




	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: running = false; break;
			case SDL_KEYUP:
				SetKeyState(event.key.keysym.scancode, 0);
				break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0)
					SetKeyState(event.key.keysym.scancode, 1);

				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					running = false;
				break;
			}
		}

		time = SDL_GetTicks();
		deltatime = 0.001F * (float)(time - pretime);
		pretime = time;

		SetWindowTitle(window, time);
		UpdateGame(deltatime);
		SDL_GL_SwapWindow(window);

		dtrest = roundf(1.0F / 30.0F - deltatime);
		if (dtrest > 0.0F) SDL_Delay((Uint32)(dtrest * 1000));
	}
	SDL_Quit();
	return 0;
}