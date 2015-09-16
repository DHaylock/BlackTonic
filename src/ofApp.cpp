#include "ofApp.h"
#pragma mark - Load Config
//--------------------------------------------------------------
void ofApp::loadAppConfig()
{
    // Check if we can open the file
    bool opened = configFile.open("blacktonicconfig.json");
    if (!opened) {
        cout << "Could not find config file" << endl;
        cout << "Exiting" << endl;
        return;
    }
    
    cardLabel.push_back("A");
    cardLabel.push_back("2");
    cardLabel.push_back("3");
    cardLabel.push_back("4");
    cardLabel.push_back("5");
    cardLabel.push_back("6");
    cardLabel.push_back("7");
    cardLabel.push_back("8");
    cardLabel.push_back("9");
    cardLabel.push_back("10");
    cardLabel.push_back("J");
    cardLabel.push_back("Q");
    
    //--------------------------------------------
    cout << "Loaded Config File" << endl;
    //--------------------------------------------
    arddevicename = configFile["connections"]["arduino"]["arduinodevicename"].asString();
    ardbaud = configFile["connections"]["arduino"]["baud"].asInt();
    cout << "-----------------------" << endl;
    cout << "Got Arduino Data" << endl;
    //--------------------------------------------
    rfiddevicename = configFile["connections"]["rfid"]["rfiddevicename"].asString();
    rfidbaud = configFile["connections"]["rfid"]["baud"].asInt();
    cout << "-----------------------" << endl;
    cout << "Got RFID Data" << endl;
    //--------------------------------------------
    oschostname = configFile["connections"]["osc"]["hostname"].asString();
    oscPort = configFile["connections"]["osc"]["port"].asInt();
    cout << "-----------------------" << endl;
    cout << "Got OSC Data" << endl;
    //--------------------------------------------
    timerValue = configFile["appsettings"]["delaytimer"].asInt();
    thresholdValue = configFile["appsettings"]["threshold"].asInt();
    cout << "-----------------------" << endl;
    cout << "Got App Settings" << endl;
    
    rfidTag1 = configFile["rfid"]["tag1"].asString();
    rfidTag2 = configFile["rfid"]["tag2"].asString();
    
}
#pragma mark - Standard
//--------------------------------------------------------------
void ofApp::setup()
{
    //--------------------------------------------
    _x = ofGetWidth()/2;
    _y = ofGetHeight()/2;
    
    //--------------------------------------------
    loadAppConfig();
    resetLatches();
    
    //--------------------------------------------
    clockLabels.loadFont("NewMedia Fett.ttf", 15);
    title.loadFont("NewMedia Fett.ttf", 20);
    indicatorFont.loadFont("NewMedia Fett.ttf", 10);

    //--------------------------------------------
    ard.connect(arddevicename,ardbaud);
    cardReader.setup(rfiddevicename,1, rfidbaud);
    
    //--------------------------------------------
    setupLDRPositions(_x,_y);
    setupTimers();
    setupGUI();
    setupOSC(oschostname);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;
    killLatch = false;
}
//--------------------------------------------------------------
void ofApp::update()
{
    updateTimers();
    updateArduino();
    
    if (cardReader.tagIsNew()){
        if (!rfidLatches[0] && ofIsStringInString(cardReader.newTag(),rfidTag1)) {
            fireSignal(13);
            ofSleepMillis(200);
            fireSignal(0);
            rfidLatches[0] = true;
        }
        else if (!rfidLatches[1] && ofIsStringInString(cardReader.newTag(), rfidTag2)) {
            fireSignal(13);
            ofSleepMillis(200);
            fireSignal(15);
            rfidLatches[1] = true;
        }
        else {
            
        }
    }
    
    cardReader.update();
    if (reset) {
        resetLatches();
    }
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0,0,0);
    if (!bSetupArduino){
        title.drawString("arduino not ready...\n", 515, 40);
    }
    drawTimers();
    drawLDRPositions();
    cardReader.draw(ofGetWidth()-200, 0);
    if (!rfidLatches[0]) {
        ofSetColor(ofColor::red);
    }
    else {
        ofSetColor(51, 153, 51);
    }
    clockLabels.drawString("Card 1 : "+rfidTag1, 5,40);

    if (!rfidLatches[1]) {
        ofSetColor(ofColor::red);
    }
    else {
        ofSetColor(51, 153, 51);
    }
    clockLabels.drawString("Card 2 : "+rfidTag2, 5,65);
    
    gui.draw();
    ofSetColor(255,200);
    title.drawString("Black Tonic", 10,ofGetHeight()-15);
    indicatorFont.drawString("built by David Haylock", 170,ofGetHeight()-15);
}
//--------------------------------------------------------------
void ofApp::exit()
{
//    ard.disconnect();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
//    switch (key) {
//        case 'a':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "A" << endl;
//            fireSignal(1);
//            triggerLatch[0] = true;
//            break;
//        case '2':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "2" << endl;
//            fireSignal(2);
//            triggerLatch[1] = true;
//            break;
//        case '3':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "3" << endl;
//            fireSignal(3);
//            triggerLatch[2] = true;
//            break;
//        case '4':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "4" << endl;
//            fireSignal(4);
//            triggerLatch[3] = true;
//            break;
//        case '5':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "5" << endl;
//            fireSignal(5);
//            triggerLatch[4] = true;
//            break;
//        case '6':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "6" << endl;
//            fireSignal(6);
//            triggerLatch[5] = true;
//            break;
//        case '7':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "7" << endl;
//            fireSignal(7);
//            triggerLatch[6] = true;
//            break;
//        case '8':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "8" << endl;
//            fireSignal(8);
//            triggerLatch[7] = true;
//            break;
//        case '9':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "9" << endl;
//            fireSignal(9);
//            triggerLatch[8] = true;
//            break;
//        case '0':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "J" << endl;
//            fireSignal(10);
//            triggerLatch[9] = true;
//            break;
//        case 'j':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "Q" << endl;
//            fireSignal(11);
//            triggerLatch[10] = true;
//            break;
//        case 'q':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "Q" << endl;
//            fireSignal(12);
//            triggerLatch[11] = true;
//            break;
//        case '[':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "RFID 1" << endl;
//            fireSignal(0);
//            rfidLatches[0] = true;
//            break;
//        case ']':
//            cout << "Firing Dead Cue" << endl;
//            fireSignal(13);
//            ofSleepMillis(400);
//            cout << "Firing Cue" << "A" << endl;
//            fireSignal(15);
//            rfidLatches[1] = true;
//            break;
//        default:
//            break;
//    }
}
#pragma mark - Arduino
//--------------------------------------------------------------
//
// Other Stuff
//
//--------------------------------------------------------------
void ofApp::setupArduino(const int & version)
{
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    goodLEDValue = false;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "Firmata V" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();

    // Setup the LED Response Pins
    ard.sendDigitalPinMode(RESET_BUTTON_PIN, ARD_INPUT);
    ard.sendDigitalPinMode(ERROR_LED, ARD_OUTPUT);
    ard.sendDigitalPinMode(GOOD_LED_PIN, ARD_OUTPUT);
    ard.sendDigitalPinMode(BUTTON_ON, ARD_OUTPUT);

    // Setup the LDR's
    for(int i = 0; i < NUM_TRIGGERS; i++) {
        ard.sendAnalogPinReporting(i, ARD_ANALOG);
    }
    
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}
//--------------------------------------------------------------
void ofApp::updateArduino()
{
    // If the Arduino is running
    if (bSetupArduino) {
        
        if (ofGetFrameNum() % 30 == 0 && !triggerLatch[11]) {
            goodLEDValue = !goodLEDValue;
        }
        else if (triggerLatch[11])  {
            goodLEDValue = true;
        }
        
        ard.sendDigital(BUTTON_ON, ARD_ON);
        ard.sendDigital(GOOD_LED_PIN,goodLEDValue);
        

        for (int i = 0; i < NUM_TRIGGERS; i++) {
            if (i > 0) {
                if (ard.getAnalog(i) < triggerThreshold && !triggerLatch[i] && triggerLatch[i-1]) {
                    timer[i].start(false);
                }
                else {
                    timer[i].stop();
                    timer[i].reset();
                }
            }
            else {
                if (ard.getAnalog(i) < triggerThreshold && !triggerLatch[i]) {
                    timer[i].start(false);
                }
                else {
                    timer[i].stop();
                    timer[i].reset();
                }
            }
        }
        
    }
    ard.update();

}
//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pinNum) {
    
    // If we get a break from the button then reset the all the latches
    if( pinNum == RESET_BUTTON_PIN ) {
        if (ard.getDigital(pinNum) == ARD_HIGH) {
            resetLatches();
        }
//        cout << pinNum << ard.getDigital(pinNum) << endl;
    }
}
//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
//cout << pinNum << ard.getAnalog(pinNum) << endl;
}
#pragma mark - LDRS
//--------------------------------------------------------------
void ofApp::drawLDRPositions()
{
    ofFill();
    ofSetColor(51, 153, 51);
    ofSetCircleResolution(250);
    ofCircle(_x, _y, 250);
    ofNoFill();
    ofSetColor(255, 255);
    ofCircle(_x, _y, 250);
//    for (int i = 0; i < pos.size(); i++) {
//        
//        ofPushMatrix();
//        ofTranslate(_x,_y);
//        ofRotateZ(-60);
//        ofPushMatrix();
//        ofTranslate(-_x, -_y);
//
//        ofSetColor(255,255);
//        clockLabels.drawString(cardLabel[i], pos[i].x,pos[i].y);
//        ofPushMatrix();
//        ofTranslate(labelPos[i]);
//        ofRotateZ(60);
//        ofPushMatrix();
//        ofTranslate(-labelPos[i]);
//        if (i >= 5) {
//            ofSetColor(51, 153, 51);
//            clockLabels.drawString(ofToString(i+1), labelPos[i].x-10,labelPos[i].y);
//        }
//        else {
//            ofSetColor(51, 153, 51);
//            clockLabels.drawString(ofToString(i+1), labelPos[i].x,labelPos[i].y);
//        }
//        ofPopMatrix();
//        
//        ofPushMatrix();
//        ofTranslate(ldrReadingLabelPos[i]);
//        ofRotateZ(60);
//        ofPushMatrix();
//        ofTranslate(-ldrReadingLabelPos[i]);
//        if (i == 11) {
//            if (!triggerLatch[i]) {
//                ofSetColor(ofColor::red);
//                clockLabels.drawString("Not Triggered ", ldrReadingLabelPos[i].x-50,ldrReadingLabelPos[i].y);
//            }
//            else {
//                ofSetColor(51, 153, 51);
//                clockLabels.drawString("Triggered ", ldrReadingLabelPos[i].x-50,ldrReadingLabelPos[i].y);
//            }
//        }
//        else if (i == 5) {
//            if (!triggerLatch[i]) {
//                ofSetColor(ofColor::red);
//                clockLabels.drawString("Not Triggered ", ldrReadingLabelPos[i].x-50,ldrReadingLabelPos[i].y);
//            }
//            else {
//                ofSetColor(51, 153, 51);
//                clockLabels.drawString("Triggered ", ldrReadingLabelPos[i].x-50,ldrReadingLabelPos[i].y);
//            }
//        }
//        else if (i > 5 && i < 11) {
//            if (!triggerLatch[i]) {
//                ofSetColor(ofColor::red);
//                clockLabels.drawString("Not Triggered ", ldrReadingLabelPos[i].x-120,ldrReadingLabelPos[i].y);
//            }
//            else {
//                ofSetColor(51, 153, 51);
//                clockLabels.drawString("Triggered ", ldrReadingLabelPos[i].x-120,ldrReadingLabelPos[i].y);
//            }
//        }
//        else {
//            if (!triggerLatch[i]) {
//                ofSetColor(ofColor::red);
//                clockLabels.drawString("Not Triggered ",ldrReadingLabelPos[i].x,ldrReadingLabelPos[i].y);
//            }
//            else {
//                ofSetColor(51, 153, 51);
//                clockLabels.drawString("Triggered ", ldrReadingLabelPos[i].x,ldrReadingLabelPos[i].y);//+ ofToString(ard.getAnalog(i))
//            }
//        }
//        ofPopMatrix();
//        ofPopMatrix();
//        ofPopMatrix();
//    }
//   
//    ofPushMatrix();
//    for (int i = 0; i < pos.size(); i++) {
//        ofPushMatrix();
//        ofTranslate(pos[i]);
//        ofRotateZ(angles[i]);
//        ofPushMatrix();
//        ofTranslate(-pos[i]);
//        ofPushStyle();
//        ofNoFill();
//        ofSetColor(255);
//        ofRect(pos[i].x-35,pos[i].y-25, 70,50);
//        ofPopStyle();
//        ofPopMatrix();
//        ofPopMatrix();
//    }
//    ofPopMatrix();
//    
//    ofPushMatrix();
//    ofTranslate(_x,_y);
//    ofRotateZ(-60);
//    ofPushMatrix();
//    ofTranslate(-_x,-_y);
//    for (int i = 0; i < pos.size(); i++) {
//        if (triggerLatch[i]) {
//            ofPushStyle();
//            ofFill();
//            ofSetColor(255, 0, 0);
//            ofRect(pos[i].x-10,pos[i].y-5, 10,10);
//            ofPopStyle();
//        }
//    }
//    ofPopMatrix();
//    ofPopMatrix();
    stringstream ss;
    for (int i = 0; i < NUM_TRIGGERS; i++) {
        ofSetColor(51, 153, 51);
        if (i == NUM_TRIGGERS) {
            ss << cardLabel[i] << ": " << ofToString(ard.getAnalog(i)) << endl;
        }
        else {
            ss << cardLabel[i] << ": " << ofToString(ard.getAnalog(i)) << " ";
        }
        
    }
    indicatorFont.drawString(ss.str(),5,15);
}
//--------------------------------------------------------------
void ofApp::setupLDRPositions(int x,int y)
{
    size = NUM_TRIGGERS;
    radius = 200;

    for (int i = 0; i < size; i++)
    {
        float angle = (1.0 * i) * (2.0 * M_PI)/(1.0 * size);
        
        float rx = x + (radius * cos(angle));
        float ry = y + (radius * sin(angle));
        
        float rx1 = x + ((radius-55) * cos(angle));
        float ry1 = y + ((radius-55) * sin(angle));
        
        float rx2 = x + ((radius+80) * cos(angle));
        float ry2 = y + ((radius+80) * sin(angle));
        
        pos.push_back(ofVec2f(rx,ry));
        labelPos.push_back(ofVec2f(rx1,ry1));
        ldrReadingLabelPos.push_back(ofVec2f(rx2,ry2));
    }
    
    for (int i = 0;  i < size; i++) {
        angles.push_back(0+(i*30));
    }
}
#pragma mark - Latches
//--------------------------------------------------------------
void ofApp::resetLatches()
{
    for (int i = 0; i < NUM_TRIGGERS; i++) {
        triggerLatch[i] = false;
    }
    rfidLatches[0] = false;
    rfidLatches[1] = false;
}
#pragma mark - Timers
//--------------------------------------------------------------
void ofApp::setupTimers()
{
    for(int i = 0; i < NUM_TRIGGERS; i++) {
        timer[i].setup(timerValue,"Timer "+ofToString(i),i);
        ofAddListener(timer[i].TIMER_COMPLETE , this, &ofApp::timerCompleteHandler);
        ofAddListener(timer[i].TIMER_STARTED , this, &ofApp::timerStartedHandler);
    }
    ofAddListener(killDelay.TIMER_COMPLETE, this, &ofApp::killDelayComplete);
    ofAddListener(killDelay.TIMER_STARTED, this, &ofApp::killDelayStarted);
    killDelay.setup(200);
}
//--------------------------------------------------------------
void ofApp::updateTimers()
{
    for(int i = 0; i < NUM_TRIGGERS; i++) {
        timer[i].update();
    }
}
//--------------------------------------------------------------
void ofApp::drawTimers()
{
    ofPushStyle();
    for(int i = 0; i < NUM_TRIGGERS; i++) {
        ofSetColor(255);
        if (triggerLatch[i]) {
            ofDrawBitmapStringHighlight(" Timer "+ofToString(i) +" Has Run", 0,100+(i*20));
        }
        else {
            timer[i].draw(0, 100+(i*20));
        }
    }
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::timerCompleteHandler(int &args)
{
    for(int i = 0; i < NUM_TRIGGERS; i++) {
        if (args == i) {
            cout << "Firing Dead Cue" << i << endl;
            fireSignal(13);
            ofSleepMillis(400);
            cout << "Firing Cue" << i << endl;
            fireSignal(i+1);
            triggerLatch[i] = true;
        }
    }
}
//--------------------------------------------------------------
void ofApp::timerStartedHandler(int &args)
{
    cout<<"TIMER STARTED"<< args << endl;
}
//--------------------------------------------------------------
void ofApp::killDelayComplete(int &args)
{
    cout << "Kill Complete" << endl;
}
//--------------------------------------------------------------
void ofApp::killDelayStarted(int &args)
{
    cout << "Kill Started" << endl;
}
#pragma mark - GUI
//--------------------------------------------------------------
void ofApp::setupGUI()
{
    gui.setup();
    gui.setPosition(ofGetWidth()-gui.getWidth(), 100);
    gui.setName("Black Tonic");
    gui.add(reset.setup("Reset Latches",false));
    gui.add(triggerThreshold.setup("Low Threshold", 350, 0, 1000));
}
#pragma mark - OSC
//--------------------------------------------------------------
void ofApp::setupOSC(string host,int port)
{
    sender.setup(host, port);
}
//--------------------------------------------------------------
string ofApp::QLAB_Command(int num)
{
    string commandLine = "/cue/"+ ofToString(num)+"/start";
    return commandLine;
}
//--------------------------------------------------------------
void ofApp::fireSignal(int num)
{
    ofxOscMessage e;
    e.setAddress(QLAB_Command(num));
    e.addStringArg("GO");
    sender.sendMessage(e);
    cout << "Fire Cue " << num << endl;
}