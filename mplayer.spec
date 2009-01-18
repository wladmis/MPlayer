# -*- rpm-spec -*-
# $Id: MPlayer,v 1.120 2005/04/21 05:28:34 grigory Exp $

%define base_version	1.0
%define real_version	%base_version
%define release		alt22
%define pre_release	pre7try2
%define skin_version	1.7
%define skin_release	alt1

%define fversion	%real_version

# Used only for CVS builds
# define cvsbuild 20031202
# define ffmpeg_version 20031202

%ifdef pre_release
%global real_version	%real_version%pre_release
%global release		%release.%pre_release
%global fversion	%base_version%pre_release
%endif

#ifdef cvsbuild
#global	real_version	%real_version%pre_release
#global release		%release.%cvsbuild
#global	fversion	%cvsbuild
#endif

# Conditional build (--enable/--disable option)
#
# ... mencoder		- unconditionally enable mencoder
# ... gui               - unconditionally build gui gtk+ interface
# ... largefiles	- unconditionally enable large files (>2GB) support
# ... termcap		- unconditionally enable termcap/tinfo support
# ... iconv		- unconditionally enable iconv(3) function
# ... setlocale		- autodetect setlocale
# --disable lirc	- disable lirc support (default: enabled)
# ... lircc		- autodetect LIRC Client Daemon input
# ... joystick		- unconditionally disable joystick support
# --disable tv		- disable TV Interface (tv/dvb grabbers) (default: enabled)
# ... tv_v4l            - autodetect Video4Linux TV Interface support
# ... tv_v4l2		- autodetect Video4Linux2 TV Interface support
# ... edl		- unconditionally enable EDL (edit decision list) support
# ... rtc		- unconditionally enable RTC (/dev/rtc) on Linux
# --disable network	- disable network support (for: http/mms/rtp) (default: enabled)
# --disable smb		- disable Samba (libsmbclient) support (default: enabled)
# ... live		- unconditionally disable LIVE.COM Streaming Media support 
# --disable dvdread	- disable libdvdread support (default: enabled)
# --disable mpdvdkit	- disable internal mpdvdkit (default: enabled)
# --disable cdparanoia	- disable support CDDA reading using cdparanoia (default: enabled)
# --disable freetype	- disable freetype2 font rendering support (default: enabled)
# --disable fontconfig  - disable font lookup support (default: enabled)
# ... unrarlib		- unconditionally enable unrar file library
# --disable menu	- disable OSD menu support (NOT DVD MENU) (default: enabled)
# ... sortsub		- unconditionally enable subtitles sorting
# ... fribidi		- unconditionally disable FriBiDi support
# ... inet6		- autodetect inet6 support
# ... gethostbyname2	- autodetect missing gethostbyname()
# ... ftp		- unconditionally enable FTP support
#
# --disable cpu_detection - disable runtime CPU detection (default: enabled)
# --enable  k6		- build K6-optimized package as i586 arch (default: disabled)
# --disable mmx         - do not build MMX-optimized package (default: build)
# --disable mmx2	- do not build MMX2-optimized package (default: build)
# --disable 3dnow	- do not build 3DNow!-enabled package (defaut: build)
# --disable 3dnowex	- do not build 3DNowEx!-enabled package (defaut: build)
# --disable sse		- do not build SSE-enabled package (default: build)
# --disable sse2	- do not build SSE2-enabled package (default: build)
# --enable  altivec     - build Altivec-enabled package (default: do not build on x86)

# --enable  debug	- enable full debugging info (default: disabled)
# ... i18n		- unconditinally enable _experimental_ gnu gettext() support
# --disable dynamic_plugins	- disable dynamic a/v plugins (default: enabled)

#
# ... 3dfx              - unconditionally disable obsolete /dev/3dfx support
# --disable aalib	- disable aalib video output (default: enabled)
# ... bl                - uncoditionally disable Blinkenlights support
# --disable directfb	- disable DirectFB video output (default: enabled)
# --disable dvb		- disable DVB-Card output (HEAD version!) (default: FIX: TEMPORARILY DISABLED)
# ... dxr2              - autodetect DXR2 render support
# --disable dxr3	- disable DXR3/H+ render support (default: FIX: TEMPORARILY DISABLED)
# --disable fbdev	- enable FBDev render support (default: enabled) 
# --enable  ggi		- enable ggi video output (default: disabled)
# --disable gl		- disable OpenGL video output (default: enabled)
# ... mga               - unconditionally enabled mga_vid (for Matrox G200/G4x0/G550)
# ... xmga              - unconditionally enabled mga_vid X Window support
# --disable sdl		- disable SDL video/audio output (default: enabled)
# --enable  svga	- enable svgalib video output (default: disabled)
# ... tdfxfb            - unconditionally disabled tdfxfb (Voodoo 3/banshee) support
# ... tdfxvid           - unconditionally disabled ??? tdfx vid support
# --disable tga         - disable targa output support (default: enabled)
# ... vesa              - autodetect VESA support
# --disable vidix	- disable vidix video output (default: enabled)
# ... vm                - unconditionally enabled XF86VidMode support for X11
# ... x11               - autodetect X11 render support
# ... xinerama          - autodetect Xinerama support
# ... xv                - unconditionally enabled Xv render support
# ... xvmc              - unconditionally enabled XvMC acceleration
# ... zr                - autodetect ZR360[56]7/ZR36060 support

# ... ossaudio          - autodetect OSS sound support 
# --disable alsa	- disable ALSA support (default: enabled)
# --disable arts	- disable aRts support (default: enabled)
# --disable esd		- disable EsounD support (default: enabled)
# ... nas               - autodetect NAS sound support
# --disable select	- disable audio select() support (ALSA and Vortex2 drivers require this option)  (default: enabled)

