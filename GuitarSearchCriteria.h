/*!
 * Copyright (c) 2022 Steve Price.
 * All Rights Reserved
 *
 * \file      GuitarSearchCriteria.h
 * \brief     <one-line description of file>
 *
 * \date      10 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef GUITARSEARCHCRITERIA_H_
#define GUITARSEARCHCRITERIA_H_


/*!
 * \class  GuitarSearchCriteria
 * \brief  
 * \details   
 *
 */
struct GuitarSearchCriteria {
public:

	GuitarSearchCriteria() :
		allowInversions(true),
		allowMutedStringsInChord(false),
		findTriads(true),
		onlyFindTriads(false)
	{}

	// Do we show inversions or not
	bool allowInversions ;

	// Normally you don't want muted strings inside the block of strings used for a chord
	bool allowMutedStringsInChord ;

	// include chords made up of just the notes of the chord played once
	bool findTriads ;

	// ONLY find triads - don't find any other chords
	bool onlyFindTriads ;
} ;


#endif /* GUITARSEARCHCRITERIA_H_ */
