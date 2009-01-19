%define set_disable() %{expand:%%force_disable %{1}} %{expand:%%undefine _enable_%{1}}
%define set_enable() %{expand:%%force_enable %{1}} %{expand:%%undefine _disable_%{1}}
%define subst_enable_to() %{expand:%%{?_enable_%{1}:--enable-%{2}}} %{expand:%%{?_disable_%{1}:--disable-%{2}}}
%define subst_o() %{expand:%%{?_enable_%{1}:%{1},}}
%define subst_o_pre() %{expand:%%{?_enable_%{2}:%{1}%{2},}}
%define subst_o_post() %{expand:%%{?_enable_%{1}:%{1}%{2},}}

%define prerel %nil
%define svnrev 19833
%define ffmpeg_svnrev 6245

#----------------------	BEGIN OF PARAMETERS -------------------------------------

# Optional features:
%def_enable mencoder
%def_enable lame
%def_enable gui
%def_disable gtk1
%def_enable largefiles
%def_disable devfs
%def_enable termcap
%def_disable termios
%def_enable iconv
%def_enable langinfo
%def_enable lirc
%def_disable lircc
%def_enable joystick
%def_enable xf86keysym
%def_enable tv
%def_enable v4l1
%def_enable v4l2
%def_enable radio
%def_enable radio_v4l1
%def_enable radio_v4l2
%def_enable radio_capture
%def_disable bsdbt848
%def_disable pvr
%def_enable rtc
%def_enable network
%def_disable winsock2
%def_enable smb
%def_enable live
%def_enable dvdnav
%def_enable dvdread
%def_enable mpdvdkit
%def_enable cdparanoia
%def_enable bitmap_font
%def_enable freetype
%def_enable fontconfig
%def_enable unrarlib
%def_enable osdmenu
%def_enable sortsub
%def_enable fribidi
%def_enable enca
%def_disable macosx
%def_disable macosx_finder
%def_disable macosx_bundle
%def_disable IPv6
%def_enable gethostbyname2
%def_enable ftp
%def_disable vstream
%def_enable pthreads
%def_enable ass
%def_disable rpath

# Codecs:
%def_enable gif
%def_enable png
%def_enable jpeg
%def_enable libcdio
%def_enable lzo
%def_enable win32
%def_enable qtx
%def_enable xanim
%def_enable real
%def_enable xvid
%def_enable x264
%def_enable ffmpeg
%def_enable shared_ffmpeg
%def_enable fame
%def_enable faad_ext
%def_enable faad_int
%def_disable tremor_internal
%def_disable tremor_low
%def_disable tremor_external
%def_enable vorbis
%def_enable speex
%def_enable theora
%def_enable faac
%def_disable ladspa
%def_enable libdv
%def_enable mad
%def_disable toolame
%def_disable twolame
%def_enable xmms
%def_enable mp3lib
%def_enable liba52
%def_enable libdts
%def_enable libmpeg2
%def_enable musepack
%def_disable dirac

# Video output:
%def_enable vidix
%define vidixlib ext
%def_enable gl
%def_enable dga
%def_disable vesa
%def_enable svga
%def_enable sdl
%def_enable aa
%def_enable caca
%def_disable ggi
%def_disable ggiwmh
%def_disable directx
%def_disable dxr2
%def_disable dxr3
%def_disable ivtv
%def_enable dvb
%def_enable dvbhead
%def_enable mga
%def_enable xmga
%def_enable xv
%def_enable xvmc
%def_enable vm
%def_enable xinerama
%def_enable x11
%def_enable fbdev
%def_disable mlib
%def_enable 3dfx
%def_enable tdfxfb
%def_enable s3fb
%def_enable directfb
%def_disable zr
%def_disable bl
%def_enable tdfxvid
%def_enable tga
%def_enable pnm
%def_enable md5sum

# Audio output:
%def_enable alsa
%def_enable oss
%def_enable arts
%def_enable esd
%def_enable pulse
%def_disable polyp
%def_disable old_polyp
%def_enable jack
%def_enable openal
%def_enable nas
%def_disable sgiaudio
%def_disable sunaudio
%def_disable waveout
%def_enable select

# Miscellaneous options:
%define swscalelib ext
%def_enable cpu_detection
%define ccomp gcc
%define asm as
%define charset UTF-8
#define language uk ru en bg cs de dk el es fr hu it ja ko mk nl no pl ro sk sv tr pt_BR zh_CN zh_TW
%define language all

# Advanced options:
%def_enable mmx
%def_enable mmxext
%def_enable 3dnow
%def_enable 3dnowext
%def_enable sse
%def_enable sse2
%def_disable altivec
%def_enable fastmemcpy
%def_disable debug
%def_disable profile
%def_enable sighandler
%def_disable gdb
%def_enable dynamic_plugins

%define termcaplib tinfo

# Other parameters
%def_enable nls
%def_without soundwrapper
%def_with htmldocs
%define default_vo %{subst_o xmga}%{subst_o xv}%{subst_o sdl}%{subst_o gl2}%{subst_o gl}%{subst_o x11}%{subst_o_pre x vidix}%{subst_o mga}%{subst_o dfbmga}%{subst_o tdfxfb}%{subst_o 3dfx}%{subst_o s3fb}%{subst_o_pre c vidix}%{subst_o_post fbdev 2}%{subst_o vesa}%{subst_o caca}%{subst_o aa}null
%define default_ao %{subst_o alsa}%{subst_o oss}%{subst_o openal}%{subst_o sdl}%{subst_o pulse}%{subst_o polyp}%{subst_o nas}null

#----------------------	END OF PARAMETERS ---------------------------------------

%{?_disable_mencoder:%set_disable lame}
%{?_enable_termcap:%set_disable termios}

%if_disabled tv
%set_disable v4l1
%set_disable v4l2
%set_disable bsdbt848
%set_disable pvr
%endif

%if_disabled network
%set_disable live
%set_disable ftp
%endif

%if_disabled macosx
%set_disable macosx_finder
%set_disable macosx_bundle
%endif

%if_enabled nls
%define awk gawk
%set_enable iconv
%{!?charset:%define charset UTF-8}
%undefine language
%define language en
%else
%define awk awk
%endif

%{?_disable_ffmpeg:%set_disable ffmpeg_shared}
%{?_disable_iconv:%set_disable freetype}
%{?_disable_freetype:%set_disable fontconfig}

%if_disabled vidix
%ifdef vidixlib
%undefine vidixlib
%endif
%define vidixlib none
%else
%ifnarch %ix86 x86_64
%ifdef vidixlib
%undefine vidixlib
%endif
%define vidixlib int
%endif
%endif
%if %vidixlib == none
%set_disable vidix
%endif

%{?_enable_tremor_external:%set_disable tremor_low}

%ifnarch %ix86
%set_disable win32
%endif

%ifnarch ppc
%set_disable altivec
%endif

