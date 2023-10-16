#pragma once

#include "LeapC.h"

#include "ofVectorMath.h"

namespace ofxUltraleapGemini 
{
	struct Bone 
	{
		glm::vec3 jointPrev;
		glm::vec3 jointNext;
		glm::quat rotation;
		float width;
	};

	struct Digit 
	{
		int32_t id;


        Bone metacarpal;
        Bone proximal;
        Bone intermediate;
        Bone distal;
        
		uint32_t extended;
	};

	struct Palm 
	{
		glm::vec3 position;
		glm::vec3 positionStable;
		glm::vec3 velocity;
		glm::vec3 normal;
		glm::vec3 direction;
		glm::quat orientation;
		float width;
	};

	std::string getResultString(eLeapRS result);
	std::string getStatusString(eLeapDeviceStatus status);

	glm::vec3 toOf(LEAP_VECTOR v);
	glm::quat toOf(LEAP_QUATERNION q);

	Bone toOf(LEAP_BONE b);
	Digit toOf(LEAP_DIGIT d);
	Palm toOf(LEAP_PALM p);
}
