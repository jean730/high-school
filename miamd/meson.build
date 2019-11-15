project('player','cpp')
src=[
  'src/daemon/render.cpp',
  'src/daemon/audio.cpp',
  'src/daemon/main.cpp',
  'src/daemon/init.cpp',
  'src/daemon/GL.cpp',
  'src/daemon/game.cpp',
  'src/daemon/global.cpp',
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
  'src/client/main.cpp',
  install : true,
  link_args : ['-lrt']
  )
