//
//  DataPipeline.hpp
//  WhoAmI
//
//  Created by Se-Hyun Kim on 16/12/2017.
//  Copyright © 2017 sehyun.kim. All rights reserved.
//

#ifndef DataPipeline_hpp
#define DataPipeline_hpp
#include <string>
#include <regex>

extern std::string IMAGE_DIR;
extern std::string SOUND_DIR;
extern const std::regex PNG_REGEX;

extern const std::regex SOUND_REGEX;
extern const std::string IMAGE_DIR_R;
extern const std::string SOUND_DIR_R;

std::vector<std::string> init_data_pipeline(const std::string& directory, const std::regex& regular_express);

void refresh_data_pipeline(std::vector<std::string>& target, const std::string& directory, const std::regex& regular_express);

#endif /* DataPipeline_hpp */
