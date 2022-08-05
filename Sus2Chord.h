/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Sus2Chord.h
 * \brief     <one-line description of file>
 *
 * \date      2 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef Sus2Chord_H_
#define Sus2Chord_H_

#include "Chord.h"

/*!
 * \class  Sus2Chord
 * \brief  
 * \details   
 *
 */
class Sus2Chord : public Chord {
public:
	Sus2Chord(const std::string& root) ;
	Sus2Chord(const Note& root) ;
	virtual ~Sus2Chord() ;

} ;


#endif /* Sus2Chord_H_ */
