#include "classes/MCWorld.cpp"
#include "classes/MCPlayer.cpp"
#include "classes/MCInventory.cpp"

void mainEventLoop(SDL_Renderer* ren) {
	
	// Initial setup and presentation
	class MCWorld world;
	class MCPlayer player;
	class MCInventory inventory;
	
	world.init(ren);
	player.init(ren);
	inventory.init(ren);
	
	world.create();
	player.create();
	inventory.create();
	
	world.draw(ren);
	player.draw(ren);
	inventory.draw(ren);
	
	bool quit = false;
	bool falling = false;
	int fallTimer = 0;
	
	while(!quit) {
		SDL_Event e;
		while(SDL_PollEvent(&e) && !quit) {
			// Keyboard Events
			if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_q:
						quit = true;
						break;
					case SDLK_SPACE:
						if(!falling) {
							if(!world.collision(player.x, player.y-1)) {
								player.moveUp();
								falling = true;
							}
						}
						break;
					case SDLK_d:
						if(!world.collision(player.x+1, player.y)) {
							player.moveRight();
							if(!world.collision(player.x, player.y+1))
								falling = true;
						}
						break;
					case SDLK_a:
						if(!world.collision(player.x-1, player.y)) {
							player.moveLeft();
							if(!world.collision(player.x, player.y+1))
								falling = true;
						}
						break;
					case SDLK_1:
						inventory.hbSelection = blockType::BEDROCK;
						break;
					case SDLK_2:
						inventory.hbSelection = blockType::GRASS;
						break;
					case SDLK_3:
						inventory.hbSelection = blockType::DIRT;
						break;
					case SDLK_4:
						inventory.hbSelection = blockType::STONE;
						break;
					case SDLK_5:
						inventory.hbSelection = blockType::DIAMOND;
						break;
					case SDLK_6:
						inventory.hbSelection = blockType::COAL;
						break;
					case SDLK_7:
						inventory.hbSelection = blockType::IRON;
						break;
					case SDLK_8:
						inventory.hbSelection = blockType::GOLD;
						break;
					case SDLK_9:
						inventory.hbSelection = blockType::REDSTONE;
						break;
					case SDLK_0:
						inventory.hbSelection = blockType::EMERALD;
						break;
				}
			}
			if(e.type == SDL_KEYUP) {
				if(e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_d) {
					player.resetSprite();
				}
			}
			
			// Mouse Events
			if(e.type == SDL_MOUSEBUTTONDOWN) {
				int x = (e.button.x - (e.button.x % tileSize))/tileSize;
				int y = (e.button.y - (e.button.y % tileSize))/tileSize;
				if(e.button.button == SDL_BUTTON_LEFT) {
					world.destroyBlock(x, y);
				}
				if(e.button.button == SDL_BUTTON_RIGHT) {
					world.createBlock(inventory.hbSelection, x, y, player.x, player.y);
				}
			}
		}
		
		if(falling) { 
			fallTimer++;
			if(fallTimer == 20) {
				if(!world.collision(player.x, player.y+1)) {
					player.moveDown();
					fallTimer = 0;
				} else {
					falling = false;
					fallTimer = 0;
				}
			}
		}
		
		// Rerender
		world.draw(ren);
		player.draw(ren);
		inventory.draw(ren);
		
		SDL_RenderPresent(ren);
		
		// Don't set cpu on fire
		SDL_Delay(16);
	}
	
	// Exit
	inventory.free();
	player.free();
	world.free();
}