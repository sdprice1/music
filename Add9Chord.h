/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Add9Chord.h
 * \brief     <one-line description of file>
 *
 * \date      2 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef Add9Chord_H_
#define Add9Chord_H_

#include "Chord.h"

/*!
 * \class  Add9Chord
 * \brief  
 * \details   
 *
 */
class Add9Chord : public Chord {
public:
	Add9Chord(const std::string& root) ;
	Add9Chord(const Note& root) ;
	virtual ~Add9Chord() ;

} ;


#endif /* Add9Chord_H_ */
