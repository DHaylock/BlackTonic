#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxGui.h"
#include "ofxSimpleTimer.h"
#include "ofxOsc.h"
#include "ofxJSON.h"
#include "RFIDReader.h"
#define NUM_TRIGGERS 12

#define RESET_BUTTON_PIN 5
#define GOOD_LED_PIN 13
#define ERROR_LED 7
#define BUTTON_ON 53

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);

        ofArduino ard;
        RFIDReader cardReader;
        bool bSetupArduino;
        bool triggerLatch[12];
    
        vector <ofColor> colors;
        vector <ofVec2f> pos;
        vector <ofVec2f> labelPos;
        vector <ofVec2f> ldrReadingLabelPos;
        vector <string> cardLabel;
        vector <int> angles;
    
        int size;
        float radius;
        ofPoint _pos;
    
        int _x;
        int _y;
    
private:
    
        void setupTimers();
        void updateTimers();
        void drawTimers();
    
        void setupArduino(const int & version);
        void digitalPinChanged(const int & pinNum);
        void analogPinChanged(const int & pinNum);
        void updateArduino();
        void setupLDRPositions(int x,int y);
        void drawLDRPositions();
    
        ofTrueTypeFont clockLabels;
        ofTrueTypeFont title;
        ofTrueTypeFont indicatorFont;
    
        void loadAppConfig();

        ofxJSONElement configFile;
    
    
        void setupGUI();
        ofxPanel gui;
        ofxIntSlider triggerThreshold;
        ofxIntSlider triggerTimer;
        ofxButton reset;
    
        ofxSimpleTimer timer[12];
        ofxSimpleTimer killDelay;
    
        void killDelayComplete(int &args);
        void killDelayStarted(int &args);
    
        bool killLatch;
    
        void setupOSC(string host,int port = 53000);
        void fireSignal(int num);
        ofxOscSender sender;
        string QLAB_Command(int num);
        
        void timerCompleteHandler(int &args);
        void timerStartedHandler(int &args);

        void resetLatches();
        bool rfidLatches[2];
        bool resetButton;
    
        bool goodLEDValue;
        bool loadedJSONLED;
    
        // Load Config Values
        string arddevicename;
        string rfiddevicename;
        string oschostname;
        int rfidbaud;
        int ardbaud;
        int oscPort;
        int timerValue;
        int thresholdValue;
        string rfidTag1;
        string rfidTag2;

};
