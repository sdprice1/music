/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      GuitarChord.cpp
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
#include <iomanip>
#include <algorithm>

#include "GuitarChord.h"

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const std::vector<unsigned> DOTTED_FRETS{1, 3, 5, 7, 9, 12, 15, 17, 19, 21} ;
const int UNUSED_FRET(-1) ;
const std::vector<std::string> STRINGS{"E", "A", "D", "G", "B", "e"} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
unsigned GuitarChord::mDisplayFretSpan(0) ;


//-------------------------------------------------------------------------------------------------------------
GuitarChord::GuitarChord(const Chord &chord) :
	mChord(chord),
	mFrets(),
	mNotes(),
	mMinFret(UNUSED_FRET),
	mMaxFret(UNUSED_FRET)
{
	for (auto string : STRINGS)
	{
		mFrets[string] = UNUSED_FRET ;
		mNotes[string] = Note() ;
	}
}

//-------------------------------------------------------------------------------------------------------------
GuitarChord::~GuitarChord()
{
}

//-------------------------------------------------------------------------------------------------------------
GuitarChord::GuitarChord(const GuitarChord &rhs) :
	mChord(rhs.mChord),
	mFrets(rhs.mFrets),
	mNotes(rhs.mNotes),
	mMinFret(rhs.mMinFret),
	mMaxFret(rhs.mMaxFret)
{
}

