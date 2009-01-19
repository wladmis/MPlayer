%define set_disable() %{expand:%%force_disable %{1}} %{expand:%%undefine _enable_%{1}}
%define set_enable() %{expand:%%force_enable %{1}} %{expand:%%undefine _disable_%{1}}
%define subst_enable_with() %{expand:%%{?_enable_%{1}:--enable-%{2}}} %{expand:%%{?_disable_%{1}:--disable-%{2}}}

%define base_version	1.0
%define real_version	%base_version
%define release		1

%define fversion	%real_version

%define cvsbuild 20060710
%define ffmpeg_version svn-20060710

%if %cvsbuild
%global release		0.%cvsbuild.%release
%global	fversion	svn-%cvsbuild
%endif

%define vidixver 0.9.9.1

%def_enable shared_ffmpeg

%def_enable lirc
%def_enable tv
%def_enable network
%def_disable smb
%def_enable dvdread
%def_enable live
%def_enable mpdvdkit
%def_enable cdparanoia
%def_enable freetype
%def_enable fontconfig
%def_enable menu
%def_enable enca

%def_disable k6
%def_disable altivec
%def_disable debug
%def_enable dynamic_plugins

%def_enable aalib
%def_enable caca
%def_enable directfb
%def_enable dvb
%def_disable dxr3
%def_enable fbdev
%def_disable ggi
%def_enable gl
%def_enable sdl
%def_enable svga
%def_enable tga
%def_enable vidix
%def_disable vidix_ext
%def_enable vidix_int
%def_disable vidix_int_drivers

%def_enable alsa
%def_enable arts
%def_enable esd
%def_enable select
%def_enable polyp
%def_enable libdts
%def_enable musepack

%def_enable gif
%def_enable png
%def_enable jpeg
%def_enable lzo
%def_disable xanim
%def_enable real
%def_enable xvid
%def_enable x264
%def_disable divx4linux
%def_enable fame
%def_enable openal
%def_enable vorbis
%def_disable tremor_internal
%def_disable tremor_low
%def_disable tremor_external
%def_enable speex
%def_enable theora
%def_enable faad
%def_disable dirac
%def_disable internal_faad
%def_enable libdv
%def_enable mad
%def_disable xmms
%def_disable dvdnav
%def_without dvdmenu
%def_enable ass # internal SSA/ASS subtitles support
%def_enable jack
%def_enable cpu_detection
%def_enable mmx
%def_enable mmxext
%def_enable 3dnow
%def_enable 3dnowext
%def_enable sse
%def_enable sse2
%def_disable fribidi

%if_disabled vidix
%set_disable vidix_ext
%set_disable vidix_int
%set_disable vidix_int_drivers
%endif
%if_disabled vidix_int
%if_disabled vidix_ext
%set_disable vidix
%endif
%endif
%if_enabled vidix_int
%set_disable vidix_ext
%endif
%if_enabled vidix_ext
%set_disable vidix_int_drivers
%endif

%if_enabled tremor_external
%set_disable tremor_low
%endif

%ifnarch %ix86
%force_disable win32
%check_def win32
%else
%def_enable win32
%endif

%ifnarch ppc
%force_disable altivec
%endif

# The language to use in mplayer: all or, one of: cz de dk en es fr hu nl no pl ro ru
%define	mplang		en

%define win32_libdir	%_libdir/w32codec
%define xanim_libdir	%_libdir/xanim
%define real_libdir	%_libdir/real

%if_disabled win32
%set_disable	directx
%set_disable	qtx
%else
%set_enable	directx
%set_enable	qtx
%endif

%if_disabled faad
%force_disable	internal_faad
%check_def	internal_faad
%endif

%define bname		MPlayer
%define fname		MPlayer
%define gui_name	%bname-gui
%define console_name	%bname

%define COMPAT_GCC 0

