/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Chord.h
 * \brief     <one-line description of file>
 *
 * \date      2 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef CHORD_H_
#define CHORD_H_

#include <vector>
#include "Scale.h"


/*!
 * \class  Chord
 * \brief  
 * \details   
 *
 */
class Chord {
public:
	Chord(const std::string& name, const Scale& scale, std::vector<unsigned> intervals) ;
	Chord(const std::string& name, const Scale& scale, const std::string& equation) ;
	virtual ~Chord() ;

	/**
	 * Chord name
	 */
	std::string name() const ;

	/**
	 * Root note
	 */
	Note root() const ;

	/**
	 * Equation used to form the chord
	 */
	std::string equation() const ;

	/**
	 * Notes in the scale
	 */
	std::vector<Note> notes() const ;

	/**
	 * Search for a note in the chord and return it.
	 * (Used to ensure flats/sharps are displayed correctly)
	 */
	Note search(const Note& note) const ;

	/**
	 * Are these collection of notes valid for this chord? Makes sure all the chord notes
	 * are present (and there are no notes in the list that are not part of the chord)
	 */
	bool valid(const std::vector<Note>& notes) const ;

	/**
	 * Comparison
	 */
	bool operator==(const Chord& rhs) const ;
	bool operator!=(const Chord& rhs) const;
	bool operator<(const Chord& rhs) const;

private:
	void initNotes() ;

private:
	std::string mName ;
	Scale mScale ;
	std::string mEquation ;
	std::vector<Note> mNotes ;
} ;


#endif /* CHORD_H_ */
