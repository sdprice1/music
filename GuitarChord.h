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
	 * Copy
	 */
	GuitarChord(const GuitarChord& rhs) ;

	/**
	 * Set the minimum displayed frets
	 */
	static void setDisplayFretSpan(unsigned span) ;

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
	 * Is this an inverted chord (i.e. root not on lowest sounding string)
	 */
	bool isInverted() const ;

	/**
	 * If the chord is inverted, remove any lower sounding strings so root is lowest
	 */
	void removeInversion() ;

	/**
	 * Display as text
	 */
	void show(std::ostream& os = std::cout, bool showTitle = true) const ;

	/**
	 * Get the chord title string
	 */
	std::string title() const ;

	/**
	 * Taking this chord as the starting point, find any triads - i.e. just the 3 (or more) notes
	 * of the chord with no multiple notes
	 */
	std::vector<GuitarChord> triads() const ;

	/**
	 * Get the frets used for this chord, starting with the bass string
	 * Fret 0 = open string
	 * Fret -1 = not used
	 */
	std::vector<int> frets() const ;

	/**
	 * Get the notes used for this chord, starting with the bass string
	 */
	std::vector<Note> notes() const ;

	/**
	 * Get the underlying chord that this implements
	 */
	Chord chord() const ;

	/**
	 * Comparison
	 */
	bool operator==(const GuitarChord& rhs) const ;
	bool operator!=(const GuitarChord& rhs) const;
	bool operator<(const GuitarChord& rhs) const;

private:
	void updateMaxMin() ;
	void updateMaxMin(unsigned fret) ;

private:
	static unsigned mDisplayFretSpan ;

	Chord mChord ;

	// -1 means string not used
	std::map<std::string, int> mFrets ;

	std::map<std::string, Note> mNotes ;

	int mMinFret ;
	int mMaxFret ;
} ;


#endif /* GUITARCHORD_H_ */
