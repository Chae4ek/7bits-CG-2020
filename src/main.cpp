#include <BearLibTerminal.h>
#include "ECS/ECSEngine.h"
#include "Advanced.h"

int main()
{
	Entity player(
		Position(0, 0),
		Movement(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN),
		Sprite('@', COLOR_WHITE),
		GameStats());
	PlayerControl player_control(player);
	
	Sprite wall_sprite('#', COLOR_GREY);
	
	Screen screen(player, wall_sprite);
	
	terminal_open();
	terminal_refresh();
	terminal_set("window: title=Game, size=80x30, resizeable=true");
	
	while (true)
	{
		if (terminal_has_input())
		{
			int key = terminal_read();
			if (key == TK_CLOSE) break;
			player_control.Update(key);
		}
		
		screen.Update();
	}
	
	terminal_close();
	return 0;
}