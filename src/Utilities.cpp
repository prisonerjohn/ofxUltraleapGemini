#include "Utilities.h"

namespace ofxUltraleapGemini
{
	std::string getResultString(eLeapRS result)
	{
		switch (result)
		{
			case eLeapRS_Success:
				return "eLeapRS_Success";
			case eLeapRS_UnknownError:
				return "eLeapRS_UnknownError";
			case eLeapRS_InvalidArgument:
				return "eLeapRS_InvalidArgument";
			case eLeapRS_InsufficientResources:
				return "eLeapRS_InsufficientResources";
			case eLeapRS_InsufficientBuffer:
				return "eLeapRS_InsufficientBuffer";
			case eLeapRS_Timeout:
				return "eLeapRS_Timeout";
			case eLeapRS_NotConnected:
				return "eLeapRS_NotConnected";
			case eLeapRS_HandshakeIncomplete:
				return "eLeapRS_HandshakeIncomplete";
			case eLeapRS_BufferSizeOverflow:
				return "eLeapRS_BufferSizeOverflow";
			case eLeapRS_ProtocolError:
				return "eLeapRS_ProtocolError";
			case eLeapRS_InvalidClientID:
				return "eLeapRS_InvalidClientID";
			case eLeapRS_UnexpectedClosed:
				return "eLeapRS_UnexpectedClosed";
			case eLeapRS_UnknownImageFrameRequest:
				return "eLeapRS_UnknownImageFrameRequest";
			case eLeapRS_UnknownTrackingFrameID:
				return "eLeapRS_UnknownTrackingFrameID";
			case eLeapRS_RoutineIsNotSeer:
				return "eLeapRS_RoutineIsNotSeer";
			case eLeapRS_TimestampTooEarly:
				return "eLeapRS_TimestampTooEarly";
			case eLeapRS_ConcurrentPoll:
				return "eLeapRS_ConcurrentPoll";
			case eLeapRS_NotAvailable:
				return "eLeapRS_NotAvailable";
			case eLeapRS_NotStreaming:
				return "eLeapRS_NotStreaming";
			case eLeapRS_CannotOpenDevice:
				return "eLeapRS_CannotOpenDevice";
			default:
				return "unknown result type.";
		}
	}

	std::string getStatusString(eLeapDeviceStatus status) 
	{
		switch (status) 
		{
			case eLeapDeviceStatus_Streaming:
				return "eLeapDeviceStatus_Streaming";
			case eLeapDeviceStatus_Paused:
				return "eLeapDeviceStatus_Paused";
			case eLeapDeviceStatus_Robust:
				return "eLeapDeviceStatus_Robust";
			case eLeapDeviceStatus_Smudged:
				return "eLeapDeviceStatus_Smudged";
			case eLeapDeviceStatus_LowResource:
				return "eLeapDeviceStatus_LowResource";
			case eLeapDeviceStatus_UnknownFailure:
				return "eLeapDeviceStatus_UnknownFailure";
			case eLeapDeviceStatus_BadCalibration:
				return "eLeapDeviceStatus_BadCalibration";
			case eLeapDeviceStatus_BadFirmware:
				return "eLeapDeviceStatus_BadFirmware";
			case eLeapDeviceStatus_BadTransport:
				return "eLeapDeviceStatus_BadTransport";
			case eLeapDeviceStatus_BadControl:
				return "eLeapDeviceStatus_BadControl";
			default:
				return "unknown status type.";
		}
	}

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
            toOf(d.metacarpal),
            toOf(d.proximal),
            toOf(d.intermediate),
            toOf(d.distal),
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
