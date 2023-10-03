#pragma once

#include "LeapC.h"

#include <map>

#include "ofThread.h"

namespace ofxUltraleapGemini 
{
	class Device;

	class Connection 
		: ofThread
	{
	public:
		Connection();
		~Connection();

		bool open();
		bool close();

		const std::map<int, std::shared_ptr<Device>>& getDevices() const;
		std::shared_ptr<Device> getDevice() const;

	protected:
		void threadedFunction() override;

	private:
		std::string getResultString(eLeapRS result);
		std::string getStatusString(eLeapDeviceStatus status);

		void onConnection(const LEAP_CONNECTION_EVENT * event);
		void onConnectionLost(const LEAP_CONNECTION_LOST_EVENT * event);

		void onDevice(const LEAP_DEVICE_EVENT * event);
		void onDeviceLost(const LEAP_DEVICE_EVENT * event);
		void onDeviceFailure(const LEAP_DEVICE_FAILURE_EVENT * event);

		void onTracking(uint32_t id, const LEAP_TRACKING_EVENT * event);

	private:
		LEAP_CONNECTION handle;

		std::map<int, std::shared_ptr<Device>> devices;
	};
}
