#include "alien.hpp"

Alien::Alien(float x,float y,int nMinions){

	sp = new Sprite("img/alien.png");

	box = new Rect(x,y,sp->GetWidth(),sp->GetHeight());

	hp = INITIAL_ALIEN_HP;
	arc = 0;
	//Popular array de minions quando o alien estiver funcional
	for(int i = 0;i < nMinions; i++ ){

		minionArray.push_back(Minion(this,((2*PI)/nMinions) * i));

	}

}

Alien::~Alien(){}

void Alien::Update(float dt){

	arc -= ALIEN_ROTATION_VEL * dt;

	if(InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)){

		//Cria e enfileira ação de tiro registrando a posicao do mouse
		taskQueue.push(Action(Action::SHOOT,InputManager::GetInstance().GetMouseX(),InputManager::GetInstance().GetMouseY()));

	}
	if(InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT)){

		//Cria e enfilera ação de movimento registrando a posicao do mouse
		taskQueue.push(Action(Action::MOVE,InputManager::GetInstance().GetMouseX(),InputManager::GetInstance().GetMouseY()));
		//Trata movimentacao da camera

	}
	if(!taskQueue.empty()){

		Action action = taskQueue.front();
		float lastDistance = (action.pos - box->Center()).Magnitude();

		if(action.type == Action::MOVE){

			speed = (box->Center().Distance(action.pos)).Normalize() * ALIEN_VEL;

			if((speed * dt).Magnitude() > lastDistance){

				box->SetX(action.pos.GetX() - (box->GetW()/2));
				box->SetY(action.pos.GetY() - (box->GetH()/2));
				taskQueue.pop();

			}
			else{

				box->SetX(box->Center().GetX() + (speed * dt).GetX() - box->GetW()/2);
				box->SetY(box->Center().GetY() + (speed * dt).GetY() - box->GetH()/2);

			}

		}
		else if(action.type == Action::SHOOT){

			float min_distance = std::numeric_limits<float>::max();
			unsigned int minion;

			for(unsigned int i = 0;i < minionArray.size();i++){

				if(min_distance > minionArray[i].box->Center().Distance(action.pos).Magnitude()){

					min_distance = minionArray[i].box->Center().Distance(action.pos).Magnitude();
					minion = i;

				}
			}

			minionArray[minion].Shoot(action.pos);
			taskQueue.pop();

		}

	}

	for(unsigned int i = 0;i < minionArray.size();i++){

		minionArray[i].Update(dt);

	}
}

void Alien::Render(){

	sp->Render(box->GetX() + Camera::pos.GetX(),box->GetY() + Camera::pos.GetY(),arc);
	//Chamar a renderização de cada Minion.
	for(unsigned int i = 0;i < minionArray.size();i++){

		minionArray[i].Render();

	}

}
bool Alien::IsDead(){

	return (hp <= 0);

}

Alien::Action::Action(ActionType type,float x,float y){

	this->type = type;
	pos = Vec2(x,y);

}