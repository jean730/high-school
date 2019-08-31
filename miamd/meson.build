project('player','cpp')
src=[
  'src/render.cpp',
  'src/audio.cpp',
  'src/main.cpp',
  'src/init.cpp',
  'src/GL.cpp',
  'src/game.cpp',
]
sfmlsystem=dependency('sfml-system')
sfmlnetwork=dependency('sfml-network')
sfmlwindow=dependency('sfml-window')
notifs=dependency('libnotify')
GL=dependency('GL')
GLEW=dependency('glew')
threads=dependency('threads')
mpv=dependency('mpv')
X11=dependency('x11')
sqlite3=dependency('sqlite3')
headers = include_directories('headers')
executable(
  'miamd',
  src,
  dependencies : [
    sfmlsystem,
    sfmlwindow,
    GL,
    GLEW,
    threads,
    mpv,
    X11,
    sqlite3,
    notifs,
    ],
  include_directories : headers,
  install : true,
  link_args : ['-lrt','-lmariadb']
  )
executable(
  'miamd-controller',
  'controller/main.cpp',
  install : true,
  link_args : ['-lrt']
  )
