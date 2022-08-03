/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      MajorScale.h
 * \brief     Major scale
 *
 * \date      2 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef MajorScale_H_
#define MajorScale_H_

#include "Scale.h"

/*!
 * \class  MajorScale
 * \brief  
 * \details   
 *
 */
class MajorScale : public Scale {
public:
	MajorScale(const Note& root) ;
	virtual ~MajorScale() ;
} ;


#endif /* MajorScale_H_ */
