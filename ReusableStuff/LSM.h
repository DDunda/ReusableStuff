#pragma once

#include "SM.h"

enum class LSM_Event {
	ADVANCE,
	RESET,
};

class LSM : public SM<LSM_Event> {
public:

	class LState : public State {
	protected:
		size_t _start;
		size_t _end;
		size_t _state;

	public:
		LState(size_t state, size_t start, size_t end) : _state((size_t)state), _start(start), _end(end)  {}

		inline size_t GetState() { return _state; }

		inline bool AtStart() { return _state == _start; }
		inline bool AtEnd() { return _state == _end; }
		inline bool ReachedState(size_t state) { return _state >= state; }

		State* RecieveEvent(LSM_Event e) { 
			switch (e)
			{
			case LSM_Event::ADVANCE:
				return AtEnd() ? nullptr : new LState(_state + 1, _start, _end);
			case LSM_Event::RESET:
				return new LState(_start, _start, _end);
			default:
				return nullptr;
			}
		}
	};

	LSM(size_t start, size_t end) : SM(new LState(start, start, end)) {}
	
	inline LState* Get() { return (LState*)SM::Get(); }
	inline size_t GetState() { return Get()->GetState(); }

	inline bool AtStart() { return Get()->AtStart(); }
	inline bool AtEnd()   { return Get()->AtEnd();   }
	inline bool ReachedState(size_t state) { return Get()->ReachedState(state); }

	inline void Advance()  { SendEvent(LSM_Event::ADVANCE ); }
	inline void Reset()    { SendEvent(LSM_Event::RESET   ); }
};