%define win32_libdir	%_libdir/w32codec
%define xanim_libdir	%_libdir/xanim
%define real_libdir	%_libdir/real

%{?_disable_win32:%set_disable qtx}
%{?_enable_faad_int:%set_disable faad_ext}

%if_disabled x11
%set_disable xv
%set_disable xvmc
%set_disable xinerama
%set_disable xf86keysym
%set_disable vm
%set_disable dga
%endif


%define lname mplayer
%define Name MPlayer
Name: %lname
Serial: 1
Version: 1.0
%define altrel 2
%ifdef svnrev
Release: alt1.%svnrev.%altrel
%define pkgver svn-r%svnrev
%else
Release: alt%altrel
%define pkgver %version%prerel
%endif
Summary: Media player
Summary(uk_UA.CP1251): Медіаплейер
Summary(ru_RU.CP1251): Медиаплейер
License: GPL
Group: Video
URL: http://www.mplayerhq.hu
%if %name != %Name
Provides: %Name = %{?serial:%serial:}%version-%release
Obsoletes: %Name
%endif
%if_enabled freetype
%{?_disable_fontconfig:Requires: fonts-type1-urw}
Conflicts: %Name-fonts %lname-fonts < 1.0-alt0.20060719.1
%else
Requires: %name-fonts
%endif

%ifdef svnrev
Source0: %lname-svn-r%svnrev.tar.bz2
%else
Source0: %Name-%version%prerel.tar.bz2
%endif
# svn checkout svn.mplayerhq.hu/mplayer/trunk
%{?ffmpeg_svnrev:%{?_disable_shared_ffmpeg:Source1: ffmpeg-svn-r%ffmpeg_svnrev.tar.bz2}}
Source3: %lname.sh
Source4: standard-1.9.tar.bz2
Source5: %lname.conf.in.gz
Source6: mp_help2msg.awk.gz
Source7: mp_msg2po.awk.gz
Patch1: %Name-svn-20060710-alt-external_fame.patch.gz
Patch2: %lname-dvd-ru-svn19389.patch.gz
Patch3: %Name-1.0pre4-alt-explicit_gif.patch
Patch4: %lname-svn-r19427-libdha.patch.gz
Patch5: %lname-svn-r19447-vo_vidix.patch.gz
Patch6: %lname-svn-r19389-alt-artsc_ldflags.patch.gz
Patch7: %Name-svn-20060707_dirac-0.5.x.patch.bz2
Patch8: %lname-svn-r19389-ext_libswscale.patch.bz2
%{?_disable_shared_ffmpeg:Patch9: ffmpeg-svn-20060630-dirac-0.5.x.patch.bz2}
Patch10: %lname-svn-r19558-generic-x86_64.patch.gz
Patch11: %lname-svn-r19595-nls.patch.gz
Patch12: %lname-uni-svn19558.diff.gz
Patch13: %Name-svn-20060711-vbe.patch.gz
Patch14: %Name-1.0pre7try2-xmmslibs_fix.patch
Patch15: %lname-svn-r19671-pulseaudio.patch.bz2
Patch16: %Name-1.0pre8-udev.patch.gz
Patch17: %lname-svn-r19389-ext_ffmpeg.patch.gz
Patch21: %Name-svn-20060607-vf_mcdeint.patch.gz
Patch22: %lname-svn-r19389-polyp0.8.patch.gz
Patch26: %lname-svn-r19467-configure.patch.gz
%{?svnrev:Patch27: %Name-cvs-20060331-builddocs.patch.gz}

BuildRequires: %awk pkgconfig libncurses-devel libslang-devel zlib-devel
BuildRequires: cpp >= 3.3 gcc >= 3.3 gcc-c++ >= 3.3
%{?svnrev:BuildRequires: docbook-style-dsssl openjade xsltproc}

%{?_enable_lame:BuildRequires: liblame-devel}
%{?_enable_termcap:BuildRequires: libtinfo-devel}
%{?_enable_lirc:BuildRequires: liblirc-devel}
%{?_enable_tv:BuildRequires: linux-libc-headers}
%{?_enable_radio:BuildRequires: linux-libc-headers}
%{?_enable_pvr:BuildRequires: linux-libc-headers}
%{?_enable_rtc:BuildRequires: linux-libc-headers}
%{?_enable_smb:BuildRequires: libsmbclient-devel >= 3.0.3}
%{?_enable_live:BuildRequires: liblive555-devel >= 0.0.0-alt0.2006.05.15}
%{?_enable_dvdnav:BuildRequires: libdvdnav-devel}
%{?_enable_dvdread:BuildRequires: libdvdread-devel}
%{?_enable_mpdvdkit:BuildRequires: linux-libc-headers}
%{?_enable_cdparanoia:BuildRequires: libcdparanoia-devel}
%{?_enable_freetype:BuildRequires: libfreetype-devel >= 2.0.9}
%{?_enable_fontconfig:BuildRequires: fontconfig-devel}
%{?_enable_fribidi:BuildRequires: libfribidi-devel}
%{?_enable_enca:BuildRequires: libenca-devel}
%{?_enable_vstream:BuildRequires: libvstream-client-devel}

%{?_enable_gif:BuildRequires: libungif-devel}
%{?_enable_png:BuildRequires: libpng-devel}
%{?_enable_jpeg:BuildRequires: libjpeg-devel}
%{?_enable_libcdio:BuildRequires: libcdio-devel}
%{?_enable_lzo:BuildRequires: liblzo-devel}
%{?_enable_xvid:BuildRequires: libxvid-devel}
%{?_enable_x264:BuildRequires: libx264-devel}
%{?_enable_shared_ffmpeg:BuildRequires: libffmpeg-devel >= 0.5.0}
%{?_enable_fame:BuildRequires: libfame-devel}
%{?_enable_tremor_external:BuildRequires: libtremor-devel}
%{?_enable_vorbis:BuildRequires: libvorbis-devel}
%{?_enable_speex:BuildRequires: libspeex-devel}
%{?_enable_theora:BuildRequires: libtheora-devel}
%{?_enable_faad_ext:BuildRequires: libfaad-devel}
%{?_enable_faac:BuildRequires: libfaac-devel}
%{?_enable_libdv:BuildRequires: libdv-devel}
%{?_enable_mad:BuildRequires: libmad-devel}
%{?_enable_xmms:BuildRequires: libxmms-devel}
%{?_enable_libdts:BuildRequires: libdca-devel}
%{?_enable_libmpeg2:BuildRequires: libmpeg2-devel}
%{?_enable_musepack:BuildRequires: libmpcdec-devel >= 1.2.1}
%{?_enable_dirac:BuildRequires: libdirac-devel}

