/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      Note.h
 * \brief     <one-line description of file>
 *
 * \date      2 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef NOTE_H_
#define NOTE_H_

#include <string>


/*!
 * \class  Note
 * \brief  
 * \details   
 *
 */
class Note {
public:
	enum NoteVal {
		C		=  0,
		Csharp	=  1,
		Dflat	=  1,
		D		=  2,
		Dsharp	=  3,
		Eflat	=  3,
		E		=  4,
		F		=  5,
		Fsharp	=  6,
		Gflat	=  6,
		G		=  7,
		Gsharp	=  8,
		Aflat	=  8,
		A		=  9,
		Asharp	=  10,
		Bflat	=  10,
		B		=  11,

		NO_NOTE =  12,
	};

	Note() ;
	Note(NoteVal val) ;
	Note(const std::string& val) ;
	virtual ~Note() ;

	/**
	 * Copy
	 */
	Note(const Note& rhs) ;

	/**
	 * Flatten
	 */
	void flat() ;

	/**
	 * Sharpen
	 */
	void sharp() ;

	/**
	 * Get note as string
	 */
	std::string toString() const ;

	/**
	 * Comparison
	 */
	bool operator==(const Note& rhs) const ;
	bool operator!=(const Note& rhs) const;
	bool operator<(const Note& rhs) const;

private:
	bool mFlattening ; // do we want to show the flat accidental or the sharp?
	NoteVal mVal ;
} ;



#endif /* NOTE_H_ */
