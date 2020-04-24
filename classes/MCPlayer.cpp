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
		x = (screenTileWidth/2);
		y = (screenTileHeight-8);
		currentSprite = playerForward;
	}

	void draw(SDL_Renderer* ren) {
		renderTexture(playerSprites, ren, tileSize, tileSize*2, x*tileSize, y*tileSize, currentSprite);
	}
	
	void moveUp() {
		if(y-1 >= 0) {
			y -= 1;
			if(currentSprite != playerForward) resetSprite();
			printLocation();
		}
	}
	
	void moveDown() {
		if(y+1 <= screenTileHeight-3) {
			y += 1;
			if(currentSprite != playerForward) resetSprite();
			printLocation();
		}
	}

	void moveLeft() {
		if(x-1 >= 0) {
			x -= 1;
			if(currentSprite != playerLeft) currentSprite = playerLeft;
			printLocation();
		}
	}

	void moveRight() {
		if(x+1 <= screenTileWidth-1) {
			x += 1;
			if(currentSprite != playerRight) currentSprite = playerRight;
		} else {
			x = 0;
		}
		printLocation();
	}
	
	void printLocation() {
		printf("Player: (%i, %i)\n", x, y);
	}
	
	void resetSprite() {
		currentSprite = playerForward;
	}

	void free() {
		SDL_DestroyTexture(playerSprites);
	}
};