#include "Hand.h"

#include "ofLog.h"

namespace ofxUltraleapGemini 
{
	Hand::Hand()
		: id(-1)
	{
	
	}

	Hand::~Hand() 
	{
	
	}

	void Hand::setup(uint32_t id, const LEAP_HAND * hand) 
	{
		ofLogNotice(__FUNCTION__) << "id: " << id << ", type: " << this->getTypeString(hand->type);

		this->id = id;
		this->type = hand->type;

		this->update(hand);
	}

	void Hand::update(const LEAP_HAND * hand) 
	{
		ofLogVerbose(__FUNCTION__);

		this->visibleTime = hand->visible_time;
		this->pinchDistance = hand->pinch_distance;
		this->pinchStrength = hand->pinch_strength;
		this->grabAngle = hand->grab_angle;
		this->grabStrength = hand->grab_strength;

		this->arm = toOf(hand->arm);
		this->palm = toOf(hand->palm);

		this->thumb = toOf(hand->thumb);
		this->index = toOf(hand->index);
		this->middle = toOf(hand->middle);
		this->ring = toOf(hand->ring);
		this->pinky = toOf(hand->pinky);
	}

	uint32_t Hand::getId() const
	{
		return this->id;
	}

	eLeapHandType Hand::getType() const
	{
		return this->type;
	}
	
	uint64_t Hand::getVisibleTime() const
	{
		return this->visibleTime;
	}

	float Hand::getPinchDistance() const
	{
		return this->pinchDistance;
	}
	
	float Hand::getPinchStrength() const
	{
		return this->pinchStrength;
	}

	float Hand::getGrabAngle() const
	{
		return this->grabAngle;
	}
	
	float Hand::getGrabStrength() const
	{
		return this->grabStrength;
	}

	Bone Hand::getArm() const
	{
		return this->arm;
	}

	Palm Hand::getPalm() const
	{
		return this->palm;
	}

	const Digit* Hand::getDigits() const
	{
		return this->digits;
	}

	Digit Hand::getThumb() const
	{
		return this->thumb;
	}

	Digit Hand::getIndex() const
	{
		return this->index;
	}

	Digit Hand::getMiddle() const
	{
		return this->middle;
	}

	Digit Hand::getRing() const
	{
		return this->ring;
	}

	Digit Hand::getPinky() const
	{
		return this->pinky;
	}

	std::string Hand::getTypeString(eLeapHandType type)
	{
		switch (type)
		{
			case eLeapHandType_Left:
				return "eLeapHandType_Left";
			case eLeapHandType_Right:
				return "eLeapHandType_Right";
			default:
				return "unknown type.";
		}
	}
}
