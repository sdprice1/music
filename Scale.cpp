/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Scale.cpp
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
#include "StringUtils.hpp"
#include "Scale.h"

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Scale::Scale(const std::string &name, const Note& root, const std::string &intervals) :
	mName(name),
	mRootNote(root),
	mIntervals(StringUtils::toUpper(intervals)),
	mNotes()
{
	mNotes.push_back(mRootNote) ;
	Note note(mRootNote) ;

	for (auto cc : mIntervals)
	{
		if (cc == 'W')
		{
			note.sharp() ;
			note.sharp() ;
		}
		if (cc == 'H')
		{
			note.sharp() ;
		}

		// 'turn' note into flat
		note.sharp() ;
		note.flat() ;

		mNotes.push_back(note) ;
	}

	// repeat
	mNotes.insert(mNotes.end(), mNotes.begin(), mNotes.end()) ;
}

//-------------------------------------------------------------------------------------------------------------
Scale::Scale() :
	mName(),
	mRootNote(),
	mIntervals(),
	mNotes()
{
}

//-------------------------------------------------------------------------------------------------------------
Scale::~Scale()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string Scale::name() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
Note Scale::root() const
{
	return mRootNote ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<Note> Scale::notes() const
{
	return mNotes ;
}

