project(
  'Music utils',
  'cpp',
  version: '1.0.0',
default_options : [
  'warning_level=3',
  'cpp_std=c++17'
])

# ============================================================
# Library target
# ============================================================
project_includes = include_directories('.')

lib_source = [
	'Note.cpp', 
	'Scale.cpp',
	'MajorScale.cpp',
	'MinorScale.cpp',
	'Chord.cpp',
	'ChordFactory.cpp',
	'MajorChord.cpp',
	'MinorChord.cpp',
	'Sus2Chord.cpp',
	'Sus4Chord.cpp',
	'Add9Chord.cpp',
	'GuitarString.cpp',
	'GuitarChord.cpp',
	'Guitar.cpp',
]

libname = 'music' 
project_lib = static_library(
  libname,
  sources : lib_source,
  include_directories : project_includes,

  install: true,
)


#executable('Music', [
#	'Music.cpp', 
#	lib_source,
#]
#)

executable('print-chords', 
	sources : [
		'print-chords.cpp', 
	],
	
	link_with : [
		project_lib,
	]
)

