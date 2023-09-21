#ifndef TILESET_H
#define TILESET_H

#include <string>

#include "Sprite.h"
#include "GameObject.h"

class TileSet {
	public:
		TileSet(int tileWidth, int tileHeight, std::string file);
		~TileSet();
		void RenderTile(unsigned int index, float x, float y);
		int GetTileWidth(){return tileWidth;};
		int GetTileHeight(){return tileHeight;};
	
	private:
		Sprite* tileSet;
		GameObject* go;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;
};

#endif
