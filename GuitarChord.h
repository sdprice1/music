/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      GuitarChord.h
 * \brief     A chord played on guitar
 *
 * \date      3 Aug 2022
 * \author    sprice
 *
 * \details   As well as the chord information, this also contains the frets of the strings being played for the chord
 * 			Strings are accessed by name: "E", "A", "D", "G", "B", "e" (i.e. high string is labelled "e")
 *
 */


#ifndef GUITARCHORD_H_
#define GUITARCHORD_H_

#include <map>
#include <iostream>

#include "Chord.h"
#include "Note.h"


/*!
 * \class  GuitarChord
 * \brief  
 * \details   
 *
 */
class GuitarChord {
public:
	GuitarChord(const Chord& chord) ;
	virtual ~GuitarChord() ;

	/**
	 * Add a fret definition to a string
	 */
	bool addFret(const std::string& stringName, unsigned fret, const Note& note) ;

	/**
	 * Is this string used for the chord?
	 */
	bool isUsed(const std::string& stringName) const ;

	/**
	 * Does this collection of string notes make up the chord?
	 */
	bool isValid() const ;

	/**
	 * Display as text
	 */
	void show(std::ostream& os = std::cout) const ;

private:
	Chord mChord ;

	// -1 means string not used
	std::map<std::string, int> mFrets ;

	std::map<std::string, Note> mNotes ;

	int mMinFret ;
	int mMaxFret ;
} ;


#endif /* GUITARCHORD_H_ */
