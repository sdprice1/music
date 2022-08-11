/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Guitar.h
 * \brief     <one-line description of file>
 *
 * \date      3 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef GUITAR_H_
#define GUITAR_H_

#include <vector>

#include "GuitarSearchCriteria.h"
#include "GuitarString.h"
#include "GuitarChord.h"

/*!
 * \class  Guitar
 * \brief  
 * \details   
 *
 */
class Guitar {
public:
	Guitar() ;
	virtual ~Guitar() ;

	/**
	 * Look for ways to play the chord in this range of frets. If any are found, returns the list of chords for guitar
	 */
	std::vector<GuitarChord> search(const Chord& chord, unsigned startFret,
			const GuitarSearchCriteria& criteria = GuitarSearchCriteria()) const ;

private:
	struct GuitarChordsearch {
		GuitarChordsearch(unsigned start, unsigned num) :
			startString(start),
			numStrings(num)
		{}

		unsigned startString ;
		unsigned numStrings ;
	};

	std::vector<GuitarChordsearch> getSearches(const Chord& chord,
			const std::vector<std::vector<unsigned>>& stringFrets,
			const GuitarSearchCriteria& criteria) const ;

private:
	GuitarString mString_e ;
	GuitarString mString_B ;
	GuitarString mString_G ;
	GuitarString mString_D ;
	GuitarString mString_A ;
	GuitarString mString_E ;
} ;


#endif /* GUITAR_H_ */
