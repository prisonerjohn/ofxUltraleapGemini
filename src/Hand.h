#pragma once

#include "LeapC.h"

#include "Utilities.h"

#include "ofVectorMath.h"

namespace ofxUltraleapGemini 
{
	class Hand 
	{
	public:
		Hand();
		~Hand();

		void setup(uint32_t id, const LEAP_HAND * hand);

		void update(const LEAP_HAND * hand);

		uint32_t getId() const;
		eLeapHandType getType() const;
		uint64_t getVisibleTime() const;

		float getPinchDistance() const;
		float getPinchStrength() const;

		float getGrabAngle() const;
		float getGrabStrength() const;

		Bone getArm() const;

		Palm getPalm() const;

		const Digit* getDigits() const;
		Digit getThumb() const;
		Digit getIndex() const;
		Digit getMiddle() const;
		Digit getRing() const;
		Digit getPinky() const;

	private:
		std::string getTypeString(eLeapHandType result);

	private:
		uint32_t id;
		eLeapHandType type;

		uint64_t visibleTime;

		float pinchDistance;
		float pinchStrength;

		float grabAngle;
		float grabStrength;

		Bone arm;

		Palm palm;

		union
		{
			struct
			{
				Digit thumb;
				Digit index;
				Digit middle;
				Digit ring;
				Digit pinky;
			};
			Digit digits[5];
		};
	};
}