# --disable gif		- disable GIF89a input/output support (default: enabled)
# --disable png		- disable PNG input/output support (default: enabled, enabled automatically for GUI)
# --disable jpeg	- disable JPEG input/output support (default: enabled)
# --disable lzo		- enable external LZO codec (default: enabled)
# --disable win32	- disable support for win32 codecs (default: enabled)
# --disable dshow	- disable support for DirectShow codecs (default: enabled)
# --disable qtx		- disable support for QuickTime codecs (default: enabled)
# --enable  xanim	- enable support for XAnim codecs (default: disabled)
# --disable real	- disable support for RealPlayer codecs (default: enabled)
# --disable xvid	- disable external xvid codec (default: enabled)
# --enable  divx4linux	- enable external divx4linux codec (DivX4Linux) (default: disabled)
# ... opendivx          - unconditionally disabled _old_ OpenDivx codec
# ... libavcodec        - unconditionally enabled libavcodec
# --disable fame	- disable fame realtime encoder (default: enabled)
# --disable vorbis	- disable external Ogg/Vorbis codec (default: enabled)
# ... tremor		- unconditionally disable integer-only OggVorbis support
# ... theora		- autodetect Ogg/Theora
# --disable matroska	- disable support for Matroska files (default: enabled)
# --enable  internal_matroska - enable internal support for Matroska (default: use external)
# --disable faad	- disable FAAD2(AAC) codec (default: enabled)
# --enable  internal_faad  - enable internal FAAD2 codec (default: use external)
# --disable libdv       - disable libdv 0.9.5 en/decoding support (default: enabled)
# --disable mad		- disable MAD support (default: enabled)
# --disable xmms	- disable XMMS input plugins support (default: enabled)

# FLAC support is in ffmpeg, so there's no need in libmpflac and external library
# Obsolete:
# --enable  flac	- disable FLAC codec (default: disabled)
# --enable  external_flac  - enable external FLAC codec (default: use internal, BTW: WHY?!)

%ifnarch %ix86
%force_disable win32
%force_disable cpu_detection
%force_disable mmx
%force_disable mmx2
%force_disable 3dnow
%force_disable 3dnowex
%force_disable sse
%force_disable sse2
%endif

%ifnarch ppc
%force_disable altivec
%endif

%def_enable  lirc
%def_enable  tv
%def_enable  network
%def_disable  smb
%def_enable  dvdread
%def_enable  mpdvdkit
%def_enable  cdparanoia
%def_enable  freetype
%def_enable  fontconfig
%def_enable  menu

%def_enable  cpu_detection
%def_enable  k6
%def_enable  mmx
%def_enable  mmx2
%def_enable  3dnow
%def_enable  3dnowex
%def_enable  sse
%def_enable  sse2
%def_disable altivec
%def_disable debug
%def_enable  dynamic_plugins

%def_disable aalib
%def_enable  directfb
%def_enable  dvb
%def_disable  dxr3
%def_enable  fbdev
%def_disable ggi
%def_enable  gl
%def_enable  sdl
%def_disable svga
%def_enable  tga
%def_enable  vidix

%def_enable  alsa
%def_enable  arts
%def_enable  esd
%def_enable  select

%def_enable  gif
%def_enable  png
%def_enable  jpeg
%def_enable  lzo
%def_enable  win32
%def_enable  dshow
%def_enable  qtx
%def_disable xanim
%def_enable  real
%def_enable  xvid
%def_disable divx4linux
%def_enable  fame
%def_enable  vorbis
%def_enable  theora
%def_enable  matroska
%def_enable  faad
%def_disable internal_faad
%def_enable  libdv
%def_enable  mad
%def_enable  xmms
%def_enable  jack
#%%def_enable  flac
#%%def_disable external_flac

# The language to use in mplayer: all or, one of: cz de dk en es fr hu nl no pl ro ru
%define	mplang		en

%define win32_libdir	%_libdir/%bname/w32codec
%define xanim_libdir	%_libdir/xanim
%define real_libdir	%_libdir/real

%if_disabled win32
%force_disable	dshow
%force_disable	qtx
%check_def	dshow
%check_def	qtx
%endif

%if_disabled matroska
%force_disable	internal_matroska
%check_def	internal_matroska
%endif

%if_disabled faad
%force_disable	internal_faad
%check_def	internal_faad
%endif

#if_disabled flac
#force_disable	external_flac
#check_def	external_flac
#endif

%define bname		MPlayer
%define fname		MPlayer
%define gui_name	%bname-gui
%define console_name	%bname

%define COMPAT_GCC 0

Name:     %console_name
Version:  %base_version
Release:  %release

Summary:  %bname is the Unix video player (console version)
Summary(ru_RU.KOI8-R): %bname - ��� ��������� ���������� (���������� �������)
License: GPL for all but not for OpenDivX
Group:    Video
URL:      http://www.mplayerhq.hu
Provides: %bname = %real_version
Provides: %bname = %base_version
# KPlayer doesn't work well w/ GUI-enabled version
Provides: %bname-console = %real_version
%if_disabled fontconfig
%if_enabled freetype
Requires: urw-fonts
%endif
%endif

Source0:  %bname-%fversion.tar.bz2
#ifdef %cvsbuild
#Source1:  http://prdownloads.sourceforge.net/ffmpeg/ffmpeg-%ffmpeg_version.tar.bz2
#endif
Source2:  %bname.menu
Source3:  cp1251-font.tar.bz2
Source4:  default-%skin_version.tar.bz2
Source5:  mplayer.sh
Source6:  http://icculus.org/~jcspray/gnome-mplayer-32.png
Source7:  http://icculus.org/~jcspray/gnome-mplayer-48.png
Source8:  http://icculus.org/~jcspray/gnome-mplayer-16.png
Patch1:   MPlayer-1.0pre5-alt-external_fame.patch
Patch2:   MPlayer-dvd-ru.patch
Patch3:   MPlayer-1.0pre4-alt-explicit_gif.patch
Patch4:   MPlayer-1.0pre5-alt-translation.patch
Patch5:   MPlayer-1.0pre4-alt-explicit_termcap.patch
Patch6:   MPlayer-1.0pre4-alt-artsc_ldflags.patch
Patch11:  mplayer-rpm-cvs.patch
Patch12:  MPlayer-1.0pre5-alt-gcc-check.patch

Patch13:  MPlayer-1.0pre5-nodebug.patch
#Patch14:  mplayer-lavc.patch
#Patch15:  mplayer-gui.patch
# Patch16:  MPlayer-1.0pre5-warnings.patch
# Patch17:  MPlayer-1.0pre5-loader.patch
# Patch18:  mplayer-loader-printf.patch
Patch19:  mplayer-libmpdvdkit2.patch
# Patch20:  MPlayer-1.0pre4-printf-format.patch
# Patch21:  MPlayer-1.0pre5-warnings-printf.patch
Patch23:  ad_pcm_fix_20050826.diff

