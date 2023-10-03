#pragma once

#include "LeapC.h"

#include <map>
#include <memory>
#include <string>

namespace ofxUltraleapGemini 
{
	class Hand;

	class Device 
	{
	public: 
		Device();
		~Device();

		void setup(uint32_t id, const LEAP_DEVICE_INFO * info);
		void close();

		void update(const LEAP_TRACKING_EVENT * event);

		uint32_t getId() const;

		const std::map<uint32_t, std::shared_ptr<Hand>>& getHands() const;
		std::shared_ptr<Hand> getHand(eLeapHandType type) const;

	private:
		uint32_t id;
		std::string serial;
		float hFov;
		float vFov;

		int64_t lastTrackingFrame;

		std::map<uint32_t, std::shared_ptr<Hand>> hands;
	};
}
