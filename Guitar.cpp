/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Guitar.cpp
 * \brief     <one-line description of file>
 *
 * \date      3 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Guitar.h"


//=============================================================================================================
// LOCAL
//=============================================================================================================
struct guitarChordsearch {
	guitarChordsearch(unsigned start, unsigned num) :
		startString(start),
		numStrings(num)
	{}

	unsigned startString ;
	unsigned numStrings ;
};


//=============================================================================================================
// PUBLIC
//=============================================================================================================
//#define DEBUG_CHORD_SEARCH

// I can only manage a chord of 4 frets width!
const unsigned CHORD_SPAN(4) ;

//-------------------------------------------------------------------------------------------------------------
Guitar::Guitar() :
	mString_e("e", "E"),
	mString_B("B", "B"),
	mString_G("G", "G"),
	mString_D("D", "D"),
	mString_A("A", "A"),
	mString_E("E", "E")
{
	// ensure we display the whole span
	GuitarChord::setDisplayFretSpan(CHORD_SPAN) ;
}

//-------------------------------------------------------------------------------------------------------------
Guitar::~Guitar()
{
}

//-------------------------------------------------------------------------------------------------------------
std::vector<GuitarChord> Guitar::search(const Chord &chord, unsigned startFret) const
{
	std::vector<GuitarString> strings ;
	strings.push_back(mString_E) ;
	strings.push_back(mString_A) ;
	strings.push_back(mString_D) ;
	strings.push_back(mString_G) ;
	strings.push_back(mString_B) ;
	strings.push_back(mString_e) ;

	std::vector<std::vector<unsigned>> stringFrets ;
	for (auto string=0; string < 6; ++string)
	{
		std::vector<unsigned> frets(strings[string].search(startFret, startFret + CHORD_SPAN - 1, chord.notes())) ;
		stringFrets.push_back(frets) ;

#ifdef DEBUG_CHORD_SEARCH

std::cerr << string << ": " ;
for (auto fret : frets)
	std::cerr << "[" << fret << "] " ;
std::cerr << std::endl ;

#endif
	}



	// need blocks of at least the same number of notes as the chord
	// Any string that has no options is a 'do not play' and I don't want to create guitarChords with muted strings
	unsigned numNotes(chord.notes().size()) ;

	std::vector<guitarChordsearch> searches ;
	int currentStart(-1) ;
	unsigned currentCount(0) ;
	for (unsigned i=0; i < 6; ++i)
	{
		unsigned count(stringFrets[i].size()) ;
		if (count > 0)
		{
			// add to current or start
			if (currentStart == -1)
			{
				currentStart = i ;
				currentCount = 1 ;
			}
			else
			{
				++currentCount ;
			}
		}
		else
		{
			if (currentStart != -1)
			{
				if (currentCount >= numNotes)
				{
					// save
					guitarChordsearch search(currentStart, currentCount) ;
					searches.push_back(search) ;
				}

				currentStart = -1 ;
				currentCount = 0 ;
			}
		}
	}

	if (currentStart != -1)
	{
		if (currentCount >= numNotes)
		{
			// save
			guitarChordsearch search(currentStart, currentCount) ;
			searches.push_back(search) ;
		}
	}


#ifdef DEBUG_CHORD_SEARCH
std::cerr << "SEARCHES" << std::endl ;
for (auto& search : searches)
{
	std::cerr << " * start=" << search.startString << " number=" << search.numStrings << std::endl ;
}
#endif

	// Can now build the guitar guitarChords and see if they are valid
	std::vector<GuitarChord> guitarChords ;
	guitarChords.push_back(GuitarChord(chord)) ; // start with an empty entry
	for (auto& search : searches)
	{
		for (unsigned i=search.startString; i < (search.startString + search.numStrings); ++i)
		{
			unsigned count(stringFrets[i].size()) ;

			// should never happen
			if (count == 0)
				continue ;

			// need to duplicate previous set by the number of options we have on this string
			if (count > 1)
			{
				std::vector<GuitarChord> base(guitarChords) ;
				for (auto copy=0; copy < count; ++copy)
				{
					unsigned fret(stringFrets[i][copy]) ;
					if (copy == 0)
					{
						for (auto& gc : guitarChords)
						{
							gc.addFret(strings[i].name(), fret, strings[i].note(fret)) ;
						}
						continue ;
					}

					std::vector<GuitarChord> newcopy(base) ;
					for (auto& gc : newcopy)
					{
						gc.addFret(strings[i].name(), fret, strings[i].note(fret)) ;
					}
					guitarChords.insert(guitarChords.end(), newcopy.begin(), newcopy.end()) ;
				}
			}
			else
			{
				// just apply this fret to existing entries
				unsigned fret(stringFrets[i][0]) ;
				for (auto& gc : guitarChords)
				{
					gc.addFret(strings[i].name(), fret, strings[i].note(fret)) ;
				}
			}
		}
	}

	// now only report the valid ones
	std::vector<GuitarChord> validGuitarChords ;
	for (auto& gc : guitarChords)
	{
#ifdef DEBUG_CHORD_SEARCH
std::cerr << "Found chord:" << std::endl ;
gc.show() ;
std::cerr << "==" << std::endl ;
#endif

		if (!gc.isValid())
			continue ;

#ifdef DEBUG_CHORD_SEARCH
std::cerr << "VALID" << std::endl ;
#endif

		validGuitarChords.push_back(gc) ;
	}

	return validGuitarChords ;

}
