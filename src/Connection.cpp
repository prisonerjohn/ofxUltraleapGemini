#include "Connection.h"

#include "Device.h"
#include "Utilities.h"

#include "ofLog.h"

namespace ofxUltraleapGemini
{
	Connection::Connection()
		: handle(NULL)
	{

	}

	Connection::~Connection()
	{
		this->close();
		this->waitForThread();
	}

	bool Connection::open()
	{
		if (this->isThreadRunning()) return true;

		if (handle || LeapCreateConnection(NULL, &handle) == eLeapRS_Success) 
		{
			eLeapRS result = LeapOpenConnection(handle);
			if (result == eLeapRS_Success) 
			{
				this->startThread();
			}
		}

		return this->handle != NULL;
	}

	bool Connection::close() 
	{
		this->stopThread();

		if (handle)
		{
			LeapCloseConnection(handle);
			LeapDestroyConnection(handle);
			handle = NULL;

			return true;
		}

		return this->handle == NULL;
	}

	void Connection::threadedFunction()
	{
		eLeapRS result;
		LEAP_CONNECTION_MESSAGE msg;

		while (this->isThreadRunning()) 
		{
			unsigned int timeout = 1000;
			result = LeapPollConnection(this->handle, timeout, &msg);

			if (result != eLeapRS_Success) 
			{
				ofLogError(__FUNCTION__) << "LeapPollConnection call was " << getResultString(result);
				continue;
			}

			switch (msg.type) 
			{
				case eLeapEventType_Connection:
					this->onConnection(msg.connection_event);
					break;
				case eLeapEventType_ConnectionLost:
					this->onConnectionLost(msg.connection_lost_event);
					break;
				case eLeapEventType_Device:
					this->onDevice(msg.device_event);
					break;
				case eLeapEventType_DeviceLost:
					this->onDeviceLost(msg.device_event);
					break;
				case eLeapEventType_DeviceFailure:
					this->onDeviceFailure(msg.device_failure_event);
					break;
				case eLeapEventType_Tracking:
					this->onTracking(msg.device_id, msg.tracking_event);
					break;
				//case eLeapEventType_ImageComplete:
				//// Ignore
				//break;
				//case eLeapEventType_ImageRequestError:
				//// Ignore
				//break;
				//case eLeapEventType_LogEvent:
				//handleLogEvent(msg.log_event);
				//break;
				//case eLeapEventType_Policy:
				//handlePolicyEvent(msg.policy_event);
				//break;
				//case eLeapEventType_ConfigChange:
				//handleConfigChangeEvent(msg.config_change_event);
				//break;
				//case eLeapEventType_ConfigResponse:
				//handleConfigResponseEvent(msg.config_response_event);
				//break;
				//case eLeapEventType_Image:
				//handleImageEvent(msg.image_event);
				//break;
				//case eLeapEventType_PointMappingChange:
				//handlePointMappingChangeEvent(msg.point_mapping_change_event);
				//break;
				//case eLeapEventType_TrackingMode:
				//handleTrackingModeEvent(msg.tracking_mode_event);
				//break;
				//case eLeapEventType_LogEvents:
				//handleLogEvents(msg.log_events);
				//break;
				//case eLeapEventType_HeadPose:
				//handleHeadPoseEvent(msg.head_pose_event);
				//break;
				//case eLeapEventType_IMU:
				//handleImuEvent(msg.imu_event);
				//break;
				//default:
					//discard unknown message types
					//ofLogWarning(__FUNCTION__) << "Unhandled message type " << msg.type;
			}
		}
	}

	void Connection::onConnection(const LEAP_CONNECTION_EVENT * event) 
	{
		ofLogNotice(__FUNCTION__);
	}

	void Connection::onConnectionLost(const LEAP_CONNECTION_LOST_EVENT * event) 
	{
		ofLogNotice(__FUNCTION__);
	}

	void Connection::onDevice(const LEAP_DEVICE_EVENT * event)
	{
		ofLogNotice(__FUNCTION__) << "id: " << event->device.id;

		LEAP_DEVICE deviceHandle;

		// Open device using LEAP_DEVICE_REF from event struct.
		eLeapRS result = LeapOpenDevice(event->device, &deviceHandle);
		if (result != eLeapRS_Success) 
		{
			ofLogError(__FUNCTION__) << "Could not open device: " << getResultString(result);
			return;
		}

		// Create a struct to hold the device properties, we have to provide a buffer for the serial string.
		LEAP_DEVICE_INFO deviceProperties = { sizeof(deviceProperties) };
		// Start with a length of 1 (pretending we don't know a priori what the length is).
		// Currently device serial numbers are all the same length, but that could change in the future
		deviceProperties.serial_length = 1;
		deviceProperties.serial = (char *)malloc(deviceProperties.serial_length);
		// This will fail since the serial buffer is only 1 character long,
		// but deviceProperties is updated to contain the required buffer length.
		result = LeapGetDeviceInfo(deviceHandle, &deviceProperties);
		if (result == eLeapRS_InsufficientBuffer) 
		{
			// Try again with correct buffer size.
			deviceProperties.serial = (char *)realloc(deviceProperties.serial, deviceProperties.serial_length);
			result = LeapGetDeviceInfo(deviceHandle, &deviceProperties);
			if (result != eLeapRS_Success) 
			{
				ofLogError(__FUNCTION__) << "Failed to get device info: " << getResultString(result);
				free(deviceProperties.serial);
				return;
			}
		}

		this->lock();
		{
			auto device = std::make_shared<Device>();
			device->setup(event->device.id, &deviceProperties);
			this->devices.emplace(event->device.id, device);
		}
		this->unlock();

		free(deviceProperties.serial);
		LeapCloseDevice(deviceHandle);
	}

	void Connection::onDeviceLost(const LEAP_DEVICE_EVENT * event) 
	{
		ofLogNotice(__FUNCTION__) << "id: " << event->device.id;

		this->lock();
		{
			auto it = this->devices.find(event->device.id);
			if (it != this->devices.end())
			{
				this->devices.erase(it);
			}
		}
		this->unlock();
	}

	void Connection::onDeviceFailure(const LEAP_DEVICE_FAILURE_EVENT * event)
	{
		ofLogNotice(__FUNCTION__) << "status: " << getStatusString(event->status);
	}

	void Connection::onTracking(uint32_t id, const LEAP_TRACKING_EVENT * event) 
	{
		ofLogVerbose(__FUNCTION__) << "id: " << id;

		this->lock();
		{
			auto it = this->devices.find(id);
			if (it != this->devices.end()) 
			{
				it->second->update(event);
			}
		}
		this->unlock();
	}

	const std::map<int, std::shared_ptr<Device>> & Connection::getDevices() const
	{
		return this->devices;
	}

	std::shared_ptr<Device> Connection::getDevice() const 
	{
		if (this->devices.empty()) return nullptr;

		return this->devices.begin()->second;
	}
}