BuildRequires: xorg-x11-devel xorg-x11-mesaGL

# termcap/tinfo
BuildRequires: libtinfo-devel
BuildRequires: pkgconfig
#

%if_enabled lirc
BuildRequires: liblirc-devel
%endif

%if_enabled tv
BuildRequires: glibc-kernheaders
%endif

# tv_v4l

# tv_v4l2

# network

%if_enabled smb
# Earlier builds conflicts w/ glibc-2.3
BuildRequires: libsmbclient-devel >= 3.0.3-alt1
%endif

%if_enabled dvdread
BuildRequires: libdvdread-devel 
#BuildRequires: libdvdcss-devel libdvdnav-devel
%endif

# mpdvdkit

%if_enabled cdparanoia
BuildRequires: libcdparanoia-devel
%endif

%if_enabled freetype
BuildRequires: freetype2-devel >= 2.0.9
%endif

%if_enabled fontconfig
BuildRequires: fontconfig-devel
%endif


%if_enabled aalib
BuildRequires: aalib-devel
%endif

%if_enabled directfb
BuildRequires: directfb-devel
%endif

%if_enabled dvb
BuildRequires: kernel-headers-dvb
%endif

%if_enabled dxr3
BuildRequires: libdxr3-devel
%endif

%if_enabled fbdev
#BuildRequires:
%endif

%if_enabled ggi
BuildRequires: libggi-devel
%endif

%if_enabled gl
BuildRequires: Mesa-devel
%endif

%if_enabled sdl
BuildRequires: libSDL-devel >= 1.1.7
BuildRequires: libSDL_mixer-devel
%endif

%if_enabled svga
BuildRequires: svgalib-devel
%endif

# tga

# vidix

%if_enabled jack
BuildRequires: jackit-devel
%endif

%if_enabled alsa
BuildRequires: libalsa-devel
%endif

%if_enabled arts
BuildRequires: libarts-devel
%endif

%if_enabled esd
BuildRequires: esound-devel
%endif


%if_enabled gif
BuildRequires: libungif-devel
%endif

%if_enabled png
BuildRequires: libpng3-devel
%endif

%if_enabled jpeg
BuildRequires: libjpeg-devel
%endif

%if_enabled lzo
BuildRequires: liblzo-devel
%endif

# win32

# dshow

# qtx

# xanim

# real

%if_enabled xvid
BuildRequires: xvid-devel
%endif

%if_enabled divx4linux
BuildRequires: divx4linux-devel
%endif

%if_enabled fame
BuildRequires: libfame-devel
%endif

%if_enabled vorbis
BuildRequires: libogg-devel libvorbis-devel
%endif

%if_enabled theora
BuildRequires: libtheora-devel
%endif

%if_enabled faad
%if_disabled internal_faad
BuildRequires: libfaad-devel
%endif
%endif

%if_enabled libdv
BuildRequires: libdv-devel
%endif

%if_enabled mad
BuildRequires: libmad-devel
%endif

%if_enabled xmms
BuildRequires: libxmms-devel
%endif

#if_enabled external_flac
#BuildRequires: libflac-devel
#endif

# Automatically added by buildreq on Fri Sep 05 2003
# Manually edited by AM
BuildRequires: zlib-devel

BuildRequires: libGLwrapper
#BuildRequires: libaudio-devel libaudiofile-devel
BuildRequires: liblame-devel

%if %COMPAT_GCC
BuildRequires: cpp2.95 gcc2.95 gcc2.95-c++
%else
BuildRequires: cpp >= 3.2 gcc >= 3.2 gcc-c++ >= 3.2
%endif

# rename options for automatic use in configure parameters
%if_enabled lzo
%force_enable liblzo
%endif

%if_disabled lzo
%force_disable liblzo
%endif

%if_enabled aalib
%force_enable aa
%endif

%if_disabled aalib
%force_disable aa
%endif

%if_enabled fame
%force_enable libfame
%endif

%if_disabled fame
%force_disable libfame
%endif

%if_enabled dvb
%force_enable dvbhead
%endif

%if_disabled dvb
%force_disable dvbhead
%endif

# if %WITH_FFMPEG_DYNAMIC
# BuildRequires: ffmpeg-devel
# endif

Autoreq: yes, noperl

%description
MPlayer is a movie and animation player that supports a wide range of file
formats, including AVI, MPEG, and Quicktime. It has many MMX/SSE/3DNow! etc.
optimized native audio and video codecs, but allows using XAnim's and
RealPlayer's binary codec plugins, and Win32 codec DLLs. It has basic
VCD/DVD playback functionality, including DVD subtitles, but supports many
text-based subtitle formats too.

For video and audio output, nearly every existing interface is
supported including some low-level card-specific drivers
(for Matrox, Nvidia, 3Dfx and Radeon, Mach64, Permedia3), hardware AC3
decoding and few hardware MPEG decoding boards such as DVB and
DXR3/Hollywood+.

It also supports video grabbing from V4L devices.

This package provides only console version of the MPlayer. Install
%gui_name *instead* if you need a nice skinnable GUI player

%description -l ru_RU.KOI8-R
MPlayer - ��� ������������������, ������� ������������ ������� ������
�������� ������, � ��� ����� AVI, MPEG � Quicktime. � ���� ��������
��������� �����- � ������������, ���������������� ��� MMX, SSE, 3DNow!
�.�.�. ����� �����, ������� ����������� ������������� ������� �������:
XAnim, RealPlayer � Win32. ����������� �������� ������� ���
������������ VCD/DVD, ������� �������� DVD, � ����� ��������� ������
��������� �������� ���������.

�������������� ����������� ��� ������� ������ ����������� � ����� �
�������������� ��������. ������� �������������� ������������������
�������� ��� ��������� ���������: Matrox, Nvidia, 3Dfx, Radeon,
Mach64, Permedia3, - ����������� ������������� AC3, � ����� ����������
����, ��������� ������������ MPEG, ����� ��� DVB � DXR3/Hollywood+.

����� �����, MPlayer �������� ����������� ������ � ��������� V4L.

���� ����� �������� ������ ���������� ������ MPlayer. ��� �������
������������� ����� %gui_name *������* ������� ������, ���� ���
��������� ������������������ � ������� ������������� GUI (�����������
����������� ������������)

