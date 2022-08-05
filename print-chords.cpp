#include <iostream>
#include <set>

#include "Note.h"
#include "Scale.h"
#include "MajorScale.h"
#include "MinorScale.h"
#include "Chord.h"
#include "MajorChord.h"
#include "MinorChord.h"
#include "Sus2Chord.h"
#include "GuitarString.h"
#include "GuitarChord.h"
#include "Guitar.h"

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cerr << "Error: Must specify a note" << std::endl ;
		return -1 ;
	}
	std::string noteName(argv[1]) ;

	Sus2Chord chord(noteName) ;

	Guitar guitar ;

	std::set<GuitarChord> sortedChords ;
	for (unsigned fret=0; fret < 12; fret++)
	{
		std::vector<GuitarChord> chords(guitar.search(chord, fret)) ;
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