%if %vidixlib == ext
BuildRequires: libvidix-devel
%endif
%{?_enable_gl:BuildRequires: libmesa-devel libGLwrapper}
%{?_enable_vesa:BuildRequires: libvbe-devel}
%{?_enable_svga:BuildRequires: svgalib-devel}
%{?_enable_sdl:BuildRequires: libSDL-devel >= 1.1.7 libSDL_mixer-devel}
%{?_enable_aa:BuildRequires: aalib-devel libgpm-devel libslang-devel libX11-devel}
%{?_enable_caca:BuildRequires: libcaca-devel libslang-devel libX11-devel}
%{?_enable_ggi:BuildRequires: libggi-devel}
%{?_enable_dxr3:BuildRequires: libdxr3-devel}
%{?_enable_xv:BuildRequires: libXv-devel}
%{?_enable_xvmc:BuildRequires: libXvMC-devel}
%{?_enable_vm:BuildRequires: libXxf86vm-devel}
%{?_enable_xinerama:BuildRequires: libXinerama-devel}
%{?_enable_x11:BuildRequires: libXt-devel}
%{?_enable_dga:BuildRequires: libXxf86dga-devel}
%{?_enable_dvb:BuildRequires: linux-libc-headers}
%{?_enable_directfb:BuildRequires: libdirectfb-devel}
%{?_enable_pnm:BuildRequires: libnetpbm-devel}

%{?_enable_alsa:BuildRequires: libalsa-devel}
%{?_enable_oss:BuildRequires: linux-libc-headers}
%{?_enable_arts:BuildRequires: libarts-devel}
%{?_enable_esd:BuildRequires: esound-devel}
%{?_enable_pulse:BuildRequires: libpulseaudio-devel >= 0.9}
%{?_enable_polyp:BuildRequires: libpolypaudio-devel >= 0.8}
%{?_enable_jack:BuildRequires: jackit-devel}
%{?_enable_openal:BuildRequires: libopenal-devel}
%{?_enable_nas:BuildRequires: libaudio-devel}

%{?_enable_nls:BuildRequires: gettext-tools}

Autoreq: yes, noperl

%description
%Name is a movie and animation player that supports a wide range of file
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

This package provides only console version of the %Name. Install
%name-gui *instead* if you need a nice skinnable GUI player.

%description -l ru_RU.CP1251
%Name - это видеопроигрыватель, который поддерживает широкий спектр
форматов файлов, в том числе AVI, MPEG и Quicktime. В него включено
множество аудио- и видеокодеков, оптимизированных для MMX, SSE, 3DNow!
и.т.п. Кроме этого, имеется возможность использования внешних кодеков:
XAnim, RealPlayer и Win32. Реализованы основные функции для
проигрывания VCD/DVD, включая субтитры DVD, а также множества других
текстовых форматов субтитров.

Поддерживаются практически все способы вывода изображения и звука в
юниксоподобных системах. Имеются низкоуровневые специализированные
драйвера для некоторых видеокарт: Matrox, Nvidia, 3Dfx, Radeon,
Mach64, Permedia3, - аппаратного декодирования AC3, а также нескольких
плат, аппаратно декодирующих MPEG, таких как DVB и DXR3/Hollywood+.

Кроме этого, %Name способен захватывать сигнал с устройств V4L.

Этот пакет содержит только консольную версию %Name. Вам следует
устанавливать пакет %name-gui *вместо* данного пакета, если Вам
требуется видеопроигрыватель с хорошим настраиваемым GUI (графическим
интерфейсом пользователя).


%if_enabled gui
%package gui
%define gname g%lname
Summary:  %Name (GUI version)
Summary(uk_UA.CP1251): Медіаплейер (GUI вариант)
Summary(ru_RU.CP1251): Медиаплейер (GUI вариант)
Group: Video
Requires: %name >= 1.0
Provides: %gname
Obsoletes: %Name-skin-default
%if %name != %Name
Provides: %Name-gui = %{?serial:%serial:}%version-%release
Obsoletes: %Name-gui
%endif
%if_enabled gtk1
BuildRequires: gtk+-devel
%else
BuildRequires: libgtk+2-devel
%endif

%description gui
%Name is a movie and animation player that supports a wide range of
file formats, including AVI, MPEG, and Quicktime. It has many
MMX/SSE/3DNow! etc. optimized native audio and video codecs, but allows
using XAnim's and RealPlayer's binary codec plugins, and Win32 codec
DLLs. It has basic VCD/DVD playback functionality, including DVD
subtitles, but supports many text-based subtitle formats too.
For video and audio output, nearly every existing interface is
supported including some low-level card-specific drivers (for Matrox,
Nvidia, 3Dfx and Radeon, Mach64, Permedia3), hardware AC3 decoding and
few hardware MPEG decoding boards such as DVB and DXR3/Hollywood+.
It also supports video grabbing from V4L devices.
This package provides GUI version of the %Name. A console-only
version with trimmed down dependencies is also available as %name.

%description gui -l ru_RU.CP1251
%Name - это видеопроигрыватель, который поддерживает широкий спектр
форматов файлов, в том числе AVI, MPEG и Quicktime. В него включено
множество аудио- и видеокодеков, оптимизированных для MMX, SSE, 3DNow!
и т.п. Кроме этого, имеется возможность использования внешних кодеков:
XAnim, RealPlayer и Win32. Реализованы основные функции для
проигрывания VCD/DVD, включая субтитры DVD, а также множества других
текстовых форматов субтитров.
Поддерживаются практически все способы вывода изображения и звука в
юниксоподобных системах. Имеются низкоуровневые специализированные
драйвера для некоторых видеокарт: Matrox, Nvidia, 3Dfx, Radeon,
Mach64, Permedia3, - аппаратного декодирования AC3, а также нескольких
плат, аппаратно декодирующих MPEG, таких как DVB и DXR3/Hollywood+.
Кроме этого, %Name способен захватывать сигнал с устройств V4L.
Этот пакет содержит версию %Name c GUI (графическим интерфейсом).
Также имеется %name - консольная версия пакета с меньшим числом
зависимостей.
%endif


%if_enabled freetype
%package fontutils
Group: Video
Summary: Font utils for the %Name
Requires: %name
Conflicts: %Name-fonts %lname-fonts < 1.0-alt0.20060719.1

%description fontutils
Font utils for use with %Name.
%endif


%if_enabled mencoder
%package -n mencoder
Group: Video
Summary: Movie encoder for Unix.
Summary(ru_RU.CP1251): Кодировщик фильмов для Unix.

%description -n mencoder
MEncoder a movie encoder for Unix and is a part of the %name package.
%endif


%package docs
Group: Video
Summary: %Name all docs
Requires: %name-doc-en
Requires: %name-doc-de
Requires: %name-doc-cs
Requires: %name-doc-es
Requires: %name-doc-fr
Requires: %name-doc-hu
Requires: %name-doc-it
Requires: %name-doc-pl
Requires: %name-doc-ru
Requires: %name-doc-zh
%if %name != %Name
Provides: %Name-docs
Obsoletes: %Name-docs
%endif

%description docs
%Name all docs.


