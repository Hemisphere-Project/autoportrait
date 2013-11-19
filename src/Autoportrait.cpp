//
//  Autoportrait.cpp
//  promenade_mobile_tvs
//
//  Created by Alain Barthelemy on 27/10/13.
//
//

#include "Autoportrait.h"

Autoportrait::Autoportrait(float _x, float _y, float _w, float _h)
{
	x = _x;
	y = _y;
	w = _w;
    h = _h;
	
    imgHIndex = 0;
    imgBIndex = 0;
    
    loadingHIndex=0;
    loadingBIndex=0;
    FIRST_LOAD_H=true;
    FIRST_LOAD_B=true;
    
    ofRegisterURLNotification(this);
    
    timestamp = ofGetUnixTime();
    
    loadH();
    loadB();
	
}


void Autoportrait::update(){
	w = ofGetWidth();
    h = ofGetHeight();
    
    /*if(ofGetUnixTime() <= (timestamp + STATIC_LENGHT)){
    }else{
        timestamp = ofGetUnixTime();//reset the counter
        imgHIndex++;
        if(imgHIndex >= IMG_STACK_LENGHT)
            imgHIndex = 0;
        imgBIndex++;
        if(imgBIndex >= IMG_STACK_LENGHT)
            imgBIndex = 0;
        
        loadH();
        loadB();
        
    }*/
    
    int nextHIndex = (imgHIndex >= IMG_STACK_LENGHT-1) ? 0 : imgHIndex+1;
    int nextBIndex = (imgBIndex >= IMG_STACK_LENGHT-1) ? 0 : imgBIndex+1;
    
    if(imgH[nextHIndex].bAllocated()){
        imgHIndex++;
        if(imgHIndex >= IMG_STACK_LENGHT)
            imgHIndex = 0;
        loadH();
    }
    if(imgB[nextBIndex].bAllocated()){
        imgBIndex++;
        if(imgBIndex >= IMG_STACK_LENGHT)
            imgBIndex = 0;
        loadB();
    }
	
}


void Autoportrait::draw(){
	
    drawStatic();
    
}

void Autoportrait::drawStatic(){

    
	if(imgH[imgHIndex].bAllocated()){
        
        //if(hasJustArrived(imgH[imgHIndex])) prepareLoadedImageH(&imgH[imgHIndex]);
        
		ofSetColor(255);
        imgH[imgHIndex].draw(x, y);
        
    }
	if(imgB[imgBIndex].bAllocated()){
        
        //if(hasJustArrived(imgB[imgBIndex])) prepareLoadedImageB(&imgB[imgBIndex]);
        
        ofSetColor(255);
        imgB[imgBIndex].draw(x+w/2,y);
    }
    
}

/*void Autoportrait::prepareLoadedImageH(ofImage* image){
    
    image->resize(image->getWidth()/PIXEL_SIZE, image->getHeight()/PIXEL_SIZE);
    image->resize(image->getWidth()*PIXEL_SIZE, image->getHeight()*PIXEL_SIZE);
    
    image->resize((int)floor(image->getWidth()*h/image->getHeight()),h);
    image->crop(0, 0, w/2, h);
    

}
void Autoportrait::prepareLoadedImageB(ofImage* image){
    
    image->resize(image->getWidth()/PIXEL_SIZE, image->getHeight()/PIXEL_SIZE);
    image->resize(image->getWidth()*PIXEL_SIZE, image->getHeight()*PIXEL_SIZE);
    
    image->resize((int)floor(image->getWidth()*h/image->getHeight()),h);
    image->crop(0, 0, w/2, h);
    

}
bool Autoportrait::hasJustArrived(ofImage image){
    //cout << " w "<<image.getWidth()<<" h "<<image.getHeight()<<"\n"<<"  "<<ofGetWidth()<<"  "<<ofGetHeight();
    if(image.isAllocated() && (image.getWidth() != w/2) && (image.getHeight() != h)){/// HACK !!!
        return true;
    }else{
        return false;
    }
}*/



