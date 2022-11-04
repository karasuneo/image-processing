#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第２回/imgWaku
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第２回/imgWaku/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第２回/imgWaku
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第２回/imgWaku/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第２回/imgWaku
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第２回/imgWaku/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第２回/imgWaku
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第２回/imgWaku/CMakeScripts/ReRunCMake.make
fi

