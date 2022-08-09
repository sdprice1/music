/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Sus4Chord.h
 * \brief     <one-line description of file>
 *
 * \date      2 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef Sus4Chord_H_
#define Sus4Chord_H_

#include "Chord.h"

/*!
 * \class  Sus4Chord
 * \brief  
 * \details   
 *
 */
class Sus4Chord : public Chord {
public:
	Sus4Chord(const std::string& root) ;
	Sus4Chord(const Note& root) ;
	virtual ~Sus4Chord() ;

} ;


#endif /* Sus4Chord_H_ */