%define Name MPlayer
Name:     %console_name
Version:  %base_version
Release:  alt%release
Serial: 1
Summary:  %bname is the Unix video player (console version)
Summary(ru_RU.CP1251): %bname - это настоящий видеоплеер (консольный вариант)
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
# svn checkout svn.mplayerhq.hu/mplayer/trunk
%if %cvsbuild
%{?_disable_shared_ffmpeg:Source1: ffmpeg-%ffmpeg_version.tar.bz2}
# svn checkout svn.mplayerhq.hu/ffmpeg/trunk
%endif
%{?_with_dvdmenu:Source2: mplayer-dvdnav-20060614-patch.tar.bz2}
Source3: cp1251-font.tar.bz2
Source4: standard-1.9.tar.bz2
Source5: mplayer.sh
%{?_enable_vidix_int_drivers:Source6: vidix-%vidixver.tar.bz2}
Source9: ao_polyp.c.bz2
Patch1: MPlayer-svn-20060710-alt-external_fame.patch.gz
Patch2: MPlayer-dvd-ru-20060705.patch.gz
Patch3: MPlayer-1.0pre4-alt-explicit_gif.patch
Patch4: MPlayer-svn-20060707-ext_vidix_drivers-0.9.9.1.patch.bz2
Patch5: vidix-0.9.9.1-pm3_vid.patch.gz
Patch6: MPlayer-1.0pre4-alt-artsc_ldflags.patch
#Patch7: MPlayer-1.0pre7_dirac-0.5.x.patch
#Patch7: MPlayer-1.0pre7try2_dirac-0.6.x.patch
Patch7: MPlayer-svn-20060707_dirac-0.5.x.patch.bz2
%{?_with_dvdmenu:Patch8: navmplayer-20060630.patch.bz2}
%{?_disable_shared_ffmpeg:Patch9: ffmpeg-svn-20060630-dirac-0.5.x.patch.bz2}
Patch10: MPlayer-svn-20060630-vidix_ext_drivers.patch.gz
Patch11: MPlayer-svn-20060630-vidix_0.9.9.1.patch.gz
Patch21: MPlayer-svn-20060607-vf_mcdeint.patch.gz
Patch22: MPlayer-cvs-20060519-polyp0.8.patch.gz
Patch24: MPlayer-1.0pre7try2-xmmslibs_fix.patch
Patch25: MPlayer-1.0pre7try2-libdir_fix.patch
Patch26: MPlayer-svn-20060621-configure.patch.gz
%if %cvsbuild
Patch27: MPlayer-cvs-20060331-builddocs.patch.gz
%endif


BuildRequires: libXinerama-devel libXt-devel libXvMC-devel libXxf86dga-devel
BuildRequires: libXxf86vm-devel
BuildRequires: awk libmesa-devel
BuildRequires: libncurses-devel libslang-devel
%if %cvsbuild
BuildRequires: docbook-style-dsssl openjade xsltproc
%endif

# termcap/tinfo
BuildRequires: libtinfo-devel
BuildRequires: pkgconfig
#

%if_enabled shared_ffmpeg
BuildRequires: libffmpeg-devel >= 1:0.5.0-alt0.20060703.1
%endif

%if_enabled lirc
BuildRequires: liblirc-devel
%endif

%if_enabled tv
BuildRequires: linux-libc-headers
%endif

%if_enabled smb
# Earlier builds conflicts w/ glibc-2.3
BuildRequires: libsmbclient-devel >= 3.0.3-alt1
%endif

%if_enabled dvdread
BuildRequires: libdvdread-devel 
%endif

%if_enabled live
BuildRequires: liblive-devel >= 0.0.0-alt0.2006.05.15
%endif

# mpdvdkit

%if_enabled cdparanoia
BuildRequires: libcdparanoia-devel
%endif

%if_enabled freetype
BuildRequires: libfreetype-devel >= 2.0.9
%endif

%if_enabled fontconfig
BuildRequires: fontconfig-devel
%endif

%if_enabled enca
BuildRequires: libenca-devel
%endif


%if_enabled aalib
BuildRequires: aalib-devel
%endif

%if_enabled caca
BuildRequires: libcaca-devel
%endif

%if_enabled directfb
BuildRequires: libdirectfb-devel
%endif

%if_enabled dvb
BuildRequires: linux-libc-headers
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
BuildRequires: libmesa-devel
%endif

%if_enabled sdl
BuildRequires: libSDL-devel >= 1.1.7
BuildRequires: libSDL_mixer-devel
%endif

%if_enabled svga
BuildRequires: svgalib-devel
%endif

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

%if_enabled polyp
BuildRequires: libpolypaudio-devel >= 0.9
%endif

%if_enabled libdts
BuildRequires: libdca-devel
%endif

%if_enabled musepack
BuildRequires: libmpcdec-devel >= 1.2.1
%endif


%if_enabled gif
BuildRequires: libungif-devel
%endif

%if_enabled png
BuildRequires: libpng-devel
%endif

%if_enabled jpeg
BuildRequires: libjpeg-devel
%endif

%if_enabled lzo
BuildRequires: liblzo-devel
%endif

%if_enabled xvid
BuildRequires: libxvid-devel
%endif

%if_enabled x264
BuildRequires: libx264-devel
%endif

%if_enabled divx4linux
BuildRequires: divx4linux-devel
%endif

%if_enabled fame
BuildRequires: libfame-devel
%endif

%if_enabled openal
BuildRequires: libopenal-devel
%endif

%if_enabled vorbis
BuildRequires: libogg-devel libvorbis-devel
%endif

%if_enabled tremor_external
BuildRequires: libtremor-devel
%endif

%if_enabled speex
BuildRequires: libspeex-devel
%endif

%if_enabled theora
BuildRequires: libtheora-devel
%endif

