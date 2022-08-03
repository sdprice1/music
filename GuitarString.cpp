/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      GuitarString.cpp
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

#include "GuitarString.h"


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
GuitarString::GuitarString(const std::string& name, const Note &open) :
	mName(name),
	mOpen(open),
	mNotes()
{
	Note note(mOpen) ;
	for (unsigned fret=0; fret < 24; ++fret)
	{
		mNotes.push_back(note) ;
		note.sharp() ;
	}
}

//-------------------------------------------------------------------------------------------------------------
GuitarString::GuitarString(const std::string& name, const std::string &open) :
	GuitarString(name, Note(open))
{
}


//-------------------------------------------------------------------------------------------------------------
GuitarString::~GuitarString()
{
}

//-------------------------------------------------------------------------------------------------------------
Note GuitarString::note(unsigned fret) const
{
	if (fret >= mNotes.size())
		return Note("C") ;

	return mNotes.at(fret) ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<unsigned> GuitarString::search(unsigned startFret,
		unsigned endFret, const std::vector<Note> notes) const
{
	if (startFret > endFret)
		return std::vector<unsigned>() ;

	if (startFret >= mNotes.size())
		return std::vector<unsigned>() ;

	if (endFret >= mNotes.size())
		return std::vector<unsigned>() ;

	std::vector<unsigned> frets ;
	for (unsigned fret=startFret; fret <= endFret; ++fret)
	{
		for (auto& note : notes)
		{
			if (mNotes.at(fret) != note)
				continue ;

			frets.push_back(fret) ;
		}
	}

	return frets ;
}

//-------------------------------------------------------------------------------------------------------------
std::string GuitarString::name() const
{
	return mName ;
}
