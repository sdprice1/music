#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Note.h"
#include "Scale.h"
#include "MajorScale.h"
#include "MinorScale.h"
#include "Chord.h"
#include "MajorChord.h"
#include "MinorChord.h"
#include "GuitarString.h"
#include "GuitarChord.h"
#include "Guitar.h"

const std::vector<std::string> chromatic = {
    "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"
};

const std::map<const std::string, const std::vector<int>> degrees = {
    {"Major",       { 0, 2, 4, 5, 7, 9, 11, 12 }},
    {"Minor",       { 0, 2, 3, 5, 7, 8, 10, 12 }},
    {"Harmonic",    { 0, 2, 3, 5, 7, 8, 11, 12 }},
    {"Melodic",     { 0, 2, 3, 5, 7, 9, 11, 12 }}
};

std::string scalenotes(const std::string& rootnote, const std::string& scale) {
    int root = std::distance(chromatic.begin(), std::find(chromatic.begin(), chromatic.end(), rootnote));
    if (root >= chromatic.size()) {
        return "";
    }
    std::stringstream ss;
    for (int i : degrees.at(scale)) {
        ss << chromatic[(root + i) % chromatic.size()] << " ";
    }
    return ss.str();
}

std::stringstream ask(const std::string& question) {
    std::string line;
    std::cout << question;
    std::getline(std::cin, line);
    return std::stringstream(line);
}

void show_frets(const std::string& stringName, const Chord& chord, const std::vector<unsigned>& frets, const GuitarString& string)
{
	std::cerr << stringName << " : " ;
	for (auto fret : frets)
	{
		std::cerr << "[" << fret << "] " ;

		Note note(string.note(fret)) ;
		if (note == chord.root())
			std::cerr << "*" ;
		std::cerr << chord.search(note).toString() << "  ";
	}
	std::cerr << std::endl ;
}


void show_guitar_chord(const GuitarChord& chord)
{
	chord.show() ;
}