%if_enabled faad
%if_disabled internal_faad
BuildRequires: libfaad-devel
%endif
%endif

%if_enabled dirac
BuildRequires: libdirac-devel
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

%if_enabled dvdnav
BuildRequires: libdvdnav-devel
%endif

%if_enabled fribidi
BuildRequires: libfribidi-devel fribidi
%endif

%if_enabled vidix_ext
BuildRequires: libvidix-devel
%endif

#if_enabled external_flac
#BuildRequires: libflac-devel
#endif

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

%description -l ru_RU.CP1251
MPlayer - это видеопроигрыватель, который поддерживает широкий спектр
форматов файлов, в том числе AVI, MPEG и Quicktime. В него включено
множество аудио- и видеокодеков, оптимизированных для MMX, SSE, 3DNow!
и.т.п. Кроме этого, имеется возможность использования внешних кодеков:
XAnim, RealPlayer и Win32. Реализованы основные функции для
проигрывания VCD/DVD, включая субтитры DVD, а также множества других
текстовых форматов субтитров.

Поддерживаются практически все способы вывода изображения и звука в
юниксоподобных системах. Имеются низкоуровневые специализарованные
драйвера для некоторых видеокарт: Matrox, Nvidia, 3Dfx, Radeon,
Mach64, Permedia3, - аппаратного декодирования AC3, а также нескольких
плат, аппаратно декодирующих MPEG, таких как DVB и DXR3/Hollywood+.

Кроме этого, MPlayer способен захватывать сигнал с устройств V4L.

Этот пакет содержит только консольную версию MPlayer. Вам следует
устанавливать пакет %gui_name *вместо* данного пакета, если Вам
требуется видеопроигрыватель с хорошим настраиваемым GUI (графическим
интерфейсом пользователя)

%package -n %gui_name
%define gname gmplayer
Summary:  %bname is the Unix video player (GUI version)
Summary(ru_RU.CP1251): %bname - это настоящий видеоплеер (GUI вариант)
License:  GPL for all but not for OpenDivX
Group:    Video
Requires: %bname-console = %real_version
Provides: %bname = %real_version
Provides: %bname = %base_version
Obsoletes: %bname-skin-default
BuildRequires: glib2-devel libgtk+2-devel
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

%description -n %gui_name -l ru_RU.CP1251
MPlayer - это видеопроигрыватель, который поддерживает широкий спектр
форматов файлов, в том числе AVI, MPEG и Quicktime. В него включено
множество аудио- и видеокодеков, оптимизированных для MMX, SSE, 3DNow!
и.т.п. Кроме этого, имеется возможность использования внешних кодеков:
XAnim, RealPlayer и Win32. Реализованы основные функции для
проигрывания VCD/DVD, включая субтитры DVD, а также множества других
текстовых форматов субтитров.

Поддерживаются практически все способы вывода изображения и звука в
юниксоподобных системах. Имеются низкоуровневые специализарованные
драйвера для некоторых видеокарт: Matrox, Nvidia, 3Dfx, Radeon,
Mach64, Permedia3, - аппаратного декодирования AC3, а также нескольких
плат, аппаратно декодирующих MPEG, таких как DVB и DXR3/Hollywood+.

Кроме этого, MPlayer способен захватывать сигнал с устройств V4L.

Этот пакет содержит версию MPlayer c GUI (графическим интерфейсом).
Также имеется %console_name - консольная версия пакета с меньшим
числом зависимостей.

%package -n mencoder
Group: Video
Summary: MEncoder is a movie encoder for Unix.
Summary(ru_RU.CP1251): MEncoder - это кодировщик фильмов для Unix.
Requires: %bname = %base_version

%description -n mencoder
MEncoder a movie encoder for Unix and is a part of the MPlayer package.


%package docs
Group: Video
Summary: MPlayer all docs
Requires: %bname-doc-en = %version-%release
Requires: %bname-doc-de = %version-%release
Requires: %bname-doc-cs = %version-%release
Requires: %bname-doc-es = %version-%release
Requires: %bname-doc-fr = %version-%release
Requires: %bname-doc-hu = %version-%release
Requires: %bname-doc-it = %version-%release
Requires: %bname-doc-pl = %version-%release
Requires: %bname-doc-ru = %version-%release
Requires: %bname-doc-zh = %version-%release

%description docs
MPlayer all docs.


%package doc-en
Group: Video
Summary: MPlayer English docs
Obsoletes: MPlayer-doc
Provides: MPlayer-doc

%description doc-en
MPlayer English docs.


%package doc-cs
Group: Video
Summary: MPlayer Czesh docs

%description doc-cs
MPlayer Czesh docs.


%package doc-de
Group: Video
Summary: MPlayer German docs

%description doc-de
MPlayer German docs.


%package doc-es
Group: Video
Summary: MPlayer Spanish docs

