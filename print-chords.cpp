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

#include "TextPublisher.h"
#include "HtmlPublisher.h"

//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {
	struct Options {
		bool wholeNeck ;
		bool triadsOnly ;
		unsigned debug ;
		bool listTypes ;
		bool pageBreaks ;
		std::vector<std::string> type ;
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
		std::cout << "  -T, --only-triads          Only find triads" << std::endl ;
		std::cout << "  -t, --type <type>          Select chord type (default: Major)" << std::endl ;
		std::cout << "  -l, --list-types           List available chord types" << std::endl ;
		std::cout << "  -P, --page-breaks          Add page breaks for printing" << std::endl ;
		std::cout << std::endl ;
	}

	bool getOptions(int argc, char** argv, Options& options)
	{
		options.wholeNeck = false ;
		options.debug = 0 ;
		options.triadsOnly = false ;
		options.listTypes = false ;
		options.pageBreaks = false ;
		options.type.clear() ;
		options.args.clear() ;

		struct option long_options[] = {
			{"help", OPT_NO_ARGS, nullptr, 'h'},
			{"whole-neck", OPT_NO_ARGS, nullptr, 'w'},
			{"only-triads", OPT_NO_ARGS, nullptr, 'T'},
			{"list-types", OPT_NO_ARGS, nullptr, 'l'},
			{"page-breaks", OPT_NO_ARGS, nullptr, 'P'},
			{"type", OPT_REQUIRED, nullptr, 't'},
			{0, 0, 0, 0}
		};
		int option_index = 0;
		optind = 0 ;

		int c ;
	    while ((c = getopt_long(argc, argv, "hd:wTlPt:", long_options, &option_index)) != -1)
	    {
	    	std::string optArgStr(optarg) ;
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

	        case 'T':
	        	options.triadsOnly = true ;
	        	break ;

	        case 'l':
	        	options.listTypes = true ;
	        	break ;

	        case 'P':
	        	options.pageBreaks = true ;
	        	break ;

	        case 't':
	        	options.type.push_back(optarg) ;
	        	if (optArgStr == "all")
	        	{
	        		options.type.clear() ;
	        		options.type = Chord::types() ;
	        	}
	        	break ;
	        }
	    }

	    while (optind < argc)
	    {
	    	options.args.push_back(argv[optind++]) ;
	    }
	    if (options.args.empty())
	    	options.args = std::vector<std::string>{"A", "B", "C", "D", "E", "F", "G"} ;


	    if (options.type.empty())
	    	options.type = std::vector<std::string>{"Major", "Minor"} ;

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

    if (options.listTypes)
    {
    	std::vector<std::string> list(Chord::types()) ;
    	std::cout << "Available chord types:" << std::endl ;
    	for (auto& type : list)
    		std::cout << type << std::endl ;
    	return 0 ;
    }


	if (options.args.empty())
	{
		std::cerr << "Error: Must specify a note" << std::endl ;
		return -1 ;
	}

	unsigned endFret(0) ;
	if (options.wholeNeck)
		endFret = 12 ;

	GuitarSearchCriteria criteria ;
	if (options.triadsOnly)
		criteria.onlyFindTriads = true ;


	Guitar guitar ;
	std::vector<GuitarChord> sortedChords ;

	// process each note
	for (auto& noteName : options.args)
	{
		for (auto& type : options.type)
		{
			std::shared_ptr<Chord> chord(Chord::factory(type, noteName)) ;
			if (!chord)
			{
				std::cerr << "ERROR: Unable to create " << type << " chord" << std::endl ;
				return -1 ;
			}

			// generate chords
			std::vector<GuitarChord> chords( guitar.search(*chord, 0, endFret, criteria) ) ;
			sortedChords.insert(sortedChords.end(), chords.begin(), chords.end()) ;
		}
	}

	// print them
//	std::shared_ptr<IPublisher> publisher(std::make_shared<TextPublisher>()) ;
	std::shared_ptr<IPublisher> publisher(std::make_shared<HtmlPublisher>()) ;
	publisher->begin() ;
	for (auto gc : sortedChords)
	{
		publisher->addChord(gc) ;
	}

//publisher->addChord(sortedChords[0]) ;
	publisher->end() ;

	std::cout << publisher->output() ;

}
