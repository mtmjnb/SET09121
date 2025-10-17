#include <iostream>
#include <fstream>
#include "level_system.hpp"
#include "renderer.hpp"

std::unique_ptr<LevelSystem::Tile[]> LevelSystem::tiles;
int LevelSystem::width;
int LevelSystem::height;
sf::Vector2f LevelSystem::offset(0.0f, 0.0f);

float LevelSystem::tile_size(100.f);
std::vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::sprites;

std::map<LevelSystem::Tile, sf::Color> LevelSystem::colors{{WALL, sf::Color::White}, {END, sf::Color::Red}};
sf::Vector2f LevelSystem::start_position;

int LevelSystem::get_height() {return LevelSystem::height;}
int LevelSystem::get_width() {return LevelSystem::width;}
float LevelSystem::get_tile_size() {return LevelSystem::tile_size;}

sf::Vector2f LevelSystem::get_start_position() {
    return LevelSystem::start_position;
}

sf::Color LevelSystem::get_color(LevelSystem::Tile tile) {
    auto it = LevelSystem::colors.find(tile);
    if (it == LevelSystem::colors.end()) {
        LevelSystem::colors[tile] = sf::Color::Transparent;
    }
    return LevelSystem::colors[tile];
}

void LevelSystem::set_color(LevelSystem::Tile tile, sf::Color color) {}

void LevelSystem::load_level(const std::string& path, float tile_size) {
    LevelSystem::tile_size = tile_size;
    int width = 0, height = 0;
    std::string buffer;

    // Load in file to buffer
    std::ifstream fh(path);
    if (fh.good()) {
        buffer.assign(
            (std::istreambuf_iterator<char>(fh)),
            (std::istreambuf_iterator<char>())
        );
    } else {
        throw std::string("Couldn't open level file: ") + path;
    }
    int x = 0;

    std::vector<Tile> temp_tiles;
    for (int i = 0; i < buffer.size(); ++i) {
        const char tile = buffer[i];
        switch (tile) {
            case 'w':
                temp_tiles.push_back(WALL);
                break;
            case 's':
                temp_tiles.push_back(START);
                LevelSystem::start_position = get_tile_position({x, height});
                break;
            case 'e':
                temp_tiles.push_back(END);
                break;
            case ' ':
                temp_tiles.push_back(EMPTY);
                break;
            case '+':
                temp_tiles.push_back(WAYPOINT);
                break;
            case 'n':
                temp_tiles.push_back(ENEMY);
                break;
            case '\n':
                if (width == 0) {  // If we haven't written width yet
                    width = i;  // Set width
                }
                x = -1;  // Gets increment to start at index 0 after switch
                height++;
                break;
            default:
                std::cout << "Don't know what tile type \"" << tile << "\" is" << std::endl;
        }
        x++;
    }
    if (temp_tiles.size() != (width * height)) {
        throw std::string("Can't parse level file: ") + path;  // The file should end with a newline
    }
    LevelSystem::tiles = std::make_unique<Tile[]>(width * height);
    LevelSystem::width = width;  // Set static class vars
    LevelSystem::height = height;
    std::copy(temp_tiles.begin(), temp_tiles.end(), &LevelSystem::tiles[0]);
    std::cout << "Level " << path << " Loaded. " << width << "x" << height << std::endl;
    build_sprites();
}

//level_system.cpp
void LevelSystem::build_sprites() {
    LevelSystem::sprites.clear();
    for (int y = 0; y < LevelSystem::get_height(); ++y) {
        for (int x = 0; x < LevelSystem::get_width(); ++x) {
            std::unique_ptr<sf::RectangleShape> shape = std::make_unique<sf::RectangleShape>();
            shape->setPosition(get_tile_position({x, y}));
            shape->setSize(sf::Vector2f(LevelSystem::tile_size, LevelSystem::tile_size));
            shape->setFillColor(get_color(get_tile({x, y})));
            LevelSystem::sprites.push_back(move(shape));
        }
    }
}

sf::Vector2f LevelSystem::get_tile_position(sf::Vector2i position) {
    return (sf::Vector2f(position.x, position.y) * LevelSystem::tile_size);
}

LevelSystem::Tile LevelSystem::get_tile(sf::Vector2i position) {
    if (position.x > LevelSystem::width || position.y > LevelSystem::height) {
        throw std::string("Tile out of range: ") + std::to_string(position.x) + "," + std::to_string(position.y) + ")";
    }
    return LevelSystem::tiles[(position.y * static_cast<size_t>(LevelSystem::width)) + position.x];
}

LevelSystem::Tile LevelSystem::get_tile_at(sf::Vector2f vector) {
    auto a = vector - LevelSystem::offset;
    if (a.x < 0 || a.y < 0) {
        throw std::string("Tile out of range ");
    }
    return get_tile(sf::Vector2i((vector - LevelSystem::offset) / (LevelSystem::tile_size)));
}

void LevelSystem::render() {
    for (size_t i = 0; i < LevelSystem::width * LevelSystem::height; ++i) {
        Renderer::queue(LevelSystem::sprites[i].get());
    }
}