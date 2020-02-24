#ifndef GS2EMU_TGAMEWINDOW_H
#define GS2EMU_TGAMEWINDOW_H

#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "IConfig.h"

#include "TClient.h"

#if SDL_VERSION_ATLEAST(2,0,0)
#define GameTexture SDL_Texture
#define RENDER_RESIZE_EVENT event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED
#else
#define GameTexture SDL_Surface
#define SDL_Keysym SDL_keysym
#define RENDER_RESIZE_EVENT event.type == SDL_VIDEORESIZE
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class TImage;

class TGameWindow
{
public:
	explicit TGameWindow(TClient* server);

	~TGameWindow();

	void init();

	bool doMain();

	void drawText(const char *text);

	static void renderSetAlpha(GameTexture * texture, Uint8 alpha);

	static void renderDestroyTexture(GameTexture * texture);

	static void renderQueryTexture(GameTexture * texture, int *w, int *h);

	GameTexture * renderLoadImage(const char *file);

	void renderBlit(GameTexture * texture, SDL_Rect * srcrect, SDL_Rect * dstrect);

	void renderClear();

private:

	TClient * client;
	TImage *tileset{};

	void keyPressed(SDL_Keysym * keysym);

	void keyReleased(SDL_Keysym * keysym);

	std::chrono::high_resolution_clock::time_point startTimer;
	Sint16 screenWidth;
	Sint16 screenHeight;
	const static int FRAMES_PER_SECOND = 60;
	SDL_Event event;
	int frame = 0;
	Timer fps;

	int prevY;
	std::map<Sint32, bool> keys;
	TTF_Font *font;
	static int BUFFER;

	void sdlEvents();

	void drawAnimation(CAnimationObjectStub * animationObject, int x, int y, float time);

	void drawScreen();

#if SDL_VERSION_ATLEAST(2,0,0)
	SDL_Window *window{};
	SDL_Renderer *renderer{};
#else
	SDL_Surface *screen{};
#endif

	void createRenderer();

	void renderPresent();

	GameTexture * renderText(TTF_Font *font, const char *text, SDL_Color fg);

	void renderToggleFullscreen();

	void renderChangeSurfaceSize();

	int fps_current;
};

#endif //GS2EMU_TGAMEWINDOW_H
