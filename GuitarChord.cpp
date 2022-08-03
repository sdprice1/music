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
#include "GuitarChord.h"

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
GuitarChord::GuitarChord(const Chord &chord) :
	mChord(chord),
	mFrets(),
	mNotes(),
	mMinFret(-1),
	mMaxFret(-1)
{
	for (auto string : std::vector<std::string>{"E", "A", "D", "G", "B", "e"})
	{
		mFrets[string] = -1 ;
		mNotes[string] = Note() ;
	}
}

//-------------------------------------------------------------------------------------------------------------
GuitarChord::~GuitarChord()
{
}

//-------------------------------------------------------------------------------------------------------------
bool GuitarChord::addFret(const std::string &stringName, unsigned fret, const Note &note)
{
	if (mFrets.find(stringName) == mFrets.end())
		return false ;

	mFrets[stringName] = fret ;
	mNotes[stringName] = note ;

	if (mMinFret == -1)
	{
		mMinFret = fret ;
	}
	else
	{
		if (mMinFret > fret)
			mMinFret = fret ;
	}

	if (mMaxFret == -1)
	{
		mMaxFret = fret ;
	}
	else
	{
		if (mMaxFret < fret)
			mMaxFret = fret ;
	}


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
		notes.push_back(note) ;
	return mChord.valid(notes) ;
}

//-------------------------------------------------------------------------------------------------------------
void GuitarChord::show(std::ostream &os) const
{
//	for (auto string : std::vector<std::string>{"e", "B", "G", "D", "A", "E"})
//	{
//		os << string << ": " ;
//		if (mFrets.at(string) < 0)
//		{
//			os << "x" ;
//		}
//		else
//		{
//			os << "[" << mFrets.at(string) << "] " ;
//			auto note(mChord.search(mNotes.at(string))) ;
//			if (note == mChord.root())
//				os << "*" ;
//			os << note.toString() ;
//		}
//		os << std::endl ;
//	}

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

	// start
	os << "    " ;
	for (auto string : std::vector<std::string>{"E", "A", "D", "G", "B", "e"})
	{
		if (mFrets.at(string) == -1)
			os << "   " ;
		else
			os << std::setw(3) << std::left << mNotes.at(string).toString() ;
	}
	os << std::endl ;

	if (startFret != 0)
	{
		os << "    +--------------+" << std::endl ;
	}

	for (unsigned fret=startFret; fret <= mMaxFret; ++fret)
	{
		char sep(':') ;
		if (fret == startFret)
			sep = ' ' ;

		// do strings
		if (fret == (startFret + 1))
			os << std::setw(2) << fret << "  " ;
		else
			os << "    " ;

		for (auto string : std::vector<std::string>{"E", "A", "D", "G", "B", "e"})
		{
			if ( mFrets.at(string) == -1)
			{
				if (fret == startFret)
					os << 'X' ;
				else
					os << sep ;
			}
			else
			{
				if (fret == mFrets.at(string))
					os << 'o' ;
				else
					os << sep ;
			}

			os << "  " ;

		}
		os << std::endl ;


		// end of this fret
		if (fret == 0)
		{
			os << "    ================" << std::endl ;
		}
		else
		{
			os << "    +--------------+" << std::endl ;
		}
	}

}


