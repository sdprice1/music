#include <iostream>
#include <set>

#include "Note.h"
#include "Scale.h"
#include "MajorScale.h"
#include "MinorScale.h"
#include "Chord.h"
#include "GuitarString.h"
#include "GuitarChord.h"
#include "Guitar.h"

#include "MajorChord.h"
#include "MinorChord.h"
#include "Sus2Chord.h"
#include "Sus4Chord.h"
#include "Add9Chord.h"

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cerr << "Error: Must specify a note" << std::endl ;
		return -1 ;
	}
	std::string noteName(argv[1]) ;

	std::string type("Major") ;
	if (argc >= 3)
	{
		type = argv[2] ;
	}

	unsigned endFret(0) ;

//	Sus2Chord chord(noteName) ;
//	Sus4Chord chord(noteName) ;
//	Add9Chord chord(noteName) ;
//	Add9Chord chord(noteName) ;

	std::shared_ptr<Chord> chord(Chord::factory(type, noteName)) ;
	if (!chord)
	{
		std::cerr << "ERROR: Unable to create " << type << " chord" << std::endl ;
		return -1 ;
	}

	Guitar guitar ;

	std::set<GuitarChord> sortedChords ;
	for (unsigned fret=0; fret <= endFret; fret++)
	{
		std::vector<GuitarChord> chords(guitar.search(*chord, fret)) ;
		for (auto gc : chords)
		{
			sortedChords.insert(gc) ;
		}
	}

	for (auto gc : sortedChords)
	{
		gc.show() ;
		std::cerr << std::endl ;
	}

}
