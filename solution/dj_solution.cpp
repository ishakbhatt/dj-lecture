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
    // Create base score variable
    double dj_score = 0;

    // Update score
    dj_score += pow(abs(year_sp - song.year), 2);
    dj_score += pow(abs(bpm_sp - song.bpm), 2);
    dj_score += pow(abs(nrgy_sp - song.nrgy), 2);
    dj_score += pow(abs(dnce_sp - song.dnce), 2);
    dj_score += pow(abs(dB_sp - song.dB), 2);
    dj_score += pow(abs(live_sp - song.live), 2);
    dj_score += pow(abs(val_sp - song.val), 2);
    dj_score += pow(abs(dur_sp - song.dur), 2);
    dj_score += pow(abs(acous_sp - song.acous), 2);
    dj_score += pow(abs(spch_sp - song.spch), 2);
    dj_score += pow(abs(pop_sp - song.pop), 2);
    
    // Return score
    return sqrt(dj_score);
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
    for(int i = 0; i < sortedSongData.size(); i++)
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
    /*
     * Create input file streams.
     */
    ifstream in1990("1990.csv");
    ifstream in2000("2000.csv");
    ifstream in2010("2010.csv");

    /**
     * Read data from each file stream. You will need to call
     * the readFile() function once for each filestream
     */
    readFile(in1990, songData);
    in1990.close();
    readFile(in2000, songData);
    in2000.close();
    readFile(in2010, songData);
    in2010.close();

    // Sort your vector!
    sort(songData.begin(), songData.end(), compareSong);

    // Print out your developed playlist!
    ofstream outFile("playlist.txt");
    print_playlist(songData, outFile);
    outFile.close();

    return 0;
}