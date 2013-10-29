//
//  Autoportrait.h
//  promenade_mobile_tvs
//
//  Created by Alain Barthelemy on 27/10/13.
//
//

#ifndef promenade_mobile_tvs_Autoportrait_h
#define promenade_mobile_tvs_Autoportrait_h

#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

#define IMG_STACK_LENGHT 3 // must be more than 2

#define STATIC_LENGHT 10

#define PIXEL_SIZE 100 //10
class Autoportrait {
    
    
    
public:
    
    // methods
    void update();
    void draw();
    void drawStatic();
    
    void prepareLoadedImageH(ofImage* image);
    void prepareLoadedImageB(ofImage* image);
    bool hasJustArrived(ofImage image);
    
    void urlResponse(ofHttpResponse & response);
    void loadH();
    void loadB();
    void exit();
    
    
    //constructor
    Autoportrait(float x, float y, float w, float h);
    
    // variables
    float x;
    float y;
    float w;
    float h;
    
    ofImage imgH[IMG_STACK_LENGHT];
    ofImage imgB[IMG_STACK_LENGHT];
    
    int imgHIndex;
    int imgBIndex;
    
    int loadingHIndex;
    int loadingBIndex;
    bool FIRST_LOAD_H;
    bool FIRST_LOAD_B;
        
    int timestamp;
    
    ofxThreadedImageLoader loader;
    
    
    
private:
    
    
};						//don't forget the semicolon in the end of the class definition

#endif