%package doc-en
Group: Video
Summary: %Name English docs
Obsoletes: %Name-doc
Provides: %Name-doc
%if %name != %Name
Provides: %Name-doc-en
Obsoletes: %Name-doc-en
%endif

%description doc-en
%Name English docs.


%package doc-cs
Group: Video
Summary: %Name Czesh docs
%if %name != %Name
Provides: %Name-doc-cs
Obsoletes: %Name-doc-cs
%endif

%description doc-cs
%Name Czesh docs.


%package doc-de
Group: Video
Summary: %Name German docs
%if %name != %Name
Provides: %Name-doc-de
Obsoletes: %Name-doc-de
%endif

%description doc-de
%Name German docs.


%package doc-es
Group: Video
Summary: %Name Spanish docs
%if %name != %Name
Provides: %Name-doc-es
Obsoletes: %Name-doc-es
%endif

%description doc-es
%Name Spanish docs.


%package doc-fr
Group: Video
Summary: %Name French docs
%if %name != %Name
Provides: %Name-doc-fr
Obsoletes: %Name-doc-fr
%endif

%description doc-fr
%Name French docs.


%package doc-hu
Group: Video
Summary: %Name Hungarian docs
%if %name != %Name
Provides: %Name-doc-hu
Obsoletes: %Name-doc-hu
%endif

%description doc-hu
%Name Hungarian docs.


%package doc-it
Group: Video
Summary: %Name Italian docs
%if %name != %Name
Provides: %Name-doc-it
Obsoletes: %Name-doc-it
%endif

%description doc-it
%Name Italian docs.


%package doc-pl
Group: Video
Summary: %Name Polish docs
%if %name != %Name
Provides: %Name-doc-pl
Obsoletes: %Name-doc-pl
%endif

%description doc-pl
%Name Polish docs.


%package doc-ru
Group: Video
Summary: %Name Russian docs
%if %name != %Name
Provides: %Name-doc-ru
Obsoletes: %Name-doc-ru
%endif

%description doc-ru
%Name Russian docs.


%package doc-zh
Group: Video
Summary: %Name Taiwan Chinese docs
%if %name != %Name
Provides: %Name-doc-zh
Obsoletes: %Name-doc-zh
%endif

%description doc-zh
%Name Taiwan Chinese docs.


%if %vidixlib == int
%package vidix-drivers
Group: Video
Summary: VIDeo Interface for *nIX
Requires: %lname-vidix-trident = %version-%release
Requires: %lname-vidix-mga = %version-%release
Requires: %lname-vidix-permedia2 = %version-%release
Requires: %lname-vidix-permedia3 = %version-%release
Requires: %lname-vidix-radeon = %version-%release
Requires: %lname-vidix-rage128 = %version-%release
Requires: %lname-vidix-savage = %version-%release
Requires: %lname-vidix-nvidia = %version-%release
Requires: %lname-vidix-sis = %version-%release
Requires: %lname-vidix-unichrome = %version-%release
Requires: %lname-vidix-genfb = %version-%release
%if %name != %Name
Obsoletes: %Name-vidix
%endif

%description vidix-drivers
VIDIX is the abbreviation for VIDeo Interface for *niX.
VIDIX was designed and introduced as an interface for fast user-space
drivers providing DGA. Hopefully these drivers will be as portable as
X11 (not only on *nix).
Basic features:
* It's a portable successor of mga_vid technology, but it's located in
  user-space. 
* Unlike X11 it provides DGA everywhere it's possible.
* Unlike v4l it provides interface for video playback.
* Unlike linux's drivers it uses the math library.
This virtual package provides VIDIX drivers.

%description vidix-drivers -l ru_RU.CP1251
VIDIX - это аббревиатура для VIDeo Interface for *niX (ВИДео Интерфейс
для юниКСоподобных операционных систем).
VIDIX был спроектирован и разработан как интерфейс для быстрых
драйверов уровня приложения для DGA (Direct Graphics Access - прямой
доступ к графике). Предполагалось, что эти драйвера будут также
переносимы как и X11 (не только на юникс).
Основные характеристики:
* Это переносимое развитие технологии mga_vid, работающее на уровне
  приложения.
* В отличие от X11 он предоставляет DGA везде, где это возможно.
* В отличие от v4l он предоставляет интерфейс для воспроизведения 
  видео.
* В отличие от драйверов линукс он использует библиотеку math.
Этот виртуальный пакет предоставляет VIDIX-драйверы.


%package vidix-mach64
Group: Video
Summary: VIDIX driver for ATI Mach64 and 3DRage chips
Requires: %lname
Provides: %name-vidix-driver
%if %name != %Name
Provides: %Name-vidix-mach64
Obsoletes: %Name-vidix-mach64
%endif

%description vidix-mach64
VIDIX driver for ATI Mach64 and 3DRage chips.


%package vidix-mga
Group: Video
Summary: VIDIX drivers for Matrox Gxxx series
Requires: %lname
Provides: %name-vidix-driver
%if %name != %Name
Provides: %Name-vidix-mga
Obsoletes: %Name-vidix-mga
%endif

%description vidix-mga
Two VIDIX drivers for Matrox Gxxx series (using BES and CRTC2).


%package vidix-nvidia
Group: Video
Summary: VIDIX driver for nVidia chips
Requires: %lname
Provides: %name-vidix-driver
%if %name != %Name
Provides: %Name-vidix-nvidia
Obsoletes: %Name-vidix-nvidia
%endif

%description vidix-nvidia
VIDIX driver for nVidia chips.


%package vidix-permedia3
Group: Video
Summary: VIDIX driver for 3DLabs Permedia3 cards
Requires: %lname
Provides: %name-vidix-driver
%if %name != %Name
Provides: %Name-vidix-permedia
Obsoletes: %Name-vidix-permedia
%endif

%description vidix-permedia3
VIDIX driver for 3DLabs GLINT R3/Permedia3 cards.


%package vidix-radeon
Group: Video
Summary: VIDIX driver for ATI Radeon
Requires: %lname
Provides: %name-vidix-driver
%if %name != %Name
Provides: %Name-vidix-radeon
Obsoletes: %Name-vidix-radeon
%endif

%description vidix-radeon
VIDIX driver for ATI Radeon.


%package vidix-rage128
Group: Video
Summary: VIDIX driver for ATI Rage128
Requires: %lname
Provides: %name-vidix-driver
%if %name != %Name
Provides: %Name-vidix-rage128
Obsoletes: %Name-vidix-rage128
%endif

%description vidix-rage128
VIDIX driver for ATI Rage128.


%package vidix-savage
Group: Video
Summary: VIDIX driver for S3 Savage
Requires: %lname
Provides: %name-vidix-driver
%if %name != %Name
Provides: %Name-vidix-savage
Obsoletes: %Name-vidix-savage
%endif

%description vidix-savage
VIDIX driver for S3 Savage.


