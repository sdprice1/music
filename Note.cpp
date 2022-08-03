/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Note.cpp
 * \brief     <one-line description of file>
 *
 * \date      2 Aug 2022
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
#include "Note.h"


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::map<Note::NoteVal, std::string> NOTES_SHARP{
	{ Note::C,		"C"  },
	{ Note::Csharp,	"C#" },
	{ Note::D,		"D" },
	{ Note::Dsharp,	"D#" },
	{ Note::E,		"E" },
	{ Note::F,		"F" },
	{ Note::Fsharp,	"F#" },
	{ Note::G,		"G" },
	{ Note::Gsharp,	"G#" },
	{ Note::A,		"A" },
	{ Note::Asharp,	"A#" },
	{ Note::B,		"B" },
	{ Note::NO_NOTE,"" },
} ;

const std::map<Note::NoteVal, std::string> NOTES_FLAT{
	{ Note::C,		"C"  },
	{ Note::Dflat,	"Db" },
	{ Note::D,		"D" },
	{ Note::Eflat,	"Eb" },
	{ Note::E,		"E" },
	{ Note::F,		"F" },
	{ Note::Gflat,	"Gb" },
	{ Note::G,		"G" },
	{ Note::Aflat,	"Ab" },
	{ Note::A,		"A" },
	{ Note::Bflat,	"Bb" },
	{ Note::B,		"B" },
	{ Note::NO_NOTE,"" },
} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Note::Note() :
	Note(NO_NOTE)
{
}

//-------------------------------------------------------------------------------------------------------------
Note::Note(NoteVal val) :
	mFlattening(false),
	mVal(val)
{
}

//-------------------------------------------------------------------------------------------------------------
Note::Note(const Note &rhs) :
	mFlattening(rhs.mFlattening),
	mVal(rhs.mVal)
{
}

//-------------------------------------------------------------------------------------------------------------
Note::Note(const std::string &val) :
	Note()
{
	if (val.empty())
		return ;

	std::string lcval(StringUtils::toLower(val)) ;
	for (auto& [note, name] : NOTES_SHARP)
	{
		if (lcval == StringUtils::toLower(name))
		{
			mVal = note ;
			return ;
		}
	}
	for (auto& [note, name] : NOTES_FLAT)
	{
		if (lcval == StringUtils::toLower(name))
		{
			mVal = note ;
			mFlattening = true ;
			return ;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
Note::~Note()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string Note::toString() const
{
	const std::map<Note::NoteVal, std::string>* map_ptr(&NOTES_SHARP) ;
	if (mFlattening)
		map_ptr = &NOTES_FLAT ;

	return (*map_ptr).at(mVal) ;
}

//-------------------------------------------------------------------------------------------------------------
void Note::flat()
{
	if (mVal == NO_NOTE)
		return ;

	unsigned ival((unsigned)mVal) ;
	if ( ival == 0)
		ival = 11 ;
	else
		--ival ;

	mVal = static_cast<NoteVal>(ival) ;
	mFlattening = true ;
}

//-------------------------------------------------------------------------------------------------------------
void Note::sharp()
{
	if (mVal == NO_NOTE)
		return ;

	unsigned ival((unsigned)mVal) ;
	ival = (ival + 1) % 12 ;
	mVal = static_cast<NoteVal>(ival) ;
	mFlattening = false ;
}

//-------------------------------------------------------------------------------------------------------------
bool Note::operator ==(const Note &rhs) const
{
	if (mVal == NO_NOTE)
		return false ;
	if (rhs.mVal == NO_NOTE)
		return false ;

	return mVal == rhs.mVal ;
}

//-------------------------------------------------------------------------------------------------------------
bool Note::operator !=(const Note &rhs) const
{
	return !operator==(rhs.mVal) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Note::operator <(const Note &rhs) const
{
	if (mVal == NO_NOTE)
		return false ;
	if (rhs.mVal == NO_NOTE)
		return false ;

	return mVal < rhs.mVal ;
}
