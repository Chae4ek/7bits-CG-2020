#include <BearLibTerminal.h>
#include "ECS/ECSEngine.h"

int main()
{
	terminal_open();
	terminal_refresh();
	// TODO: resizeable window with resize object sprites
	terminal_set("window: title=Game, size=80x30");
	
	Entity player(
		Position(0, 0),
		Movement(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN),
		Sprite('@', COLOR_WHITE),
		GameStats());
	PlayerControl player_control(player);
	
	Sprite wall_sprite('#', COLOR_GREY);
	
	MapManager map_manager(player.Get<Position>());
	GenerateMap gen_map(1, map_manager);
	
	Screen screen(map_manager, player, wall_sprite);
	
	while (true)
	{
		if (terminal_has_input())
		{
			int key = terminal_read();
			if (key == TK_CLOSE) break;
			player_control.Update(key);
		}
		gen_map.Update();
		
		screen.Update();
		screen.PostUpdate();
	}
	
	terminal_close();
	return 0;
}