%package vidix-sis
Group: Video
Summary: VIDIX driver for SiS 300 and 310/325 series chips
Requires: %lname
Provides: %name-vidix-driver
%if %name != %Name
Provides: %Name-vidix-sis
Obsoletes: %Name-vidix-sis
%endif

%description vidix-sis
VIDIX driver for SiS 300 and 310/325 series chips.


%package vidix-trident
Group: Video
Summary: VIDIX driver for Trident Cyberblade/i1
Provides: %name-vidix-cyberblade
Provides: %name-vidix-driver
%if %name != %Name
Provides: %Name-vidix-trident
Obsoletes: %Name-vidix-trident
%endif

%description vidix-trident
VIDIX driver for Trident Cyberblade/i1.


%package vidix-unichrome
Group: Video
Summary: VIDIX driver for VIA CLE266 Unichrome
Requires: %lname
Provides: %name-vidix-via
Provides: %name-vidix-driver

%description vidix-unichrome
VIDIX driver for VIA CLE266 Unichrome.
%endif


%if_enabled nls
%package i18n
Group: Video
Summary: Languages support for %Name

%description i18n
Languages support for %Name.
%endif


%prep
%if %svnrev
%if_enabled shared_ffmpeg
%setup -q -n %lname-%pkgver
%else
%setup -q -n %lname-%pkgver -a 1
%if_enabled dirac
pushd ffmpeg-svn-%ffmpeg_svnrev
%patch9 -p1
popd
%endif
mv ffmpeg-svn-%ffmpeg_svnrev/lib{av{codec,format,util},postproc} .
%endif
%else
%setup -q -n %Name-%pkgver
%endif

%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1
%{?_enabl_dirac:%patch7 -p1}
%if %swscalelib == ext
%patch8 -p1
%endif
%patch10 -p1
%patch11 -p1
%patch12 -p1
%patch13 -p1
%patch14 -p1
%patch15 -p1
%patch16 -p1
%patch17 -p1
%patch21 -p1
%{?_enable_polyp:%{?_disable_old_polyp:%patch22 -p1}}
%ifdef svnrev
%patch26 -p1
%patch27 -p1
%endif
%{?_enable_polyp:%{?_disable_old_polyp:sed -e 's/\([Pp]\)ulse/\1olyp/g' -e 's/PULSE/POLYP/g' libao2/ao_pulse.c > libao2/ao_polyp.c}}

subst 's/\(ldconfig\)/\#\1/g' libdha/Makefile
%{?_enable_dvdnav:subst 's|\(\<\)\(dvdnav\)\(\.h\>\)|\1\2/\2\3|' configure}

%ifdef svnrev
subst 's/UNKNOWN/%svnrev/' version.sh
# iconv pl docs
pushd DOCS/xml/pl
for f in $(grep -H -l ' encoding="utf-8"' *.xml); do
    mv -f $f xml.utf8
    sed -e '1 s/ encoding="utf-8"/ encoding="iso-8859-2"/' xml.utf8 | iconv -c -f utf-8 -t ISO-8859-2 > $f
done
rm -f xml.utf8
popd
%endif

%if_enabled nls
install -d -m 0755 po
gzip -dc %SOURCE6 > po/mp_help2msg.awk
gzip -dc %SOURCE7 > po/mp_msg2po.awk
%endif

%build
%if_disabled debug
%define _optlevel 4
export CFLAGS="%optflags"
%endif
export LC_MESSAGES=C
./configure \
		--prefix=%_prefix \
		--bindir=%_bindir \
		--datadir=%_datadir/%name \
		--mandir=%_mandir \
		--confdir=%_sysconfdir/%name \
		--libdir=%_libdir \
		%{subst_enable mencoder} \
		%{subst_enable gui} \
		%{subst_enable gtk1} \
		%{subst_enable largefiles} \
		%{subst_enable_to devfs linux-devfs} \
		%{subst_enable termcap} \
		%{subst_enable termios} \
		%{subst_enable nls} \
		%{subst_enable iconv} \
		%{subst_enable langinfo} \
		%{subst_enable lirc} \
		%{subst_enable lircc} \
		%{subst_enable joystick} \
		%{subst_enable xf86keysym} \
		%{subst_enable tv} \
		%{subst_enable_to v4l1 tv-v4l1} \
		%{subst_enable_to v4l2 tv-v4l2} \
                %{subst_enable radio} \
		%{subst_enable_to radio_v4l1 radio-v4l} \
		%{subst_enable_to radio_v4l2 radio-v4l2} \
		%{subst_enable_to radio_capture radio-capture} \
		%{subst_enable_to bsdbt848 tv-bsdbt848} \
		%{subst_enable pvr} \
		%{subst_enable rtc} \
		%{subst_enable network} \
		%{subst_enable winsock2} \
		%{subst_enable smb} \
		%{subst_enable live} \
		%{?_enable_live:--with-livelibdir=%_libdir/live} \
		%{subst_enable dvdnav} \
		%{subst_enable dvdread} \
		%{subst_enable mpdvdkit} \
		%{subst_enable cdparanoia} \
		%{subst_enable_to bitmap_font bitmap-font} \
		%{subst_enable freetype} \
		%{subst_enable fontconfig} \
		%{subst_enable unrarlib} \
		%{subst_enable_to osdmenu menu} \
		%{subst_enable sortsub} \
		%{subst_enable fribidi} \
		%{?_enable_fribidi:--with-fribidi-config="pkg-config fribidi"} \
		%{subst_enable enca} \
		%{subst_enable macosx} \
		%{subst_enable_to macosx_finder macosx-finder-support} \
		%{subst_enable_to macosx_bundle macosx-bundle} \
		%{subst_enable_to IPv6 inet6} \
		%{subst_enable gethostbyname2} \
		%{subst_enable ftp} \
		%{subst_enable vstream} \
		%{subst_enable pthreads} \
		%{subst_enable ass} \
		%{subst_enable rpath} \
		%{subst_enable gif} \
		%{subst_enable png} \
		%{subst_enable jpeg} \
		%{subst_enable libcdio} \
		%{subst_enable_to lzo liblzo} \
		%{subst_enable win32} \
		%{?_enable_win32:--with-win32libdir=%win32_libdir} \
		%{subst_enable qtx} \
		%{subst_enable xanim} \
		%{?_enable_xanim:--with-xanimlibdir=%xanim_libdir} \
		%{subst_enable real} \
		%{?_enable_real:--with-reallibdir=%real_libdir} \
		%{subst_enable xvid} \
		%{subst_enable x264} \
%if_enabled ffmpeg
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
%else
		--disable-libavcodec \
		--disable-libavformat \
		--disable-libavutil \
		--disable-libpostproc \
		--disable-libavcodec_so \
		--disable-libavformat_so \
		--disable-libavutil_so \
		--disable-libpostproc_so \
