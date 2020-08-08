#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(5);

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->frame.clear();

	for (int i = 0; i < 3; i++) {

		auto direction = 5 * glm::normalize(glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), 0));
		vector<glm::vec3> log;
		ofColor color;
		color.setHsb(ofRandom(255), 255, 230);
		
		log.push_back(direction * 10);
		this->log_list.push_back(log);
		this->direction_list.push_back(direction);
		this->param_list.push_back(512);
		this->color_list.push_back(color);
	}

	for (int i = 0; i < this->log_list.size(); i++) {

		auto location = this->log_list[i].back() + this->direction_list[i];
		this->log_list[i].push_back(location);
	}

	for (int i = 0; i < this->log_list.size(); i++) {

		int index = this->frame.getNumVertices();
		this->frame.addVertices(this->log_list[i]);

		this->param_list[i] -= 2;

		for (int k = index; k < this->frame.getNumVertices() - 1; k++) {

			this->frame.addIndex(k);
			this->frame.addIndex(k + 1);
		}

		ofColor color = this->param_list[i] > 255 ? 
			this->color_list[i] : ofColor(this->color_list[i], ofMap(this->param_list[i], 0, 255, 0, 255));
		for (int k = index; k < this->frame.getNumVertices(); k++) {

			this->frame.addColor(color);
		}
	}

	for (int i = this->log_list.size() - 1; i >= 0; i--) {

		if (this->param_list[i] <= 0) {

			this->log_list.erase(this->log_list.begin() + i);
			this->direction_list.erase(this->direction_list.begin() + i);
			this->param_list.erase(this->param_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	this->frame.drawWireframe();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}