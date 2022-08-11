/*!
 * Copyright (c) 2022 Steve Price
 * All Rights Reserved
 *
 * \file      print-chords.cpp
 * \brief     Print guitar chords chart
 *
 * \date      3 Aug 2022
 * \author    sprice
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <unistd.h>
#include <getopt.h>

#include <iostream>
#include <sstream>
#include <set>

#include "StringUtils.hpp"
#include "Note.h"
#include "Scale.h"
#include "MajorScale.h"
#include "MinorScale.h"
#include "Chord.h"
#include "GuitarString.h"
#include "GuitarChord.h"
#include "Guitar.h"

//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {
	struct Options {
		bool wholeNeck ;
		bool triadsOnly ;
		unsigned debug ;
		std::vector<std::string> args ;
	};

	enum LongOption {
		OPT_NO_ARGS		= 0,
		OPT_REQUIRED	= 1,
		OPT_OPTIONAL	= 2,
	};

	void help()
	{
		std::cout << "print-chords" << std::endl ;
		std::cout << "Options" << std::endl ;
		std::cout << "  -h, --help                 Show this help " << std::endl ;
		std::cout << "  -d, --debug <level>        Set debug level " << std::endl ;
		std::cout << "  -w, --whole-neck           Search across the whole neck" << std::endl ;
		std::cout << "  -t, --only-triads          Only find triads" << std::endl ;
		std::cout << std::endl ;
	}

	bool getOptions(int argc, char** argv, Options& options)
	{
		options.wholeNeck = false ;
		options.debug = 0 ;
		options.triadsOnly = false ;
		options.args.clear() ;

		struct option long_options[] = {
			{"help", OPT_NO_ARGS, nullptr, 'h'},
			{"whole-neck", OPT_NO_ARGS, nullptr, 'w'},
			{"only-triads", OPT_NO_ARGS, nullptr, 't'},
			{0, 0, 0, 0}
		};
		int option_index = 0;
		optind = 0 ;

		int c ;
	    while ((c = getopt_long(argc, argv, "hd:wt", long_options, &option_index)) != -1)
	    {
	        switch (c)
	        {
	        case 'h':
	            help();
	            exit(0);
	            break;

	        case 'd':
	        	options.debug = (unsigned)std::stoul(optarg) ;
	        	break ;

	        case 'w':
	        	options.wholeNeck = true ;
	        	break ;

	        case 't':
	        	options.triadsOnly = true ;
	        	break ;
	        }
	    }

	    while (optind < argc)
	    {
	    	options.args.push_back(argv[optind++]) ;
	    }

		return true ;
	}

}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    Options options ;
    if (!getOptions(argc, argv, options))
    	return -1 ;

	if (options.args.empty())
	{
		std::cerr << "Error: Must specify a note" << std::endl ;
		return -1 ;
	}
	std::string noteName(options.args[0]) ;

	std::string type("Major") ;
	if (options.args.size() >= 2)
	{
		type = options.args[0] ;
	}

	unsigned endFret(0) ;
	if (options.wholeNeck)
		endFret = 12 ;

	GuitarSearchCriteria criteria ;
	if (options.triadsOnly)
		criteria.onlyFindTriads = true ;

	std::shared_ptr<Chord> chord(Chord::factory(type, noteName)) ;
	if (!chord)
	{
		std::cerr << "ERROR: Unable to create " << type << " chord" << std::endl ;
		return -1 ;
	}

	Guitar guitar ;

	// generate chords
	std::string title ;
	std::set<GuitarChord> sortedChords ;
	for (unsigned fret=0; fret <= endFret; fret++)
	{
		std::vector<GuitarChord> chords(guitar.search(*chord, fret, criteria)) ;
		for (auto gc : chords)
		{
			sortedChords.insert(gc) ;
			title = gc.title() ;
		}
	}

	// display chords
	std::cout << title << std::endl << std::endl ;
	std::vector<std::string> lines ;
	unsigned chordCount(0) ;
	for (auto gc : sortedChords)
	{
		std::stringstream ss ;
		gc.show(ss, false) ;

		std::vector<std::string> chordLines(StringUtils::splitStr(ss.str(), '\n')) ;
		++chordCount ;
		if (chordCount == 1)
		{
			lines = chordLines ;
			continue ;
		}

		for (unsigned i=0; (i < chordLines.size()) && (i < lines.size()); ++i)
			lines[i] += chordLines[i] ;

		if (chordCount >= 4)
		{
			for (auto& line : lines)
				std::cout << line << std::endl ;

			std::cout << std::endl << std::endl ;

			chordCount = 0 ;
			lines.clear() ;
		}
	}

	if (chordCount > 0)
	{
		for (auto& line : lines)
			std::cout << line << std::endl ;
	}

}
