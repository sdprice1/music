/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      MinorScale.h
 * \brief     Minor scale
 *
 * \date      2 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef MinorScale_H_
#define MinorScale_H_

#include "Scale.h"

/*!
 * \class  MinorScale
 * \brief  
 * \details   
 *
 */
class MinorScale : public Scale {
public:
	MinorScale(const Note& root) ;
	virtual ~MinorScale() ;
} ;


#endif /* MinorScale_H_ */
