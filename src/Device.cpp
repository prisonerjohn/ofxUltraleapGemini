#include "Device.h"

#include "Hand.h"

#include <vector>
#include "ofLog.h"

namespace ofxUltraleapGemini 
{
	Device::Device()
		: id(-1)
		, hFov(0)
		, vFov(0)
	{
	
	}

	Device::~Device()
	{
	
	}

	void Device::setup(uint32_t id, const LEAP_DEVICE_INFO * info) 
	{
		ofLogNotice(__FUNCTION__) << "id: " << id << ", serial: " << info->serial;

		this->id = id;
		this->serial = info->serial;
		this->hFov = info->h_fov;
		this->vFov = info->v_fov;
	}

	void Device::close()
	{

	}

	void Device::update(const LEAP_TRACKING_EVENT * event) 
	{
		ofLogVerbose(__FUNCTION__) << "frame: " << event->tracking_frame_id << ", numHands: " << event->nHands;

		this->lastTrackingFrame = event->tracking_frame_id;

		std::vector<uint32_t> toErase;
		for (const auto& it : this->hands) 
		{
			toErase.push_back(it.first);
		}

		for (uint32_t i = 0; i < event->nHands; ++i) 
		{
			LEAP_HAND * h = &event->pHands[i];

			auto it = this->hands.find(h->id);
			if (it == this->hands.end()) 
			{
				auto hand = std::make_shared<Hand>();
				hand->setup(h->id, h);
				this->hands.emplace(h->id, hand);
			}
			else
			{
				it->second->update(h);
			}

			toErase.erase(std::remove(toErase.begin(), toErase.end(), h->id), toErase.end());
		}

		// Remove old hands.
		for (auto id : toErase)
		{
			this->hands.erase(id);
		}
	}

	uint32_t Device::getId() const 
	{
		return this->id;
	}

	const std::map<uint32_t, std::shared_ptr<Hand>>& Device::getHands() const
	{
		return this->hands;
	}

	std::shared_ptr<Hand> Device::getHand(eLeapHandType type) const 
	{
		auto it = std::find_if(this->hands.begin(), this->hands.end(),
			[type](const auto& pair)
			{
				return (pair.second->getType() == type);
			});
		if (it != this->hands.end()) return it->second;
		return nullptr;
	}
}
