#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    autoportrait = new Autoportrait(0,0,ofGetWidth(),ofGetHeight());

}

//--------------------------------------------------------------
void testApp::update(){
    autoportrait->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    autoportrait->draw();
}

void testApp::exit(){
    autoportrait->exit();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
