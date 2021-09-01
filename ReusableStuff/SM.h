#pragma once
#include <exception>

/// <summary>
/// This is a state machine; it handles transitions between different user defined states, using user-defined events.
/// </summary>
/// <typeparam name="...T">The argument list used for events.</typeparam>
template <typename ...T>
class SM {
public:
	/// <summary>
	/// States are used to define the state of a state machine.
	/// </summary>
	class State {
	public:	
		/// <summary>
		/// This function recieves an event, and decides whether to transition to a new state.
		/// </summary>
		/// <param name="eventArgs">A variadic list of arguments relavant to the event.</param>
		/// <returns>A pointer to the next state if successful, or nullptr otherwise.</returns>
		virtual State* RecieveEvent(T...) = 0;
	};

private:
	State* _state;

public:
	SM(State* state) : _state(state) {}
	~SM() { delete _state; }

	/// <summary>
	/// This function sends a event to the current state to try to transition to a new state.
	/// </summary>
	/// <param name="eventArgs">A variadic list of arguments relavant to the event.</param>
	/// <returns>A bool of whether the transition was successful</returns>
	bool SendEvent(T... eventArgs) {
		auto result = _state->RecieveEvent(eventArgs...);

		if (result == nullptr) return false;

		delete _state;
		_state = result;
		return true;
	}

	inline State* Get(void) { return _state; }
};