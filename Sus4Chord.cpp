/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Sus4Chord.cpp
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
#include "MajorScale.h"
#include "Sus4Chord.h"

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Sus4Chord::Sus4Chord(const Note& root) :
	Chord(root.toString() + "sus4", MajorScale(root), "1-4-5")
{
}

//-------------------------------------------------------------------------------------------------------------
Sus4Chord::Sus4Chord(const std::string &root) :
	Sus4Chord(Note(root))

{
}

//-------------------------------------------------------------------------------------------------------------
Sus4Chord::~Sus4Chord()
{
}