%description doc-es
MPlayer Spanish docs.


%package doc-fr
Group: Video
Summary: MPlayer French docs

%description doc-fr
MPlayer French docs.


%package doc-hu
Group: Video
Summary: MPlayer Hungarian docs

%description doc-hu
MPlayer Hungarian docs.


%package doc-it
Group: Video
Summary: MPlayer Italian docs

%description doc-it
MPlayer Italian docs.


%package doc-pl
Group: Video
Summary: MPlayer Polish docs

%description doc-pl
MPlayer Polish docs.


%package doc-ru
Group: Video
Summary: MPlayer Russian docs

%description doc-ru
MPlayer Russian docs.


%package doc-zh
Group: Video
Summary: MPlayer Taiwan Chinese docs

%description doc-zh
MPlayer Taiwan Chinese docs.


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


%if_enabled vidix_int
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

%description -n %bname-vidix -l ru_RU.CP1251
VIDIX - это аббревиатура для VIDeo Interface for *niX (ВИДео Интерфейс
для юниКСоподобных операционных систем)

VIDIX был спроектирован и разработан как интерфейс для быстрых
драйверов уровня приложения для DGA (Direct Graphics Access - прямой
доступ к графике). Предполагалось, что эти драйвера будут также
переносимы как и X11 (не только на юникс).

Основные характеристики:
* Это переносимое развитие технологии mga_vid, работающее на уровне
  приложения
* В отличие от X11 он предоставляет DGA везде, где это возможно
* В отличие от v4l он предоставляет интерфейс для воспроизведения
  видео
* В отличие от драйверов линукс он использует библиотеку math


%if_enabled vidix_int_drivers
%package -n %bname-vidix-trident
Group: Video
Summary: VIDIX driver for Trident Cyberblade/i1
Provides: %bname-vidix-cyberblade = %version-%release
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-trident
VIDIX driver for Trident Cyberblade/i1.


%package -n %bname-vidix-mach64
Group: Video
Summary: VIDIX driver for ATI Mach64 and 3DRage chips
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-mach64
VIDIX driver for ATI Mach64 and 3DRage chips.


%package -n %bname-vidix-mga
Group: Video
Summary: VIDIX drivers for Matrox Gxxx series
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-mga
Two VIDIX drivers for Matrox Gxxx series (using BES and CRTC2).


%package -n %bname-vidix-permedia2
Group: Video
Summary: VIDIX driver for 3DLabs Permedia2 cards
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-permedia2
VIDIX driver for 3DLabs Permedia2 cards.


%package -n %bname-vidix-permedia3
Group: Video
Summary: VIDIX driver for 3DLabs Permedia3 cards
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-permedia3
VIDIX driver for 3DLabs GLINT R3/Permedia3 cards.


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
Summary: VIDIX driver for S3 Savage
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-savage
VIDIX driver for S3 Savage.


%package -n %bname-vidix-nvidia
Group: Video
Summary: VIDIX driver for nVidia chips
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-nvidia
VIDIX driver for nVidia chips.


%package -n %bname-vidix-sis
Group: Video
Summary: VIDIX driver for SiS 300 and 310/325 series chips
Provides: %bname-vidix-driver = %version-%release

%description -n %bname-vidix-sis
VIDIX driver for SiS 300 and 310/325 series chips.


%package -n %bname-vidix-unichrome
Group: Video
Summary: VIDIX driver for VIA CLE266 Unichrome
Provides: %bname-vidix-driver = %version-%release
Provides: %bname-vidix-via = %version-%release

%description -n %bname-vidix-unichrome
VIDIX driver for VIA CLE266 Unichrome.


%package -n %bname-vidix-genfb
Group: Video
Summary: VIDIX driver for framebuffer
Provides: %bname-vidix-driver = %version-%release
Provides: %bname-vidix-fb = %version-%release

%description -n %bname-vidix-genfb
VIDIX driver for framebuffer.
%endif
%endif


%prep
%if %cvsbuild
# CVS Build
%if_enabled shared_ffmpeg
%setup -q -n %fname-%fversion%{?_with_dvdmenu: -a 2}
%else
%setup -q -n %fname-%fversion -a 1%{?_with_dvdmenu: -a 2}
# needed with CVS snapshots
%if_enabled dirac
pushd ffmpeg-%ffmpeg_version
%patch9 -p1
popd
%endif
mv ffmpeg-%ffmpeg_version/lib{av{codec,format,util}postproc} .
%endif
%else
# A Release Build
%setup -q -n %fname-%fversion
%endif
%if_enabled vidix_int_drivers
tar -xjvf %SOURCE6
rm -rf vidix
mv vidix-%vidixver/vidix ./
%endif

