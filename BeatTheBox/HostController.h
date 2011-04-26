//
//  HostController.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

class IHostController{
public: 
    virtual ~IHostController(){}
    virtual void makeOnset() = 0;
    virtual void restartLoop() = 0;
};

class HostControllerMock : public IHostController {
public:
    virtual void makeOnset(){}
    virtual void restartLoop(){}
    
};
