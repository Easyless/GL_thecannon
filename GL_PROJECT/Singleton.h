#pragma once
#include <memory>

template<typename Ty>
class Singleton
{
	static std::unique_ptr<Ty> instance;
protected:
	Singleton() {}
public:
	static Ty* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = std::make_unique<Ty>();
		}
		return instance.get();
	}
};