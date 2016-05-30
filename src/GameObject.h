#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void render() = 0;
	virtual void tick() = 0;
};

