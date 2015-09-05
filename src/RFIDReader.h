//
//  RFIDReader.h
//  BlackTonicArduinoOSC
//
//  Created by David Haylock on 30/08/2015.
//
//
#include "ofMain.h"
#include "ofxJSON.h"

struct RFIDCard
{
    int id;
    int value;
    string tagValue;
};

//--------------------------------------------------------------
class RFIDReader {
public:
    void setup(string name, int ReaderId,int baud = 9600);
    void update();
    void draw(int x,int y);
    void close();
    
    bool latchLocked();
    bool tagIsNew();
    bool isConnected();
    
    string newTag();
    string readerValue();
    
private:
    ofSerial reader;
    unsigned char readStuff[16];
    bool latch;
    std::deque<string> tagList;
    int _id;
};

