/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      MajorChord.h
 * \brief     <one-line description of file>
 *
 * \date      2 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef MajorChord_H_
#define MajorChord_H_

#include "Chord.h"

/*!
 * \class  MajorChord
 * \brief  
 * \details   
 *
 */
class MajorChord : public Chord {
public:
	MajorChord(const std::string& root) ;
	MajorChord(const Note& root) ;
	virtual ~MajorChord() ;

} ;


#endif /* MajorChord_H_ */
