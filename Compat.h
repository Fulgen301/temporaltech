#pragma once

#define DEFAULT_PROPERTY(Type, name, variable, getAccess, setAccess) \
	property Type ^name \
	{ \
	getAccess: \
		Type ^get() \
		{ \
			return variable; \
		} \
	setAccess: \
		void set(Type ^type) \
		{ \
			variable = type; \
		} \
	}