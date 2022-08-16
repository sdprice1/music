/*!
 * Copyright (c) 2022 Steve Price.
 * All Rights Reserved
 *
 * \file      Publisher.h
 * \brief     <one-line description of file>
 *
 * \date      15 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "IPublisher.h"

/*!
 * \class  Publisher
 * \brief  
 * \details   
 *
 */
class Publisher : virtual public IPublisher {
public:
	Publisher() ;
	virtual ~Publisher() ;

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

	/**
	 * Perform the publishing of the data and output it as a string
	 */
	virtual std::string output() override ;


protected:
	/**
	 * Append output to string
	 */
	void addOutput(const std::string& out) ;

	/**
	 * Insert output at start of existing string
	 */
	void insertOutput(const std::string& out) ;

private:
	std::string mOutput ;
} ;

#endif /* PUBLISHER_H_ */
