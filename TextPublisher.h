/*!
 * Copyright (c) 2022 Steve Price.
 * All Rights Reserved
 *
 * \file      TextPublisher.h
 * \brief     Text output
 *
 * \date      15 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef TEXTPUBLISHER_H_
#define TEXTPUBLISHER_H_


#include "Publisher.h"

/*!
 * \class  TextPublisher
 * \brief  
 * \details   
 *
 */
class TextPublisher : public Publisher {
public:
	TextPublisher() ;
	virtual ~TextPublisher() ;

	/**
	 * Add a guitar chord
	 */
	virtual bool addChord(const GuitarChord& chord) override ;

	/**
	 * Finish publishing. Create footers, end of file etc
	 */
	virtual bool end() override ;

private:
	std::string mTitle ;
	std::vector<std::string> mLines ;
	unsigned mChordCount ;
	unsigned mChordLineCount ;

} ;


#endif /* TEXTPUBLISHER_H_ */
