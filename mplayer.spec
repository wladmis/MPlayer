# -*- rpm-spec -*-
# $Id: MPlayer,v 1.92 2004/07/22 05:43:22 grigory Exp $

%define COMPAT_GCC 0

# Optional features
%define WITH_LIRC 1
%define WITH_DXR 0

%define WITH_FFMPEG_STATIC 1
%define WITH_FFMPEG_DYNAMIC 0

%define WITH_ARTS 1

%define WITH_SDL 1

%define codec w32codec

%define real_version 1.0
%define pre_release pre5

Name: MPlayer
Version: %real_version
Release: alt13.%pre_release

Summary: %name - Video player for LINUX
License: GPL for all but not for OpenDivX
Group: Video
URL: http://www.mplayerhq.hu

Source0: %name-%version%pre_release.tar.bz2
Source2: %name.menu
Source3: cp1251-font.tar.bz2
Source4: default-1.7.tar.bz2
Source5: mplayer.sh
Patch1: %name-tinfo.patch
Patch2: %name-dvd-ru.patch

# REMOVE ME
#BuildArch: i686

# If you have divx4linux uncoment next line
#BuildRequires: divx4linux

# Automatically added by buildreq on Thu Jul 15 2004
BuildRequires: glib-devel ms-fonts-ttf pkgconfig univga-fonts-bitmap dmtr40in-fonts

BuildRequires: XFree86-devel XFree86-libs aalib-devel directfb-devel esound-devel
BuildRequires: freetype2-devel glib2-devel gtk+-devel libGLwrapper
BuildRequires: libalsa-devel libaudio-devel libaudiofile-devel libcdparanoia-devel
BuildRequires: libdirectfb libdv-devel libdvdcss-devel libjpeg-devel liblame-devel
BuildRequires: libogg-devel libpng-devel libslang libvorbis-devel libungif-devel
BuildRequires: xvid-devel zlib-devel

BuildRequires: libtinfo-devel fontconfig fontconfig-devel freetype2 libexpat
BuildRequires: libdvdread-devel libdvdnav-devel
BuildRequires: kernel-headers-dvb

%if %WITH_LIRC
BuildRequires: liblirc-devel
%endif
%if %COMPAT_GCC
BuildRequires: cpp2.95 gcc2.95
%else
BuildRequires: cpp3.3 gcc3.3 gcc3.3-c++
%endif

%if %WITH_ARTS
BuildRequires: libarts-devel
%endif

%if %WITH_SDL
BuildRequires: libSDL-devel, libSDL_mixer-devel
%endif

%if %WITH_FFMPEG_DYNAMIC
BuildRequires: ffmpeg-devel
%endif

Autoreq: yes, noperl

%description
MPlayer is a movie player for LINUX (runs on many other Unices, and
non-x86 CPUs, see section 6). It plays most MPEG, VOB, AVI, VIVO, ASF/WMV,
QT/MOV, FLI, RM, NuppelVideo, yuv4mpeg, FILM, RoQ files, supported by many
native, XAnim, and Win32 DLL codecs. You can watch VideoCD, SVCD, DVD,
3ivx, and even DivX movies too (and you don't need the avifile library at
all!). The another big feature of mplayer is the wide range of supported
output drivers. It works with X11, Xv, DGA, OpenGL, SVGAlib, fbdev, AAlib,
DirectFB, but you can use GGI and SDL (and this way all their drivers) and
some lowlevel card-specific drivers (for Matrox, 3Dfx and Radeon) too!
Most of them supports software or hardware scaling, so you can enjoy
movies in fullscreen. MPlayer supports displaying through some hardware
MPEG decoder boards, such as the DVB and DXR3/Hollywood+ ! And what about
the nice big antialiased shaded subtitles (10 supported types!!!) with
european/ISO 8859-1,2 (hungarian, english, czech, etc), cyrillic, korean
fonts, and OSD?

%description -l ru_RU.KOI8-R
MPlayer это проигрыватель фильмов для Linux (movie player for LINUX). Он
играет большинство MPEG, AVI и ASF файлов, поддерживаемых родными и
win32 DLL кодеками. Вы можете смотреть VCD, DVD и даже DivX фильмы. Другая
огромная особенность mplayer'а - широкий диапазон поддерживаемых драйверов
вывода. Он работает с X11, Xv, DGA, OpenGL, SVGAlib, fbdev, но Вы можете
использовать SDL (и таким образом все драйверы SDL к примеру AAlib) и некоторые 
низкоуровневые драйверы видеокарт (к прим.: Matrox)! Большинство из
них поддерживают программное и аппаратное масштабирование, так что Вы можете
наслаждаться фильмами на полном экране. А что говорить об огромном числе
приятных сглаженных затененных субтитров (поддерживат 7 типов) с венгерскими,
английскими, кирилическими, чешскими, корейскими шрифтами и OSD
(On Screen Display - надписи на картинке)?

%package fonts
Summary: Fonts for MPlayer
Group: Video
Requires: MPlayer >= 0.90

%description fonts
cp1251-a cp1251b arpi_osd_a arpi_osd_b fonts for MPlayer


%package gui
Summary: GUI for MPlayer
Group: Video
Requires: MPlayer >= 0.90

%description gui
GUI for MPlayer and default skin

%package doc
Summary: Documentation for MPlayer
Group: Video
Requires: MPlayer >= 0.90

%description doc
Documentation for MPlayer and tools

