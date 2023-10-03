#include "Utilities.h"

namespace ofxUltraleapGemini
{
	glm::vec3 toOf(LEAP_VECTOR v) 
	{
		return glm::vec3(v.x, v.y, v.z);
	}

	glm::quat toOf(LEAP_QUATERNION q)
	{
		return glm::quat(q.w, q.x, q.y, q.z);
	}

	Bone toOf(LEAP_BONE b) 
	{
		return Bone 
		{ 
			toOf(b.prev_joint),
			toOf(b.next_joint),
			toOf(b.rotation),
			b.width
		};
	}

	Digit toOf(LEAP_DIGIT d) 
	{
		return Digit 
		{ 
			d.finger_id,
			{ 
				toOf(d.metacarpal),
				toOf(d.proximal),
				toOf(d.intermediate),
				toOf(d.distal)
			},
			d.is_extended
		};
	}

	Palm toOf(LEAP_PALM p)
	{
		return Palm
		{
			toOf(p.position),
			toOf(p.stabilized_position),
			toOf(p.velocity),
			toOf(p.normal),
			toOf(p.direction),
			toOf(p.orientation),
			p.width
		};
	}
}