%package -n %gui_name
Summary:  %bname is the Unix video player (GUI version)
Summary(ru_RU.KOI8-R): %bname - ��� ��������� ���������� (GUI �������)
License:  GPL for all but not for OpenDivX
Group:    Video
Requires: %bname-skin %bname-console = %real_version
Provides: %bname = %real_version
Provides: %bname = %base_version
BuildRequires: XFree86-devel XFree86-libs gtk+-devel glib-devel
BuildRequires: libpng3-devel
Requires: gtk+ >= 1.2.0
%if_enabled sdl
Requires: libSDL >= 1.1.7
%endif

%description -n %gui_name
MPlayer is a movie and animation player that supports a wide range of file
formats, including AVI, MPEG, and Quicktime. It has many MMX/SSE/3DNow! etc.
optimized native audio and video codecs, but allows using XAnim's and
RealPlayer's binary codec plugins, and Win32 codec DLLs. It has basic
VCD/DVD playback functionality, including DVD subtitles, but supports many
text-based subtitle formats too.

For video and audio output, nearly every existing interface is
supported including some low-level card-specific drivers
(for Matrox, Nvidia, 3Dfx and Radeon, Mach64, Permedia3), hardware AC3
decoding and few hardware MPEG decoding boards such as DVB and
DXR3/Hollywood+.

It also supports video grabbing from V4L devices.

This package provides GUI version of the MPlayer. A console-only
version with trimmed down dependencies is also available as
%console_name

%description -n %gui_name -l ru_RU.KOI8-R
MPlayer - ��� ������������������, ������� ������������ ������� ������
�������� ������, � ��� ����� AVI, MPEG � Quicktime. � ���� ��������
��������� �����- � ������������, ���������������� ��� MMX, SSE, 3DNow!
�.�.�. ����� �����, ������� ����������� ������������� ������� �������:
XAnim, RealPlayer � Win32. ����������� �������� ������� ���
������������ VCD/DVD, ������� �������� DVD, � ����� ��������� ������
��������� �������� ���������.

�������������� ����������� ��� ������� ������ ����������� � ����� �
�������������� ��������. ������� �������������� ������������������
�������� ��� ��������� ���������: Matrox, Nvidia, 3Dfx, Radeon,
Mach64, Permedia3, - ����������� ������������� AC3, � ����� ����������
����, ��������� ������������ MPEG, ����� ��� DVB � DXR3/Hollywood+.

����� �����, MPlayer �������� ����������� ������ � ��������� V4L.

���� ����� �������� ������ MPlayer c GUI (����������� �����������).
����� ������� %console_name - ���������� ������ ������ � �������
������ ������������.

%package -n mencoder
Group: Video
Summary: MEncoder is a movie encoder for Unix.
Summary(ru_RU.KOI8-R): MEncoder - ��� ���������� ������� ��� Unix.
Requires: %bname = %base_version

%description -n mencoder
MEncoder a movie encoder for Unix and is a part of the MPlayer package.


%package doc
Group: Video
Summary: MPlayer docs
Summary(ru_RU.KOI8-R): %bname-doc - ������������ � ������ %bname
Requires: %bname = %base_version

%description doc
MPlayer docs

%if_enabled freetype
%package -n %bname-fonts
Group: Video 
Summary: fonts and font tools for the MPlayer
BuildRequires: freetype2-devel >= 2.0.9
Requires: %bname

%description -n %bname-fonts
Fonts and font tools for use with MPlayer.

Currently included:
* mplayer_subfont	a tool for creating OSD fonts
%endif

%package -n %bname-vidix
Group: Video 
Summary: VIDeo Interface for *nIX
Requires: %bname = %version-%release
Requires: %bname-vidix-driver

%description -n %bname-vidix
VIDIX is the abbreviation for VIDeo Interface for *niX.

VIDIX was designed and introduced as an interface for fast user-space
drivers providing DGA. Hopefully these drivers will be as portable as
X11 (not only on *nix).

Basic features:
* It's a portable successor of mga_vid technology, but it's located in
  user-space. 
* Unlike X11 it provides DGA everywhere it's possible
* Unlike v4l it provides interface for video playback
* Unlike linux's drivers it uses the math library

%description -n %bname-vidix -l ru_RU.KOI8-R
VIDIX - ��� ������������ ��� VIDeo Interface for *niX (����� ���������
��� �������������� ������������ ������)

VIDIX ��� ������������� � ���������� ��� ��������� ��� �������
��������� ������ ���������� ��� DGA (Direct Graphics Access - ������
������ � �������). ��������������, ��� ��� �������� ����� �����
���������� ��� � X11 (�� ������ �� �����).

�������� ��������������:
* ��� ����������� �������� ���������� mga_vid, ���������� �� ������
  ����������
* � ������� �� X11 �� ������������� DGA �����, ��� ��� ��������
* � ������� �� v4l �� ������������� ��������� ��� ���������������
  �����
* � ������� �� ��������� ������ �� ���������� ���������� math

%package -n %bname-vidix-trident
Group: Video
Summary: VIDIX driver for Trident Cyberblade i1
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-trident
VIDIX driver for Trident Cyberblade i1.

%package -n %bname-vidix-mach64
Group: Video
Summary: VIDIX driver for ATI Mach64
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-mach64
VIDIX driver for ATI Mach64.

%package -n %bname-vidix-mga
Group: Video
Summary: VIDIX drivers for Matrox Gxxx series
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-mga
Two VIDIX drivers for Matrox Gxxx series (using BES and CRTC2).

%package -n %bname-vidix-permedia
Group: Video
Summary: VIDIX driver for 3DLabs Permedia3 cards
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-permedia
VIDIX driver for 3DLabs GLINT R3/Permedia3 driver.

%package -n %bname-vidix-radeon
Group: Video
Summary: VIDIX driver for ATI Radeon
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-radeon
VIDIX driver for ATI Radeon.

%package -n %bname-vidix-rage128
Group: Video
Summary: VIDIX driver for ATI Rage128
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-rage128
VIDIX driver for ATI Rage128.

%package -n %bname-vidix-savage
Group: Video
Summary: VIDIX driver for ATI Savage
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-savage
VIDIX driver for ATI Savage.

%package -n %bname-vidix-nvidia
Group: Video
Summary: VIDIX driver for nVidia chips (experimental)
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-nvidia
VIDIX driver for nVidia chips (experimental)

