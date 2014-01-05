#include "StdAfx.h"
#include "EnumUtils.h"

namespace aislingim_libjingle
{
	 STATUS_ENUM EnumUtils::convert(buzz::PresenceStatus::Show status)
	 {
		 switch(status)
		{
			case buzz::PresenceStatus::SHOW_OFFLINE:
				return OFFLINE;
			case buzz::PresenceStatus::SHOW_ONLINE:
				return ONLINE;
			case buzz::PresenceStatus::SHOW_AWAY:
				return AWAY;
			case buzz::PresenceStatus::SHOW_CHAT:
				return FREE_FOR_CHAT;
			case buzz::PresenceStatus::SHOW_DND:
				return DND;
			case buzz::PresenceStatus::SHOW_XA:
				return XA;
			default:
				return OFFLINE; //TODO; consider throwing
		}
	 }

	 buzz::PresenceStatus::Show EnumUtils::convert(STATUS_ENUM status)
	 {
		 switch(status)
		{
			case OFFLINE:
				return buzz::PresenceStatus::SHOW_OFFLINE;
			case ONLINE:
				return buzz::PresenceStatus::SHOW_ONLINE;
			case FREE_FOR_CHAT:
				return buzz::PresenceStatus::SHOW_CHAT;
			case AWAY:
				return buzz::PresenceStatus::SHOW_AWAY;
			case XA:
				return buzz::PresenceStatus::SHOW_XA;
			case DND:
				return buzz::PresenceStatus::SHOW_DND;
			default:
				return buzz::PresenceStatus::SHOW_OFFLINE;
		}
	 }

	 std::string EnumUtils::to_string(buzz::XmppEngine::State state)
	 {
		 switch(state)
		{
		case buzz::XmppEngine::STATE_NONE:        //!< Nonexistent state
			return "NONE";
		case buzz::XmppEngine::STATE_START:         //!< Initial state.
			return "START";
		case buzz::XmppEngine::STATE_OPENING:         //!< Exchanging stream headers, authenticating and so on.
			return "OPENING";
		case buzz::XmppEngine::STATE_OPEN:            //!< Authenticated and bound.
			return "OPEN";
		case buzz::XmppEngine::STATE_CLOSED:
			return "CLOSED";
		default:
			return "UNEXPECTED buzz::XmppEngine::State STATE";
		}
	 }
}