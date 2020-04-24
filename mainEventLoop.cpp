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
	int cnt = 0;
	
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
							if(!world.collision(player.x, player.y-tileSize)) {
								player.moveUp();
								falling = true;
								cnt = 0;
							}
						}
						break;
					case SDLK_LCTRL:
						if(!world.collision(player.x, player.y+tileSize))
							//while(world.map[world.ts(player.x)][world.ts(player.y)+2] == nullptr) {
								player.moveDown();
							//}
						break;
					case SDLK_d:
						if(!world.collision(player.x+tileSize, player.y))
							player.moveRight();
						break;
					case SDLK_a:
						if(!world.collision(player.x-tileSize, player.y))
							player.moveLeft();
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
			
			// ideally do this inside every playerMovement function or make one playermovement function
			//player.ground(world.map);
			
			// Mouse Events
			if(e.type == SDL_MOUSEBUTTONDOWN) {
				int x = (e.button.x - (e.button.x % tileSize))/tileSize;
				int y = (e.button.y - (e.button.y % tileSize))/tileSize;
				// Click is not on bedrock && in range of players reach
				if(e.button.button == SDL_BUTTON_LEFT) {
					world.destroyBlock(x, y);
				}
				if(e.button.button == SDL_BUTTON_RIGHT) {
					world.createBlock(inventory.hbSelection, x, y, player.x, player.y);
				}
			}
			
		}
		
		if(falling) {
			cnt++;
			printf("cnt = %i\n", cnt);
		}
		if(cnt == 20) {
			printf("Moving player down\n");
			cnt = 0;
			if(!world.collision(player.x, player.y+tileSize))
				player.moveDown();
			falling = false;
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