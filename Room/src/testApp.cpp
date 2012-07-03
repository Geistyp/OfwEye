#include "testApp.h"

#include "Room.h"

Room room;

//--------------------------------------------------------------
void testApp::setup(){

	grcam.setPosition(ofVec3f(0, 0, -400));
	grcam.lookAt(ofVec3f(0, 0, 0));

	int *p[2];

	p[0] = new int[5];

	room.init(ofVec3f(640, 360, 600), &grcam);

}

//--------------------------------------------------------------
void testApp::update(){

	room.update();

	room.drawRoom();

}

//--------------------------------------------------------------
void testApp::draw(){

	ofBackground(0);

	room.draw();

	

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if ( key == 'r' ) 
	{
		room.shader_.unload();
		room.shader_.load("room");
	}

	if ( key == ' ' ) room.toggle_power();

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