%if_with dvdmenu
for d in codecs demux dvdnav; do
    mkdir -p libmp$d
    mv mplayer-dvdnav-patch/mplayer-add/libmp$d/* ./libmp$d/
done
for p in doc gui; do
    patch -p0 < mplayer-dvdnav-patch/nav$p.patch
done
%patch8 -p1
%endif
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%{!?_disable_vidix_int_drivers:%patch5 -p1}
%patch6 -p1
%if_enabled dirac
%patch7 -p1
%endif
%{?_disable_vidix_int_drivers:%patch11 -p1}
%{?_disable_vidix_int_drivers:%patch10 -p1}
%patch21 -p1
%{?_enable_polyp:%patch22 -p1}
%patch24 -p1
%patch25 -p1
%if %cvsbuild
%patch26 -p1
%patch27 -p1
%endif
%{?_enable_polyp:bzip2 -dcf %SOURCE9 > libao2/ao_polyp.c}

%if_enabled vidix_int_drivers
rm -rf libdha/*
mv vidix-%vidixver/libdha/* libdha/
subst 's/\(ldconfig\)/\#\1/g' libdha/Makefile
%else
mv libdha/Makefile libdha/Makefile.orig
cat > libdha/Makefile <<__MAKE__
all:

install:
__MAKE__
%endif
%if_enabled vidix_int
subst 's,\(.*\)\/mplayer\/vidix,\1/vidix,g' vidix/drivers/Makefile
subst 's,/mplayer\(/vidix/\),\1,' configure
%endif
%{?_enable_dvdnav:subst 's|\(\<\)\(dvdnav\)\(\.h\>\)|\1\2/\2\3|' configure}

%if %cvsbuild
subst 's|"libavutil/md5.h"|<ffmpeg/md5.h>|' libvo/vo_md5sum.c
# iconv pl docs
pushd DOCS/xml/pl
for f in $(grep -H -l ' encoding="utf-8"' *.xml); do
    mv -f $f xml.utf8
    sed -e '1 s/ encoding="utf-8"/ encoding="iso-8859-2"/' xml.utf8 | iconv -c -f utf-8 -t ISO-8859-2 > $f
done
rm -f xml.utf8
popd
%endif

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
	for CC in gcc-4.1 gcc-4.0 gcc-3.4 gcc-3.3 gcc-3.2 gcc-badversion; do
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
		--disable-debug \
		--disable-profile \
		--enable-gui \
		--enable-termcap \
		--with-termcaplib=tinfo \
%if_enabled shared_ffmpeg
		--disable-libavcodec \
		--disable-libavformat \
		--disable-libavutil \
		--disable-libpostproc \
		--enable-libavcodec_so \
		--enable-libavformat_so \
		--enable-libavutil_so \
		--enable-libpostproc_so \
%else
		--disable-libavcodec_so \
		--disable-libavformat_so \
		--disable-libavutil_so \
		--disable-libpostproc_so \
		--enable-libavcodec \
		--enable-libavformat \
		--enable-libavutil \
		--enable-libpostproc \
%endif
		%{subst_enable png} \
		--enable-mencoder \
		%{subst_enable libfame} \
		--cc=$CC \
		--prefix=%_prefix \
		--bindir=%_bindir \
		--datadir=%_datadir/%bname \
		--mandir=%_mandir \
		--confdir=%_sysconfdir/%bname \
		--libdir=%_libdir \
		--enable-largefiles \
		--enable-iconv \
		%{subst_enable lirc} \
		--disable-joystick \
		%{subst_enable tv} \
		--enable-rtc \
		%{subst_enable network} \
		%{subst_enable smb} \
		%{subst_enable dvdread} \
%if_enabled live
		--enable-live \
		--with-livelibdir=%_libdir/live \
%else
		--disable-live \
%endif
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
		%{subst_enable_with cpu_detection runtime-cpudetection} \
		%{subst_enable mmx} \
		%{subst_enable mmxext} \
		%{subst_enable 3dnow} \
		%{subst_enable 3dnowext} \
		%{subst_enable sse} \
		%{subst_enable sse2} \
		%{subst_enable altivec} \
%if_enabled debug
		--enable-debug=3 \
%endif
		--language=%mplang \
		%{subst_enable_with dynamic_plugins dynamic-plugins} \
		%{subst_enable aa} \
		%{subst_enable caca} \
		%{subst_enable fbdev} \
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
%if_enabled vidix
		%{subst_enable_with vidix_ext vidix-external} \
		%{subst_enable_with vidix_int vidix-internal} \
%else
		--disable-vidix-external \
		--disable-vidix-internal \
%endif
		%{?enable_vidix:--disable-vidix-external} \
		--enable-vm \
		--enable-xv \
		--enable-xvmc \
		%{subst_enable alsa} \
		%{subst_enable arts} \
		%{subst_enable esd} \
		%{subst_enable select} \
		%{subst_enable polyp} \
		%{subst_enable libdts} \
		%{subst_enable musepack} \
		%{subst_enable gif} \
		%{subst_enable jpeg} \
		%{subst_enable liblzo} \
		%{subst_enable win32} \
		%{?_enable_win32:--with-win32libdir=%win32_libdir} \
		%{subst_enable directx} \
		%{subst_enable qtx} \
		%{subst_enable xanim} \
		%{?_enable_xanim:--with-xanimlibdir=%xanim_libdir} \
		%{subst_enable real} \
		%{?_enable_real:--with-reallibdir=%real_libdir} \
		%{subst_enable xvid} \
		%{subst_enable x264} \
		%{subst_enable divx4linux} \
		--disable-opendivx \
		%{subst_enable openal} \
		%{subst_enable vorbis} \
		%{subst_enable_with tremor_internal tremor-internal} \
		%{subst_enable_with tremor_low tremor-low} \
		%{subst_enable_with tremor_external tremor-external} \
		%{subst_enable speex} \
		%{subst_enable theora} \
%if_enabled faad
%if_enabled internal_faad
		--enable-faad-internal \
		--disable-faad-external \
%else
		--disable-faad-internal \
		--enable-faad-external \
%endif
%else
		--disable-faad-internal \
		--disable-faad-external \
%endif
		%{?_enable dirac:%{subst_enable dirac}} \
		%{subst_enable libdv} \
		%{subst_enable mad} \
		%{subst_enable xmms} \
%if_enabled dvdnav
		--with-dvdnavdir=%_includedir/dvdnav \
%endif
		%{subst_enable dvdnav} \
		%{subst_enable ass} \
		%{subst_enable fribidi}


%ifarch %ix86
%make_build
%else
%__make # x86_64 smp incompatible.
%endif

%if_enabled freetype
pushd TOOLS/subfont-c
make
popd
%endif

pushd TOOLS
#make
# can't build vivodump subrip
%make 302m_convert 360m_convert alaw-gen asfinfo avi-fix avisubdump bios2dump dump_mp4 mem2dump movinfo png2raw
popd

%if %cvsbuild
# build HTML documentation from XML files
pushd DOCS/xml
cp -fL %_sysconfdir/sgml/catalog ./
echo 'CATALOG "/usr/share/xml/xml-iso-entities-8879.1986/catalog"' >> ./catalog
./configure
for lang in cs de en es fr hu pl ru; do
    make html-chunked-$lang
done
popd
%endif


%install
%makeinstall DESTDIR=%buildroot 

pushd %buildroot%_bindir
ln -sf mplayer gmplayer
install -d -m 0755 %buildroot%_datadir/%bname/skins
tar -C %buildroot%_datadir/%bname/skins -xjf %SOURCE4
ln -sf standard %buildroot%_datadir/%bname/skins/default
popd

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
tar xjf %SOURCE3 -C %buildroot%_datadir/%bname
%endif
%endif

install -m 0644 etc/{codecs,input}.conf %buildroot%_sysconfdir/%bname/

%if_enabled menu
install -m 0644 etc/menu.conf %buildroot%_sysconfdir/%bname/
%if_enabled dvb
install -m 0644 etc/dvb-menu.conf %buildroot%_sysconfdir/%bname/
%endif
%endif

%if_enabled freetype
# install tools
pushd TOOLS/subfont-c
install -d %buildroot%_datadir/%bname/fonts/{osd,encodings}
install osd/{gen.py,osd.pfb,README,runme} %buildroot%_datadir/%bname/fonts/osd/
install encodings/* %buildroot%_datadir/%bname/fonts/encodings/
install -m 0755 subfont %buildroot%_bindir/mplayer_subfont
popd
%endif

install -d %buildroot%_sysconfdir/bashrc.d

install -m 0755 %SOURCE5 %buildroot%_sysconfdir/bashrc.d/

# Menus
mv %buildroot%_desktopdir/mplayer.desktop %buildroot%_desktopdir/%bname.desktop
iconv -f cp1251 -t utf-8 >> %buildroot%_desktopdir/%bname.desktop <<__MENU__
Version=1.0
GenericName[uk]=Програвач мультимедіа
X-MultipleArgs=true
StartupNotify=true
__MENU__

#Icons
find etc DOCS -type f -exec chmod 644 {} \;

# add mencoder.1 man-link
rm -f %buildroot%_man1dir/mencoder.1 ||:
echo ".so mplayer.1" > %buildroot%_man1dir/mencoder.1

# docs
bzip2 --best --force --keep -- ChangeLog
for l in cs de es fr hu it pl sv zh; do
    install -pD -m 0644 DOCS/man/$l/mplayer.1 %buildroot%_mandir/$l/man1/mplayer.1
    ln -s mplayer.1 %buildroot%_mandir/$l/man1/mencoder.1
done
for l in it zh; do
    install -d %buildroot%_docdir/%name-doc-%version/$l
    install -m 0644 DOCS/$l/*.html %buildroot%_docdir/%name-doc-%version/$l/
done
for l in cs de en es fr hu pl ru; do
    install -d %buildroot%_docdir/%name-doc-%version/$l
    install -m 0644 DOCS/HTML/$l/{*.htm,*.css} %buildroot%_docdir/%name-doc-%version/$l/
done
install -d %buildroot%_docdir/%name-doc-%version/en/tech/realcodecs
install -m 0644 DOCS/tech/{MAINTAINERS,TODO,*.txt,mpsub.sub,playtree,wishlist} %buildroot%_docdir/%name-doc-%version/en/tech/
install -pD -m 0644 DOCS/tech/playtree-hun %buildroot%_docdir/%name-doc-%version/hu/tech/playtree
install -m 0644 DOCS/tech/realcodecs/{TODO,*.txt} %buildroot%_docdir/%name-doc-%version/en/tech/realcodecs/

# a tribute to clever python support
unset RPM_PYTHON


%if_enabled vidix_int
%post -n %bname-vidix -p /sbin/ldconfig


%postun -n %bname-vidix -p /sbin/ldconfig
%endif


%post -n %gui_name
%update_menus


%postun -n %gui_name
%clean_menus


%files -n %console_name
%doc README AUTHORS ChangeLog.*
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
%_mandir/*/man1/*


%files -n %gui_name
%_bindir/gmplayer
%dir %_datadir/%bname
%_desktopdir/*
%_datadir/pixmaps/*
%_datadir/%bname/skins/standard
%_datadir/%bname/skins/default


%files -n mencoder
%_bindir/mencoder


%files doc-en
%_docdir/%name-doc-%version/en


%files doc-de
%_docdir/%name-doc-%version/de


%files doc-cs
%_docdir/%name-doc-%version/cs


%files doc-es
%_docdir/%name-doc-%version/es


%files doc-fr
%_docdir/%name-doc-%version/fr


%files doc-hu
%_docdir/%name-doc-%version/hu


%files doc-it
%_docdir/%name-doc-%version/it


%files doc-pl
%_docdir/%name-doc-%version/pl


%files doc-ru
%_docdir/%name-doc-%version/ru


%files doc-zh
%_docdir/%name-doc-%version/zh


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


%if_enabled vidix_int
%if_enabled vidix_int_drivers
%files -n %bname-vidix
%_libdir/libdha*


%files -n %bname-vidix-trident
%_libdir/vidix/cyberblade_vid.so


%files -n %bname-vidix-mach64
%_libdir/vidix/mach64_vid.so


%files -n %bname-vidix-mga
%_libdir/vidix/mga_crtc2_vid.so
%_libdir/vidix/mga_vid.so
%_libdir/vidix/mga_tv_vid.so


%files -n %bname-vidix-nvidia
%_libdir/vidix/nvidia_vid.so


%files -n %bname-vidix-radeon
%_libdir/vidix/radeon_vid.so


%files -n %bname-vidix-rage128
%_libdir/vidix/rage128_vid.so


%files -n %bname-vidix-savage
%_libdir/vidix/savage_vid.so


%files -n %bname-vidix-sis
%_libdir/vidix/sis_vid.so


%files -n %bname-vidix-unichrome
%_libdir/vidix/unichrome_vid.so


%files -n %bname-vidix-genfb
%_libdir/vidix/genfb_vid.so


%files -n %bname-vidix-permedia2
%_libdir/vidix/pm2_vid.so


%files -n %bname-vidix-permedia3
%_libdir/vidix/pm3_vid.so
%endif
%endif


%changelog
* Mon Jul 10 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060710.1
- new SVN sbapshot (revision 18986)
- updated MPlayer-svn-20060710-alt-external_fame.patch
- enabled ass (internal SSA/ASS subtitles support)
- fixed spec

* Mon Jul 10 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060707.3
- replaced vidix-0.9.9.1.tar.bz2 with
  MPlayer-svn-20060707-ext_vidix_drivers-0.9.9.1.patch

* Sat Jul 08 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060707.2
- disabled dirac

* Fri Jul 07 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060707.1
- new SVN sbapshot (revision 18929)
- fixed spec
- updated MPlayer-svn-20060707_dirac-0.5.x.patch

* Thu Jul 06 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060630.5
- enabled internal VIDIX
- disabled external VIDIX
- added vidix-0.9.9.1 with vidix-0.9.9.1-pm3_vid.patch
- added MPlayer-svn-20060630-vidix_0.9.9.1.patch
- added MPlayer-svn-20060630-vidix_ext_drivers.patch

* Thu Jul 06 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060630.4
- disabled internal VIDIX
- enabled external VIDIX

* Fri Jun 30 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060630.3
- don't include ffmpeg tarball if shared_ffmpeg enabled (default)
- updated MPlayer-dvd-ru patch
- cleaned up bogus patches
- fixed spec
- fixed libvo/vo_md5sum.c
- trying dvdmenu (disabled by deafult)
- some fixes from LAKostis (vidix prefixes, bogus BuildRequires)
- added MPlayer-svn-20060704_dirac-0.5.x.patch
- enabled dirac

* Fri Jun 30 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060630.1
- new SVN sbapshot (revision 18853)
- enabled dvdnav
- fixed dvdnav detect

* Thu Jun 29 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060629.1
- new SVN sbapshot (revision 18847)

* Mon Jun 26 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060626.1
- new SVN sbapshot (revision 18821)
- removed MPlayer-cvs-20060506-docs.patch, used sed & iconv instead

* Fri Jun 23 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060623.1
- new SVN sbapshot (revision 18791)

* Thu Jun 22 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060622.1
- new SVN sbapshot (revision 18781)
- returned mplayer.sh (soundwrapper)
- cleaned up spec

* Wed Jun 21 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060621.1
- new SVN sbapshot (revision 18766)
- added macroses
- enabled external tremor
- force enabled openal
- MPlayer-cvs-20060220-configure.patch merged with
  MPlayer-1.0pre7-aalib.patch and some additions to
  MPlayer-svn-20060621-configure.patch

* Tue Jun 20 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060620.1
- new SVN sbapshot (revision 18760)
- fixed spec
- updated MPlayer-svn-20060620-alt-external_fame.patch
- fixed configure parameters
- cleaned up spec

* Tue Jun 13 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060613.1
- new SVN sbapshot (revision 18698)
- removed additional icons
- fixed .desktop file
- removed mplayer.sh (soundwrapper)
- cleaned up spec

* Wed Jun 07 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060607.1
- 20060607 SVN snapshot
- fixed spec

* Fri Jun 02 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060519.4
- fixed fbdev support

* Wed May 31 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060519.3
- added menu file
- cleaned up spec

* Tue May 30 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060519.2
- cleaned up spec
- enabled polyp (thanx icesik and polypaudio's author)
- added MPlayer-cvs-20060519-polyp0.8.patch

* Thu May 25 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060519.1
- 20060519 CVS snapshot
- removed mplayer-rpm-cvs.patch

* Thu May 25 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060515.5
- rebuild for libffmpeg

* Wed May 24 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060515.4
- disabled xmms
- enabled gtk+2.0 GUI
- added default (standard) skin to %gui_name package
- cleaned up spec

* Tue May 23 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060515.3
- enabled shared FFmpeg libs

* Mon May 15 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060515.2
- enabled live.com support

* Mon May 15 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060515.1
- 20060515 CVS snapshot
- cleanup %name-cvs-20060506-docs.patch

* Wed May 03 2006 Led <led@altlinux.ru> 1.0-alt0.20060503.1
- 20060503 CVS snapshot
- fixed %%changelog
- fixed configure parameters in spec
- added %name-cvs-20060503-docs.patch
- enabled pl docs

* Wed Apr 26 2006 Led <led@altlinux.ru> 1.0-alt0.20060426.1
- 20060426 CVS snapshot
- disabled polyp because changes in it's API
- replaced mmx2 with mmxext and 3dnowex with 3dnowext in configure parameters
- fixed spec

* Thu Apr 20 2006 Led <led@altlinux.ru> 1.0-alt0.20060420.1
- 20060420 CVS snapshot
- fixed %%changelog
- added fr docs and de HTML docs
- splited docs to languages

* Wed Apr 19 2006 Led <led@altlinux.ru> 1.0-alt0.20060417.2
- enabled libdts

* Mon Apr 17 2006 Led <led@altlinux.ru> 1.0-alt0.20060417.1
- 20060417 CVS snapshot
- fixed spec

* Tue Apr 04 2006 Led <led@altlinux.ru> 1.0-alt0.20060331.2
- enabled musepack

* Fri Mar 31 2006 Led <led@altlinux.ru> 1.0-alt0.20060331.1
- CVS snapshot
- upgraded spec
- added configure and builddocs patches
- enabled svgalib, aalib, caca, png, speex, enca, polyp
- enabled x264 for mencoder

* Thu Jan 26 2006 ALT QA Team Robot <qa-robot@altlinux.org> 1.0-alt23.pre7try2
- Packaged skins separately.

* Fri Jan 13 2006 LAKostis <lakostis at altlinux.ru> 1.0-alt22.1.pre7try2
- NMU;
- x86_64 fixes;
- fix jackd builddep;
- fix unparseable macros;
- remove old menu files;
- remove kernel-headers-dvb deps, move to linux-libc-headers.

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
