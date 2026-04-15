// CMakeProject1.cpp: 定义应用程序的入口点。
//
#define SDL_MAIN_HANDLED        //解决1120，2019问题 ，main在sdl里面有重复函数

#include "CMakeProject1.h"



using namespace std;

int main()
{
	//cout << "Hello CMake." << endl;
	//sdl 初始化
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cerr << "框架处理初始化 Error: " << SDL_GetError() << endl;
		return 1;
	}
	SDL_Window* w = SDL_CreateWindow("otto", 100, 100, 600, 800, SDL_WINDOW_SHOWN);//窗口
	SDL_Renderer* r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);


	//初始化SDL_image（加载图片）
	
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)!= (IMG_INIT_PNG | IMG_INIT_JPG))//初始化读取png和jpg
	{
		cerr<<"图像处理初始化 Error: "<< IMG_GetError()<<endl;
		return 1;
	}

	SDL_Texture* texture = IMG_LoadTexture(r, "D:/Text game/CMakeProject1/jpg & png/set2.png");//加载图片
	if (texture == NULL)
	{
		cerr << "未加载图片" << IMG_GetError() << endl;
		return -1;
	}


	//初始化音频处理

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cerr << "音频处理初始化 Error: " << Mix_GetError() << endl;
		return 1;
	}

	Mix_Music* music = Mix_LoadMUS("D:/Text game/CMakeProject1/sound/fairy stage.mp3");//加载音乐
	if (music == NULL)
	{
		cerr << "音频加载错误" << Mix_GetError() << endl;
		return -1;
	}
	Mix_PlayMusic(music, -1); //播放音乐




	while (true) {         //       渲染器刷新帧绘制
		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				break;
		}
		SDL_RenderClear(r);//清除屏幕


		SDL_Rect rect = { 100,100,200,200}; 
		SDL_SetRenderDrawColor(r, 255, 0, 0, 255);//绘制颜色 A
		SDL_RenderFillRect(r, &rect);
		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);//背景颜色 B           ab交替完成刷新帧绘制
		
		//绘制他图片
		SDL_Rect s = { 200,200,300,400 };
		SDL_RenderCopy(r, texture, NULL,&s);//参数为渲染器，图片，源矩形，目标矩形

		
























		SDL_RenderPresent(r);//刷新帧



	}
	


	//清图
	SDL_DestroyTexture(texture);
	IMG_Quit();


	//清音
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	Mix_Quit();



	SDL_DestroyRenderer(r);//           清除窗口，清除渲染，关闭
	SDL_DestroyWindow(w);
	SDL_Quit();



	return 0;
}