int main()
{

	Note c(Note::C) ;
	Note cs(Note::Csharp) ;
	Note d("d") ;
	Note ds("D#") ;
	Note db("Db") ;

	std::cerr << c.toString() << " " <<
			cs.toString() << " " <<
			d.toString() << " " <<
			ds.toString() << " " <<
			db.toString() << " " <<
			std::endl ;

	std::cerr << "Flat from D" << std::endl ;
	for (unsigned i=0; i <= 12; ++i)
	{
		d.flat() ;
		std::cerr << d.toString() << std::endl ;
	}

	std::cerr << "Sharp from Db" << std::endl ;
	for (unsigned i=0; i <= 12; ++i)
	{
		db.sharp() ;
		std::cerr << db.toString() << std::endl ;
	}


	{
	Scale majorC("Major C", Note("C"), "WWHWWW") ;
	auto notes(majorC.notes()) ;
	std::cerr << majorC.name() << std::endl ;
	for (auto& note : notes)
		std::cerr << note.toString() << " " ;
	std::cerr << std::endl ;
	}

	{
	MajorScale majorC(Note("C")) ;
	auto notes(majorC.notes()) ;
	std::cerr << majorC.name() << std::endl ;
	for (auto& note : notes)
		std::cerr << note.toString() << " " ;
	std::cerr << std::endl ;

	Chord cChord("Cmaj", majorC, std::vector<unsigned>{1, 3, 5}) ;
	notes = cChord.notes() ;
	std::cerr << cChord.name() << std::endl ;
	for (auto& note : notes)
		std::cerr << note.toString() << " " ;
	std::cerr << std::endl ;

	}

	{
		MajorChord cChord(Note("C")) ;
		auto notes = cChord.notes() ;
		std::cerr << cChord.name() << std::endl ;
		for (auto& note : notes)
			std::cerr << note.toString() << " " ;
		std::cerr << std::endl ;

		GuitarString stringE("E", "E") ;
		GuitarString stringA("A", "A") ;
		GuitarString stringD("D", "D") ;
		GuitarString stringG("G", "G") ;
		GuitarString stringB("B", "B") ;
		GuitarString stringe("e", "E") ;

		std::vector<unsigned> notes_E(stringE.search(0, 3, cChord.notes())) ;
		std::vector<unsigned> notes_A(stringA.search(0, 3, cChord.notes())) ;
		std::vector<unsigned> notes_D(stringD.search(0, 3, cChord.notes())) ;
		std::vector<unsigned> notes_G(stringG.search(0, 3, cChord.notes())) ;
		std::vector<unsigned> notes_B(stringB.search(0, 3, cChord.notes())) ;
		std::vector<unsigned> notes_e(stringe.search(0, 3, cChord.notes())) ;

		std::cerr << "Frets for " << cChord.name() << std::endl ;
		show_frets("e", cChord, notes_e, stringe) ;
		show_frets("B", cChord, notes_B, stringB) ;
		show_frets("G", cChord, notes_G, stringG) ;
		show_frets("D", cChord, notes_D, stringD) ;
		show_frets("A", cChord, notes_A, stringA) ;
		show_frets("E", cChord, notes_E, stringE) ;
	}

	{
		MajorChord aChord(Note("A")) ;

		GuitarString stringE("E", "E") ;
		GuitarString stringA("A", "A") ;
		GuitarString stringD("D", "D") ;
		GuitarString stringG("G", "G") ;
		GuitarString stringB("B", "B") ;
		GuitarString stringe("e", "E") ;

		std::vector<unsigned> notes_E(stringE.search(0, 3, aChord.notes())) ;
		std::vector<unsigned> notes_A(stringA.search(0, 3, aChord.notes())) ;
		std::vector<unsigned> notes_D(stringD.search(0, 3, aChord.notes())) ;
		std::vector<unsigned> notes_G(stringG.search(0, 3, aChord.notes())) ;
		std::vector<unsigned> notes_B(stringB.search(0, 3, aChord.notes())) ;
		std::vector<unsigned> notes_e(stringe.search(0, 3, aChord.notes())) ;

		std::cerr << "Frets for " << aChord.name() << std::endl ;
		show_frets("e", aChord, notes_e, stringe) ;
		show_frets("B", aChord, notes_B, stringB) ;
		show_frets("G", aChord, notes_G, stringG) ;
		show_frets("D", aChord, notes_D, stringD) ;
		show_frets("A", aChord, notes_A, stringA) ;
		show_frets("E", aChord, notes_E, stringE) ;
	}

	{
		MinorChord aChord(Note("A")) ;

		GuitarString stringE("E", "E") ;
		GuitarString stringA("A", "A") ;
		GuitarString stringD("D", "D") ;
		GuitarString stringG("G", "G") ;
		GuitarString stringB("B", "B") ;
		GuitarString stringe("e", "E") ;

		std::vector<unsigned> notes_E(stringE.search(0, 3, aChord.notes())) ;
		std::vector<unsigned> notes_A(stringA.search(0, 3, aChord.notes())) ;
		std::vector<unsigned> notes_D(stringD.search(0, 3, aChord.notes())) ;
		std::vector<unsigned> notes_G(stringG.search(0, 3, aChord.notes())) ;
		std::vector<unsigned> notes_B(stringB.search(0, 3, aChord.notes())) ;
		std::vector<unsigned> notes_e(stringe.search(0, 3, aChord.notes())) ;

		std::cerr << "Frets for " << aChord.name() << std::endl ;
		show_frets("e", aChord, notes_e, stringe) ;
		show_frets("B", aChord, notes_B, stringB) ;
		show_frets("G", aChord, notes_G, stringG) ;
		show_frets("D", aChord, notes_D, stringD) ;
		show_frets("A", aChord, notes_A, stringA) ;
		show_frets("E", aChord, notes_E, stringE) ;
	}

	{
		MajorChord chord("D") ;

		GuitarString stringE("E", "E") ;
		GuitarString stringA("A", "A") ;
		GuitarString stringD("D", "D") ;
		GuitarString stringG("G", "G") ;
		GuitarString stringB("B", "B") ;
		GuitarString stringe("e", "E") ;

		std::vector<unsigned> notes_E(stringE.search(0, 3, chord.notes())) ;
		std::vector<unsigned> notes_A(stringA.search(0, 3, chord.notes())) ;
		std::vector<unsigned> notes_D(stringD.search(0, 3, chord.notes())) ;
		std::vector<unsigned> notes_G(stringG.search(0, 3, chord.notes())) ;
		std::vector<unsigned> notes_B(stringB.search(0, 3, chord.notes())) ;
		std::vector<unsigned> notes_e(stringe.search(0, 3, chord.notes())) ;

		std::cerr << "Frets for " << chord.name() << std::endl ;
		show_frets("e", chord, notes_e, stringe) ;
		show_frets("B", chord, notes_B, stringB) ;
		show_frets("G", chord, notes_G, stringG) ;
		show_frets("D", chord, notes_D, stringD) ;
		show_frets("A", chord, notes_A, stringA) ;
		show_frets("E", chord, notes_E, stringE) ;
	}



	{
	Scale minorC("Minor C", Note("C"), "WHWWHW") ;
	auto notes(minorC.notes()) ;
	std::cerr << minorC.name() << std::endl ;
	for (auto& note : notes)
		std::cerr << note.toString() << " " ;
	std::cerr << std::endl ;
	}

	{
	MinorScale minorC(Note("C")) ;
	auto notes(minorC.notes()) ;
	std::cerr << minorC.name() << std::endl ;
	for (auto& note : notes)
		std::cerr << note.toString() << " " ;
	std::cerr << std::endl ;
	}

	{
		MinorChord cChord(Note("C")) ;
		auto notes = cChord.notes() ;
		std::cerr << cChord.name() << std::endl ;
		for (auto& note : notes)
			std::cerr << note.toString() << " " ;
		std::cerr << std::endl ;
	}

	{
		MajorChord chord("D") ;

		Guitar guitar ;

		std::vector<GuitarChord> chords(guitar.search(chord, 0)) ;
		for (auto gc : chords)
		{
			gc.show() ;
			std::cerr << "----" << std::endl ;
		}
	}


	return 0 ;

    std::string rootnote, scale;
    while (ask("Please enter your root note and scale: ") >> rootnote >> scale) {
        std::cout << "\nroot scale: " << rootnote << " " << scale
                  << ": " << scalenotes(rootnote, scale) << "\n\n";
    }
}
