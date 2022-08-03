/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      GuitarString.h
 * \brief     <one-line description of file>
 *
 * \date      3 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef GUITARSTRING_H_
#define GUITARSTRING_H_

#include <string>
#include <vector>

#include "Note.h"


/*!
 * \class  GuitarString
 * \brief  
 * \details   
 *
 */
class GuitarString {
public:
	GuitarString(const std::string& name, const std::string& open) ;
	GuitarString(const std::string& name, const Note& open) ;
	virtual ~GuitarString() ;

	/**
	 * Get name
	 */
	std::string name() const ;

	/**
	 * Get the note at a fret
	 */
	Note note(unsigned fret) const ;

	/**
	 * Search range of frets for the specified notes. Returns list of matching frets
	 */
	std::vector<unsigned> search(unsigned startFret, unsigned endFret, const std::vector<Note> notes) const ;


private:
	std::string mName ;
	Note mOpen ;
	std::vector<Note> mNotes ;
} ;


#endif /* GUITARSTRING_H_ */
