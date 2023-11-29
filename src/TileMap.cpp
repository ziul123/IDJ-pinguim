#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include "GameObject.h"
#include "TileSet.h"
#include "TileMap.h"

#ifdef _WIN32
char* strtok_r(char *str, const char *delim, char **nextp)
{
    char *ret;
    if (str == NULL)
    {
        str = *nextp;
    }
    str += strspn(str, delim);
    if (*str == '\0')
    {
        return NULL;
    }
    ret = str;
    str += strcspn(str, delim);
    if (*str)
    {
        *str++ = '\0';
    }
    *nextp = str;
    return ret;
}
#endif

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet): Component(associated){
	Load(file);
	this->tileSet = tileSet;
}

void TileMap::Load(std::string file){
	FILE* f = fopen(file.c_str(), "r");
	if (!f){
		std::cout << "Tilemap not found" << std::endl;
		throw;
	}

	long int str_len;
	fseek(f, 0L, SEEK_END);
	str_len = ftell(f);
	rewind(f);

	char* orig = (char*) calloc(str_len, sizeof(char));
	char* aux = orig;
	char c;
	while ((c = fgetc(f)) != EOF){
		if (std::isspace(c))
			continue;
		*aux = c;
		aux++;
	}
	fclose(f);

	aux = orig;
	std::string width(strtok_r(aux, ",", &aux));
	std::string height(strtok_r(aux, ",", &aux));
	std::string depth(strtok_r(aux, ",", &aux));
	mapWidth = std::stoi(width);
	mapHeight = std::stoi(height);
	mapDepth = std::stoi(depth);

	char* token;
	while ((token = strtok_r(aux, ",", &aux))){
		std::string tile(token);
		tileMatrix.push_back(std::stoi(tile) - 1);
	}
	free(orig);
}

void TileMap::SetTileSet(TileSet* tileSet){
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
	int i = x + mapWidth * y + mapWidth * mapHeight * z;
	return tileMatrix[i];
}

void TileMap::Render(){
	for (int i = 0; i < mapDepth; i++)
		RenderLayer(i, associated.box.x, associated.box.y);
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
	int tileWidth = tileSet->GetTileWidth();
	int tileHeight = tileSet->GetTileHeight();
	for (int y = 0; y < mapHeight; y++){
		for (int x = 0; x < mapWidth; x++){
			tileSet->RenderTile((unsigned int) At(x, y, layer), (float) (x * tileWidth) - cameraX, (float) (y * tileHeight) - cameraY);
		}
	}
}

bool TileMap::Is(std::string type){
	return type == "TileMap";
}
