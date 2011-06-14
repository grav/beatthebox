//
//  SoundHelper.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 13/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <vector>

class SoundHelper{
public:
    static void loadMono(std::string fileName, std::vector<double> *&samples);
    static void saveMono(std::string fileName, std::vector<double> *samples);
    static void debug(std::vector<double> *samples);
};