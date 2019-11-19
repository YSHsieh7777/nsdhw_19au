#include <utility>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>

typedef std::pair<float, float> pos_t; 
typedef std::pair<float, float> vel_t; 

const int SCREEN_WIDTH = 590;
const int SCREEN_HEIGHT = 590;

extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindow;

class Person
{
public:
	Person(float x, float y , float r);

	//Moves the Person and checks collision
	void move();

	void setColor();

	//Shows the Person on the screen
	void render();

private:
	pos_t m_position;
	float m_radius;
	vel_t m_moving_direction;

	uint8_t m_panic_degree;
	float m_moving_distance_last_few_seconds;  // A factor that affects panic_degree.
    bool m_dead;
};