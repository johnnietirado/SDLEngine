#pragma once
#include "Component.h"
class TransformComponent : public Component
{
public:
	void SendMessage(Message *message);
	void Update(float dt);
	void Initialize(void);
	void Shutdown(void);
	void Translate(Vector2D v);

	float getPosX() {
		return pos.getX();
	}

	float getPosY() {
		return pos.getY();
	}

	void SetPosition(float x, float y){
		pos.setX(x);
		pos.setY(y);
	}

private:
	Vector2D pos;
};

