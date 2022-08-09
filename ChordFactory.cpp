/*!
 * Copyright (c) 2022 Steve Price.
 * All Rights Reserved
 *
 * \file      ChordFactory.cpp
 * \brief     <one-line description of file>
 *
 * \date      8 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <map>

#include "StringUtils.hpp"
#include "MajorScale.h"
#include "Chord.h"

//=============================================================================================================
// LOCAL
//=============================================================================================================
struct ChordFactoryEntry {

	ChordFactoryEntry(const std::string& _suffix, const std::string& _equation) :
		suffix(_suffix), equation(_equation)
	{}

	std::string suffix ;
	std::string equation ;
};

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
std::map<std::string, ChordFactoryEntry> CHORDS{

	{ "major",		ChordFactoryEntry("", 		"1-3-5") },
	{ "minor",		ChordFactoryEntry("m", 		"1-b3-5") },
	{ "dim",		ChordFactoryEntry("dim", 	"1-b3-b5") },
	{ "add9",		ChordFactoryEntry("add9", 	"1-3-5-9") },
	{ "sus2",		ChordFactoryEntry("sus2", 	"1-2-5") },
	{ "sus4",		ChordFactoryEntry("sus4", 	"1-4-5") },
	{ "5",			ChordFactoryEntry("5", 		"1-5") },
	{ "7",			ChordFactoryEntry("7", 		"1-3-5-b7") },
	{ "aug",		ChordFactoryEntry("aug", 	"1-3-#5") },
	{ "7#5",		ChordFactoryEntry("7#5", 	"1-3-#5-b7") },
	{ "7#9",		ChordFactoryEntry("7#9",	"1-3-5-b7-#9") },
	{ "dim",		ChordFactoryEntry("dim", 	"1-b3-b5") },
	{ "dim7",		ChordFactoryEntry("dim7", 	"1-b3-b5-bb7") },
	{ "minor7",		ChordFactoryEntry("m7", 	"1-b3-5-b7") },
	{ "minor7b5",	ChordFactoryEntry("m7b5", 	"1-b3-b5-b7") },
	{ "major7",		ChordFactoryEntry("maj7", 	"1-3-5-7") },
	{ "minor6",		ChordFactoryEntry("m6", 	"1-b3-5-6") },
	{ "6",			ChordFactoryEntry("6", 		"1-3-5-6") },
	{ "minor7b5",	ChordFactoryEntry("m7b5", 	"1-b3-b5-b7") },
	{ "9",			ChordFactoryEntry("9", 		"1-3-5-b7-9") },
	{ "minor9",		ChordFactoryEntry("m9", 	"1-b3-5-b7-9") },
	{ "major9",		ChordFactoryEntry("maj9", 	"1-3-5-7-9") },
	{ "minor-add9", ChordFactoryEntry("m(add9)","1-b3-5-9") },
	{ "11",			ChordFactoryEntry("11", 	"1-5-b7-9-11") },
	{ "minor11",	ChordFactoryEntry("m11", 	"1-b3-5-b7-9-11") },
	{ "7#11",		ChordFactoryEntry("7#11", 	"1-3-5-b7-9-#11") },
	{ "major7#11",	ChordFactoryEntry("maj7#11","1-3-5-7-9-#11") },
	{ "13",			ChordFactoryEntry("13", 	"1-3-5-b7-9-13") },
	{ "major13",	ChordFactoryEntry("maj13", 	"1-3-5-7-9-13") },
	{ "minor13",	ChordFactoryEntry("m13", 	"1-b3-5-b7-9-11-13") },

} ;


//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<Chord> Chord::factory(const std::string chordType, const std::string& root)
{
	MajorScale scale(root) ;
	Note note(root) ;

	std::string type(StringUtils::toLower(chordType)) ;
	if (CHORDS.find(type) == CHORDS.end())
		return std::shared_ptr<Chord>() ;

	std::string name(note.toString() + CHORDS.at(type).suffix) ;
	return std::make_shared<Chord>(name, scale, CHORDS.at(type).equation) ;
}

