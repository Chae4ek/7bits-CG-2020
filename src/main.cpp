#include <BearLibTerminal.h>
#include "ECS/ECSEngine.h"

int main()
{
	Entity player(Position(0, 0), Test(1));
	PlayerControl player_control(player.Get<Position>());
	Screen screen(player.Get<Position>());
	
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