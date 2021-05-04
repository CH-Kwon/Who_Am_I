//
//  DataPipeline.cpp
//  WhoAmI
//
//  Created by Se-Hyun Kim on 16/12/2017.
//  Copyright © 2017 sehyun.kim. All rights reserved.
//

#include "DataPipeline.hpp"

#include <iostream>
#ifdef _WIN32

#include <filesystem>

#else
#include <dirent.h>
#endif
#include <regex>
#include <string>

#include <Windows.h>
#include <SDL.h>
#include <tchar.h>
//
// Drag and drop (an image or a sound)

#ifdef _WIN32

std::string IMAGE_DIR;

std::string SOUND_DIR;

const std::string IMAGE_DIR_R(".\\Images\\");

const std::string SOUND_DIR_R(".\\Sound\\");
#include <strsafe.h>
#pragma comment(lib, "User32.lib")
#else
const std::string IMAGE_DIR("./Images/");

const std::string SOUND_DIR("./Sound/");
#endif
const std::regex PNG_REGEX("()*.png");
const std::regex SOUND_REGEX("()*.mp3|wav");


std::vector<std::string> init_data_pipeline(const std::string& directory, const std::regex& regular_express)
{

    std::vector<std::string> files;
#ifdef _WIN32
    //namespace fs = std::experimental::filesystem;
    //for (auto & p : fs::directory_iterator("C:\\"))
    //{
    //   
    //    const std::string fname = p.path().filename().generic_string();

    //    if (std::regex_search(fname, regular_express))
    //    {
    //        files.push_back(fname);
    //    }
    //}

    WIN32_FIND_DATA FindFileData;
    TCHAR szDir[MAX_PATH];
    HANDLE hFind;


   StringCchCopy(szDir, MAX_PATH, directory.c_str());
   StringCchCat(szDir, MAX_PATH, TEXT(".\\*"));

//    std::string dir = ".,fsdfs";

    hFind = FindFirstFile(szDir, &FindFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Could not open directory!\n";
        return files;
    }

    do
    {
        std::string&& fname = FindFileData.cFileName;
        if (std::regex_search(fname, regular_express)) {
            files.push_back(fname);
        }

    } while (FindNextFile(hFind, &FindFileData) != 0);

    FindClose(hFind);

#else
    DIR * dir;
    dirent *ent;

    if ((dir = opendir(directory.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (std::regex_search(ent->d_name, regular_express))
            {
                files.push_back(ent->d_name);
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory!");
        std::sort(std::begin(files), std::end(files));
        return files;
    }
#endif

    std::sort(std::begin(files), std::end(files));
    return files;
}

void refresh_data_pipeline(std::vector<std::string>& target, const std::string& directory, const std::regex& regular_express)
{
    namespace fs = std::experimental::filesystem;
    std::vector<std::string> files;
#ifdef _WIN32
    for (auto & p : fs::directory_iterator(directory))
    {

        const std::string fname = p.path().filename().generic_string();

        if (std::regex_search(fname, regular_express))
        {
            if (std::find(std::begin(target), std::end(target), fname) == std::end(target))
            {
                target.push_back(fname);
            }
        }
    }
#else
    DIR * dir;
    dirent *ent;
    
    if ((dir = opendir(directory.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (std::regex_search(ent->d_name, regular_express))
            {
                if (std::find(std::begin(target), std::end(target), ent->d_name) == std::end(target))
                {
                    target.push_back(ent->d_name);
                }
                
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory!");
        return;
    }
#endif
    std::sort(std::begin(target), std::end(target));
}


