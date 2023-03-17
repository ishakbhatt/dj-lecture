/**
 * @file dj.h
 * @author Harsh Jhaveri (hjhaveri@umich.edu)
 * @brief A framework for reading in and processing Spotify song data from CSV files.
 * Once song data is read in, tunable parameters can be utilized to create and optimize playlist output.
 * This file contains the implementation of all necessary C++ code. Function documentation
 * can be found in dj.h.
 *
 * Dataset Source: https://www.kaggle.com/cnic92/spotify-past-decades-songs-50s10s
 *
 * @version 1.0
 * @date 2021-11-15
 *
 * @copyright Copyright (c) 2021
 *
 */

// Imports
#include "dj.h"

using namespace std;

void readFile(istream &inFile, vector<Song> & songData)
{
    // Create necessary variables
    string line;
    Song song;
    string val;
    string id;

    // Read in header line
    getline(inFile, line);

    // Read in all other lines which include song data
    while(getline(inFile, line))
    {
        //Create stringstream to parse line
        stringstream songLine(line);

        // Read in each attribute one at a time
        getline(songLine, id, ','); // song ID - We don't care about this
        getline(songLine, song.title, ',');
        getline(songLine, song.artist, ',');
        getline(songLine, song.genre, ',');

        getline(songLine, val, ','); // year
        song.year = stoi(val);

        getline(songLine, val, ','); // bpm
        song.bpm = stoi(val);

        getline(songLine, val, ','); // nrgy
        song.nrgy = stoi(val);

        getline(songLine, val, ','); // dnce
        song.dnce = stoi(val);

        getline(songLine, val, ','); // db
        song.dB = stoi(val);

        getline(songLine, val, ','); // live
        song.live = stoi(val);

        getline(songLine, val, ','); // val
        song.val = stoi(val);

        getline(songLine, val, ','); // dur
        song.dur = stoi(val);

        getline(songLine, val, ','); // acous
        song.acous = stoi(val);

        getline(songLine, val, ','); // spch
        song.spch = stoi(val);

        getline(songLine, val); // pop
        song.pop = stoi(val);

        // Calculate DJ Score
        song.dj_score = calcDJScore(song);

        // Add song to songData vector
        songData.push_back(song);
    }
}

double calcDJScore(const Song &song)
{
    // TODO: Create base score variable

    // TODO: Update score

    // Return score. You will need to update the following line!
    return 0.0;
}

bool compareSong(Song rhs, Song lhs)
{
    // First sort by minimizing the DJ score
    if (abs(rhs.dj_score-lhs.dj_score) > 0.0005)
    {
        return rhs.dj_score < lhs.dj_score;
    }
    // If ties exist, alphabetize by the artist's name
    else
    {
        return rhs.artist < lhs.artist;
    }
}

void print_playlist(vector<Song> & sortedSongData, ostream & out)
{
    out << "Playlist created using data from " << sortedSongData.size() << " songs!" << endl;
    for(int i = 0; i < SIZE_PLAYLIST; i++)
    {
        out << i+1  << " - "
             << " DJ Score: " << sortedSongData[i].dj_score << endl
             << "\t\t" << sortedSongData[i].title // The \t character is an escape sequence for a tab!
             << " by " << sortedSongData[i].artist
             << " from " << sortedSongData[i].year << endl;
    }
}

int main()
{
    // Create vector of songs
    vector<Song> songData;

    /**
     * Create input file streams.
     * Create as many as you want, one per each file.
     * An example is completed for you.
     */
    ifstream in1950("1950.csv");

    /**
     * Read data from each file stream. You will need to call
     * the readFile() function once for each filestream.
     * 
     * Don't forget to close the filestream once you are done!
     */
    readFile(in1950, songData);
    in1950.close();

    // Sort your vector!
    sort(songData.begin(), songData.end(), compareSong);


    // TODO: Create an output stream

    // TODO: Print out your developed playlist! Update and uncomment the following line
    // print_playlist(songData, TODO);

    // TODO: Don't forget to close your output filestream!

    return 0;
}