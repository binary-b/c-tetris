import os
import ycm_core

flags = [
  '-Wall',
  '-Werror',
  '-std=c99',
  '-xc',
  '-I/usr/include/',
  '-I/usr/include/allegro5',
  '-I./include',
  ]

SOURCE_EXTENSIONS = [ '.c', ]

def IsHeaderFile( filename ):
  extension = os.path.splitext( filename )[ 1 ]
  return extension in [ '.h', '.hxx', '.hpp', '.hh' ]

def FlagsForFile( filename, **kwargs ):
  return {
  'flags': flags,
  'do_cache': True
  }