%endif
		%{subst_enable_to fame libfame} \
		%{subst_enable_to tremor_internal tremor-internal} \
		%{subst_enable_to tremor_low tremor-low} \
		%{subst_enable_to tremor_external tremor-external} \
		%{subst_enable_to vorbis libvorbis} \
		%{subst_enable speex} \
		%{subst_enable theora} \
		%{?_enabled_faad_int:--enable-faad-internal --disable-faad-external} \
		%{?_enabled_faad_ext:--enable-faad-external --disable-faad-internal} \
		%{subst_enable faac} \
		%{subst_enable ladspa} \
		%{subst_enable libdv} \
		%{subst_enable mad} \
		%{subst_enable toolame} \
		%{subst_enable twolame} \
		%{subst_enable xmms} \
		%{subst_enable mp3lib} \
		%{subst_enable liba52} \
		%{subst_enable libdts} \
		%{subst_enable libmpeg2} \
		%{subst_enable musepack} \
		%{?_enable_dirac:--enable-dirac} \
%if_enabled vidix
%if %vidixlib == ext
		--enable-vidix-external --disable-vidix-internal \
%else
		--disable-vidix-external --enable-vidix-internal \
%endif
%else
		--disable-vidix-external --disable-vidix-internal \
%endif
		%{subst_enable gl} \
		%{subst_enable dga} \
		%{subst_enable vesa} \
		%{subst_enable svga} \
		%{subst_enable sdl} \
		%{subst_enable aa} \
		%{subst_enable caca} \
		%{subst_enable ggi} \
		%{subst_enable ggiwmh} \
		%{subst_enable directx} \
		%{subst_enable dxr2} \
		%{subst_enable dxr3} \
		%{subst_enable ivtv} \
		%{subst_enable dvb} \
		%{subst_enable dvbhead} \
		%{subst_enable mga} \
	        %{subst_enable xmga} \
		%{subst_enable xv} \
		%{subst_enable xvmc} \
		%{subst_enable vm} \
		%{subst_enable xinerama} \
		%{subst_enable x11} \
		%{subst_enable fbdev} \
		%{subst_enable mlib} \
		%{subst_enable 3dfx} \
		%{subst_enable tdfxfb} \
		%{subst_enable s3fb} \
		%{subst_enable directfb} \
		%{subst_enable zr} \
		%{subst_enable bl} \
		%{subst_enable tdfxvid} \
		%{subst_enable tga} \
		%{subst_enable pnm} \
		%{subst_enable md5sum} \
		%{subst_enable alsa} \
		%{subst_enable_to oss ossaudio} \
		%{subst_enable arts} \
		%{subst_enable esd} \
		%{subst_enable pulse} \
		%{subst_enable polyp} \
		%{subst_enable jack} \
		%{subst_enable openal} \
		%{subst_enable nas} \
		%{subst_enable sgiaudio} \
		%{subst_enable sunaudio} \
		%{subst_enable_to waveout win32waveout} \
		%{subst_enable select} \
		%{subst_enable_to cpu_detection runtime-cpudetection} \
		--cc=%ccomp \
		--as=%asm \
		--charset=%charset \
		--language="%language" \
		%{subst_enable mmx} \
		%{subst_enable mmxext} \
		%{subst_enable 3dnow} \
		%{subst_enable 3dnowext} \
		%{subst_enable sse} \
		%{subst_enable sse2} \
		%{subst_enable altivec} \
		%{subst_enable fastmemcpy} \
%if_enabled debug
		--enable-debug=3} \
%else
		--disable-debug \
%endif
		%{subst_enable prifile} \
		%{subst_enable sighandler} \
		%{subst_enable_to gdb crash-debug} \
		%{subst_enable_to dynamic_plugins dynamic-plugins} \
		--with-extraincdir=%_includedir/vidix:%_includedir/directfb

%ifnarch x86_64
make
%else
%make_build
%endif

# make conf file
gzip -dc %SOURCE5 |
sed -e 's/^@VO@/vo = %default_vo/' \
    -e 's/^@AO@/ao = %default_ao/' \
    -e 's|@CONF_FILE@|%_sysconfdir/%name/%lname.conf|g' \
    -e 's|@SKINS_DIR@|%_datadir/%name/skins|g' \
    > etc/%lname.conf
%if_enabled fontconfig
echo "fontconfig = yes" >> etc/%lname.conf
%else
echo "fontconfig = no" >> etc/%lname.conf
%endif

%{?_enable_freetype:make -C TOOLS/subfont-c}

# can't build vivodump subrip
%make_build -C TOOLS 302m_convert 360m_convert alaw-gen asfinfo avi-fix avisubdump bios2dump dump_mp4 mem2dump movinfo png2raw

%if %svnrev
# build HTML documentation from XML files
pushd DOCS/xml
cp -fL %_sysconfdir/sgml/catalog ./
echo 'CATALOG "/usr/share/xml/xml-iso-entities-8879.1986/catalog"' >> ./catalog
./configure
%make_build html-chunked
#for lang in cs de en es fr hu pl ru; do
#    make html-chunked-$lang
#done
popd
%endif

%if_enabled nls
pushd po
gawk -f ./mp_help2msg.awk ../help/help_mp-en.h > en.msg
for h in $(ls ../help/help_mp-*.h | grep -v '..help/help_mp-en.h$'); do
    l=$(basename ${h/help_mp-} .h)
    gawk -f ./mp_help2msg.awk $h | iconv -c -f $(cat $h.charset) -t UTF-8 | awk -f ./mp_msg2po.awk en.msg > $l.po
    msgfmt -o $l.gmo $l.po
done
popd
%endif


%install

%make_install DESTDIR=%buildroot install

install -d -m 0755 %buildroot%_datadir/%name/skins
tar -C %buildroot%_datadir/%name/skins -xjf %SOURCE4
ln -s standard %buildroot%_datadir/%name/skins/default

%{?_enable_freetype:%{?_disable_fontconfig:ln -s ../fonts/default/Type1/n019003l.pfb %buildroot%_datadir/%name/subfont.ttf}}

install -m 0644 etc/{codecs,input,%lname}.conf %buildroot%_sysconfdir/%name/

%{?_enable_osdmenu:install -m 0644 etc/menu.conf %buildroot%_sysconfdir/%name/}
%{?_enable_dvb:install -m 0644 etc/dvb-menu.conf %buildroot%_sysconfdir/%name/}

%if_enabled freetype
install -d %buildroot%_datadir/%name/fonts/{osd,encodings}
install -m 0644 TOOLS/subfont-c/font.desc.tail %buildroot%_datadir/%name/fonts/
install -m 0755 TOOLS/subfont-c/{fontgen,runme} %buildroot%_datadir/%name/fonts/
install -m 0644 TOOLS/subfont-c/osd/osd.pfb %buildroot%_datadir/%name/fonts/osd/
install -m 0755 TOOLS/subfont-c/osd/{gen.py,runme} %buildroot%_datadir/%name/fonts/osd/
install -m 0644 TOOLS/subfont-c/encodings/{osd-%lname,runme-kr} %buildroot%_datadir/%name/fonts/encodings/
install -m 0755 TOOLS/subfont-c/encodings/charmap2enc %buildroot%_datadir/%name/fonts/encodings/
install -m 0755 TOOLS/subfont-c/subfont %buildroot%_bindir/%{lname}_subfont
%endif

