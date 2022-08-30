#pragma once
#include <map>
#include <string>

struct SoyVariant
{
	union
	{
		float floatValue;
		int intValue;
		bool boolValue;
	};

public:
	template<typename Ty>
	Ty Get() const
	{
	}
	template<>
	float Get<float>() const
	{
		return this->floatValue;
	}
	template<>
	int Get<int>() const
	{
		return this->intValue;
	}
	template<>
	bool Get<bool>() const
	{
		return this->boolValue;
	}

	template<typename Ty>
	void Set(Ty value)
	{
	}
	template<>
	void Set<float>(float value)
	{
		this->floatValue = value;
	}
	template<>
	void Set<int>(int value)
	{
		this->intValue = value;
	}
	template<>
	void Set<bool>(bool value)
	{
		this->boolValue = value;
	}
};


class BlackBoard
{
public:
	using BlackBoardVar = SoyVariant;
private:
	std::map<std::string, BlackBoardVar> blackBoard;
public:
	template<class Ty>
	void SetVariable(const std::string& tag, Ty value)
	{
		this->blackBoard[tag].Set<Ty>(value);
	};

	template<class Ty>
	Ty GetVariable(const std::string& tag) const
	{
		return this->blackBoard.at(tag).Get<Ty>();
	};

};