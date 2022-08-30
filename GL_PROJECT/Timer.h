#pragma once
#include <Windows.h>
class Timer
{
public:
	Timer()
	{
		__int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		this->mSecondsPerCount = 1.0 / static_cast<double>(countsPerSec);
	}
	float GameTime() const
	{
		if (this->mStopped)
		{
			return static_cast<float>(
				((this->mStopTime - this->mPausedTime) - this->mBaseTime) * this->mSecondsPerCount
				);
		}
		else
		{
			return static_cast<float>(
				((this->mCurrTIme - this->mPausedTime) - this->mBaseTime) * this->mSecondsPerCount
				);
		}
	}
	float DeltaTime() const
	{
		return static_cast<float>(this->mDeltaTime);
	}

	void Reset()
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		this->mBaseTime = currTime;
		this->mPrevTime = currTime;
		this->mStopTime = 0;
		mStopped = false;
	}
	void Start()
	{
		__int64 startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
		if (this->mStopped)
		{
			this->mPausedTime += (startTime - this->mStopTime);
			this->mPrevTime = startTime;
			this->mStopTime = 0;
			this->mStopped = false;
		}
	}
	void Stop()
	{
		if (!this->mStopped)
		{
			__int64 currTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
			this->mStopTime = currTime;
			this->mStopped = true;
		}
	}
	void Tick()
	{
		if (mStopped)
		{
			this->mDeltaTime = 0;
			return;
		}
		//이번 프레임의 시간을 얻는다.
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		this->mCurrTIme = currTime;

		//이번 프레임의 시간과 이전 프레임의 시간의 차이를 구한다.
		this->mDeltaTime = (this->mCurrTIme - this->mPrevTime) * this->mSecondsPerCount;

		//다음 프레임을 준비한다.
		this->mPrevTime = this->mCurrTIme;
	}
private:
	double mSecondsPerCount = 0.0;
	double mDeltaTime = -1.0;

	__int64 mBaseTime = 0;
	__int64 mPausedTime = 0;
	__int64 mStopTime = 0;
	__int64 mPrevTime = 0;
	__int64 mCurrTIme = 0;

	bool mStopped = false;
};