void Autoportrait::urlResponse(ofHttpResponse & response){

//cout << "response  "<< response.request.name << "\n";
    
	if(response.status==200 && response.request.name == "imgHAutoportrait"){
        //imgH[loadingHIndex].setCompression(OF_COMPRESS_NONE);
		imgH[loadingHIndex].loadImage(response.data);
        
        imgH[loadingHIndex].resize(imgH[loadingHIndex].getWidth()/PIXEL_SIZE, imgH[loadingHIndex].getHeight()/PIXEL_SIZE);
        imgH[loadingHIndex].resize(imgH[loadingHIndex].getWidth()*PIXEL_SIZE, imgH[loadingHIndex].getHeight()*PIXEL_SIZE);

        imgH[loadingHIndex].resize((int)floor(imgH[loadingHIndex].getWidth()*h/imgH[loadingHIndex].getHeight()),h);
        imgH[loadingHIndex].crop(0, 0, w/2, h);
        

        
        
        loadingHIndex++;
        
        if(loadingHIndex >= IMG_STACK_LENGHT)
            loadingHIndex = 0;
        
        if(FIRST_LOAD_H){ // in the beginning we load twice
            loadH();
            FIRST_LOAD_H = false;
        }else{
            //imgHIndex++;
            //if(imgHIndex >= IMG_STACK_LENGHT)
            //    imgHIndex = 0;
            //loadH();
        }
        
        
	}else if(response.status==200 && response.request.name == "imgBAutoportrait"){
		imgB[loadingBIndex].loadImage(response.data);
        
        imgB[loadingBIndex].resize(imgB[loadingBIndex].getWidth()/PIXEL_SIZE, imgB[loadingBIndex].getHeight()/PIXEL_SIZE);
        imgB[loadingBIndex].resize(imgB[loadingBIndex].getWidth()*PIXEL_SIZE, imgB[loadingBIndex].getHeight()*PIXEL_SIZE);

        imgB[loadingBIndex].resize((int)floor(imgB[loadingBIndex].getWidth()*h/imgB[loadingBIndex].getHeight()),h);
        imgB[loadingBIndex].crop(0, 0, w/2, h);
        

        
        
        loadingBIndex++;
        
        if(loadingBIndex >= IMG_STACK_LENGHT)
            loadingBIndex = 0;
        
        if(FIRST_LOAD_B){ // in the beginning we load twice
            loadB();
            FIRST_LOAD_B = false;
        }else{
            //imgBIndex++;
            //if(imgBIndex >= IMG_STACK_LENGHT)
            //    imgBIndex = 0;
            //loadB();
        }
        
	}else {
		//cout << response.status << " " << response.error << endl;
		//if(response.status!=-1) loading=false;
	}
}

void Autoportrait::loadH(){
    imgH[loadingHIndex].clear();
    int imgNbr = (int)floor(1+ofRandom(1)*44.99);
	ofLoadURLAsync("http://pm.alainbarthelemy.com/portrait/img" + ofToString(imgNbr) + ".jpg","imgHAutoportrait");
    
}

void Autoportrait::loadB(){
    imgB[loadingBIndex].clear();
    int imgNbr = (int)floor(1+ofRandom(1)*44.99);
	ofLoadURLAsync("http://pm.alainbarthelemy.com/portrait/img" + ofToString(imgNbr) + ".jpg","imgBAutoportrait");
}

/*void Autoportrait::loadH(){
    
    if(FIRST_LOAD_H){ // in the beginning we load twice
        
        imgH[loadingHIndex].clear();
        imgH[loadingHIndex+1].clear();
        
        int imgNbr = (int)floor(1+ofRandom(1)*44.99);
        loader.loadFromURL(imgH[loadingHIndex], "http://pm.alainbarthelemy.com/portrait/img" + ofToString(imgNbr) + ".jpg");
        imgNbr = (int)floor(1+ofRandom(1)*44.99);
        loader.loadFromURL(imgH[loadingHIndex+1], "http://pm.alainbarthelemy.com/portrait/img" + ofToString(imgNbr) + ".jpg");
        
        
        
        loadingHIndex+=2;
        if(loadingHIndex >= IMG_STACK_LENGHT)
            loadingHIndex = 0;
        
        FIRST_LOAD_H = false;
    }else{
        
        imgH[loadingHIndex].clear();
        
        int imgNbr = (int)floor(1+ofRandom(1)*44.99);
        loader.loadFromURL(imgH[loadingHIndex], "http://pm.alainbarthelemy.com/portrait/img" + ofToString(imgNbr) + ".jpg");
        
        
        
        loadingHIndex++;
        if(loadingHIndex >= IMG_STACK_LENGHT)
            loadingHIndex = 0;
        
    }

    
}
void Autoportrait::loadB(){
    
    if(FIRST_LOAD_B){ // in the beginning we load twice
        
        imgB[loadingBIndex].clear();
        imgB[loadingBIndex+1].clear();
        
        int imgNbr = (int)floor(1+ofRandom(1)*44.99);
        loader.loadFromURL(imgB[loadingBIndex], "http://pm.alainbarthelemy.com/portrait/img" + ofToString(imgNbr) + ".jpg");
        imgNbr = (int)floor(1+ofRandom(1)*44.99);
        loader.loadFromURL(imgB[loadingBIndex+1], "http://pm.alainbarthelemy.com/portrait/img" + ofToString(imgNbr) + ".jpg");
        
        loadingBIndex+=2;
        if(loadingBIndex >= IMG_STACK_LENGHT)
            loadingBIndex = 0;
        
        FIRST_LOAD_B = false;
    }else{
        
        imgB[loadingBIndex].clear();
        
        int imgNbr = (int)floor(1+ofRandom(1)*44.99);
        loader.loadFromURL(imgB[loadingBIndex], "http://pm.alainbarthelemy.com/portrait/img" + ofToString(imgNbr) + ".jpg");
        
        //[loadingBIndex].resize(10,10);
        
        loadingBIndex++;
        if(loadingBIndex >= IMG_STACK_LENGHT)
            loadingBIndex = 0;
        
    }

}*/

void Autoportrait::exit() {
    //loader.stopThread();
    ofUnregisterURLNotification(this);

}