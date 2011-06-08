//
//  constants.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#define PATH_PREFIX "/Users/grav/repositories/uni/feature/"

#define LINEAR_MODEL_PATH "/Users/grav/Desktop/linearmodel.data"
#define FLAT_FILE_PATH "/Users/grav/Desktop/flat.data"

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