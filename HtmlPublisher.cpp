/*!
 * Copyright (c) 2022 Steve Price.
 * All Rights Reserved
 *
 * \file      HtmlPublisher.cpp
 * \brief     <one-line description of file>
 *
 * \date      15 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "HtmlPublisher.h"


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// TODO: get this from Guitar
const unsigned FRET_SPAN(4) ;

//-------------------------------------------------------------------------------------------------------------
const unsigned X_STRING_SPACE(30) ;
const unsigned Y_FRET_SPACE(50) ;

const unsigned X_START(40) ;
const unsigned Y_START(40) ;

const unsigned X_OFFSET(100) ;
const unsigned Y_OFFSET(50) ;

const unsigned FINGER_RADIUS(14) ;
const unsigned MUTED_SIZE(20) ;
const unsigned OPEN_SIZE(MUTED_SIZE) ;

const unsigned CHORDS_PER_LINE(4) ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
HtmlPublisher::HtmlPublisher() :
	Publisher(),
	mWidth(0),
	mHeight(0),
	mTotalWidth(0),
	mTotalHeight(0),
	mRow(0),
	mCol(0),
	mChord()
{
}

//-------------------------------------------------------------------------------------------------------------
HtmlPublisher::~HtmlPublisher()
{
}

//-------------------------------------------------------------------------------------------------------------
bool HtmlPublisher::begin()
{
	mWidth = (5 * X_STRING_SPACE) ;
	mHeight = ( FRET_SPAN * Y_FRET_SPACE) ;

	mTotalWidth = mWidth + X_OFFSET ;
	mTotalHeight = mHeight + Y_OFFSET + Y_FRET_SPACE ; // add extra space at bottom for fretted notes

//	addOutput("<!DOCTYPE html>\n") ;
//	addOutput("<html>\n<body>\n") ;
//
//	addOutput("<svg width=\"400px\" height=\"400px\" viewBox=\"0 0 400 400\">\n") ;
//	addOutput("<title>Guitar Chords</title>\n") ;
//	<desc>Drawing example of different chords displayed as SVG</desc>

	addOutput("<defs>\n") ;

	std::string radiusStr(std::to_string(FINGER_RADIUS)) ;
	addOutput("<symbol id=\"sym-finger-pos\" style=\"stroke: black;\">\n") ;
	addOutput("    <desc>Finger position</desc>\n") ;
	addOutput("    <circle cx=\"" + radiusStr + "\" cy=\"" + radiusStr + "\" r=\"" + radiusStr + "\" fill=\"#00f\" />\n") ;
	addOutput("</symbol>\n\n") ;


	addOutput("<symbol id=\"sym-open-pos\" style=\"stroke: black;\">\n") ;
	addOutput("    <desc>Finger position</desc>\n") ;
	addOutput("    <circle cx=\"" + std::to_string(OPEN_SIZE/2) + "\" cy=\"" + std::to_string(OPEN_SIZE/2) + "\" r=\"" + std::to_string(OPEN_SIZE/2) + "\" fill=\"none\" />\n") ;
	addOutput("</symbol>\n\n") ;

	addOutput("<symbol id=\"sym-muted-pos\" style=\"stroke: black;\">\n") ;
	addOutput("    <desc>Finger position</desc>\n") ;
	addOutput("    <line x1=\"2\" y1=\"0\" x2=\"" + std::to_string(MUTED_SIZE-2) + "\" y2=\"" + std::to_string(MUTED_SIZE) + "\" stroke-width=\"1\"/>\n") ;
	addOutput("    <line x1=\"2\" y1=\"" + std::to_string(MUTED_SIZE) + "\" x2=\"" + std::to_string(MUTED_SIZE-2) + "\" y2=\"0\" stroke-width=\"1\"/>\n") ;
	addOutput("</symbol>\n\n") ;

	addOutput("<symbol id=\"sym-chart\" style=\"stroke: black;\"                 \n") ;
	addOutput("   preserveAspectRatio=\"xMidYMid slice\" viewBox=\"0 0 " + std::to_string(mWidth) + " " + std::to_string(mHeight) + "\">\n") ;
	addOutput("    <desc>Guitar strings</desc>                                   \n") ;

	for (unsigned string=0; string < 6; ++string)
	{
		unsigned x(string * X_STRING_SPACE) ;
		unsigned y2(mHeight-1) ;

		if (x == 0)
			++x ;
		if (x >= mWidth)
			--x ;

		addOutput("    <line x1=\"" + std::to_string(x) + "\" y1=\"0\" x2=\"" + std::to_string(x) + "\" y2=\"" + std::to_string(y2) + "\"/>  \n") ;
	}


	for (unsigned fret=0; fret <= 4; ++fret)
	{
		unsigned y(fret * Y_FRET_SPACE) ;

		if (y == 0)
			++y ;
		if (y >= mHeight)
			--y ;

		addOutput("    <line x1=\"0\" y1=\"" + std::to_string(y) + "\" x2=\"" + std::to_string(mWidth-1) + "\" y2=\"" + std::to_string(y) + "\"/>\n") ;
	}
	addOutput("</symbol>\n\n") ;

//	unsigned cx(mWidth/2) ;
//	unsigned cy(Y_FRET_SPACE/2) ;
	addOutput("<symbol id=\"sym-chart-1\" style=\"stroke: black;\"\n") ;
	addOutput("   preserveAspectRatio=\"xMidYMid slice\" viewBox=\"0 0 " + std::to_string(mWidth) + " " + std::to_string(mHeight) + "\">\n") ;
	addOutput("    <desc>Guitar strings at nut position</desc>\n") ;
//	addOutput("    <circle cx=\"" + std::to_string(cx) + "\" cy=\"" + std::to_string(cy) + "\" r=\"12\" fill=\"#ccc\" style=\"stroke: #ccc;\" />\n") ;
	addOutput("    <line x1=\"0\" y1=\"0\" x2=\"" + std::to_string(mWidth-1) + "\" y2=\"0\" stroke-width=\"19\"/>\n") ;
	addOutput("	<use xlink:href=\"#sym-chart\" x=\"0\" y=\"0\" width=\"" + std::to_string(mWidth) + "\" height=\"" + std::to_string(mHeight) + "\" />\n") ;
	addOutput("</symbol>\n\n") ;

	addOutput("</defs>\n\n") ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool HtmlPublisher::addChord(const GuitarChord &chord)
{

//std::cerr << "-- Add chord ----" << std::endl ;

	bool showTitle(chord.chord() != mChord) ;

	// save the last drawn chord
	mChord = chord.chord() ;

	// get min/max frets
	int minFret(-1) ;
	int maxFret(-1) ;
	std::vector<int> frets(chord.frets()) ;
	for (unsigned string=0; string < frets.size(); ++string)
	{
		if (frets[string] < 0)
			continue ;

		if (minFret < 0)
		{
			minFret = frets[string] ;
		}
		if (maxFret < 0)
		{
			maxFret = frets[string] ;
		}

		if (minFret > frets[string])
		{
			minFret = frets[string] ;
		}
		if (maxFret < frets[string])
		{
			maxFret = frets[string] ;
		}
	}

	if (minFret < 0)
		return false ;

	if ((minFret > 1) && (maxFret <= 4))
		minFret = 1 ;

	if (minFret == 0)
		minFret = 1 ;

//	std::cerr << "min fret=" << minFret << std::endl ;
//	std::cerr << "max fret=" << maxFret << std::endl ;

	// show the title when chord changes
	if (showTitle)
	{
		if (mCol > 0)
		{
			mCol = 0 ;
			++mRow ;
		}

		const unsigned TITLE_FONT(100) ;
		const unsigned SUBTITLE_FONT(40) ;
		unsigned tx( (mCol * mTotalWidth) + X_START) ;
		unsigned ty( (mRow * mTotalHeight) + Y_START + TITLE_FONT - 35) ;

		addOutput("<text x=\"" + std::to_string(tx) + "\" y=\"" + std::to_string(ty) + "\" font-size=\"" + std::to_string(TITLE_FONT) +
				"\">" + chord.chord().name() + "</text>") ;

		ty += SUBTITLE_FONT + 20 ;
		addOutput("<text x=\"" + std::to_string(tx) + "\" y=\"" + std::to_string(ty) + "\" font-size=\"" + std::to_string(SUBTITLE_FONT) +
				"\">" + chord.chord().notesStr() + "</text>") ;

		ty += SUBTITLE_FONT + 15 ;
		addOutput("<text x=\"" + std::to_string(tx) + "\" y=\"" + std::to_string(ty) + "\" font-size=\"" + std::to_string(SUBTITLE_FONT) +
				"\" style=\"font-style: italic;\">[" + chord.chord().equation() + "]</text>") ;

		++mRow ;
	}

	// draw guitar neck
	unsigned x( (mCol * mTotalWidth) + X_START) ;
	unsigned y( (mRow * mTotalHeight) + Y_START) ;

	if (minFret <= 1)
	{
		addOutput("<use xlink:href=\"#sym-chart-1\" x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) + "\" width=\"" +
				std::to_string(mWidth) + "\" height=\"" + std::to_string(mHeight) + "\" />\n") ;
	}
	else
	{
		addOutput("<use xlink:href=\"#sym-chart\" x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) + "\" width=\"" +
				std::to_string(mWidth) + "\" height=\"" + std::to_string(mHeight) + "\" />\n") ;

		unsigned tx(x - X_START + 10) ;
		unsigned ty(y + (Y_FRET_SPACE/2) + 10) ;
		addOutput("<text x=\"" + std::to_string(tx) + "\" y=\"" + std::to_string(ty) + "\" font-size=\"20\">" + std::to_string(minFret) + "</text>") ;
	}

	// show finger positions
	std::vector<Note> notes(chord.notes()) ;
	for (unsigned string=0; string < frets.size(); ++string)
	{
		int fret(frets[string]) ;

//		std::cerr << "String " << string << " fret " << fret << std::endl ;


		// Display the note at this string
		if (fret >= 0)
		{
			const unsigned NOTES_SIZE(20) ;
			unsigned notex( x + (string * X_STRING_SPACE)) ;
			unsigned notey( y + mHeight + NOTES_SIZE ) ;
			addOutput("<text x=\"" + std::to_string(notex) +
					"\" y=\"" + std::to_string(notey) +
					"\" font-size=\"" + std::to_string(NOTES_SIZE) +
					"\" style=\"text-anchor: middle;\">" +
					mChord.search(notes[string]).toString() + "</text>") ;
		}

		// if we're doing the open/muted strings then display them
		if (fret <= 0)
		{
			unsigned posx( x - (MUTED_SIZE/2) + (string * X_STRING_SPACE) ) ;
			unsigned posy( y - (MUTED_SIZE+2) ) ;

			if (fret < 0)
			{
				addOutput("<use xlink:href=\"#sym-muted-pos\" x=\"" + std::to_string(posx) + "\" y=\"" + std::to_string(posy) + "\" />\n") ;
				continue ;
			}

			if (fret == 0)
			{
				addOutput("<use xlink:href=\"#sym-open-pos\" x=\"" + std::to_string(posx) + "\" y=\"" + std::to_string(posy) + "\" />\n") ;
				continue ;
			}

		}

		unsigned posx( (x - FINGER_RADIUS) + (string * X_STRING_SPACE) ) ;
		unsigned posy( (y + 12) + ( (fret - minFret) * Y_FRET_SPACE) ) ;

//		std::cerr << "String " << string << " fret " << fret << " (" << posx << ", " << posy << ")" << std::endl ;

		// <use xlink:href=\"#sym-finger-pos\" x=\"26\" y=\"50\" />
		addOutput("<use xlink:href=\"#sym-finger-pos\" x=\"" + std::to_string(posx) + "\" y=\"" + std::to_string(posy) + "\" />\n") ;



	}

std::cerr << chord.chord().name() << " row=" << mRow << " y=" << y << " y+totalHeight=" << (y+mTotalHeight) << std::endl ;



	// update position
	if (++mCol >= CHORDS_PER_LINE)
	{
		mCol = 0 ;
		++mRow ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool HtmlPublisher::end()
{
	addOutput("</svg>\n") ;
	addOutput("</body>\n</html>\n") ;


	unsigned totalWidth( (CHORDS_PER_LINE * mTotalWidth) + X_START) ;
	unsigned totalHeight( ++mRow * mTotalHeight + Y_START) ;

	// insert at start of string (needs to be in reverse order)
	insertOutput("<title>Guitar Chords</title>\n") ;
	insertOutput("<svg width=\"" + std::to_string(totalWidth) + "px\" height=\"" + std::to_string(totalHeight) + "px\" viewBox=\"0 0 " + std::to_string(totalWidth) + " " + std::to_string(totalHeight) + "\">\n") ;
	insertOutput("<html>\n<body>\n") ;
	insertOutput("<!DOCTYPE html>\n") ;

	return true ;
}


