/**
 * @file playlist_generator.cpp
 * @authors Isha Bhatt (ibhatt), Mary Silvio (msilvio), Harsh Jhaveri (hjhaveri)
 * @brief A framework for reading in and processing Spotify song data from CSV files.
 * Once song data is read in, tunable parameters can be utilized to create and optimize playlist output.
 * This file contains the implementation of all necessary C++ code and function docstrings.
 *
 * Dataset Source: https://www.kaggle.com/cnic92/spotify-past-decades-songs-50s10s
 *
 * @version 2.0
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023
 *
 */

// Libraries to include
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

// DEFINITIONS

// Setpoints to compare songs to
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

/**
 * @brief Song structure to represent our song attributes in C++
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

// HELPER FUNCTION DEFINITIONS
void readFile(istream &inFile, vector<Song> & songData);
double calcDJScore(const Song &song);
bool compareSong(Song rhs, Song lhs);
void print_playlist(vector<Song> & sortedSongData, ostream & out);
bool setInputSong(istream &inFile, string query_title);

// HELPER FUNCTIONS
void readFile(istream &inFile, vector<Song> & songData)
{
/**
 * @brief Function used to read song data into vector
 *
 * @param inFile - input file stream, used to read in Song Data
 * @param songData - vector of all song data
 */
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
        // Create stringstream to parse line
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
/**
 * @brief Function used to calculate dj_score for each Song object.
 * Score is calculated based on a modified Mean Squared Error, thus a lower score
 * is better
 *
 * @param song - Song object to calculate dj_score for
 */
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
/**
 * @brief Custom comparator used to compare the dj_score of all songs.
 * Will sort the songs in ascending order based on dj_score. If the dj_score
 * is within 0.0005 of another song, then songs are sorted based on artist name.
 *
 * @param rhs - the "right" song
 * @param lhs - the "left" song
 */
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
/**
 * @brief Print function used to print songs to the terminal
 *
 * @param songData - vector of all song data
 * @param out - the output stream where playlist information will be output to
 */
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

bool setInputSong(istream &inFile, string query_title)
{
/**
 * @brief Modifies setpoints based on a song title
 *
 * @param inFile - input file stream, used to read in Song Data
 * @param query_title - input title used to define setpoint values
 */

    // bool to return whether query song found or not
    bool song_found = false;

    // necessary and temporary variables
    string line;
    string id;
    string title;
    string genre;
    string artist;
    string val; 

    // get header file
    getline(inFile, line);

    while(getline(inFile, line)){
        // Create stringstream to parse line
        stringstream songLine(line);

        // song ID - We don't care about this
        getline(songLine, id, ','); 

        // title - compary query title against this
        getline(songLine, title, ',');

        // we don't care about artist & genre
        getline(songLine, artist, ',');
        getline(songLine, genre, ',');

        getline(songLine, val, ','); // year
        year_sp = stoi(val);

        getline(songLine, val, ','); // bpm
        bpm_sp = stoi(val);

        getline(songLine, val, ','); // nrgy
        nrgy_sp = stoi(val);

        getline(songLine, val, ','); // dnce
        dnce_sp = stoi(val);

        getline(songLine, val, ','); // db
        dB_sp = stoi(val);

        getline(songLine, val, ','); // live
        live_sp = stoi(val);

        getline(songLine, val, ','); // val
        val_sp = stoi(val);

        getline(songLine, val, ','); // dur
        dur_sp = stoi(val);

        getline(songLine, val, ','); // acous
        acous_sp = stoi(val);

        getline(songLine, val, ','); // spch
        spch_sp = stoi(val);

        getline(songLine, val); // pop
        pop_sp = stoi(val);

        if(title == query_title){ // set setpoints based on query title
            // song title found
            song_found = true;

            // print song title found
            cout << "Modifying setpoints to user's input song..." << endl;
            
            // finished searching, leave loop
            break;
        }
    }

    return song_found;
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
     * Query user for song title to define song attribute setpoints.
     * Exit with message + non-zero return value if song title not found.
     */
    string query_title;
    cout << "Enter a song title: ";
    getline(cin, query_title);
    if(!setInputSong(in1990, query_title) && !setInputSong(in2000, query_title) && !setInputSong(in2010, query_title)){
        cout << "Song title not found. Please enter a valid song title." << endl;
        return 1;
    }

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
    cout << "Creating playlist..." << endl;
    ofstream outFile("playlist.txt");
    print_playlist(songData, outFile);
    outFile.close();

    return 0;
}
