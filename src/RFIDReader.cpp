//
//  RFIDReader.cpp
//  BlackTonicArduinoOSC
//
//  Created by David Haylock on 30/08/2015.
//
//

#include "RFIDReader.h"
//--------------------------------------------------------------
void RFIDReader::setup(string name, int ReaderId, int baud)
{
    latch = false;
    reader.setup(name,baud);
    _id = ReaderId;
}
//--------------------------------------------------------------
void RFIDReader::update()
{
    if (tagList.size() > 5) {
        tagList.pop_back();
    }
    if (reader.available() > 12) {
        cout << reader.available() << endl;
        reader.readBytes(readStuff, 16);
        cout << "Reader Id:" << ofToString(_id) << ": " << readStuff << endl;
        reader.flush();
        latch = true;
    }
    else if(reader.available() <= 11)
    {
        latch = false;
    }
}
//--------------------------------------------------------------
void RFIDReader::close()
{
    reader.close();
}
//--------------------------------------------------------------
void RFIDReader::draw(int x,int y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofSetColor(0);
    ofFill();
    ofRect(0,0, 200, 100);
    ofSetColor(255);
    ofNoFill();
    ofRect(0,0, 200, 100);
    
    if (!isConnected()) {
        ofDrawBitmapString("Reader "+ ofToString(_id)+" is not Connected", 5,15);
    }
    else {
        ofDrawBitmapString("Reader "+ ofToString(_id)+" is Connected", 5,15);
    }
    ofDrawBitmapString("Last Tag", 110,30);
    for (int i = 0; i < tagList.size(); i++) {
        ofSetColor(255-(i*30));
        ofDrawBitmapString(tagList[i], 5,30+(i*15));
    }
    ofPopMatrix();
}
//--------------------------------------------------------------
bool RFIDReader::tagIsNew()
{
    if (latch) {
        return true;
    }
    else{
        return false;
    }
}
//--------------------------------------------------------------
string RFIDReader::newTag()
{
    if (tagIsNew()) {
        string TAG = ofToString(readStuff);
        tagList.push_front(TAG);
        return TAG;
    }
}
//--------------------------------------------------------------
bool RFIDReader::isConnected()
{
    if (reader.isInitialized()) {
        return true;
    }
    else
    {
        return false;
    }
}