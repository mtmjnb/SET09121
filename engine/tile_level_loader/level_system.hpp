#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>

class LevelSystem {
    public:
        enum Tile {EMPTY, START, END, WALL, ENEMY, WAYPOINT};

        static void load_level(const std::string&, float tile_size = 100.f);
        static void render();
        static sf::Color get_color(Tile tile);
        static void set_color(Tile tile, sf::Color color);
        static Tile get_tile(sf::Vector2i);  // Get Tile at grid coordinate
        static sf::Vector2f get_tile_position(sf::Vector2i); //  Get Screenspace coordinate of tile
        static Tile get_tile_at(sf::Vector2f);  // Get the tile at screenspace pos
        static int get_height();
        static int get_width();
        static float get_tile_size();
        static sf::Vector2f get_start_position();
        static std::vector<sf::Vector2i> find_tiles(Tile tile);

    protected:
        static std::unique_ptr<Tile[]> tiles;  // Internal array of tiles
        static int width;  // How many tiles wide is level
        static int height;  // How many tile high is level
        static sf::Vector2f offset;  // Screenspace offset of level, when rendered.
        static float tile_size;  // Screenspace size of each tile, when rendered.
        static std::map<Tile, sf::Color> colors;  // Color to render each tile type
        static sf::Vector2f start_position;  // Starting position for the player

        static std::vector<std::unique_ptr<sf::RectangleShape>> sprites;  // Array of sfml sprites of each tile
        static void build_sprites();  // Generate the sprites array

    private:
        LevelSystem() = delete;
        ~LevelSystem() = delete;
};