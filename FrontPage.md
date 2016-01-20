# AVbin #

## Quickly ##

AVbin is a thin wrapper around FFmpeg, providing binary compatibility for applications and languages that need it.

## Details ##

FFmpeg is a collection of audio and video codecs widely used in projects such as mplayer, xine, gstreamer and VLC.  It is under continuous development; so much so that its developers rarely provide a release, and SVN snapshots of the library must be statically linked to avoid version incompatibilities.

AVbin allows programs that require dynamic linkage to use FFmpeg.  It does this by providing

  * an accurate version number within the shared library, allowing applications to select the appropriate data structures and functions to use at runtime, and
  * a simplified interface with an unchanging ABI to the most common decoding functionality within FFmpeg.

AVbin is distributed as a single dynamic library (.so on Linux, .dylib on Mac OS X, and .dll on Windows) that depends on no other files or installations.  This eliminates the many complexities of building FFmpeg on platforms other than Linux; however you can still build it from source if you prefer.

## For users ##

Download the appropriate binary package from the downloads page.

  * Windows users, this is **avbin-win32-5.zip**
  * Mac OS X users, this is **avbin-darwin-universal-5.zip**
  * Linux users, this is either **avbin-linux-x86-32-5.tar.gz** or **avbin-linux-x86-64-5.tar.gz**

Inside the archive you will find a single shared library, which needs to be copied into the appropriate directory for your system.  Details can be found in the accompanying readme file.

## For developers ##

You can use AVbin in one of two ways.  Linking against the avbin shared library provides all libavcodec, libavutil and libavformat functions.  You can use the `avbin_get_ffmpeg_revision` function to determine the exact version of FFmpeg that has been linked, and use the appropriate data structures and functions.

Because the FFmpeg interface changes quite quickly, AVbin also provides a simpler interface that is guaranteed to be backward and forward compatible with future releases.  The source release contains a header file and HTML documentation for this interface.