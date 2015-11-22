#pragma once

#include "RenderGroup.h"
#include "Player.h"
class screen
{
	//每个都是正方形，数据排列为12(形状)+8(纹理)+16(颜色),法线这类的以后在加
	std::vector<renderGroup> RenderGroup;

	bool IsGameScreen = false;
public:
	renderGroup* addRenderGroup()
	{
		RenderGroup.push_back(renderGroup());

		return &RenderGroup[RenderGroup.size() - 1];
	}
	renderGroup* getRenderGroup(int Count)
	{
		return &RenderGroup[Count];
	}
	screen(bool IsGameScreen)
	{
		screen::IsGameScreen = IsGameScreen;
	}
	void screenLoop()
	{
		if (IsGameScreen)
		{
			//游戏主循环
			Player.playerMove();
		}
	}
	void drawScreen()
	{
		for (unsigned int i = 0; i < RenderGroup.size(); i++)
		{
			RenderGroup[i].draw();
		}
	}
};

//首先需要激活需要修改的Screen，然后再进行操作
class screens
{
	std::vector<screen> Screen;
	std::vector<GLuint> VertexArrays;

	unsigned int	NowEnableScreen = 0;
public:
	//渲染
	void enableScreen(unsigned int ScreenID)
	{
		if (ScreenID < Screen.size())
		{
			glBindVertexArray(VertexArrays[ScreenID]);

			NowEnableScreen = ScreenID;
		}
	}
	void drawScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Screen[NowEnableScreen].drawScreen();
	}
	//修改数据
	unsigned int addScreen(bool IsGameScreen)
	{
		Screen.push_back(screen(IsGameScreen));
		VertexArrays.resize(Screen.size());

		glGenVertexArrays(1,&VertexArrays[Screen.size() - 1]);

		return Screen.size() - 1;
	}
	renderGroup* addRenderGroup()
	{
		return Screen[NowEnableScreen].addRenderGroup();
	}
	//读取数据
	unsigned int getSize()
	{
		return Screen.size();
	}
	//处理屏幕内的消息
	void screenLoop()
	{
		Screen[NowEnableScreen].screenLoop();
	}
};

extern screens Screen;