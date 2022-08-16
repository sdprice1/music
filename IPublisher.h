/*!
 * Copyright (c) 2022 Steve Price.
 * All Rights Reserved
 *
 * \file      IPublisher.h
 * \brief     Virtual interface to publishing guitar chords
 *
 * \date      15 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <string>
#include <memory>

#include "GuitarChord.h"

/*!
 * \class  IPublisher
 * \brief  
 * \details   
 *
 */
class IPublisher {
public:
	IPublisher() {}
	virtual ~IPublisher() {}

	/**
	 * Start publishing. Create and headers etc.
	 */
	virtual bool begin() =0 ;

	/**
	 * Add a guitar chord
	 */
	virtual bool addChord(const GuitarChord& chord) =0 ;

	/**
	 * Finish publishing. Create footers, end of file etc
	 */
	virtual bool end() =0 ;

	/**
	 * Perform the publishing of the data and output it as a string
	 */
	virtual std::string output() =0 ;

} ;

#endif /* IPUBLISHER_H_ */
