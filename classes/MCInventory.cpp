class MCInventory {
private:
	SDL_Texture* inventorySprites;
	SDL_Rect hotbar, hbOverlay;
public:
	blockType hbSelection;
	
	void init(SDL_Renderer* ren) {
		inventorySprites = IMG_LoadTexture(ren, "assets/inventory.png");
		if(!inventorySprites) {
			logSDLError();
		}
		hotbar.x = 0;
		hotbar.y = 0;
		hotbar.w = 160;
		hotbar.h = 16;
		
		hbOverlay.x = 160;
		hbOverlay.y = 0;
		hbOverlay.h = 16;
		hbOverlay.w = 16;
		
		
		hbSelection = blockType::BEDROCK;
	}
	
	void create() {
		
	}
	
	void draw(SDL_Renderer* ren) {
		renderTexture(inventorySprites, ren, tileSize*10, tileSize, (RESOLUTION_W/2)-(tileSize*5), 0, &hotbar);
		renderTexture(inventorySprites, ren, tileSize, tileSize, (RESOLUTION_W/2)-(tileSize*5) + (tileSize*hbSelection), 0, &hbOverlay);
		return;
	}
	void free() {
		SDL_DestroyTexture(inventorySprites);
	}
};