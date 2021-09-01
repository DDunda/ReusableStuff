#define MAKE_ENUM_VAL(x) x,
#define MAKE_ENUM_STRING(x) #x,
#define MAKE_ENUM(name, ENUM)\
	enum name { ENUM(MAKE_ENUM_VAL) NUM };\
	const char* name##Text[] = { ENUM(MAKE_ENUM_STRING) "INVALID" };\
	inline constexpr const char* to_string(name x) { return name##Text[(size_t)x]; };

#define MAKE_ENUM_CLASS(name, ENUM)\
	enum class name { ENUM(MAKE_ENUM_VAL) NUM };\
	const char* name##Text[] = { ENUM(MAKE_ENUM_STRING) "INVALID" };\
	inline constexpr const char* to_string(name x) { return name##Text[(size_t)x]; };