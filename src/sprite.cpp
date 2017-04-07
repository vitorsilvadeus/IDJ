#include "sprite.hpp"

Sprite::Sprite(){

	this->texture = nullptr;

}

Sprite::Sprite(std::string file){

	this->texture = nullptr;
	Open(file);	

}

Sprite::~Sprite(){

	

}

void Sprite::Open(std::string file){

	Resources::GetImage(file.c_str());
	SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);

	Sprite::SetClip(0,0,width,height);

}

void Sprite::SetClip (int x,int y,int w,int h){

	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;

	}

void Sprite::Render(int x,int y){

	SDL_Rect dstrect;

	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = clipRect.w;
	dstrect.h = clipRect.h;
	
	if(Game::GetInstance()->GetRenderer() == nullptr){printf( "%s\t%d\t\n", __FILE__, __LINE__ );exit(1);}
	if(texture == nullptr){printf( "%s\t%d\t\n", __FILE__, __LINE__ );exit(1);}

	SDL_RenderCopy(Game::GetInstance()->GetRenderer(),texture,&clipRect,&dstrect);

}

int Sprite::GetWidth(){

	return(width);
}

int Sprite::GetHeight(){

	return(height);

}

bool Sprite::IsOpen(){

	if(texture == nullptr){return(false);}

	return(true);

}