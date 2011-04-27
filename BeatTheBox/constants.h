//
//  constants.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

enum InstrumentClass{
    BD = 2,
    SD = 3,
    HH = 4,
    NN = -1
};

enum State{
    HALT,RECORD,PLAYBACK
};

enum Classification{
    MOCK = 0, NEAREST_NEIGHBOUR = 1, LINEAR = 2
};