#include "DxLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int map[10][10] =
{ {0,0,0,0,0,0,0,0,0,0},
 {0,1,1,1,1,1,1,1,1,0},
 {0,1,0,0,0,0,0,0,1,0},
 {0,1,0,1,1,1,1,0,1,0},
 {0,1,0,1,2,2,1,0,1,0},
 {0,1,0,1,2,2,1,0,1,0},
 {0,1,0,1,1,0,1,0,1,0},
 {0,1,0,0,0,0,1,0,1,0},
 {0,1,1,1,1,1,1,0,1,0},
 {0,0,0,0,0,0,0,0,1,0} };

int Key[256];

int gpUpdateKey()
{
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++)
	{
		if (tmpKey[i] != 0)
		{
			Key[i]++;
		}
		else
		{
			Key[i] = 0;
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	printf("‚­‚Ì‚¾‚æ");
	ChangeWindowMode(TRUE);
	SetGraphMode(400, 400, 16);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	LoadGraphScreen(0, 0, "shiro.png", TRUE);
	ScreenFlip();

	/*int n = 0;
	for (int i = 0; i < 10; i++)
	{
		int m = 0;
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == 1)
			{
				LoadGraphScreen(m, n, "kuro.jpg", TRUE);
				ScreenFlip();
			}
			m += 40;
		}
		n += 40;
	}*/

	int x = 380, y = 380;
	int Handle = LoadGraph("kao.png");

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0)
	{
		//LoadGraphScreen(0, 0, "meiro2.png", TRUE);

		float a = 0.01;
		int s, t;
		s = x;
		t = y;

		if (Key[KEY_INPUT_RIGHT] >= 1)
		{
			a* x++;
			x = x + a * x;
		}
		if (Key[KEY_INPUT_DOWN] >= 1)
		{
			a* y++;
			y = y + a * y;
		}
		if (Key[KEY_INPUT_LEFT] >= 1)
		{
			a* x--;
			x = x - a * x;
		}
		if (Key[KEY_INPUT_UP] >= 1)
		{
			a* y--;
			y = y - a * y;
		}

		int p, q;
		p = x / 40;
		q = y / 40;

		if ((map[p][q] == 1) || (x > 400) || (y > 400) || (x < 0) || (y < 0))
		{
			DrawRotaGraph(s, t, 1.0, 0.0, Handle, TRUE);
			x = s;
			y = t;
		}
		else if (map[p][q] == 2)
		{
			LoadGraphScreen(0, 0, "g.png", TRUE);
			ScreenFlip();
			break;
		}
		else
		{
			DrawRotaGraph(x, y, 1.0, 0.0, Handle, TRUE);
		}

		//DrawRotaGraph(x, y, 1.0, 0.0, Handle, TRUE);

		if (((x >= 160) && (x <= 240)) && ((y >= 160) && (y <= 240)))
		{
			LoadGraphScreen(0, 0, "g.png", TRUE);
			ScreenFlip();
			break;
		}

	}

	WaitKey();
	DxLib_End();

	return 0;
}