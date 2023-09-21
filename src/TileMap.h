#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <vector>

#include "Component.h"
#include "GameObject.h"
#include "TileSet.h"

class TileMap: public Component {
	public:
		TileMap(GameObject& associated, std::string file, TileSet* tileSet);
		void Load(std::string file);
		void SetTileSet(TileSet* tileSet);
		int& At(int x, int y, int z = 0);
		void Render() override;
		void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
		int GetWidth() {return mapWidth;};
		int GetHeight() {return mapHeight;};
		int GetDepth() {return mapDepth;};
		void Update(float dt) override {};
		bool Is(std::string type) override;

	private:
		std::vector<int> tileMatrix;
		TileSet* tileSet;
		int mapWidth;
		int mapHeight;
		int mapDepth;
};

#endif
