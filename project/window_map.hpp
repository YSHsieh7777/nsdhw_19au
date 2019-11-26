//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "person.hpp"

class WindowMap
{
public:
    WindowMap();
    ~WindowMap();

    void init_walls();   
    const std::vector<SDL_Rect> & walls() const;
    void init_people();

    void update_people();
    void update_screen();

private:
    SDL_Renderer* gRenderer;
    SDL_Window* gWindow;
	std::vector<SDL_Rect> m_walls;
	std::vector<Person> lu_people;
    std::vector<Person> ld_people;
    std::vector<Person> ru_people;
    std::vector<Person> rd_people;

    const uint16_t SCREEN_WIDTH = 590;
    const uint16_t SCREEN_HEIGHT = 590;
};
