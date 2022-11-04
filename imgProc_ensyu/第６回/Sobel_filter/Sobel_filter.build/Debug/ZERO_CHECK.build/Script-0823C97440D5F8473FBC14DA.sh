#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第６回/Sobel_filter
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第６回/Sobel_filter/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第６回/Sobel_filter
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第６回/Sobel_filter/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第６回/Sobel_filter
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第６回/Sobel_filter/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/k21116kk/src/imageProc/imgProc_ensyu/第６回/Sobel_filter
  make -f /Users/k21116kk/src/imageProc/imgProc_ensyu/第６回/Sobel_filter/CMakeScripts/ReRunCMake.make
fi

