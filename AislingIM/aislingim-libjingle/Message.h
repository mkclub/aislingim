#ifndef AISLINGIM_MESSAGE_H
#define AISLINGIM_MESSAGE_H
#include <string>
#include "definitions.h"

namespace aislingim_libjingle
{
	

	struct AISLINGIMLIBJINGLE_API Message
	{
	public:

		const std::string& getId() const {return id_;}
		const std::string& getEncoding() const {return encoding_;}
		const std::string& getFrom() const {return from_;}
		const std::string& getTo() const {return to_;}
		bool isChatMessage() const {return isChatMessage_;}
		const std::string& getSubject() const {return subject_;}
		const std::string& getBody() const {return body_;}

		void setId(const std::string& id){id_ = id;}
		void setEncoding(const std::string& encoding){encoding_ = encoding;}
		void setChatMessage(bool isChatMessage){isChatMessage_ = isChatMessage;}
		void setFrom(const std::string& from){from_ = from;}
		void setTo(const std::string& to){to_ = to;}
		void setSubject(const std::string& subject){subject_ = subject;}
		void setBody(const std::string& body){body_ = body;}
	
	private:
		#pragma warning(push)
		#pragma warning(disable: 4251)
		std::string id_;
		std::string encoding_;
		std::string from_;
		std::string to_;
		bool isChatMessage_;
		std::string subject_;
		std::string body_;
		#pragma warning(pop)
	};
}
#endif