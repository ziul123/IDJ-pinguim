#ifndef TIMER_H
#define TIMER_H

class Timer {
	public:
		Timer() {time = 0;};
		void Update(float dt) {time += dt;};
		void Restart() {time = 0;};
		float Get() {return time;};

	private:
		float time;
};

#endif
