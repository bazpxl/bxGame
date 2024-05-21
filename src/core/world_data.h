//
// Created by bzl on 21.05.2024.
//

#pragma once

#include <libs/json.hpp>

#include "global.h"

struct Tile{
    u16 type {};
    u8  assetIndex {};
};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

struct Layer{
    Vector<Tile> tiles {};
    bool isVisible = true;

};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
class TileMap{
public:
    Vector<Layer> layer;
    u8 tileSize = 16;

    explicit TileMap(const char * filepath = BasePath"assets/map.json")
    {
        loadFromJson(filepath);
    };
    explicit TileMap(
            Vector<Layer> layer_ = {{{{1, 1}, {1, 1}}, true}},
            u8 tileSize_ = 32
            ) : layer(std::move(layer_)), tileSize(tileSize_){}

    ~TileMap() = default;


    void saveToJson(const std::string& filename) {
        using namespace nlohmann;
        json j;

        for ( auto& l : layer) {
            json layerJson;
            for (const auto& t : l.tiles) {
                nlohmann::json tileJson;
                tileJson["type"] = t.type;
                tileJson["assetIndex"] = t.assetIndex;
                layerJson["tiles"].push_back(tileJson);
            }
            layerJson["isVisible"] = l.isVisible;
            j["layer"].push_back(layerJson);
        }

        j["tileSize"] = tileSize;

        std::ofstream file(filename);
        if(file.is_open()) {
            file << j;
            print("{} \n", j);
        }else {
            print("Error: Could not open {}", filename);
            exit(3);
        }
    }

    void loadFromJson(const std::string& filename) {
        using namespace nlohmann;
        std::ifstream file(filename);
        if (!file.is_open()) {
            print("Error: Could not open {}", filename);
            exit(3);
        };
        json j;
        file >> j;

        layer.clear();
        for (const auto& l : j["layer"]) {
            Layer layer_;
            for (const auto& t : l["tiles"]) {
                Tile tile;
                tile.type = t["type"];
                tile.assetIndex = t["assetIndex"];
                layer_.tiles.push_back(tile);
            }
            layer_.isVisible = l["isVisible"];
            layer.push_back(layer_);
        }

        tileSize = j["tileSize"];
    }

};


// inline void to_json(nlohmann::json &j, const Tile &p) {
//     j = nlohmann::json{{"type",       p.type},
//              {"assetIndex", p.assetIndex}};
// }
//
// inline void from_json(const nlohmann::json &j, Tile &p) {
//     j.at("type").get_to(p.type);
//     j.at("assetIndex").get_to(p.assetIndex);
// }
//
// inline void to_json(nlohmann::json &j, const Layer &p) {
//     j = nlohmann::json{{"tiles",     p.tiles},
//              {"isVisible", p.isVisible}};
// }
//
// inline void from_json(const nlohmann::json &j, Layer &p) {
//     j.at("tiles").get_to(p.tiles);
//     j.at("isVisible").get_to(p.isVisible);
// }
//
// inline void to_json(nlohmann::json &j, const TileMap &p) {
//     j = nlohmann::json{{"layer",    p.layer},
//              {"tileSize", p.tileSize}};
// }
//
// inline void from_json(const nlohmann::json &j, TileMap &p) {
//     j.at("layer").get_to(p.layer);
//     j.at("tileSize").get_to(p.tileSize);
// }


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------




