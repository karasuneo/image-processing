#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第１１回/colorBar
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第１１回/colorBar/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第１１回/colorBar
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第１１回/colorBar/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第１１回/colorBar
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第１１回/colorBar/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第１１回/colorBar
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第１１回/colorBar/CMakeScripts/ReRunCMake.make
fi

