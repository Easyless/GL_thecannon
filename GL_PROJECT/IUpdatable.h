#pragma once
class IUpdatable
{
public:
	virtual void Update(float deltaTime) = 0;
};