#include <BearLibTerminal.h>
#include "Player.h"
#include "ControlSystem.h"
#include "ScreenOutput.h"

int main()
{
	Player player;
	Controls controls(player);
	Screen screen(player);
	
	terminal_open();
	while (true)
	{
		terminal_refresh();
		terminal_clear();
		
		if (terminal_has_input())
		{
			int key = terminal_read();
			if (key == TK_CLOSE) break;
			controls.Check(key);
		}
		
		screen.Output();
	}
	
	terminal_close();
	return 0;
}