#include <bass.h>
#include <locale>
#include "Interface.h"
#pragma comment (lib, "bass")
#pragma comment (lib, "id3v2.lib")

using namespace std;
int main()
{
	setlocale(LC_CTYPE, "Russian");
	Interface Player;
	Player.StartMenu();
}

