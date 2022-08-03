/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Scale.h
 * \brief     Base for any scale
 *
 * \date      2 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef SCALE_H_
#define SCALE_H_

#include <string>
#include <vector>

#include "Note.h"

/*!
 * \class  Scale
 * \brief  
 * \details   
 *
 */
class Scale {
public:
	Scale(const std::string& name, const Note& root, const std::string& intervals) ;
	virtual ~Scale() ;

	/**
	 * Scale name
	 */
	std::string name() const ;

	/**
	 * Root note
	 */
	Note root() const ;

	/**
	 * Notes in the scale
	 */
	std::vector<Note> notes() const ;

private:
	std::string mName ;
	Note mRootNote ;
	std::string mIntervals ;
	std::vector<Note> mNotes ;
} ;


#endif /* SCALE_H_ */
