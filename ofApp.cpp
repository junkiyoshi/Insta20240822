#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(0.5);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);

	for (int base_x = -240; base_x <= 240; base_x += 5) {

		for (int base_z = -240; base_z <= 240; base_z += 5) {

			auto angle = std::atan2(base_z, base_x);
			
			auto noise_location = glm::vec2((angle), sin(angle));
			auto radius = ofMap(ofNoise(noise_location.x * 0.5, noise_location.y * 0.5, ofGetFrameNum() * 0.05), 0, 1, 30, 230);
			auto location = glm::vec2(radius * cos(angle), radius * sin(angle));
			auto distance = glm::distance(location, glm::vec2(base_x, base_z));

			auto param = 5;
			if (distance < 50) {
								
				param = ofMap(glm::distance(location, glm::vec2(base_x, base_z)), 0, 50, 0, 5);
			}

			for (int i = 0; i <= 10; i++) {

				if (i < param) {

					ofPushMatrix();
					ofTranslate(base_x, -150 + i * 10, base_z);

					ofSetColor(0);
					ofFill();
					ofDrawBox(9.5);

					ofSetColor(255);
					ofNoFill();
					ofDrawBox(10);

					ofPopMatrix();
				}
				else if (param < i) {

					ofPushMatrix();
					ofTranslate(base_x, 150 - (10 - i) * 10, base_z);

					ofSetColor(0);
					ofFill();
					ofDrawBox(9.5);

					ofSetColor(255);
					ofNoFill();
					ofDrawBox(10);

					ofPopMatrix();
				}
				else {

				}
			}
		}
	}

	this->cam.end();

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}