class MCPlayer {
private:
	SDL_Texture* playerSprites;
	SDL_Rect playerClips[3];
	SDL_Rect *playerForward, *playerRight, *playerLeft, *currentSprite;

public:
	int x;
	int y;
	
	// Load spritesheet into SDL_Rects
	void init(SDL_Renderer* ren) {
		playerSprites = IMG_LoadTexture(ren, "assets/player.png");
		if(!playerSprites) {
			logSDLError();
		}
		// Load each player sprite in the sheet into a SDL_Rect clip
		for(int i=0;i<3;i++) {
			playerClips[i].x = i*16;
			playerClips[i].y = 0;
			playerClips[i].w = 16;
			playerClips[i].h = 32;
		}
		
		playerForward = &playerClips[0];
		playerRight = &playerClips[1];
		playerLeft = &playerClips[2];
	}

	// Create player at (20, 22)
	void create() {
		x = (screenTileWidth/2) * tileSize;
		y = (screenTileHeight-8) * tileSize;
		currentSprite = playerForward;
	}

	void draw(SDL_Renderer* ren) {
		renderTexture(playerSprites, ren, tileSize, tileSize*2, x, y, currentSprite);
	}
	
	void moveUp() {
		if(y-tileSize >= 0) {
			y -= tileSize;
			if(currentSprite != playerForward) resetSprite();
		}
	}
	
	void moveDown() {
		if(y+tileSize <= RESOLUTION_H-(tileSize*3)) {
			y += tileSize;
			if(currentSprite != playerForward) resetSprite();
		}
	}

	void moveLeft() {
		if(x-tileSize >= 0) {
			x -= tileSize;
			if(currentSprite != playerLeft) currentSprite = playerLeft;
		} else {
			x = RESOLUTION_W - tileSize;
		}
	}

	void moveRight() {
		if(x+tileSize <= RESOLUTION_W-tileSize) {
			x += tileSize;
			if(currentSprite != playerRight) currentSprite = playerRight;
		} else {
			x = 0;
		}
	}
	
	int ts(int coord) {
		return coord /= tileSize;
	}
	
	void resetSprite() {
		currentSprite = playerForward;
	}

	void free() {
		SDL_DestroyTexture(playerSprites);
	}
};