//-------------------------------------------------------------------------------------------------------------
bool GuitarChord::isInverted() const
{
	if (mNotes.empty())
		return false ;

	for (auto string : STRINGS)
	{
		// find first used string
		if (mFrets.at(string) == UNUSED_FRET)
			continue ;

		return mNotes.at(string) != mChord.root() ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
void GuitarChord::removeInversion()
{
	if (!isInverted())
		return ;

	// find first string with root note
	for (auto string : STRINGS)
	{
		if (mFrets.at(string) == UNUSED_FRET)
			continue ;

		if (mNotes.at(string) == mChord.root())
			break ;

		// remove note
		mNotes[string] = Note() ;
		mFrets[string] = UNUSED_FRET ;
	}

	// need to update max/min
	updateMaxMin() ;
}


//-------------------------------------------------------------------------------------------------------------
bool GuitarChord::addFret(const std::string &stringName, unsigned fret, const Note &note)
{
	if (mFrets.find(stringName) == mFrets.end())
		return false ;

	mFrets[stringName] = fret ;
	mNotes[stringName] = note ;

	updateMaxMin(fret) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool GuitarChord::isUsed(const std::string &stringName) const
{
	if (mFrets.find(stringName) == mFrets.end())
		return false ;

	return mFrets.at(stringName) >= 0 ;
}

//-------------------------------------------------------------------------------------------------------------
bool GuitarChord::isValid() const
{
	std::vector<Note> notes ;
	for (auto [string, note] : mNotes)
	{
		if (!note.isValid())
			continue ;
		notes.push_back(note) ;
	}
	return mChord.valid(notes) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string GuitarChord::title() const
{
	std::string titleStr = mChord.name() + " (" + mChord.notesStr() + ") [" +
			mChord.equation() + "]" ;

	return titleStr ;
}

//-------------------------------------------------------------------------------------------------------------
void GuitarChord::show(std::ostream &os, bool showTitle) const
{
#if 0

	X     o   o
	===========
1   : : : : o :
	+---------+
	: : o : : :
	+---------+
	: o : : : :
	+---------+

	X     o   o
	+---------+
7   : : : : o :
	+---------+
	: : o : : :
	+---------+
	: o : : : :
	+---------+

#endif

	if (mMinFret < 0)
		return ;

	unsigned startFret(mMinFret) ;
	if (startFret > 0)
		startFret-- ;

	unsigned endFret(mMaxFret) ;
	if (endFret < (startFret + mDisplayFretSpan))
		endFret = startFret + mDisplayFretSpan ;

	if (showTitle)
		os << title() << std::endl ;

	// start
	os << "    " ;
	for (auto string : STRINGS)
	{
		if (mFrets.at(string) == UNUSED_FRET)
			os << "   " ;
		else
			os << std::setw(3) << std::left << mChord.search(mNotes.at(string)).toString() ;
	}
	os << std::endl ;

	for (unsigned fret=startFret; fret <= endFret; ++fret)
	{
		char vert(':') ;
		if (fret == startFret)
			vert = ' ' ;

//		if (fret == (startFret + 1))
//			os << std::setw(2) << fret << "  " ;
//		else
//			os << "    " ;

		// show dotted fret number if not the first displayed fret (which is used to show open
		// strings and not used strings)
		bool dotted(std::find(DOTTED_FRETS.begin(), DOTTED_FRETS.end(), fret) != DOTTED_FRETS.end()) ;
		if ( (fret != startFret) && dotted )
			os  << " " << std::setw(2) << std::right << fret << " " ;
		else
			os << "    " ;


		// do strings
		for (auto string : STRINGS)
		{
			if ( mFrets.at(string) == UNUSED_FRET)
			{
				if (fret == startFret)
					os << 'X' ;
				else
					os << vert ;
			}
			else
			{
				if ((int)fret == mFrets.at(string))
					os << 'o' ;
				else
					os << vert ;
			}

			os << "  " ;

		}
		os << std::endl ;


		// end of this fret
		if (fret == 0)
		{
			os << "    ================  " << std::endl ;
		}
		else
		{
			os << "    +--------------+  " << std::endl ;
		}
	}

	// show which part of the equation eachj of the notes is
	os << "    " ;
	for (auto string : STRINGS)
	{
		if (mFrets.at(string) == UNUSED_FRET)
			os << "   " ;
		else
			os << std::setw(3) << std::left << mChord.equationNote(mNotes.at(string)) ;
	}
	os << std::endl ;

}

//-------------------------------------------------------------------------------------------------------------
std::vector<int> GuitarChord::frets() const
{
	std::vector<int> list ;

	for (auto string : STRINGS)
	{
		list.push_back(mFrets.at(string)) ;
	}
	return list ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<Note> GuitarChord::notes() const
{
	std::vector<Note> list ;

	for (auto string : STRINGS)
	{
		list.push_back(mNotes.at(string)) ;
	}
	return list ;
}



//-------------------------------------------------------------------------------------------------------------
Chord GuitarChord::chord() const
{
	return mChord ;
}


//-------------------------------------------------------------------------------------------------------------
bool GuitarChord::operator ==(const GuitarChord &rhs) const
{

//std::cerr << "-------------------------------" << std::endl ;
//std::cerr << "GuitarChord ==" << std::endl ;
//
//std::cerr << "THIS" << std::endl ;
//show() ;
//std::cerr << "RHS" << std::endl ;
//rhs.show() ;


	if (mChord != rhs.mChord)
	{
//		std::cerr << "FALSE" << std::endl ;
		return false ;
	}

	if (mMinFret != rhs.mMinFret)
	{
//		std::cerr << "FALSE" << std::endl ;
		return false ;
	}

	if (mMaxFret != rhs.mMaxFret)
	{
//		std::cerr << "FALSE" << std::endl ;
		return false ;
	}

	for (auto string : STRINGS)
	{
		if (mFrets.at(string) != rhs.mFrets.at(string))
		{
//			std::cerr << "FALSE" << std::endl ;
			return false ;
		}

		if (mNotes.at(string) != rhs.mNotes.at(string))
		{
//			std::cerr << "FALSE" << std::endl ;
			return false ;
		}
	}

//	std::cerr << "TRUE" << std::endl ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool GuitarChord::operator !=(const GuitarChord &rhs) const
{
	return !operator==(rhs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool GuitarChord::operator <(const GuitarChord &rhs) const
{
//	std::cerr << "-------------------------------" << std::endl ;
//	std::cerr << "GuitarChord <" << std::endl ;
//
//	std::cerr << "THIS" << std::endl ;
//	show() ;
//	std::cerr << "RHS" << std::endl ;
//	rhs.show() ;

	if (mMinFret < rhs.mMinFret)
	{
//		std::cerr << "TRUE" << std::endl ;
		return true ;
	}

	if (mMinFret > rhs.mMinFret)
	{
//		std::cerr << "FALSE" << std::endl ;
		return false ;
	}

	if (mMaxFret < rhs.mMaxFret)
	{
//		std::cerr << "TRUE" << std::endl ;
		return true ;
	}

	if (mMaxFret > rhs.mMaxFret)
	{
//		std::cerr << "FALSE" << std::endl ;
		return false ;
	}

	for (auto string : STRINGS)
	{
		if (mFrets.at(string) < rhs.mFrets.at(string))
		{
//			std::cerr << "TRUE" << std::endl ;
			return true ;

		}
	}

//	std::cerr << "FALSE" << std::endl ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<GuitarChord> GuitarChord::triads() const
{
	std::vector<GuitarChord> triadChords ;
	unsigned chordSize(mChord.notes().size()) ;

	// starting at each string, create a chord using the same number of strings as the number
	// of notes in the chord. If this is then a valid chord (i.e. has all the chord notes)
	// then this will contain each note of the chord once
	for (unsigned stringnum=0; stringnum < (6 - chordSize); ++stringnum)
	{
		GuitarChord triad(*this) ;

		// clear strings before this one
		for (unsigned i=0; i < stringnum; ++i)
		{
			auto string(STRINGS.at(i)) ;
			triad.mFrets[string] = UNUSED_FRET ;
			triad.mNotes[string] = Note() ;
		}

		// clear strings after the last note
		for (unsigned i=(stringnum+chordSize); i < 6; ++i)
		{
			auto string(STRINGS.at(i)) ;
			triad.mFrets[string] = UNUSED_FRET ;
			triad.mNotes[string] = Note() ;
		}

		if (!triad.isValid())
			continue ;

		// skip if we've just found the same chord!
		if (triad == *this)
			continue ;

		triad.updateMaxMin() ;
		triadChords.push_back(triad) ;
	}

	return triadChords ;
}

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void GuitarChord::setDisplayFretSpan(unsigned span)
{
	mDisplayFretSpan = span ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void GuitarChord::updateMaxMin()
{
	mMinFret = UNUSED_FRET ;
	mMaxFret = UNUSED_FRET ;
	for (auto string : STRINGS)
	{
		if (mFrets.at(string) == UNUSED_FRET)
			continue ;

		updateMaxMin(mFrets.at(string)) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void GuitarChord::updateMaxMin(unsigned fret)
{
	if (mMinFret == UNUSED_FRET)
	{
		mMinFret = fret ;
	}
	else
	{
		if (mMinFret > (int)fret)
			mMinFret = fret ;
	}

	if (mMaxFret == UNUSED_FRET)
	{
		mMaxFret = fret ;
	}
	else
	{
		if (mMaxFret < (int)fret)
			mMaxFret = fret ;
	}
}

