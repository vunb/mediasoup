#define MS_CLASS "RTC::RTCP::FeedbackRtpEcnPacket"
// #define MS_LOG_DEV

#include "RTC/RTCP/FeedbackRtpEcn.hpp"
#include "Logger.hpp"
#include <cstring>

namespace RTC { namespace RTCP
{
	/* Class methods. */

	EcnItem* EcnItem::Parse(const uint8_t* data, size_t len)
	{
		MS_TRACE();

		// data size must be >= header + length value.
		if (sizeof(Header) > len)
		{
			MS_WARN_TAG(rtcp, "not enough space for Ecn item, discarded");

			return nullptr;
		}

		Header* header = const_cast<Header*>(reinterpret_cast<const Header*>(data));

		return new EcnItem(header);
	}

	size_t EcnItem::Serialize(uint8_t* buffer)
	{
		MS_TRACE();

		// Add minimum header.
		std::memcpy(buffer, this->header, sizeof(Header));

		return sizeof(Header);
	}

	void EcnItem::Dump()
	{
		MS_TRACE();

		MS_DEBUG_DEV("<EcnItem>");
		MS_DEBUG_DEV("  sequence number    : %" PRIu32, this->GetSequenceNumber());
		MS_DEBUG_DEV("  ect0 counter       : %" PRIu32, this->GetEct0Counter());
		MS_DEBUG_DEV("  ect1 counter       : %" PRIu32, this->GetEct1Counter());
		MS_DEBUG_DEV("  ecn ce counter     : %" PRIu16, this->GetEcnCeCounter());
		MS_DEBUG_DEV("  not ect counter    : %" PRIu16, this->GetNotEctcounter());
		MS_DEBUG_DEV("  lost packets       : %" PRIu16, this->GetLostPackets());
		MS_DEBUG_DEV("  duplicated packets : %" PRIu16, this->GetDuplicatedPackets());
		MS_DEBUG_DEV("</EcnItem>");
	}
}}
