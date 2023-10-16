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
                    this->renderBone(digit.metacarpal, colors[0]);
                    this->renderBone(digit.proximal, colors[1]);
                    this->renderBone(digit.intermediate, colors[2]);
                    this->renderBone(digit.distal, colors[3]);
				}
			}
		}
	}
	this->cam.end();

	ofSetColor(255);

	int currY = 20;
	const auto & devices = this->connection.getDevices();
	for (auto dp : devices)
	{
		auto device = dp.second;
		for (auto hp : device->getHands())
		{
			auto hand = hp.second;
			std::ostringstream oss;
			oss << "Hand " << (hand->getType() == eLeapHandType_Left ? "LEFT" : "RIGHT") << std::endl
				<< "Pinch Distance = " << ofToString(hand->getPinchDistance(), 2) << ", Strength = " << ofToString(hand->getPinchStrength(), 2) << std::endl
				<< "Grab Distance = " << ofToString(hand->getGrabAngle(), 2) << ", Strength = " << ofToString(hand->getGrabStrength(), 2);
			ofDrawBitmapString(oss.str(), 10, currY);
			currY += 60;
		}
	}
}

void ofApp::renderBone(const ofxUltraleapGemini::Bone& bone, const ofFloatColor& color)
{
    glm::mat4 xform;
    xform *= glm::translate(bone.jointPrev);
    xform *= glm::toMat4(bone.rotation);
    xform *= glm::eulerAngleX(ofDegToRad(90));

    ofPushMatrix();
    ofMultMatrix(xform);
    {
        ofSetColor(color);
        ofDrawCylinder(bone.width * 0.5f, glm::distance(bone.jointNext, bone.jointPrev));
    }
    ofPopMatrix();

    ofSetColor(color);
    ofDrawLine(bone.jointPrev, bone.jointNext);
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
