/*!
 * Copyright (c) 2022 Steve Price.
 * All Rights Reserved
 *
 * \file      TextPublisher.cpp
 * \brief     <one-line description of file>
 *
 * \date      15 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>

#include "StringUtils.hpp"
#include "TextPublisher.h"

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TextPublisher::TextPublisher() :
	Publisher(),
	mTitle(),
	mLines(),
	mChordCount(0),
	mChordLineCount(0)
{
}

//-------------------------------------------------------------------------------------------------------------
TextPublisher::~TextPublisher()
{
}

//-------------------------------------------------------------------------------------------------------------
bool TextPublisher::addChord(const GuitarChord &chord)
{
	if (mTitle.empty())
	{
		mTitle = chord.title() ;
		addOutput(mTitle + "\n\n") ;
	}

	std::stringstream ss ;
	chord.show(ss, false) ;

	std::vector<std::string> chordLines(StringUtils::splitStr(ss.str(), '\n')) ;
	++mChordCount ;
	if (mChordCount == 1)
	{
		mLines = chordLines ;
		return true ;
	}

	for (unsigned i=0; (i < chordLines.size()) && (i < mLines.size()); ++i)
		mLines[i] += chordLines[i] ;

	if (mChordCount >= 4)
	{
		for (auto& line : mLines)
			addOutput(line + "\n") ;

		addOutput("\n\n") ;

		mChordCount = 0 ;
		mLines.clear() ;

		++mChordLineCount ;

		if (mChordLineCount >= 5)
		{
//			addOutput(mTitle + "\n\n") ;
			mChordLineCount = 0 ;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool TextPublisher::end()
{
	if (mChordCount > 0)
	{
		for (auto& line : mLines)
			addOutput(line + "\n") ;
	}
	return true ;
}


