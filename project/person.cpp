#include "person.hpp"

std::map<uint8_t, uint8_t> panic_to_red = {{0, 0}, {1, 255}};
std::map<uint8_t, uint8_t> panic_to_green = {{0, 0}, {1, 0}};
std::map<uint8_t, uint8_t> panic_to_blue = {{0, 0}, {1, 0}};

Person::Person(float x, float y , float r)
{
    m_position = std::make_pair(x, y);
    m_radius = r;
    m_moving_direction = std::make_pair(0, 0);

    m_panic_degree = 0;
	m_moving_distance_last_few_seconds = 0;  // A factor that affects panic_degree.
    m_dead = false;  
}

void Person::move()
{
    //Move the Person left or right
    m_position.first += m_moving_direction.first;

    //If the Person collided or went too far to the left or right
	if((m_position.first-m_radius < 0) || (m_position.first+m_radius > SCREEN_WIDTH))
    {
        m_position.first -= m_moving_direction.first;
    }

    //Move the Person up or down
    m_position.second += m_moving_direction.second;

    //If the Person collided or went too far up or down
    if((m_position.second-m_radius < 0) || (m_position.second+m_radius > SCREEN_HEIGHT))
    {
        //Move back
        m_position.second -= m_moving_direction.second;
    }
}

void Person::setColor()
{
    SDL_SetRenderDrawColor(gRenderer, panic_to_red[m_panic_degree], panic_to_green[m_panic_degree], panic_to_blue[m_panic_degree], 0xFF);
}

void Person::render()
{
    Person::setColor();

    const float diameter = (m_radius * 2);

    float x = (m_radius - 1);
    float y = 0;
    float tx = 1;
    float ty = 1;
    float error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(gRenderer, m_position.first + x, m_position.second - y);
        SDL_RenderDrawPoint(gRenderer, m_position.first + x, m_position.second + y);
        SDL_RenderDrawPoint(gRenderer, m_position.first - x, m_position.second - y);
        SDL_RenderDrawPoint(gRenderer, m_position.first - x, m_position.second + y);
        SDL_RenderDrawPoint(gRenderer, m_position.first + y, m_position.second - x);
        SDL_RenderDrawPoint(gRenderer, m_position.first + y, m_position.second + x);
        SDL_RenderDrawPoint(gRenderer, m_position.first - y, m_position.second - x);
        SDL_RenderDrawPoint(gRenderer, m_position.first - y, m_position.second + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}