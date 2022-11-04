#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_kadai/第４回/kadai01_bin
  make -f /Users/k21116kk/src/imageProc/imgProc_kadai/第４回/kadai01_bin/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_kadai/第４回/kadai01_bin
  make -f /Users/k21116kk/src/imageProc/imgProc_kadai/第４回/kadai01_bin/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_kadai/第４回/kadai01_bin
  make -f /Users/k21116kk/src/imageProc/imgProc_kadai/第４回/kadai01_bin/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_kadai/第４回/kadai01_bin
  make -f /Users/k21116kk/src/imageProc/imgProc_kadai/第４回/kadai01_bin/CMakeScripts/ReRunCMake.make
fi

