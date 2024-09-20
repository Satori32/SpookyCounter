#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>

class StopWatch {
protected:
	typedef std::chrono::steady_clock Clock;
	//typedef std::chrono::system_clock Clock;
	Clock::time_point S = Clock::now();
	Clock::time_point E = S;
public:

	bool Start() {
		S = Clock::now();
		E = S;
		return true;
	}
	bool Stop() {
		E = Clock::now();
		return true;
	}
	template<class T = std::chrono::milliseconds>
	T Result() {//stop(); first
		return std::chrono::duration_cast<T>(E - S);
	}
	template<class T = std::chrono::milliseconds>
	T Elapsed() {
		return std::chrono::duration_cast<T>(Clock::now() - S);
	}
};

bool Sleep(std::chrono::nanoseconds In) {
	std::this_thread::sleep_for(In);
	return true;
}

struct SpookyCounter {
	StopWatch SW;
	std::chrono::nanoseconds OneTick;
};

bool ConstructSpookyCounter(SpookyCounter& In,const std::chrono::nanoseconds& NS) {
	In.SW.Start();
	In.OneTick = NS;
	return true;
}

std::intmax_t Tick(SpookyCounter& In) {
	return In.SW.Elapsed<std::chrono::nanoseconds>()/In.OneTick;
}

template <class T>
std::intmax_t Elapsed(SpookyCounter& In) {
	return In.SW.Elapsed<T>();
}

bool Start(SpookyCounter& In) {
	return In.SW.Start();
}
bool Reset(SpookyCounter& In) {
	return In.SW.Start();
}
int main() {
	SpookyCounter SC;

	ConstructSpookyCounter(SC, std::chrono::seconds(1));

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	auto A = Tick(SC);

	return 0;
}