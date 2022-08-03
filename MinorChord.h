/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      MinorChord.h
 * \brief     <one-line description of file>
 *
 * \date      2 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef MinorChord_H_
#define MinorChord_H_

#include "Chord.h"

/*!
 * \class  MinorChord
 * \brief  
 * \details   
 *
 */
class MinorChord : public Chord {
public:
	MinorChord(const std::string& root) ;
	MinorChord(const Note& root) ;
	virtual ~MinorChord() ;

} ;


#endif /* MinorChord_H_ */
