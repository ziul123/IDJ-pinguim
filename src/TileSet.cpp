#include <string>

#include "TileSet.h"
#include "GameObject.h"

TileSet::TileSet(int tW, int tH, std::string file){
	tileWidth = tW;
	tileHeight = tH;
	go = new GameObject();
	tileSet = new Sprite(*go, file);
	go->AddComponent(tileSet);
	columns = tileSet->GetWidth() / tW;
	rows = tileSet->GetHeight() / tH;
}

TileSet::~TileSet(){
	delete tileSet;
	delete go;
}

void TileSet::RenderTile(unsigned int index, float x, float y){
	if ((int) index >= 0 && (int) index < rows * columns){
		tileSet->SetClip((index % columns) * tileWidth, (index / columns) * tileHeight, tileWidth, tileHeight);
		tileSet->Render(x, y);
	}
}

