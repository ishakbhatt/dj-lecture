
/**
 * @file dj.h
 * @author Harsh Jhaveri (hjhaveri@umich.edu)
 * @brief A framework for reading in and processing Spotify song data from CSV files.
 * Once song data is read in, tunable parameters can be utilized to optimize playlist output.
 * This file contains the global variables and function declarations ONLY.
 *
 * Dataset Source: https://www.kaggle.com/cnic92/spotify-past-decades-songs-50s10s
 *
 * @version 1.0
 * @date 2021-11-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef DJ_H
#define DJ_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

/////////////////////////////////////////////
///// GLOBALS - MODIFY THESE VALUES ONLY ////
/////////////////////////////////////////////
//int SIZE_PLAYLIST = 20;

// DESIRED VALUES
int year_sp = 2012;
int bpm_sp = 77;
int nrgy_sp = 47;
int dnce_sp = 62;
int dB_sp = -7;
int live_sp = 3;
int val_sp = 68;
int dur_sp = 220;
int acous_sp = 0;
int spch_sp = 4;
int pop_sp = 75;


/////////////////////////////////////////////
// DO NOT MODIFY ANY OF THE FOLLOWING CODE //
/////////////////////////////////////////////

/**
 * @brief Data structure to represent our dataset in C++
 * Dataset: https://www.kaggle.com/cnic92/spotify-past-decades-songs-50s10s
 *
 */
struct Song
{
    string title;
    string artist;
    string genre;
    int year;               // Release (or Re-Release Year)
    int bpm;                // Beats Per Minute
    int nrgy;               // Energy - The energy of a song - the higher the value, the more energetic the song
    int dnce;               // Danceability - The higher the value, the easier it is to dance to this song
    int dB;                 // Loudness (dB) - The higher the value, the louder the song
    int live;               // Liveness - The higher the value, the more likely the song is a live recording
    int val;                // Valence - the higher the value, the more positive mood for the song.
    int dur;                // Duration of the song (sec)
    int acous;              // Acousticness - The higher the value of the more acoustic the song is
    int spch;               // Spechiness - the higher the value, the more spoken word the song contains
    int pop;                // Popularity - the higher the value, the more popular the song is
    double dj_score;    // dj_score - A custom score used to calculate the "fit" of the song to your playlist
};

/**
 * @brief Function used to read song data into vector
 *
 * @param inFile - input file stream, used to read in Song Data
 * @param songData - vector of all song data
 */
void readFile(istream &inFile, vector<Song> & songData);

/**
 * @brief Function used to calculate dj_score for each Song object.
 * Score is calculated based on a modified Mean Squared Error, thus a lower score
 * is better
 *
 * @param song - Song object to calculate dj_score for
 */
double calcDJScore(const Song &song);

/**
 * @brief Custom comparator used to compare the dj_score of all songs.
 * Will sort the songs in ascending order based on dj_score. If the dj_score
 * is within 0.0005 of another song, then songs are sorted based on artist name.
 *
 * @param rhs - the "right" song
 * @param lhs - the "left" song
 */
bool compareSong(Song rhs, Song lhs);

/**
 * @brief Print function used to print SIZE_PLAYLIST songs to the terminal
 *
 * @param songData - vector of all song data
 * @param out - the output stream where playlist information will be output to
 */
void print_playlist(vector<Song> & sortedSongData, ostream & out);

#endif // DJ_H