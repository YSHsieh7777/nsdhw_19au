#include <utility>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>
#include <stdlib.h>

class Person
{
public:
	Person(float x, float y , float r);
	~Person() = default;

	const float & x() const;
    float & x();
    const float & y() const;
    float & y();
	const float & x_speed() const;
    float & x_speed();
    const float & y_speed() const;
    float & y_speed();

	void update_speed();
	void move();

	void setColor(SDL_Renderer* );

	//Shows the Person on the screen
	void render(SDL_Renderer* );

private:
	float m_x, m_y;
	float m_radius;
	float m_x_speed, m_y_speed;

	uint8_t m_panic_degree;
	float m_moving_distance_last_few_seconds;  // A factor that affects panic_degree.
    bool m_dead;
};