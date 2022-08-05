project(
  'Music utils',
  'cpp',
  version: '1.0.0',
default_options : [
  'warning_level=3',
  'cpp_std=c++17'
])

lib_source = [
	'Note.cpp', 
	'Scale.cpp',
	'MajorScale.cpp',
	'MinorScale.cpp',
	'Chord.cpp',
	'MajorChord.cpp',
	'MinorChord.cpp',
	'Sus2Chord.cpp',
	'GuitarString.cpp',
	'GuitarChord.cpp',
	'Guitar.cpp',
]

executable('Music', [
	'Music.cpp', 
	lib_source,
]
)

executable('print-chords', [
	'print-chords.cpp', 
	lib_source,
]
)