%prep
%setup -q -n %name-%real_version%pre_release
%patch2 -p0
%__subst 's/\(ldconfig\)/\#\1/g' libdha/Makefile
%__subst 's|$(LIBDIR)/mplayer/vidix|$(LIBBINDIR)/vidix/|g' vidix/drivers/Makefile
%__subst 's|\(/lib/\)mplayer/\(vidix/\)|\1\2|' libvo/Makefile
%__subst 's|/mplayer\(/vidix/\)|\1|' libvo/vosub_vidix.c

%build 
myconfig="--prefix=%_prefix \
	--confdir=%_sysconfdir/%name \
	--datadir=%_datadir/%name \
	--with-win32libdir=%_libdir/%codec \
	--with-extraincdir=/usr/include/dvdcss:/usr/include/dvdnav:/usr/include/dvdread \
	--enable-runtime-cpudetection \
	--enable-mmx \
	--enable-alsa \
	--enable-ossaudio \
	--enable-gui \
	--enable-vidix \
	--enable-iconv \
	--language=en \
	--enable-i18n \
	--enable-nas \
	--enable-dynamic-plugins \
	--enable-largefiles \
	--enable-freetype \
	--enable-dvdread \
	--enable-ftp \
	--enable-divx4linux \
	--enable-dvb \
	--with-dvbincdir=/usr/include/dvb/include"

# FIXME 
%ifarch k6 
myconfig="$myconfig --enable-3dnow"
%else
%ifarch k7
myconfig="$myconfig --enable-3dnow --enable-3dnowex"
%else
myconfig="$myconfig --disable-3dnow --disable-3dnowex"
%endif
%endif

%ifarch i686
myconfig="$myconfig --enable-mmx2 --enable-sse --enable-sse2"
%else
%ifarch i586
myconfig="$myconfig --enable-mmx2 --enable-sse --enable-sse2"
%else
myconfig="$myconfig --disable-mmx2 --disable-sse"
%endif
%endif

%if %COMPAT_GCC
myconfig="$myconfig --cc=kgcc"
%else
myconfig="$myconfig --disable-gcc-checking"
%endif

%if %WITH_FFMPEG_STATIC
myconfig="$myconfig --enable-libavcodec"
%else
myconfig="$myconfig --disable-libavcodec"
%if %WITH_FFMPEG_DYNAMIC
%__subst 's/_libavcodecso=no/_libavcodecso=auto/' configure
%endif
%endif

%if %WITH_ARTS
myconfig="$myconfig --enable-arts"
%else
myconfig="$myconfig --disable-arts"
%endif

%if %WITH_LIRC
myconfig="$myconfig --enable-lirc"
%else
myconfig="$myconfig --disable-lirc"
%endif

%if %WITH_DXR
myconfig="$myconfig --enable-dxr3"
%else 
myconfig="$myconfig --disable-dxr3"
%endif

# no configure macro here 'cause suboptimal cflags
./configure $myconfig

echo | %__make

%install 
%__mkdir_p %buildroot{%_libdir,%_sysconfdir/bashrc.d}
%makeinstall \
	BINDIR=%buildroot%_bindir \
	MANDIR=%buildroot%_mandir \
	DATADIR=%buildroot%_datadir/%name \
	CONFDIR=%buildroot%_sysconfdir/%name \
	LIBBINDIR=%buildroot%_libdir

find etc DOCS TOOLS -type f -exec %__chmod 644 {} \;

%__install -m0644 etc/*.conf %buildroot%_sysconfdir/%name/

# Menus
%__install -p -m0644 -D %SOURCE2 %buildroot%_menudir/%name
%__install -p -m0644 -D Gui/mplayer/pixmaps/icon.xpm %buildroot%_iconsdir/%name.xpm

# Russian font, that uses to show subscriptions 
%__tar xjf %SOURCE3 -C %buildroot%_datadir/%name

# Default Skin for gmplayer
%__tar xjf %SOURCE4 -C %buildroot%_datadir/%name/Skin

# bashrc.d mplayer profile, added soundwrapper
%__install -p -m 0755 %SOURCE5 %buildroot%_sysconfdir/bashrc.d/

# Delete dublicated binaries, they identical
%__ln_s -f mplayer %buildroot%_bindir/gmplayer

%files
%doc etc README
%dir %_sysconfdir/%name
%dir %_libdir/vidix
%dir %_datadir/%name
%config %_sysconfdir/%name/*
%_sysconfdir/bashrc.d/*
%_bindir/m*
%_man1dir/*
%_libdir/*.so*
%_libdir/vidix/*

%files fonts
%_datadir/%name/font*

%files gui
%dir %_datadir/%name/Skin
%_bindir/g*
%_menudir/*
%_iconsdir/*
%_datadir/%name/Skin/*

%files doc
%doc DOCS TOOLS

%changelog
* Thu Jul 22 2004 Grigory Milev <week@altlinux.ru> 1.0-alt13.pre5
- move docs to separated package

* Thu Jul 15 2004 Grigory Milev <week@altlinux.ru> 1.0-alt12.pre5
- new version released
- For more changes view package ChangeLog

* Mon Jun 28 2004 Grigory Milev <week@altlinux.ru> 1.0-alt11.pre4
- fix build requires for dvb support

* Mon Jun 07 2004 Yuri N. Sedunov <aris@altlinux.ru> 1.0-alt10.pre4
- rebuild against libdv-0.102

* Fri Apr 30 2004 Grigory Milev <week@altlinux.ru> 1.0-alt9.pre4
- new version released

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







