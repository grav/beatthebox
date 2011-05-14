//
//  SoundHelper.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 13/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "sndfile.hh"


class SoundHelper{
public:
    static void loadMono(std::string fileName, double *&samples,sf_count_t &numSamples);
};