%package -n %bname-vidix-sis
Group: Video
Summary: VIDIX driver for SiS chips (experimental)
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-sis
VIDIX driver for SiS chips (experimental)

%package -n %bname-vidix-unichrome
Group: Video
Summary: VIDIX driver for Unichrome
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-unichrome
VIDIX driver for Unichrome.

%package -n %bname-skin-default
Summary: Default skin for %gui_name
Summary(ru_RU.KOI8-R): ������� "������" ��� %gui_name
Group: Video
Provides: %bname-skin
Version: %skin_version
Release: %skin_release
%description -n %bname-skin-default
Default skin for %gui_name

%description -n %bname-skin-default -l ru_RU.KOI8-R
������� ������� ���������� ("������") ��� %gui_name

%prep
#ifdef cvsbuild
# CVS Build
#setup -q -n %fname-%fversion -a 1
## needed with CVS snapshots
#cp -ar ffmpeg/libavcodec .
#else
# A Release Build
%setup -q -n %fname-%fversion
#endif

%patch1 -p1
%patch2 -p0
%patch3 -p1
#%patch4 -p1
%patch5 -p1
%patch6 -p1

# Patches 11/12 are mutually exclusive
%ifdef cvsbuild
%patch11 -p1 -b .r
%else
cat >version.sh <<EOF
#!/bin/sh
echo "#define VERSION \\"%real_version-RPM-\$1\\"" >version.h
EOF
chmod +x version.sh
%endif
#%patch12 -p1

# %patch13 -p1 -b .nodebug
# %patch14 -p1 -b .lavc
#%{!?_without_gui:%patch15 -p1 -b .gui}
# %patch16 -p1 -b .warn
# %patch17 -p1 -b .loader
# %patch18 -p1 -b .loader-printf
%patch19 -p1 -b .mpdvdkit2
# %patch20 -p1 -b .printf-format
# %patch21 -p1 -b .printf
# %patch23 -p0

%__subst 's/\(ldconfig\)/\#\1/g' libdha/Makefile

# I hope that vidix drivers are really as portable as it was claimed above
%__subst 's|$(LIBDIR)/mplayer/vidix|$(LIBDIR)/vidix/|g' vidix/drivers/Makefile
%__subst 's|\(/lib/\)mplayer/\(vidix/\)|\1\2|' libvo/Makefile
%__subst 's|/mplayer\(/vidix/\)|\1|' libvo/vosub_vidix.c

%build
%if_disabled debug
%ifarch %ix86
%{?_enable_k6:RPM_OPT_FLAGS="-O2 -march=k6"}
%endif

# this is equivalent to -O3
CFLAGS="-Wall -Wno-unused-variable -Wno-unused-function -Wno-unused-label -Wno-uninitialized -Wno-trigraphs"
#" -W -Wfloat-equal"
CFLAGS="$CFLAGS $RPM_OPT_FLAGS -fomit-frame-pointer -ffast-math -finline-functions -frename-registers"
%ifnarch mips
CFLAGS="$CFLAGS -pipe"
%endif
export CFLAGS
%endif # if_disabled debug

%if %COMPAT_GCC
CC=gcc-2.95
%else
# A hard time of detection installed C compiler version...
VERSION=`gcc -dumpversion | cut -d '.' -f 1,2 | sed -e 's/\.//'`
if test -n "$VERSION" -a $VERSION -gt 32 ; then
	CC=gcc
else
	for CC in gcc-3.4 gcc-3.3 gcc-3.2 gcc-badversion; do
		if which $CC >/dev/null; then
			break
		fi
	done
	if test "X$CC" = "Xgcc-badversion"; then
		echo "Unable to find an appropriate gcc version (>= 3.2)" >&2
		exit 1
	fi
fi
%endif

%if_enabled dvb
CFLAGS="$CFLAGS -I/usr/include/dvb/include"
export CFLAGS
%endif

LC_MESSAGES=C ; export LC_MESSAGES

./configure \
		--enable-gui \
		--enable-termcap \
		--with-termcaplib=tinfo \
		--enable-png \
		--enable-mencoder \
		%{subst_enable libfame} \
		--cc=$CC \
		--prefix=%_prefix \
		--bindir=%_bindir \
		--datadir=%_datadir/%bname \
		--mandir=%_mandir \
		--confdir=%_sysconfdir/%bname \
		--enable-largefiles \
		--enable-iconv \
		%{subst_enable lirc} \
		--disable-joystick \
		%{subst_enable tv} \
		--enable-edl \
		--enable-rtc \
		%{subst_enable network} \
		%{subst_enable smb} \
		--disable-live \
		%{subst_enable dvdread} \
		%{subst_enable mpdvdkit} \
		%{subst_enable cdparanoia} \
		%{subst_enable freetype} \
		%{subst_enable fontconfig} \
		--enable-unrarlib \
		%{subst_enable menu} \
%if_enabled tv
		--enable-tv-v4l \
		--enable-tv-v4l2 \
%endif
%if_enabled cpu_detection
		--enable-runtime-cpudetection \
%else
		--disable-runtime-cpudetection \
%endif
		%{subst_enable mmx} \
		%{subst_enable mmx2} \
		%{subst_enable 3dnow} \
		%{subst_enable 3dnowex} \
		%{subst_enable sse} \
		%{subst_enable sse2} \
		%{subst_enable altivec} \
%if_enabled debug
		--enable-debug=3 \
%endif
		--language=%mplang \
		--enable-i18n \
%if_enabled dynamic_plugins
		--enable-dynamic-plugins \
%else
		--disable-dynamic-plugins \
%endif
		%{subst_enable aa} \
		%{subst_enable directfb} \
		--disable-dvb \
		%{subst_enable dvbhead} \
%if_enabled dvb
		--with-dvbincdir=/usr/include/dvb/include \
%endif
		%{subst_enable dxr3} \
		%{subst_enable fbdeb} \
		%{subst_enable ggi} \
		%{subst_enable gl} \
		--enable-mga \
	        --enable-xmga \
		%{subst_enable sdl} \
		%{subst_enable svga} \
		--disable-tdfxfb \
		--disable-tdfxvid \
		%{subst_enable tga} \
		%{subst_enable vidix} \
		--enable-vm \
		--enable-xv \
		--enable-xvmc \
		%{subst_enable alsa} \
		%{subst_enable arts} \
		%{subst_enable esd} \
		%{subst_enable select} \
		%{subst_enable gif} \
		%{subst_enable jpeg} \
		%{subst_enable liblzo} \
		%{subst_enable win32} \
