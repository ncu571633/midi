#ifndef __MIDI_HPP_
#define __MIDI_HPP_

#include <vector>
#include <string>

//#define NOTEVELOCITY 0x50	//notes velocity

//parse midi in verbose mode: print all the information during parsing 
//#define parseverbose 0 

typedef unsigned short WORD; //length: 2
typedef unsigned long DWORD; //length: 4

/********************************************/
/*******Midi Structure	*********************/
/********************************************/
//
//	MidiFile
//		HeadChunk
//		TrackChunk
//			MetaEvent
//  			MetaEventNode
//			MidiEvent
//  			MidiEventNode

typedef struct MetaEvent
{
	int	SequenceNumber;	//00
    std::string TextEvent;	//01
    string::string CopyRight;	//02
	string::string TrackName;	//03
	string::string InstrumentName;//04
	string::string Lyric;		//05
	string::string Marker;		//06
	string::string CuePoint;		//07
	int	tempo;			//51: microseconds/quarter note
    //51: microseconds/quarter note(unit: ms)
    //duration time per quarter note
    //convert s to ms in setTempo function in writeMetaEvent.c
    //0.5*10^6 ms, 0.5s, 0x7a120
	int	hour;			//54: SMPTE
	int	minute;
	int	second;
	int	frame;
	int	subframe;
	int	numer;			//58
	int	denom;			//key: 4/4, C major
	int	metro;
	int nds;
	int	sf;				//59: 	sharps/ flats
	int mi;				//		major/ minor
}MetaEvent;

typedef struct MetaEventNode
{
	int type;
	int	len;	//length of byte
	char *cContent;
	int iContent1; 
	int iContent2; 
	int iContent3; 
	int iContent4; 
}MetaEventNode;

typedef struct MidiEventNode
{
	int	deltaTime;
	int	MidiType;
	int	nn;
	int	cc;
}MidiEventNode;

typedef struct HeaderChunk
{
        std::string chunkID;
        DWORD   chunkSize;	//length: 6
        DWORD   format;		//format: 0, 1, 2
        DWORD   tracksNumber;
        DWORD	deltaTimeTicks;
}HeaderChunk;

typedef struct TrackChunk
{
        string chunkID;
        DWORD	chunkSize;
        //	int	index;

        MetaEvent metaEvent;

        //Midi event
        // int	noteVelocity;		    //velocity of pressing note, normally it is the volume of the note
        // int	channelNumber;
        std::vector<MidiEventNode> MidiEvents;
};

class MidiFile
{
    private:
        HeaderChunk headerChunk;      	        //header chunk
        std::vector<TrackChunk> trackChunks;	//track chunk list

        void importHeaderChunk(std::oftream midifp);
    public:
        void importMidiFile(string file);
        void exportMidiFile(string file);
};

#endif
