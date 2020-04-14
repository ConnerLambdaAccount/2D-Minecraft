#include<cstdlib>
#include<ctime>

#include "structs/Block.cpp"

class MCWorld {
private:
	SDL_Texture* blockSprites;
	SDL_Rect blockClips[blockCount];
	
public:
	Block* map[screenTileWidth][screenTileHeight];
	
	void init(SDL_Renderer* ren) {
		// Load Spritesheet sections into SDL_Rects
		blockSprites = IMG_LoadTexture(ren, "assets/blocks.png");
		if (!blockSprites) {
			logSDLError();
		}
		// Load each block in the sheet into a SDL_Rect clip
		int x = 0;
		int y = 0;
		for(int i=0;i<blockCount;i++) {
			blockClips[i].x =  x;
			blockClips[i].y = y;
			blockClips[i].w = 16;
			blockClips[i].h = 16;
			
			// if last block on the X axis (for a 64x64 spritesheet)
			if(x == 48) {
				// Move to the first block on the row below
				x = 0;
				y += 16;
			} else {
				// Move to the next block on the current row
				x += 16;
			}
		}
		
		// init map tiles to NULL
		for(int tileY=0;tileY<screenTileHeight;tileY++) {
			for(int tileX=0;tileX<screenTileWidth;tileX++) {
				map[tileX][tileY] = nullptr;
			}
		}
	}
	
	void create() {

		const int bedrockLayerStart = screenTileHeight-1; // 1 layer bedrock 
		const int stoneLayerStart = bedrockLayerStart-3; // 3 layers stone
		const int dirtLayerStart = stoneLayerStart-1; // 1 layer dirt
		const int grassLayerStart = dirtLayerStart-1; // 1 layer grass

		blockType id;
		for(int y=grassLayerStart;y<screenTileHeight;y++) {

			switch(y) {
				case grassLayerStart:
					id = blockType::GRASS;
					break;
				case dirtLayerStart:
					id = blockType::DIRT;
					break;
				case stoneLayerStart:
					id = blockType::STONE;
					break;
				case bedrockLayerStart:
					id = blockType::BEDROCK;
					break;
				default:
					break;
			}

			for(int x=0;x<screenTileWidth;x++) {
				map[x][y] = new Block;
				map[x][y]->id = id;
			}

		}
	}

	void draw(SDL_Renderer* ren) {
		// Sky
		SDL_SetRenderDrawColor(ren, 128, 192, 255, 255);
		SDL_RenderFillRect(ren, NULL);
		
		// Blocks
		for(int y=0;y<screenTileHeight;y++) {
			for(int x=0;x<screenTileWidth;x++) {
				if(map[x][y] != nullptr) {
					// if grass/dirt is above grass, make the grass below dirt
					if(map[x][y]->id == blockType::GRASS && y-1 >= 0) {
						if(map[x][y-1] != nullptr) {
								map[x][y]->id = blockType::DIRT;
						}
					}
					// render
					renderTexture(blockSprites, ren, tileSize, tileSize, x*tileSize, y*tileSize, &blockClips[map[x][y]->id]);
				}
			}
		}
	}
	
	// X and Y of where the player is trying to go
	bool collision(int x, int y) {
		x = ts(x);
		y = ts(y);
		return (map[x][y] != nullptr || map[x][y+1] != nullptr);	
	}
	
	// X and Y of the player, x,y of the block
	bool reach(int x, int y, int playerX, int playerY) {
		playerX = ts(playerX);
		playerY = ts(playerY);
		printf("Player: (%i, %i)\n", playerX, playerY);
		printf("Block: (%i, %i)\n", x, y);
		
		return true;
	}
	
	void destroyBlock(int x, int y) {
		delete map[x][y];
		map[x][y] = nullptr;
	}
	
	void createBlock(int id, int x, int y, int playerX, int playerY) {
		playerX = ts(playerX);
		playerY = ts(playerY);
		
		// Player collision
		if((y == playerY || y == playerY+1) && x == playerX) {
			return;
		}
		
		// Check if block to build upon		
		for(int xOffset=-1;xOffset<=1;xOffset++) {
			if(map[x+xOffset][y] != nullptr) {
				if(map[x][y] == nullptr) {
					map[x][y] = new Block;
					map[x][y]->id = id;
				}
			}
		}
		
		for(int yOffset=-1;yOffset<=1;yOffset++) {
			if(map[x][y+yOffset] != nullptr) {
				if(map[x][y] == nullptr) {
					map[x][y] = new Block;
					map[x][y]->id = id;
				}
			}
		}
		
	}
	
	int ts(int coord) {
		return coord /= tileSize;
	}
	
	void free() {
		// Free Textures
		SDL_DestroyTexture(blockSprites);
		
		// Free map blocks
		for(int y=0;y<screenTileHeight;y++) {
			for(int x=0;x<screenTileWidth;x++) {
				delete map[x][y];
			}
		}
	}
};