%{?_enable_win32:	--with-win32libdir=%win32_libdir} \
		%{subst_enable dshow} \
		%{subst_enable qtx} \
		%{subst_enable xanim} \
%{?_enable_xanim:	--with-xanimlibdir=%xanim_libdir} \
		%{subst_enable real} \
%{?_enable_real:	--with-reallibdir=%real_libdir} \
		%{subst_enable xvid} \
		%{subst_enable divx4linux} \
		--disable-opendivx \
		--enable-libavcodec \
		%{subst_enable vorbis} \
		%{subst_enable theora} \
%if_disabled matroska
		--disable-internal-matroska \
%endif
%if_enabled faad
%if_enabled internal_faad
		--enable-internal-faad \
		--disable-external-faad \
%else
		--disable-internal-faad \
		--enable-external-faad \
%endif
%else
		--disable-internal-faad \
		--disable-external-faad \
%endif
		%{subst_enable libdv} \
		%{subst_enable mad} \
		%{subst_enable xmms}


# %if_enabled flac
# 		--enable-flac \
# %if_disabled external_flac
# 		--disable-external-flac	\
# %else
# 		--enable-external-flac \
# %endif
# %else
# 		--disable-flac \
# 		--disable-external-flac \
# %endif

%make_build

%if_enabled freetype
pushd TOOLS/subfont-c
make
popd
%endif

%ifdef cvsbuild
# build HTML documentation from XML files
pushd DOCS/xml
make build-html-chunked
popd
%endif

%install

%ifdef cvsbuild
find . -name CVS | xargs rm -rf
%endif

%makeinstall DESTDIR=%buildroot 

pushd %buildroot%_bindir
ln -sf mplayer gmplayer
popd

# Default Skin for gmplayer
%__mkdir_p %buildroot%_datadir/%bname/Skin
%__tar xjf %SOURCE4 -C %buildroot%_datadir/%bname/Skin

default_vo=xv

sed -e 's/include =.*//' < etc/example.conf \
	| sed -e 's/fs=yes/# fs=yes/' \
	| sed -e "s/# vo=xv/vo=$default_vo/" \
	| sed -e 's|/usr/local/share/mplayer|%_datadir/%bname|g' \
	> %buildroot%_sysconfdir/%bname/mplayer.conf

%if_enabled fontconfig
echo "fontconfig = yes" >> %buildroot%_sysconfdir/%bname/mplayer.conf
%else
echo "fontconfig = no" >> %buildroot%_sysconfdir/%bname/mplayer.conf
%if_enabled freetype
pushd %buildroot%_datadir/%bname
ln -sf ../fonts/default/Type1/n019003l.pfb ./subfont.ttf
popd
%else
# Russian font, that uses to show subscriptions 
%__tar xjf %SOURCE3 -C %buildroot%_datadir/%bname
%endif
%endif

%__install -m 0644 etc/{codecs,input}.conf \
	%buildroot%_sysconfdir/%bname/

%if_enabled menu
%__install -m 0644 etc/menu.conf \
	%buildroot%_sysconfdir/%bname/
%if_enabled dvb
%__install -m 0644 etc/dvb-menu.conf \
	%buildroot%_sysconfdir/%bname/
%endif
%endif

