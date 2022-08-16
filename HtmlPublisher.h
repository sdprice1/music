/*!
 * Copyright (c) 2022 Steve Price.
 * All Rights Reserved
 *
 * \file      HtmlPublisher.h
 * \brief     Publish chords as HTML
 *
 * \date      15 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef HTMLPUBLISHER_H_
#define HTMLPUBLISHER_H_

#include "Publisher.h"

/*!
 * \class  HtmlPublisher
 * \brief  
 * \details   
 *
 */
class HtmlPublisher : public Publisher {
public:
	HtmlPublisher() ;
	virtual ~HtmlPublisher() ;

	/**
	 * Start publishing. Create and headers etc.
	 */
	virtual bool begin() override ;

	/**
	 * Add a guitar chord
	 */
	virtual bool addChord(const GuitarChord& chord) override ;

	/**
	 * Finish publishing. Create footers, end of file etc
	 */
	virtual bool end() override ;


private:
	unsigned mWidth ;
	unsigned mHeight ;
	unsigned mRow ;
	unsigned mCol ;

} ;


#endif /* HTMLPUBLISHER_H_ */