%{?_with_soundwrapper:install -pD -m 0755 %SOURCE3 %buildroot%_sysconfdir/bashrc.d/%lname.sh}

# Menus
[ "%name" = "%lname" ] || mv %buildroot%_desktopdir/%lname.desktop %buildroot%_desktopdir/%name.desktop
iconv -f cp1251 -t utf-8 >> %buildroot%_desktopdir/%name.desktop <<__MENU__
Version=1.0
GenericName[uk]=Програвач мультимедіа
X-MultipleArgs=true
StartupNotify=true
__MENU__

# docs
bzip2 --best --force --keep -- ChangeLog
for l in $(ls DOCS/man | grep -v 'en'); do
    install -pD -m 0644 DOCS/man/$l/%lname.1 %buildroot%_mandir/$l/man1/%lname.1
    %{?_enable_mencoder:install -m 0644 DOCS/man/$l/%lname.1 %buildroot%_mandir/$l/man1/mencoder.1}
done
rm -f %buildroot%_man1dir/mencoder.1
%{?_enable_mencoder:install -m 0644 DOCS/man/en/%lname.1 %buildroot%_man1dir/mencoder.1}
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

%if_enabled nls
for l in po/*.gmo; do
install -pD -m 0644 $l %buildroot%_datadir/locale/$(basename $l .gmo)/LC_MESSAGES/%name.mo
done
%endif

%find_lang --with-man %lname
%{?_enable_mencoder:%find_lang --with-man mencoder}

# a tribute to clever python support
unset RPM_PYTHON

%add_verify_elf_skiplist %_libdir/%lname/vidix/*


%if_enabled gui
%post gui
%update_menus

%postun gui
%clean_menus
%endif


%files
%doc README AUTHORS ChangeLog.*
%_bindir/%lname
%{?_enable_freetype:%_bindir/%{lname}_subfont}
%dir %_sysconfdir/%name
%config %_sysconfdir/%name/codecs.conf
%config(noreplace) %verify(not size mtime md5) %_sysconfdir/%name/%lname.conf
%config(noreplace) %verify(not size mtime md5) %_sysconfdir/%name/input.conf
%{?_enable_osdmenu:%config(noreplace) %verify(not size mtime md5) %_sysconfdir/%name/menu.conf}
%{?_enable_dvb:%config(noreplace) %verify(not size mtime md5) %_sysconfdir/%name/dvb-menu.conf}
%{?_with_soundwrapper:%_sysconfdir/bashrc.d/*}
%dir %_datadir/%name
%if_disabled fontconfig
%if_enabled freetype
%config(missingok,noreplace) %verify(not link size mtime md5) %_datadir/%name/subfont.ttf
%else
%_datadir/%name/font
%endif
%endif


%if_enabled gui
%files gui
%_bindir/%gname
%_desktopdir/*
%_datadir/pixmaps/*
%dir %_datadir/%name/skins
%_datadir/%name/skins/standard
%_datadir/%name/skins/default
%endif


%if_enabled freetype
%files fontutils
%_bindir/%{lname}_subfont
%dir %_datadir/%name/fonts
%dir %_datadir/%name/fonts/osd
%dir %_datadir/%name/fonts/encodings
%_datadir/%name/fonts/fontgen
%_datadir/%name/fonts/runme
%_datadir/%name/fonts/font.desc.tail
%_datadir/%name/fonts/osd/*
%_datadir/%name/fonts/encodings/*
%endif


%if_enabled mencoder
%files -n mencoder -f mencoder.lang
%_bindir/mencoder
%endif


%files doc-en
%_docdir/%name-doc-%version/en


%files doc-cs
%_docdir/%name-doc-%version/cs


%files doc-de
%_docdir/%name-doc-%version/de


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


%if %vidixlib == int
%files vidix-drivers


%files vidix-mach64
%_libdir/%lname/vidix/mach64_vid.so


%files vidix-mga
%_libdir/%lname/vidix/mga_crtc2_vid.so
%_libdir/%lname/vidix/mga_vid.so


%files vidix-nvidia
%_libdir/%lname/vidix/nvidia_vid.so


%files vidix-permedia3
%_libdir/%lname/vidix/pm3_vid.so

%files vidix-radeon
%_libdir/%lname/vidix/radeon_vid.so


%files vidix-rage128
%_libdir/%lname/vidix/rage128_vid.so


%files vidix-savage
%_libdir/%lname/vidix/savage_vid.so


%files vidix-sis
%_libdir/%lname/vidix/sis_vid.so


%files vidix-trident
%_libdir/%lname/vidix/cyberblade_vid.so


%files vidix-unichrome
%_libdir/%lname/vidix/unichrome_vid.so
%endif


%if_enabled nls
%files i18n -f %lname.lang
%endif


%changelog
* Fri Sep 15 2006 Led <led@altlinux.ru> 1:1.0-alt1.19833.2
- fixed %%files section

* Thu Sep 14 2006 Led <led@altlinux.ru> 1:1.0-alt1.19833.1
- new SVN snapshot (revision 19833)

* Mon Sep 11 2006 Led <led@altlinux.ru> 1:1.0-alt1.19794.1
- new SVN snapshot (revision 19794)
- cleaned up spec

* Fri Sep 08 2006 Led <led@altlinux.ru> 1:1.0-alt1.19734.1
- new SVN snapshot (revision 19734)

* Fri Sep 08 2006 Led <led@altlinux.ru> 1:1.0-alt1.19700.2
- fixed BuildRequires
- fixed install mans

* Thu Sep 07 2006 Led <led@altlinux.ru> 1:1.0-alt1.19700.1
- new SVN snapshot (revision 19700)

* Tue Sep 05 2006 Led <led@altlinux.ru> 1:1.0-alt1.19671.2
- added %lname-svn-r19671-pulseaudio.patch (based on
  mplayer-pulse.patch from http://pulseaudio.org
- enabled pulse
- disabled polyp (obsoleted with pulse)

* Tue Sep 05 2006 Led <led@altlinux.ru> 1:1.0-alt1.19671.1
- new SVN snapshot (revision 19671)
- added NLS support: mp_help2msg.awk, mp_msg2po.awk,
  %lname-svn-r19595-nls.patch
- added %name-i18n package
- fixed spec

* Wed Aug 30 2006 Led <led@altlinux.ru> 1:1.0-alt1.19595.1
- new SVN snapshot (revision 19595):
  + Radio support (radio://)
- enabled radio

* Wed Aug 30 2006 Led <led@altlinux.ru> 1:1.0-alt1.19558.3
- rebuild with external vidix from MPlayer's SVN

* Tue Aug 29 2006 Led <led@altlinux.ru> 1:1.0-alt1.19558.2
- added %lname-svn-r19558-generic-x86_64.patch (thanks LAKostis)
- disabled win32 for x86_64
- enabled internal vidix
- fixed %%prep section
- forced internal vidix (if enabled) for non-ix86 arches

* Mon Aug 28 2006 Led <led@altlinux.ru> 1:1.0-alt1.19558.1
- new SVN snapshot (revision 19558)
- fixed configure parameters
- fixed spec
- removed %Name-1.0pre7try2-libdir_fix.patch
- updated %lname-uni-svn19558.diff
- cleaned up and fixed spec
- enabled samba

* Mon Aug 21 2006 Led <led@altlinux.ru> 1:1.0-alt1.19467.1
- new SVN snapshot (revision 19467)
  + support for chapters seeking in dvdnav:// stream
- updated %lname-svn-r19467-configure.patch
- fixed %lname.conf
- fixed %%changelog

* Sat Aug 19 2006 Led <led@altlinux.ru> 1:1.0-alt1.19447.2
- enabled: dvdnav, joystick, tga, xmms
- fixed Provides
- added %lname-svn-r19447-vo_vidix.patch

* Sat Aug 19 2006 Led <led@altlinux.ru> 1:1.0-alt1.19447.1
- new SVN snapshot (revision 19447)
  + support for chapters seeking in dvd:// stream
- fixed build with external vidix
- cleaned up spec
- removed:
  + %Name-svn-20060707-ext_vidix_drivers-0.9.9.1.patch,
  + vidix-0.9.9.1-pm3_vid.patch,
  + %Name-svn-20060630-vidix_ext_drivers.patch,
  + %Name-svn-20060630-vidix_0.9.9.1.patch
- updated %lname-svn-r19447-configure.patch
- added lname-svn-r19427-libdha.patch

* Thu Aug 17 2006 Led <led@altlinux.ru> 1:1.0-alt1.19416.1
- new SVN snapshot (revision 19416)
- fixed and updated %lname-svn-r19416-configure.patch
- fixed %%changelog
- cleaned up spec
- fixed BuildRequires

* Thu Aug 17 2006 Led <led@altlinux.ru> 1:1.0-alt1.19389.1
- new SVN snapshot (revision 19389)
- fixed spec
- fixed configure parameters (renaming and removed in upstream)
- new release numbering (therewith SVN revision)
- enabled external libswscale (libffmpeg)
- added %Name-1.0pre8-udev.patch
- fixed directfb ability
- added %lname-svn-r19389-ext_ffmpeg.patch

* Thu Jul 20 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060720.1
- new SVN snapshot (revision 19134)
- fixed lapses in %%changelog and %%description
- without soundwrapper
- making correct version.h
- removed %name-fonts
- added %name-fontutils

* Mon Jul 17 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060717.1
- new SVN snapshot (revision 19126)
- removed divx4linux and opendivx (upstream)

* Mon Jul 17 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060714.1
- new SVN snapshot (revision 19058)
- cleaned up spec
- changed base package name to %lname

* Thu Jul 13 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060713.1
- new SVN snapshot (revision 19047)
- cleaned up spec
- changed %%name to %lname

* Thu Jul 13 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060712.1
- new SVN snapshot (revision 19018)
- enabled fribidi
- fixed configure parameters

* Wed Jul 12 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060711.1
- new SVN snapshot (revision 19001)
- updated %Name-svn-20060711-configure.patch
- many changes in spec
- enabled libmpeg2, md5sum, 3dfx, tdfxfb
- disabled vesa

* Mon Jul 10 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060710.2
- added %lname-uni-20060710.diff

* Mon Jul 10 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060710.1
- new SVN snapshot (revision 18986)
- updated %Name-svn-20060710-alt-external_fame.patch
- enabled ass (internal SSA/ASS subtitles support)
- fixed spec

* Mon Jul 10 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060707.3
- replaced vidix-0.9.9.1.tar.bz2 with
  %Name-svn-20060707-ext_vidix_drivers-0.9.9.1.patch

* Sat Jul 08 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060707.2
- disabled dirac

* Fri Jul 07 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060707.1
- new SVN snapshot (revision 18929)
- fixed spec
- updated %Name-svn-20060707_dirac-0.5.x.patch

* Thu Jul 06 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060630.5
- enabled internal VIDIX
- disabled external VIDIX
- added vidix-0.9.9.1 with vidix-0.9.9.1-pm3_vid.patch
- added %Name-svn-20060630-vidix_0.9.9.1.patch
- added %Name-svn-20060630-vidix_ext_drivers.patch

* Thu Jul 06 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060630.4
- disabled internal VIDIX
- enabled external VIDIX

* Fri Jun 30 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060630.3
- don't include ffmpeg tarball if shared_ffmpeg enabled (default)
- updated %Name-dvd-ru patch
- cleaned up bogus patches
- fixed spec
- fixed libvo/vo_md5sum.c
- trying dvdmenu (disabled by deafult)
- some fixes from LAKostis (vidix prefixes, bogus BuildRequires)
- added %Name-svn-20060704_dirac-0.5.x.patch
- enabled dirac

* Fri Jun 30 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060630.1
- new SVN snapshot (revision 18853)
- enabled dvdnav
- fixed dvdnav detect

* Thu Jun 29 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060629.1
- new SVN snapshot (revision 18847)

* Mon Jun 26 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060626.1
- new SVN snapshot (revision 18821)
- removed %Name-cvs-20060506-docs.patch, used sed & iconv instead

* Fri Jun 23 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060623.1
- new SVN snapshot (revision 18791)

* Thu Jun 22 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060622.1
- new SVN snapshot (revision 18781)
- returned %name.sh (soundwrapper)
- cleaned up spec

* Wed Jun 21 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060621.1
- new SVN snapshot (revision 18766)
- added macroses
- enabled external tremor
- force enabled openal
- %Name-cvs-20060220-configure.patch merged with
  %Name-1.0pre7-aalib.patch and some additions to
  %Name-svn-20060621-configure.patch

* Tue Jun 20 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060620.1
- new SVN snapshot (revision 18760)
- fixed spec
- updated %Name-svn-20060620-alt-external_fame.patch
- fixed configure parameters
- cleaned up spec

* Tue Jun 13 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060613.1
- new SVN snapshot (revision 18698)
- removed additional icons
- fixed .desktop file
- removed %name.sh (soundwrapper)
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
- added %Name-cvs-20060519-polyp0.8.patch

* Thu May 25 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060519.1
- 20060519 CVS snapshot
- removed %lname-rpm-cvs.patch

* Thu May 25 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060515.5
- rebuild for libffmpeg

* Wed May 24 2006 Led <led@altlinux.ru> 1:1.0-alt0.20060515.4
- disabled xmms
- enabled gtk+2.0 GUI
- added default (standard) skin to %name-gui package
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
