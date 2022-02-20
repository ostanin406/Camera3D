#include <GL/glew.h>
#include "engine.h"
#include "texture.h"

#define DRAW_DISTANCE 500.0F
#define SKYBOX_SIZE DRAW_DISTANCE / 2

cvar_t cv_width("width", 800);
cvar_t cv_height("height", 600);
cvar_t cv_vsync("vsync", 0);
cvar_t cv_msaa("msaa", 8);
cvar_t cv_sensitivity("sensitivity", 0.2F);
cvar_t cv_speed("speed", 10.0F);
cvar_t cv_gravity("gravity", 10.0F);
cvar_t cv_bounce("bounce", 3.0F);
cvar_t cv_sky("sky", "sky");

GLuint TexBox;
GLuint TexGround;


Uint32* gTexSkybox;


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
			movey = cv_bounce.get_float();
	}

	if (movexz.length() != 0.0F)
	{
		movexz = movexz.normalize();
		if (GetKeyState(SDL_SCANCODE_LSHIFT)) movexz *= 0.5F;
		Position.x -= movexz.x * cv_speed.get_float() * deltatime;
		Position.z -= movexz.y * cv_speed.get_float() * deltatime;
	}

	movey -= cv_gravity.get_float() * deltatime;
	Position.y += movey * cv_speed.get_float() * deltatime;

	if (Position.y < 0.0F) Position.y = movey = 0.0F;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Rotation -= GetRelativeMouse() * cv_sensitivity.get_float();

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
		sprintf(title, "3D %ix%i FPS: %i", cv_width.get_int(), cv_height.get_int(), frame);
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

	for (int i = 1; i < argc; i++)
	{
		char* a = &argv[i][2];
		if (argv[i][0] == '-') switch (argv[i][1])
		{
		case 'w': cv_width.set_string(a); break;
		case 'h': cv_height.set_string(a); break;
		case 'v': cv_vsync.set_string(a); break;
		case 'm': cv_msaa.set_string(a); break;
		case 't': flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN; break;
		}
	}

	if (cv_msaa.get_int() > 1) // включаем MSAA
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, cv_msaa.get_int());
	}

#define SDL_WIN_CENTERXY SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
	SDL_Window* window = SDL_CreateWindow("3D", SDL_WIN_CENTERXY, cv_width.get_int(), cv_height.get_int(), flags);

	SDL_SetRelativeMouseMode(SDL_TRUE); // скрытие курсора и непрерывное движение мыши
	SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(cv_vsync.get_int());

	bool running = true;
	SDL_Event event;

	glEnable(GL_DEPTH_TEST); // тест глубины
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE); // убираем нелицевые грани
	glEnable(GL_TEXTURE_2D);

	if (cv_msaa.get_int() > 1) // включаем MSAA
		glEnable(GL_MULTISAMPLE);

	ResizeWindow(cv_width.get_int(), cv_height.get_int());

	TexBox = LoadTexture("texture/box.jpg");
	TexGround = LoadTexture("texture/ground.jpg");


	str_t dirgame = "gamedir/material/skybox/";
	dirgame += cv_sky.get_string();


	gTexSkybox = LoadSkybox(dirgame.cstr);




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