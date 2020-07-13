#include <BearLibTerminal.h>
#include "ECS/ECSEngine.h"

int main()
{
	Entity player(Position(0, 0), Movement(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN), Sprite('@', COLOR_WHITE));
	PlayerControl player_control(player);
	Screen screen(player);
	
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