#include <BearLibTerminal.h>
#include "Player.h"
#include "Control.h"
#include "ScreenOutput.h"

int main()
{
	Player player;
	Control control(player);
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
			control.Check(key);
		}
		
		screen.Output();
	}
	
	terminal_close();
	return 0;
}