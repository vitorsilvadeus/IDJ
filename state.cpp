#include "state.hpp"

State(){

}

void Update(){

	if(SDL_QuitRequested()){quitRequested = true;}

}

void Render(){

	bg.render();

}

bool QuitRequested(){return(quitRequested);}

void LoadAssets(){}


