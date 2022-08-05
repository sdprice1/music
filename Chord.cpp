/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Chord.cpp
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
#include <algorithm>

#include "StringUtils.hpp"
#include "Chord.h"

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Chord::Chord(const std::string &name, const Scale &scale, std::vector<unsigned> intervals) :
	mName(name),
	mScale(scale),
	mEquation(),
	mNotes()

{
	for (auto itvl : intervals)
	{
		if (!mEquation.empty())
			mEquation += '-' ;
		mEquation += std::to_string(itvl) ;
	}
	initNotes() ;

}

//-------------------------------------------------------------------------------------------------------------
Chord::Chord(const std::string &name, const Scale &scale, const std::string &equation) :
	mName(name),
	mScale(scale),
	mEquation(equation),
	mNotes()
{
	initNotes() ;
}


//-------------------------------------------------------------------------------------------------------------
Chord::~Chord()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string Chord::name() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
Note Chord::root() const
{
	return mScale.root() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Chord::equation() const
{
	return mEquation ;
}


//-------------------------------------------------------------------------------------------------------------
std::vector<Note> Chord::notes() const
{
	return mNotes ;
}

//-------------------------------------------------------------------------------------------------------------
Note Chord::search(const Note &note) const
{
	for (auto& chordNote : mNotes)
	{
		if (note != chordNote)
			continue ;

		return chordNote ;
	}

	return Note() ;
}

//-------------------------------------------------------------------------------------------------------------
bool Chord::valid(const std::vector<Note> &notes) const
{
	std::map<Note, unsigned> seen ;
	for (auto& chordNote : mNotes)
	{
		seen[chordNote] = 0 ;
	}

	for (auto& note : notes)
	{
		if (seen.find(note) == seen.end())
			return false ;

		seen[note]++ ;
	}

	for (auto& [note, count] : seen)
	{
		if (count == 0)
			return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Chord::operator ==(const Chord &rhs) const
{
	if (mEquation != rhs.mEquation)
		return false ;

	if (mNotes.size() != rhs.mNotes.size())
		return false ;

	for (unsigned i=0; i < mNotes.size(); ++i)
	{
		if (mNotes.at(i) != rhs.mNotes.at(i))
			return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Chord::operator !=(const Chord &rhs) const
{
	return !operator==(rhs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool Chord::operator <(const Chord &rhs) const
{
	if (mNotes.size() >= rhs.mNotes.size())
		return false ;

	for (unsigned i=0; i < mNotes.size(); ++i)
	{
		if ( !(mNotes.at(i) < rhs.mNotes.at(i)) )
			return false ;
	}

	return true ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Chord::initNotes()
{
	auto scaleNotes(mScale.notes()) ;

	// process equation:
	// 1-3-5
	// 1-b3-bb5-7
	// 1-#2-##5-9

	std::vector<std::string> parts(StringUtils::splitStr(mEquation, '-')) ;

	for (auto& part : parts)
	{
		unsigned flats(std::count_if(part.begin(), part.end(), [](char cc) { return cc=='b';})) ;
		unsigned sharps(std::count_if(part.begin(), part.end(), [](char cc) { return cc=='#';})) ;

		bool ok ;
		unsigned interval(StringUtils::extractUnsigned(part, ok)) ;

		if (!ok || (interval == 0))
			continue ;

		--interval ;
		if (interval >= scaleNotes.size())
			continue ;

		Note note(scaleNotes[interval]) ;

		while (sharps)
		{
			--sharps ;
			note.sharp() ;
		}
		while (flats)
		{
			--flats ;
			note.flat() ;
		}

		mNotes.push_back(note) ;
	}
}

