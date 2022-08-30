#pragma once
#include <functional>
#include <memory>

template<class Callable>
class _CallChainNode
{
private:
public:
	std::unique_ptr<_CallChainNode<Callable>> next = nullptr;
	Callable func = nullptr;
	_CallChainNode(Callable func)
		: func(func)
	{
	}
	template<typename... Args>
	void Execute(Args&&... args)
	{
		std::invoke(this->func, std::forward<Args>(args)...);
	}
	void Add(Callable func)
	{
		if (this->next == nullptr)
		{
			this->next = std::make_unique<_CallChainNode<Callable>>(func);
		}
		else 
		{
			this->next->Add(func);
		}
	}
};

template<class Callable>
class CallChain
{
private:
public:
	std::unique_ptr<_CallChainNode<Callable>> node = nullptr;

	void Add(Callable func)
	{
		if (this->node == nullptr)
		{
			this->node = std::make_unique<_CallChainNode<Callable>>(func);
		}
		else
		{
			this->node->Add(func);
		}
	}

	template<typename... Args>
	void Execute(Args&&... args)
	{
		if (this->node != nullptr)
		{
			this->node->Execute(std::forward<Args>(args)...);
		}
	}
};