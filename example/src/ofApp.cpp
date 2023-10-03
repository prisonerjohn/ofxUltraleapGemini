#include "ofApp.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp> 

//--------------------------------------------------------------
void ofApp::setup()
{
	if (this->connection.open())
	{
		ofLogNotice(__FUNCTION__) << "Connection opened!";
	} 
	else
	{
		ofLogError(__FUNCTION__) << "Failed to open connection";
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofFloatColor colors[] = 
	{
		ofFloatColor::red,
		ofFloatColor::green,
		ofFloatColor::blue,
		ofFloatColor::yellow
	};

	this->cam.begin();
	{
		const auto & devices = this->connection.getDevices();
		for (auto dp : devices) 
		{
			auto device = dp.second;
			for (auto hp : device->getHands()) 
			{
				auto hand = hp.second;

				for (int d = 0; d < 5; ++d) 
				{
					auto & digit = hand->getDigits()[d];
					for (int b = 0; b < 4; ++b) 
					{
						auto & bone = digit.bones[b];

						glm::mat4 xform;
						xform *= glm::translate(bone.jointPrev);
						xform *= glm::toMat4(bone.rotation);
						xform *= glm::eulerAngleX(ofDegToRad(90));

						ofPushMatrix();
						ofMultMatrix(xform);
						{
							ofSetColor(colors[b]);
							ofDrawCylinder(bone.width * 0.5f, glm::distance(bone.jointNext, bone.jointPrev));
						}
						ofPopMatrix();

						ofSetColor(colors[b]);
						ofDrawLine(bone.jointPrev, bone.jointNext);
					}
				}
			}
		}
	}
	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
