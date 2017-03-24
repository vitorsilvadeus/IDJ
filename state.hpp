#include "sprite.hpp"

class State{

	public:
		State();
		bool QuitRequested();
		void LoadAssets();
		void Update();
		void Render();
	private:

		Sprite bg;
		bool quitRequested;

};
