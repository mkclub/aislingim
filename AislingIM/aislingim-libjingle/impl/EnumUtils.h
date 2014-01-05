#pragma once

#include "JabberAccountImp.h"

namespace aislingim_libjingle
{
	// handles enum-related extension operations.
	class EnumUtils
	{
	private:
		EnumUtils(void); // this class is static and should not be created.
	public:
		//
		// Conversion
		//
		static buzz::PresenceStatus::Show convert(STATUS_ENUM status);
		static STATUS_ENUM convert(buzz::PresenceStatus::Show status);

		//
		// To String
		//
		static std::string to_string(buzz::XmppEngine::State state);
	};
}