%if_enabled freetype
# install tools
pushd TOOLS/subfont-c
%__mkdir_p %buildroot%_datadir/%bname/fonts/{osd,encodings}
install osd/{gen.py,osd.pfb,README,runme} %buildroot%_datadir/%bname/fonts/osd/
install encodings/* %buildroot%_datadir/%bname/fonts/encodings/
install -m 0755 subfont %buildroot%_bindir/mplayer_subfont
popd
%endif

%__mkdir_p %buildroot%_sysconfdir/bashrc.d

%__install -m 0755 %SOURCE5 %buildroot%_sysconfdir/bashrc.d/

# Menus
%__install -p -m0644 -D %SOURCE2 %buildroot%_menudir/%bname
%__install -p -m0644 -D %SOURCE6 %buildroot%_iconsdir/%bname.png
%__install -p -m0644 -D %SOURCE7 %buildroot%_liconsdir/%bname.png
%__install -p -m0644 -D %SOURCE8 %buildroot%_miconsdir/%bname.png
find etc DOCS TOOLS -type f -exec %__chmod 644 {} \;

# add mencoder.1 man-link
rm -f %buildroot%_man1dir/mencoder.1 ||:
echo ".so mplayer.1" > %buildroot%_man1dir/mencoder.1

# install international manpages and man-links
#for dir in de es fr hu pl zh ; do
#install -d $RPM_BUILD_ROOT%{_mandir}/$dir/man1
#mv DOCS/man/$dir/mplayer.1 $RPM_BUILD_ROOT%{_mandir}/$dir/man1
#echo ".so mplayer.1" > $RPM_BUILD_ROOT%{_mandir}/$dir/man1/mencoder.1
#done

# a tribute to clever python support
unset RPM_PYTHON

%post -n %bname-vidix -p /sbin/ldconfig

%postun -n %bname-vidix -p /sbin/ldconfig

%post -n %gui_name
%update_menus

%postun -n %gui_name
%clean_menus

%files -n %console_name
%doc README AUTHORS
%_bindir/mplayer
%dir %_sysconfdir/%bname
%config %_sysconfdir/%bname/codecs.conf
%config(noreplace) %verify(not size mtime md5) %_sysconfdir/%bname/mplayer.conf
%config(noreplace) %verify(not size mtime md5) %_sysconfdir/%bname/input.conf
%if_enabled menu
%config(noreplace) %verify(not size mtime md5) %_sysconfdir/%bname/menu.conf
%if_enabled dvb
%config(noreplace) %verify(not size mtime md5) %_sysconfdir/%bname/dvb-menu.conf
%endif
%endif
%_sysconfdir/bashrc.d/*
%dir %_datadir/%bname
%if_disabled fontconfig
%if_enabled freetype
%config(missingok,noreplace) %verify(not link size mtime md5) %_datadir/%bname/subfont.ttf
%else
%_datadir/%bname/font
%endif
%endif
%_man1dir/*

%files -n %gui_name
%_bindir/gmplayer
%dir %_datadir/%bname
%dir %_datadir/%bname/Skin
%_iconsdir/%bname.png
%_miconsdir/%bname.png
%_liconsdir/%bname.png
%_menudir/*
%_datadir/applications/mplayer.desktop
%_datadir/pixmaps/mplayer-desktop.xpm

%files -n %bname-skin-default
%dir %_datadir/%bname/Skin
%_datadir/%bname/Skin/default

%files -n mencoder
%doc DOCS/tech/encoding-tips.txt DOCS/tech/swscaler_filters.txt
%doc DOCS/tech/swscaler_methods.txt DOCS/tech/colorspaces.txt
%_bindir/mencoder

%set_verify_elf_method textrel=relaxed

%files doc
%doc DOCS/tech/hwac3.txt DOCS/tech/mpsub.sub DOCS/tech/slave.txt
%doc DOCS/tech/subcp.txt
# HTML and XML-generated docs
%doc DOCS/HTML/en
%lang(de) %doc %dir DOCS/de
%lang(es) %doc %dir DOCS/HTML/es
%lang(fr) %doc %dir DOCS/HTML/fr
%lang(hu) %doc %dir DOCS/HTML/hu
%lang(it) %doc %dir DOCS/it
%lang(pl) %doc %dir DOCS/HTML/pl
%lang(ru_RU.KOI8-R) %doc %dir DOCS/HTML/ru
%lang(zh) %doc %dir DOCS/zh

%if_enabled freetype
%files -n %bname-fonts
%_bindir/mplayer_subfont
%_datadir/%bname/fonts/osd/gen.py
%_datadir/%bname/fonts/osd/osd.pfb
%_datadir/%bname/fonts/osd/README
%_datadir/%bname/fonts/osd/runme
%_datadir/%bname/fonts/encodings/charmap2enc
%_datadir/%bname/fonts/encodings/osd-mplayer
%_datadir/%bname/fonts/encodings/runme-kr
%endif

%if_enabled vidix
%files -n %bname-vidix
%_libdir/libdha.so*

%files -n %bname-vidix-trident
%_libdir/vidix/cyberblade_vid.so

%files -n %bname-vidix-mach64
%_libdir/vidix/mach64_vid.so

%files -n %bname-vidix-mga
%_libdir/vidix/mga_crtc2_vid.so
%_libdir/vidix/mga_vid.so

%files -n %bname-vidix-nvidia
%_libdir/vidix/nvidia_vid.so

%files -n %bname-vidix-permedia
%_libdir/vidix/pm3_vid.so

%files -n %bname-vidix-radeon
%_libdir/vidix/radeon_vid.so

%files -n %bname-vidix-rage128
%_libdir/vidix/rage128_vid.so

%files -n %bname-vidix-savage
%_libdir/vidix/savage_vid.so

%files -n %bname-vidix-sis
%_libdir/vidix/sis_vid.so
%endif

%files -n %bname-vidix-unichrome
%_libdir/vidix/unichrome_vid.so

%changelog
* Sat Nov 26 2005 Grigory Milev <week@altlinux.ru> 1.0-alt22.pre7try2
- update to bugfix version

* Tue Aug 30 2005 Eugene Ostapets <eostapets@altlinux.ru> 1.0-alt21.pre7
- fix CAN-2005-2718

* Thu Apr 21 2005 Grigory Milev <week@altlinux.ru> 1.0-alt20.pre7
- fixed build requires

* Mon Apr 18 2005 Grigory Milev <week@altlinux.ru> 1.0-alt19.pre7
- new version released
- build with v4l
- due compilation errors, temporary build with out aa lib

* Fri Apr 08 2005 Grigory Milev <week@altlinux.ru> 1.0-alt18.pre6a
- add theora support
- add jack support

* Fri Jan 28 2005 Grigory Milev <week@altlinux.ru> 1.0-alt17.pre6a
- new version released

* Thu Jan 20 2005 ALT QA Team Robot <qa-robot@altlinux.org> 1.0-alt16.pre5.1
- Rebuilt with libstdc++.so.6.

* Fri Dec 17 2004 Grigory Milev <week@altlinux.ru> 1.0-alt16.pre5
- rebuild with new directfb

* Fri Dec 17 2004 ALT QA Team Robot <qa-robot@altlinux.org> 1.0-alt15.pre5.1
- Rebuilt with libdirectfb-0.9.so.21.

* Mon Nov 22 2004 Grigory Milev <week@altlinux.ru> 1.0-alt15.pre5
- temporary disable smb client support, due build troubles

* Tue Aug 17 2004 Grigory Milev <week@altlinux.ru> 1.0-alt14.pre5
- rebuild from A.Morozov spec

* Tue Aug 17 2004 Alexey Morozov <morozov@altlinux.org> 1.0-alt13.1.pre5
- release bump to shut up apt :-)

* Sun Aug  8 2004 Alexey Morozov <morozov@altlinux.org> 1.0-alt11.pre5
- new version (1.0pre5)
- some patches were adapted to the new version
- fbdev support is enabled by default

* Mon May 17 2004 Alexey Morozov <morozov@altlinux.org> 1.0-alt11.pre4
- Re-enabled samba support
- Dropped non-gui version because gui doesn't give us additional dependencies

* Tue May  4 2004 Alexey Morozov <morozov@altlinux.org> 1.0-alt10.pre4
- Incorporated patches and ideas for official RPMs of MPlayer
  Re-worked build scheme. Most options are configurable now.
- Handle most video formats from within MPlayer menu file
- Dropped MPlayer's own fonts in the default build (obsolete by
  fontconfig support)
- Preliminary spec-file translation
- smb, dvb and dxr3 support is temporarily disabled due to problems
  with corresponding packages. Brave souls can try to --enable them

* Mon Apr 12 2004 Grigory Milev <week@altlinux.ru> 1.0-alt8.pre3try2
- added dvb support
- rebuild with new libxvidcore

* Wed Mar 31 2004 Grigory Milev <week@altlinux.ru> 1.0-alt7.pre3try2
- remotely exploitable buffer overflow in the HTTP streaming code fixed

* Thu Mar 25 2004 Grigory Milev <week@altlinux.ru> 1.0-alt6.pre3
- rebuild with glib2

* Fri Jan 23 2004 Grigory Milev <week@altlinux.ru> 1.0-alt5.pre3
- added patch for multiplier dvd soudn tracs (thanx Kachalov Anton)

* Mon Jan 19 2004 Grigory Milev <week@altlinux.ru> 1.0-alt4.pre3
- next pre-release

* Tue Oct  7 2003 Grigory Milev <week@altlinux.ru> 1.0-alt3.pre2
- new version released

* Fri Sep 26 2003 Grigory Milev <week@altlinux.ru> 1.0-alt2.pre1.cvs20030926
- build cvs version with fixed "Exploitable remote buffer overflow vulnerability"
- move w32codec to separated package

* Fri Sep  5 2003 Grigory Milev <week@altlinux.ru> 1.0-alt1.pre1
- new version released

* Wed Aug 27 2003 Grigory Milev <week@altlinux.ru> 0.91-alt21
- rebuild with new xvid

* Fri Aug 22 2003 Grigory Milev <week@altlinux.ru> 0.91-alt20
- new version released
- updated default skin

* Tue Jul 29 2003 Grigory Milev <week@altlinux.ru> 0.90-alt20
- rebuild with nas support

* Wed Jun 11 2003 Grigory Milev <week@altlinux.ru> 0.90-alt19
- Rebuild with Lirc enabled

* Mon May 19 2003 Grigory Milev <week@altlinux.ru> 0.90-alt18
- fixed bug with mplayer bash alias, now don't close bash
  after mplayer exit
- can't build with libdvdnav (temporary removed)

* Thu Apr 24 2003 Grigory Milev <week@altlinux.ru> 0.90-alt17
- rebuild with new directfb
- rebuild with libdvdnav and libdvdread

* Mon Apr 14 2003 Grigory Milev <week@altlinux.ru> 0.90-alt16
- working with soundwrapper

* Wed Apr  9 2003 Grigory Milev <week@altlinux.ru> 0.90-alt15
- stable version released

* Wed Mar 19 2003 Grigory Milev <week@altlinux.ru> 0.90-alt14.rc5
- new version released

* Wed Feb 12 2003 Grigory Milev <week@altlinux.ru> 0.90-alt13.rc4
- new version released

* Thu Jan 30 2003 Grigory Milev <week@altlinux.ru> 0.90-alt12.rc3
- recompile with esound support

* Mon Jan 20 2003 Grigory Milev <week@altlinux.ru> 0.90-alt11.rc3
- new version released
- build with English menus, for compatible with non KOI8-R locales
- add --enable-runtime-cpudetection

* Wed Dec 11 2002 Grigory Milev <week@altlinux.ru> 0.90-alt10.rc1
- new version released

* Tue Dec  3 2002 Grigory Milev <week@altlinux.ru> 0.90-alt9.pre10
- rebuild with tinfo

* Fri Nov 15 2002 Grigory Milev <week@altlinux.ru> 0.90-alt8.pre10
- new version released

* Mon Nov  4 2002 Grigory Milev <week@altlinux.ru> 0.90-alt8.pre9
- new version released
- fixed vidix paths

* Wed Sep 25 2002 Grigory Milev <week@altlinux.ru> 0.90-alt8.pre8
- move w32codec, fons and gui to separated packages
- move skins to MPlayer-skins package, move default skin to MPlayer-gui

* Thu Sep 19 2002 Grigory Milev <week@altlinux.ru> 0.90-alt7.pre8
- fixed gui.conf reading
- new version released

* Wed Sep 18 2002 Stanislav Ievlev <inger@altlinux.ru> 0.90-alt6.pre7
- rebuild with new XFree86
- update buildreqs

* Fri Sep  6 2002 Grigory Milev <week@altlinux.ru> 0.90-alt5.pre7
- fix typo
- remove perl and ee from buildrequires

* Fri Sep  6 2002 Grigory Milev <week@altlinux.ru> 0.90-alt4.pre7
- new prerelease version released

* Wed Aug  7 2002 Grigory Milev <week@altlinux.ru> 0.90-alt3.pre6
- new version released

* Mon Jun 10 2002 Grigory Milev <week@altlinux.ru> 0.90pre5-alt2
- added build requires for libSDL
- (inger) hotfixes

* Mon Jun 10 2002 Grigory Milev <week@altlinux.ru> 0.90pre5-alt1
- new version released

* Fri May 17 2002 Grigory Milev <week@altlinux.ru> 0.90pre4-alt1
- new version released
- added options to spec: COMPAT_GCC, WITH_LIRC, WITH_DXR

* Tue May  7 2002 Sergey Bolshakov <s.bolshakov@belcaf.com> 0.90pre3-alt2.1
- tweaks

* Mon May  6 2002 Grigory Milev <week@altlinux.ru> 0.90pre3-alt0.1
- new version released

* Tue Apr 30 2002 Grigory Milev <week@altlinux.ru> 0.90pre2-alt1
- new version released

* Wed Apr 24 2002 Grigory Milev <week@altlinux.ru> 0.90pre1-alt1
- new version released

* Fri Apr 12 2002 Grigory Milev <week@altlinux.ru> 0.60-alt6.cvs20020412
- new cvs snapshot
- change fonts

* Tue Mar 26 2002 Grigory Milev <week@altlinux.ru> 0.60-alt5.cvs20020306
- added buildrequires, for compiling GUI
- added Menu

* Wed Mar 13 2002 Grigory Milev <week@altlinux.ru> 0.60-alt4.cvs20020306
- fix descriptions and summary

* Wed Mar  6 2002 Grigory Milev <week@altlinux.ru> 0.60-alt3.cvs20020306
- new cvs snapshot 2002/03/06
- added dxr3 patch, dxr3 now compiled and work
- added compiled with gui and fbdev
- include two skin for gui
- minor spec cleanup

* Sat Jan  5 2002 Grigory Milev <week@altlinux.ru> 0.60-alt2
- corrected build requires
- fixed error in font.desk from koi8-r-font for subtitles

* Thu Jan  3 2002 Grigory Milev <week@altlinux.ru> 0.60-alt1
- new version released

* Wed Dec 26 2001 Grigory Milev <week@altlinux.ru>  0.60pre1-alt1
- Initial build for ALT Linux distribution.


