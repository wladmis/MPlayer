%define set_disable() %{expand:%%force_disable %{1}} %{expand:%%undefine _enable_%{1}}
%define set_enable() %{expand:%%force_enable %{1}} %{expand:%%undefine _disable_%{1}}
%define set_without() %{expand:%%force_without %{1}} %{expand:%%undefine _with_%{1}}
%define subst_enable_to() %{expand:%%{?_enable_%{1}:--enable-%{2}}} %{expand:%%{?_disable_%{1}:--disable-%{2}}}
%define subst_o() %{expand:%%{?_enable_%{1}:%{1},}}
%define subst_o_pre() %{expand:%%{?_enable_%{2}:%{1}%{2},}}
%define subst_o_post() %{expand:%%{?_enable_%{1}:%{1}%{2},}}

#define prerel rc2try2
%define svnrev 26763
%define ffmpeg_svnrev 13150

#----------------------	BEGIN OF PARAMETERS -------------------------------------

# Optional features:
%def_enable mplayer
%def_enable mencoder
%def_enable lame
%def_enable gui
%def_disable gtk1
%def_enable largefiles
%def_disable devfs
%def_enable termcap
%def_enable termios
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
%def_enable teletext
%def_disable pvr
%def_enable rtc
%def_enable network
%def_disable winsock2
%def_enable smb
%def_enable live
%def_enable dvdnav
%def_enable dvdread
%define dvdreadlib ext
%def_enable cdparanoia
%def_enable bitmap_font
%def_enable freetype
%def_enable fontconfig
%def_enable unrarexec
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
%def_disable faad_ext
%def_enable faad_int
%def_disable faad_fixed
%def_disable tremor_internal
%def_disable tremor_low
%def_disable tremor_external
%def_enable vorbis
%def_enable speex
%def_enable theora
%def_enable faac
%def_enable ladspa
%def_enable libdv
%def_enable mad
%def_disable toolame
%def_disable twolame
%def_enable xmms
%def_enable mp3lib
%def_enable liba52
%def_enable libmpeg2
%def_enable musepack
%def_enable dirac
%def_enable nut

# Video output:
%def_enable vidix
%define vidixlib ext
%def_enable gl
%def_disable dga1
%def_enable dga2
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
%define xvmclib XvMCW
%def_enable vm
%def_enable xinerama
%def_enable x11
%def_enable xshape
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
%def_enable jack
%def_enable openal
%def_enable nas
%def_disable sgiaudio
%def_disable sunaudio
%def_disable waveout
%def_enable select

# Miscellaneous options:
%def_enable cpu_detection
%define ccomp gcc
%define asm as
%define charset UTF-8
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
%def_with tools
%define default_vo %{subst_o xv}%{subst_o sdl}%{subst_o gl2}%{subst_o gl}%{subst_o x11}%{subst_o_pre x vidix}%{subst_o mga}%{subst_o dfbmga}%{subst_o tdfxfb}%{subst_o 3dfx}%{subst_o s3fb}%{subst_o_pre c vidix}%{subst_o_post fbdev 2}%{subst_o vesa}%{subst_o caca}%{subst_o aa}null
%define default_ao %{subst_o alsa}%{subst_o oss}%{subst_o openal}%{subst_o sdl}%{subst_o pulse}%{subst_o nas}null
#define odml_chunklen 0x40000000

#----------------------	END OF PARAMETERS ---------------------------------------

%{?_disable_mencoder:%set_disable lame}

%if_disabled tv
%set_disable v4l1
%set_disable v4l2
%set_disable bsdbt848
%set_disable teletext
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

%{?_enable_shared_ffmpeg:%set_disable zr}

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
%set_disable dga1
%set_disable dga2
%endif

%{?_disable_mplayer:%set_without tools}


%define lname mplayer
%define Name MPlayer
Name: %lname
Version: 1.0
%define rel 35
%define subrel 1
%ifdef svnrev
Release: alt%rel.%svnrev.%subrel
%define pkgver svn-r%svnrev
%else
Release: alt%rel
%define pkgver %version%prerel
%endif
Summary: Media player
Summary(uk_UA.CP1251): Медіаплейер
Summary(ru_RU.CP1251): Медиаплейер
License: GPL
Group: Video
URL: http://www.mplayerhq.hu
%if %name != %Name
Provides: %Name = %version-%release
Obsoletes: %Name
%endif
%if_enabled freetype
%{?_disable_fontconfig:Requires: fonts-type1-urw}
Conflicts: %Name-fonts < 1.0-alt28
Conflicts: %name-i18n < 1.0-35.22229.1
Obsoletes: %Name-fonts
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
Source5: %lname.conf.in
Source6: mp_help2msg.awk.gz
Source7: mp_msg2po.awk.gz
Patch0: %lname-svn-r22221-subreader.patch
Patch1: %lname-svn-r26706-dirac-0.9.1.patch
Patch2: %lname-dvd-ru-svn19389.patch.gz
Patch3: %Name-1.0pre4-alt-explicit_gif.patch
Patch4: %lname-svn-r26450-gui.patch
Patch5: %lname-svn-r25454-vo_vidix.patch
Patch6: %lname-svn-r21128-alt-artsc_ldflags.patch.gz
Patch7: %lname-svn-r23099-demux_nut.patch
Patch8: %lname-svn-r23722-VIDM-win32-codec.patch
Patch11: %lname-svn-r24081-nls.patch
Patch12: %lname-uni-svn26706.patch
Patch13: %Name-svn-20060711-vbe.patch.gz
Patch14: %lname-svn-r26450-gui_nls.patch
Patch16: %lname-svn-r26708-configure.patch
Patch17: %lname-svn-r26706-ext_ffmpeg.patch
Patch27: %lname-svn-r26450-builddocs.patch
%if_disabled shared_ffmpeg
Patch32: ffmpeg-svn-r12807-xvmc-vld.patch
Patch33: ffmpeg-svn-r13104-amr.patch
%endif

# Automatically added by buildreq on Wed May 30 2007
#BuildRequires: aalib-devel docbook-dtds docbook-style-xsl esound-devel gcc-c++ kdelibs ladspa_sdk libarts-devel libaudio-devel libavformat-devel libcaca-devel libcdparanoia-devel libdv-devel libdvdnav-devel libdvdread-devel libenca-devel libfribidi-devel libgpm-devel libgtk+2-devel libjpeg-devel liblirc-devel liblive555-devel liblzo2-devel libmesa-devel libmpcdec-devel libopenal-devel libpostproc-devel libpulseaudio-devel libSDL-devel libSDL_image-devel libslang-devel libsmbclient-devel libspeex-devel libswscale-devel libungif-devel libvidix-devel libXinerama-devel libxmms-devel libXvMC-devel libXxf86dga-devel subversion svgalib-devel xsltproc

BuildRequires: %awk libncurses-devel libslang-devel zlib-devel
BuildRequires: libdca-devel
BuildRequires: cpp >= 3.3 gcc >= 3.3 gcc-c++ >= 3.3
%{?svnrev:%{?_with_htmldocs:BuildRequires: docbook-style-xsl xsltproc sgml-common docbook-dtds}}

%{?_enable_mencoder:%{?_enable_lame:BuildRequires: liblame-devel}}
%{?_enable_termcap:BuildRequires: libtinfo-devel}
%{?_enable_smb:BuildRequires: libsmbclient-devel >= 3.0.3}
%{?_enable_live:BuildRequires: liblive555-devel >= 0.0.0-alt0.2006.03.03}
%{?_enable_dvdnav:BuildRequires: libdvdnav-devel >= 0.1.10-alt4}
%{?_enable_dvdread:BuildRequires: libdvdread-devel}
%{?_enable_cdparanoia:BuildRequires: libcdparanoia-devel}
%{?_enable_vstream:BuildRequires: libvstream-client-devel}
%if_enabled mplayer
%{?_enable_lirc:BuildRequires: liblirc-devel}
%{?_enable_freetype:BuildRequires: libfreetype-devel >= 2.0.9}
%{?_enable_fontconfig:BuildRequires: fontconfig-devel}
%{?_enable_fribidi:BuildRequires: libfribidi-devel}
%{?_enable_enca:BuildRequires: libenca-devel}
%endif

%{?_enable_gif:BuildRequires: libungif-devel}
%{?_enable_png:BuildRequires: libpng-devel}
%{?_enable_jpeg:BuildRequires: libjpeg-devel}
%{?_enable_libcdio:BuildRequires: libcdio-devel}
%{?_enable_lzo:BuildRequires: liblzo2-devel}
%{?_enable_xvid:BuildRequires: libxvid-devel}
%{?_enable_x264:BuildRequires: libx264-devel}
%{?_enable_shared_ffmpeg:BuildRequires: libffmpeg-devel >= 1:0.5.0-alt0.12828.1}
%{?_enable_tremor_external:BuildRequires: libtremor-devel}
%{?_enable_vorbis:BuildRequires: libvorbis-devel}
%{?_enable_speex:BuildRequires: libspeex-devel}
%{?_enable_theora:BuildRequires: libtheora-devel}
%{?_enable_faad_ext:BuildRequires: libfaad-devel}
%{?_enable_faac:BuildRequires: libfaac-devel}
%{?_enable_ladspa:BuildRequires: ladspa_sdk}
%{?_enable_libdv:BuildRequires: libdv-devel}
%{?_enable_mad:BuildRequires: libmad-devel}
%{?_enable_xmms:BuildRequires: libxmms-devel}
%{?_enable_liba52:BuildRequires: liba52-devel}
%{?_enable_libmpeg2:BuildRequires: libmpeg2-devel}
%{?_enable_musepack:BuildRequires: libmpcdec-devel >= 1.2.1}
%{?_enable_nut:BuildRequires: libnut-devel >= 0.0-alt0.272}
%{?_enable_dirac:BuildRequires: libdirac-devel >= 0.9}

%{?_enable_xvmc:BuildRequires: libXvMC-devel}
%if_enabled mplayer
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
%{?_enable_vm:BuildRequires: libXxf86vm-devel}
%{?_enable_xinerama:BuildRequires: libXinerama-devel}
%{?_enable_x11:BuildRequires: libXt-devel}
%{?_enable_dga1:BuildRequires: libXxf86dga-devel}
%{?_enable_dga2:BuildRequires: libXxf86dga-devel}
%{?_enable_directfb:BuildRequires: libdirectfb-devel}
%{?_enable_pnm:BuildRequires: libnetpbm-devel}

%{?_enable_alsa:BuildRequires: libalsa-devel}
%{?_enable_arts:BuildRequires: libarts-devel}
%{?_enable_esd:BuildRequires: esound-devel}
%{?_enable_pulse:BuildRequires: libpulseaudio-devel >= 0.9}
%{?_enable_jack:BuildRequires: jackit-devel}
%{?_enable_openal:BuildRequires: libopenal-devel}
%{?_enable_nas:BuildRequires: libaudio-devel}

%if_enabled gui
BuildRequires: ImageMagick desktop-file-utils
%if_enabled gtk1
BuildRequires: gtk+-devel
%else
BuildRequires: libgtk+2-devel
%endif
%endif
%endif

%{?_enable_nls:BuildRequires: gettext-tools}

%if_with tools
BuildRequires: perl-libwww perl-Math-BigInt libSDL_image-devel
BuildRequires: normalize sox termutils vcdimager mjpegtools
%endif

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


%if_enabled mplayer
%if_enabled gui
%package gui
%define gname g%lname
Summary:  %Name (GUI version)
Summary(uk_UA.CP1251): Медіаплейер (GUI вариант)
Summary(ru_RU.CP1251): Медиаплейер (GUI вариант)
Group: Video
Requires: %name >= 1.0
Provides: %gname = %version-%release
Obsoletes: %Name-skin-default
%if %name != %Name
Provides: %Name-gui = %version-%release
Obsoletes: %Name-gui
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
%endif


%if_enabled mencoder
%package -n mencoder
Group: Video
Summary: Movie encoder for Unix.
Summary(ru_RU.CP1251): Кодировщик фильмов для Unix.
Provides: MEncoder = %version-%release
Conflicts: %Name < 1.0-alt28

%description -n mencoder
MEncoder a movie encoder for Unix and is a part of the %name package.
%endif


%if_with htmldocs
%package docs
Group: Documentation
Summary: %Name all docs
Requires: %name-doc-tech
Requires: %name-doc-en
Requires: %name-doc-world
Requires: %name-doc-ru
%if %name != %Name
Provides: %Name-docs
Obsoletes: %Name-docs
%endif

%description docs
%Name all docs.


%package doc-tech
Group: Documentation
Summary: %Name Tech docs

%description doc-tech
%Name Tech docs.


%package doc-en
Group: Documentation
Summary: %Name English docs
Obsoletes: %Name-doc
Provides: %Name-doc
%if %name != %Name
Provides: %Name-doc-en = %version-%release
Obsoletes: %Name-doc-en
%endif

%description doc-en
%Name English docs.


%package doc-world
Group: Documentation
Summary: %Name docs
Conflicts: %name-doc-cs %name-doc-de %name-doc-es %name-doc-fr
Conflicts: %name-doc-hu %name-doc-it %name-doc-pl %name-doc-zh_CN

%description doc-world
%Name docs (exept English and Russian.


%package doc-ru
Group: Documentation
Summary: %Name Russian docs
%if %name != %Name
Provides: %Name-doc-ru = %version-%release
Obsoletes: %Name-doc-ru
%endif

%description doc-ru
%Name Russian docs.
%endif


%package i18n
Group: Video
Summary: Languages support for %Name
%{?_enable_mencoder:Provides: mencoder-i18n = %version-%release}
Requires: %name-i18n-world = %version-%release
Requires: %name-i18n-ru = %version-%release
%{?_enable_nls:Requires: %name-i18n-uk = %version-%release}

%description i18n
Languages support for %Name.


%package i18n-world
Group: Video
Summary: Languages support for %Name
Conflicts: %name-i18n < 1.0-35.22229.1
%{?_enable_mencoder:Provides: mencoder-i18n-world = %version-%release}

%description i18n-world
Languages support for %Name (except ru%{?_enable_nls: and uk}).


%package i18n-ru
Group: Video
Summary: Russian language support for %Name
Requires: man-pages-ru
Conflicts: %name-i18n < 1.0-35.22229.1
%{?_enable_mencoder:Provides: mencoder-i18n-ru = %version-%release}

%description i18n-ru
Russian language support for %Name.


%if_enabled nls
%package i18n-uk
Group: Video
Summary: Ukrainian language support for %Name
Conflicts: %name-i18n < 1.0-35.22229.1
%{?_enable_mencoder:Provides: mencoder-i18n-uk = %version-%release}

%description i18n-uk
Ukrainian language support for %Name.
%endif


%if_enabled mplayer
%if_with tools
%package tools
Group: Video
Summary: %Name/MEncoder tools
%if_enabled mencoder
Provides: mencoder-tools = %version-%release
Requires: mencoder
%endif
Requires: %name

%description tools
Nice scripts and code that makes using %Name and MEncoder easier, for
example scripts for DVD track encoding in three pass mode or creating
SVCDs from a movie.
%endif
%endif


%prep
%ifdef svnrev
%if_enabled shared_ffmpeg
%setup -q -n %lname-%pkgver
%else
%setup -q -n %lname-%pkgver -a 1
mv ffmpeg-svn-r%ffmpeg_svnrev/lib{av{codec,format,util},postproc} .
%endif
%else
%setup -q -n %Name-%pkgver
%endif

%patch0 -p1
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1
%patch7 -p1
%patch8 -p1
%patch11 -p1
%patch12 -p1
%patch13 -p1
%patch14 -p1
%patch16 -p1
%patch17 -p1
%patch27 -p1
%if_disabled shared_ffmpeg
%patch32 -p1
%patch33 -p1
%endif

%{?_enable_dvdnav:subst 's/--minilibs/--libs/g' configure}
%{?odml_chunklen:sed -r -i -e 's/^(#[[:blank:]]*define[[:blank:]]+ODML_CHUNKLEN[[:blank:]]+)0x[[:xdigit:]]+/\1%odml_chunklen/' libmpdemux/muxer_avi.c}

%{?svnrev:subst 's/UNKNOWN/%svnrev/' version.sh}
iconv -f cp1251 -t utf-8 >> etc/%lname.desktop <<__MENU__
Comment[ru]=Проигрыватель мультимедиа
Comment[uk]=Програвач мультимедіа
X-MultipleArgs=true
StartupNotify=true
__MENU__
sed -i -e '/^MimeType=/s|$|video/3gpp;application/x-flash-video;|' -e '/^Icon=/s/\.xpm$//' etc/%lname.desktop

%if_enabled nls
install -d -m 0755 po
gzip -dc %SOURCE6 > po/mp_help2msg.awk
gzip -dc %SOURCE7 > po/mp_msg2po.awk
%endif

%if %dvdreadlib == ext
#mv dvdread dvdread.internal
%endif

subst 's|\\/\\/|//|g' help/help_mp-zh_??.h


%build
%define _optlevel 3
%add_optflags %optflags_notraceback %optflags_fastmath -finline-functions -frename-registers
%ifarch x86_64
%add_optflags -mtune=k8 -DARCH_X86_64
%else
%ifarch %ix86
%add_optflags -DARCH_X86_32
%endif
%endif
export CFLAGS="%optflags"
./configure \
		--target=%_target \
		--prefix=%_prefix \
		--bindir=%_bindir \
		--mandir=%_mandir \
		--libdir=%_libdir \
		--datadir=%_datadir/%name \
		--confdir=%_sysconfdir/%name \
		%{subst_enable mplayer} \
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
		%{subst_enable_to teletext tv-teletext} \
		%{subst_enable pvr} \
		%{subst_enable rtc} \
		%{subst_enable network} \
		%{subst_enable winsock2} \
		%{subst_enable smb} \
		%{subst_enable live} \
		%{subst_enable dvdnav} \
		%{subst_enable dvdread} \
%if %dvdreadlib == int
		--enable-dvdread-internal \
%else
		--disable-dvdread-internal \
%endif
		%{subst_enable cdparanoia} \
		%{subst_enable_to bitmap_font bitmap-font} \
		%{subst_enable freetype} \
		%{subst_enable fontconfig} \
		%{subst_enable unrarexec} \
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
		%{subst_enable_to win32 win32dll} \
		%{?_enable_win32:--win32codecsdir=%win32_libdir} \
		%{subst_enable qtx} \
		%{subst_enable xanim} \
		%{?_enable_xanim:--xanimcodecsdir=%xanim_libdir} \
		%{subst_enable real} \
		%{?_enable_real:--realcodecsdir=%real_libdir} \
		%{subst_enable xvid} \
		%{subst_enable x264} \
%if_enabled ffmpeg
%if_enabled shared_ffmpeg
		--disable-libavcodec_a \
		--disable-libavformat_a \
		--disable-libavutil_a \
		--disable-libpostproc_a \
		--disable-libswscale_a \
		--enable-libavcodec_so \
		--enable-libavformat_so \
		--enable-libavutil_so \
		--enable-libpostproc_so \
		--enable-libswscale_so \
%else
		--disable-libavcodec_so \
		--disable-libavformat_so \
		--disable-libavutil_so \
		--disable-libpostproc_so \
		--disable-libswscale_so \
		--enable-libavcodec_a \
		--enable-libavformat_a \
		--enable-libavutil_a \
		--enable-libpostproc_a \
		--enable-libswscale_a \
%endif		
%else
		--disable-libavcodec_a \
		--disable-libavformat_a \
		--disable-libavutil_a \
		--disable-libpostproc_a \
		--disable-libswscale_a \
		--disable-libavcodec_so \
		--disable-libavformat_so \
		--disable-libavutil_so \
		--disable-libpostproc_so \
		--disable-libswscale_so \
%endif
		%{subst_enable_to tremor_internal tremor-internal} \
		%{subst_enable_to tremor_low tremor-low} \
		%{subst_enable_to tremor_external tremor-external} \
		%{subst_enable_to vorbis libvorbis} \
		%{subst_enable speex} \
		%{subst_enable theora} \
		%{?_enable_faad_int:--enable-faad-internal --disable-faad-external %{subst_enable_to faad_fixed faad-fixed}} \
		%{?_enable_faad_ext:--enable-faad-external --disable-faad-internal} \
		%{subst_enable faac} \
		%{subst_enable dirac} \
		%{subst_enable ladspa} \
		%{subst_enable libdv} \
		%{subst_enable mad} \
		%{subst_enable toolame} \
		%{subst_enable twolame} \
		%{subst_enable xmms} \
		%{subst_enable mp3lib} \
		%{subst_enable liba52} \
		%{subst_enable libmpeg2} \
		%{subst_enable musepack} \
		%{subst_enable_to nut libnut} \
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
		%{subst_enable dga1} \
		%{subst_enable dga2} \
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
		%{?_enable_xvmc:%{?xvmclib:--with-xvmclib=%xvmclib}} \
		%{subst_enable vm} \
		%{subst_enable xinerama} \
		%{subst_enable x11} \
		%{subst_enable xshape} \
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
		--enable-debug=3 \
%else
		--disable-debug \
%endif
		%{subst_enable prifile} \
		%{subst_enable sighandler} \
		%{subst_enable_to gdb crash-debug} \
		%{subst_enable_to dynamic_plugins dynamic-plugins} \
		--with-extraincdir=%_includedir/vidix:%_includedir/directfb

%make_build

# make conf file
sed -e 's/^@VO@/vo = %default_vo/' \
    -e 's/^@AO@/ao = %default_ao/' \
    -e 's|@CONF_FILE@|%_sysconfdir/%name/%lname.conf|g' \
    -e 's|@SKINS_DIR@|%_datadir/%name/skins|g' \
    %SOURCE5 \
    > etc/%lname.conf
%if_enabled fontconfig
echo "fontconfig = yes" >> etc/%lname.conf
%else
echo "fontconfig = no" >> etc/%lname.conf
%endif

%{?_enable_mplayer:%{?_with_tools:%make_build tools}}

%if_with htmldocs
%ifdef svnrev
# build HTML documentation from XML files
pushd DOCS/xml
cp -fL %_sysconfdir/sgml/catalog ./
echo 'CATALOG "/usr/share/xml/xml-iso-entities-8879.1986/catalog"' >> ./catalog
./configure
%make_build html-chunked
popd
%endif
%endif

%if_enabled nls
pushd po
gawk -f ./mp_help2msg.awk ../help/help_mp-en.h > en.msg
for h in $(ls ../help/help_mp-*.h | grep -v '..help/help_mp-en.h$'); do
    l=$(basename ${h/help_mp-} .h)
    gawk -f ./mp_help2msg.awk $h | awk -f ./mp_msg2po.awk en.msg > $l.po
    msgfmt -o $l.gmo $l.po
done
popd
%endif

%if_enabled gui
for s in 128 64 48 32 24 22 16; do
    convert -border 0x13 -bordercolor none gui/mplayer/pixmaps/MPlayer_mini.xpm \
	-resize ${s}x$s! -depth 8 gui/mplayer/pixmaps/%{lname}_$s.png
done
%endif


%install
%make_install DESTDIR=%buildroot install

%if_enabled mplayer
install -d -m 0755 %buildroot%_datadir/%name/skins
tar -C %buildroot%_datadir/%name/skins -xjf %SOURCE4
ln -s standard %buildroot%_datadir/%name/skins/default
%{?_enable_freetype:%{?_disable_fontconfig:ln -s ../fonts/default/Type1/n019003l.pfb %buildroot%_datadir/%name/subfont.ttf}}
%endif

install -m 0644 etc/{codecs,input,%lname}.conf %buildroot%_sysconfdir/%name/

%if_enabled mplayer
%{?_enable_osdmenu:install -m 0644 etc/menu.conf %buildroot%_sysconfdir/%name/}
%{?_enable_dvb:install -m 0644 etc/dvb-menu.conf %buildroot%_sysconfdir/%name/}

%if_with tools
install -m 0755 TOOLS/{aconvert,alaw-gen,asfinfo,avi-fix,avisubdump,bmovl-test,calcbpp.pl,countquant.pl,divx2svcd,dump_mp4,encode2mpeglight,mencvcd,midentify,movinfo,mpconsole,mplmult.sh,plotpsnr.pl,psnr-video.sh,subedit.pl,subsearch.sh,vobshift.py,w32codec_dl.pl,wma2ogg.pl} %buildroot/%_bindir/
%{?_enable_mencoder:install -m 0755 TOOLS/{dvd2divxscript.pl,qepdvcd.sh} %buildroot/%_bindir/}
install -pD -m 0644 TOOLS/README %buildroot%_docdir/%name-tools-%version/README
%endif

%{?_with_soundwrapper:install -pD -m 0755 %SOURCE3 %buildroot%_sysconfdir/bashrc.d/%lname.sh}
%endif

# docs
bzip2 --best --force --keep -- Changelog
for l in $(ls DOCS/man | grep -v 'en'); do
%if_enabled mplayer
    install -pD -m 0644 DOCS/man/$l/%lname.1 %buildroot%_mandir/$l/man1/%lname.1
    %{?_enable_mencoder:ln -sf %lname.1 %buildroot%_mandir/$l/man1/mencoder.1}
%else
    %{?_enable_mencoder:install -pD -m 0644 DOCS/man/$l/mencoder.1 %buildroot%_mandir/$l/man1/mencoder.1}
%endif
done
rm -f %buildroot%_man1dir/mencoder.1
%{?_enable_mencoder:install -m 0644 DOCS/man/en/%lname.1 %buildroot%_man1dir/mencoder.1}
%if_with htmldocs
for l in cs de en es fr hu it pl ru zh_CN; do
    install -d %buildroot%_docdir/%name-doc-%version/$l
    install -m 0644 DOCS/HTML/$l/{*.html,*.css} %buildroot%_docdir/%name-doc-%version/$l/
done
%endif
install -d %buildroot%_docdir/%name-doc-%version/tech/realcodecs
install -m 0644 DOCS/tech/{MAINTAINERS,TODO,*.txt,mpsub.sub,playtree,wishlist} %buildroot%_docdir/%name-doc-%version/tech/
install -m 0644 DOCS/tech/realcodecs/{TODO,*.txt} %buildroot%_docdir/%name-doc-%version/tech/realcodecs/
%find_lang --with-man %lname %lname-man

%if_enabled nls
for l in po/*.gmo; do
install -pD -m 0644 $l %buildroot%_datadir/locale/$(basename $l .gmo)/LC_MESSAGES/%name.mo
done
%endif

%{?_enable_mplayer:%add_verify_elf_skiplist %_libdir/%lname/vidix/*}

%if_enabled gui
for s in 128 64 48 32 24 22 16; do
    install -D -m 0644 {gui/mplayer/pixmaps/%{lname}_$s,%buildroot%_iconsdir/hicolor/${s}x$s/apps/%lname}.png
done
install -D -m 0644 {etc/%lname,%buildroot%_desktopdir/%name}.desktop
ln -sf %lname %buildroot%_bindir/g%lname
%endif


%if_enabled mplayer
%if_enabled gui
%post gui
%update_menus
%update_desktopdb

%postun gui
%clean_menus
%clean_desktopdb
%endif
%endif


%if_enabled mplayer
%files
%doc README AUTHORS Changelog.*
%_bindir/%lname
%_man1dir/%lname.*
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
#%%_datadir/pixmaps/*
%_iconsdir/hicolor/*/apps/*
%dir %_datadir/%name/skins
%_datadir/%name/skins/standard
%_datadir/%name/skins/default
%endif
%endif


%if_enabled mencoder
%files -n mencoder
%_bindir/mencoder
%_man1dir/mencoder.*
%if_disabled mplayer
%doc README AUTHORS Changelog.*
%dir %_sysconfdir/%name
%config %_sysconfdir/%name/codecs.conf
%endif
%endif


%if_with htmldocs
%files docs


%files doc-world
%dir %_docdir/%name-doc-%version
%lang(cs) %_docdir/%name-doc-%version/cs
%lang(de) %_docdir/%name-doc-%version/de
%lang(es) %_docdir/%name-doc-%version/es
%lang(fr) %_docdir/%name-doc-%version/fr
%lang(hu) %_docdir/%name-doc-%version/hu
%lang(it) %_docdir/%name-doc-%version/it
%lang(pl) %_docdir/%name-doc-%version/pl
%lang(zh_CN) %_docdir/%name-doc-%version/zh_CN


%files doc-tech
%dir %_docdir/%name-doc-%version
%_docdir/%name-doc-%version/tech


%files doc-en
%dir %_docdir/%name-doc-%version
%_docdir/%name-doc-%version/en


%files doc-ru
%dir %_docdir/%name-doc-%version
%_docdir/%name-doc-%version/ru
%endif


%files i18n


%files i18n-ru
%_mandir/ru/man1/*
%{?_enable_nls:%_datadir/locale/ru/LC_MESSAGES/*}


%if_enabled nls
%files i18n-uk
%_datadir/locale/uk/LC_MESSAGES/*
%endif


%files i18n-world
%lang(cs) %_mandir/cs/man1/*
%lang(de) %_mandir/de/man1/*
%lang(es) %_mandir/es/man1/*
%lang(fr) %_mandir/fr/man1/*
%lang(hu) %_mandir/hu/man1/*
%lang(it) %_mandir/it/man1/*
%lang(pl) %_mandir/pl/man1/*
%lang(zh) %_mandir/zh/man1/*
%if_enabled nls
%lang(bg) %_datadir/locale/bg/LC_MESSAGES/*
%lang(cs) %_datadir/locale/cs/LC_MESSAGES/*
%lang(de) %_datadir/locale/de/LC_MESSAGES/*
%lang(dk) %_datadir/locale/dk/LC_MESSAGES/*
%lang(el) %_datadir/locale/el/LC_MESSAGES/*
%lang(es) %_datadir/locale/es/LC_MESSAGES/*
%lang(fr) %_datadir/locale/fr/LC_MESSAGES/*
%lang(hu) %_datadir/locale/hu/LC_MESSAGES/*
%lang(it) %_datadir/locale/it/LC_MESSAGES/*
%lang(ja) %_datadir/locale/ja/LC_MESSAGES/*
%lang(ko) %_datadir/locale/ko/LC_MESSAGES/*
%lang(mk) %_datadir/locale/mk/LC_MESSAGES/*
%lang(nb) %_datadir/locale/nb/LC_MESSAGES/*
%lang(nl) %_datadir/locale/nl/LC_MESSAGES/*
%lang(pl) %_datadir/locale/pl/LC_MESSAGES/*
%lang(pt) %_datadir/locale/pt_BR/LC_MESSAGES/*
%lang(ro) %_datadir/locale/ro/LC_MESSAGES/*
%lang(sk) %_datadir/locale/sk/LC_MESSAGES/*
%lang(sv) %_datadir/locale/sv/LC_MESSAGES/*
%lang(sk) %_datadir/locale/sk/LC_MESSAGES/*
%lang(tr) %_datadir/locale/tr/LC_MESSAGES/*
%lang(zh_CN) %_datadir/locale/zh_CN/LC_MESSAGES/*
%lang(zh_TW) %_datadir/locale/zh_TW/LC_MESSAGES/*
%endif


%if_enabled mplayer
%if_with tools
%files tools
%_docdir/%name-tools-%version
#mplayer
%_bindir/mencvcd
%_bindir/midentify
%_bindir/mpconsole
%_bindir/mplmult.sh
%_bindir/psnr-video.sh
%_bindir/wma2ogg.pl
%if_enabled mencoder
#mencoder
%_bindir/dvd2divxscript.pl
%_bindir/qepdvcd.sh
%endif
#common
%_bindir/aconvert
%_bindir/divx2svcd
%_bindir/dump_mp4
%_bindir/encode2mpeglight
#other
%_bindir/alaw-gen
%_bindir/asfinfo
%_bindir/avi-fix
%_bindir/avisubdump
%_bindir/bmovl-test
%_bindir/calcbpp.pl
%_bindir/countquant.pl
%_bindir/movinfo
%_bindir/plotpsnr.pl
%_bindir/subedit.pl
%_bindir/subsearch.sh
%_bindir/vobshift.py
%_bindir/w32codec_dl.pl
%endif
%endif


%changelog
* Wed May 14 2008 Led <led@altlinux.ru> 1.0-alt35.26763.1
- new SVN snapshot (revision 26763)

* Sat May 10 2008 Led <led@altlinux.ru> 1.0-alt35.26708.1
- new SVN snapshot (revision 26708):
  + BFI video decoder
- removed ffmpeg-svn-r12807-dirac-0.9.x.patch (added in upstream)
- updated:
  + %lname-svn-r26706-ext_ffmpeg.patch (partially fixed in upstream)
  + %lname-svn-r26706-dirac-0.9.1.patch
  + %lname-uni-svn26706.patch
  + %lname-svn-r26708-configure.patch
  + ffmpeg-svn-r13104-amr.patch

* Sat Apr 19 2008 Led <led@altlinux.ru> 1.0-alt35.26470.2
- build with external ffmpeg

* Sat Apr 19 2008 Led <led@altlinux.ru> 1.0-alt35.26470.1
- new SVN snapshot (revision 26470)
- updated %lname-svn-r26470-dirac-0.9.1.patch

* Wed Apr 16 2008 Led <led@altlinux.ru> 1.0-alt35.26454.2
- build with external ffmpeg

* Tue Apr 15 2008 Led <led@altlinux.ru> 1.0-alt35.26454.1
- new SVN snapshot (revision 26454)
- removed %lname-svn-r26454-mencoder.patch (fixed in upstream)
- cleaned up %lname-svn-r26454-ext_ffmpeg.patch
- build with internal ffmpeg

* Tue Apr 15 2008 Led <led@altlinux.ru> 1.0-alt35.26450.1
- new SVN snapshot (revision 26450)
- updated:
  + %lname-svn-r26450-dirac-0.9.1.patch
  + %lname-svn-r26450-gui.patch
  + %lname-svn-r26450-gui_nls.patch
  + %lname-svn-r26450-configure.patch
  + %lname-svn-r26450-ext_ffmpeg.patch
  + %lname-svn-r26450-builddocs.patch
  + ffmpeg-svn-r12807-dirac-0.9.x.patch
  + ffmpeg-svn-r12807-amr.patch
- added %lname-svn-r26450-mencoder.patch
- replaced ffmpeg-uni-svn-r10644.patch with
  ffmpeg-svn-r12807-xvmc-vld.patch

* Fri Apr 04 2008 Led <led@altlinux.ru> 1.0-alt35.25957.5
- fixes desktop-mime-entry

* Tue Mar 04 2008 Led <led@altlinux.ru> 1.0-alt35.25957.4
- fixed typo in spec (#14746)

* Sun Mar 02 2008 Led <led@altlinux.ru> 1.0-alt35.25957.3
- added icons
- fixed BuildRequires

* Wed Feb 27 2008 Led <led@altlinux.ru> 1.0-alt35.26107.1
- new SVN snapshot (revision 26107)
- updated:
  + %lname-svn-r25957-configure.patch
  + %lname-svn-r26107-gui.patch
  + %lname-svn-r26107-ext_ffmpeg.patch

* Wed Feb 27 2008 Led <led@altlinux.ru> 1.0-alt35.25957.2
- fixed ffmpeg-svn-r11246-dirac-0.9.x.patch
- updated %lname-svn-r25957-configure.patch (fixed #13791 again)

* Tue Feb 19 2008 Led <led@altlinux.ru> 1.0-alt35.26031.1
- new SVN snapshot (revision 26031)
- fixed ffmpeg-svn-r11246-dirac-0.9.x.patch

* Tue Feb 19 2008 Led <led@altlinux.ru> 1.0-alt35.26030.1
- new SVN snapshot (revision 26030)

* Tue Feb 12 2008 Led <led@altlinux.ru> 1.0-alt35.25987.1
- new SVN snapshot (revision 25987)
- updated %lname-svn-r25987-ext_ffmpeg.patch

* Wed Feb 06 2008 Led <led@altlinux.ru> 1.0-alt35.25957.1
- new SVN snapshot (revision 25957):
  + stack overflow in demuxer_audio.c fixed
  + buffer overflow in demuxer_mov.c fixed
- updated:
  + %lname-svn-r25895-ext_ffmpeg.patch
  + %lname-svn-r25957-dirac-0.9.1.patch
  + ffmpeg-svn-r11872-dirac-0.9.x.patch

* Sun Jan 27 2008 Led <led@altlinux.ru> 1.0-alt35.25873.2
- build with internal FAAD

* Sat Jan 26 2008 Led <led@altlinux.ru> 1.0-alt35.25873.1
- new SVN snapshot (revision 25873)
- updated %lname-svn-r25873-ext_ffmpeg.patch

* Thu Jan 24 2008 Led <led@altlinux.ru> 1.0-alt35.25844.1
- new SVN snapshot (revision 25844)
- updated ffmpeg-svn-r11604-dirac-0.9.x.patch
- updated %lname-svn-r25844-dirac-0.9.0.patch

* Mon Jan 21 2008 Led <led@altlinux.ru> 1.0-alt35.25826.1
- new SVN snapshot (revision 25826):
  + buffer overflow in url.c fixed
  + buffer overflow in stream_cddb.c fixed
- updated:
  + %lname-svn-r25826-dirac-0.8.x.patch
  + %lname-svn-r25826-configure.patch
  + %lname-svn-r25826-ext_ffmpeg.patch
- build with external libfaad

* Fri Jan 11 2008 Led <led@altlinux.ru> 1.0-alt35.25678.1
- new SVN snapshot (revision 25678)
- updated %lname-uni-svn25678.patch

* Fri Jan 11 2008 Led <led@altlinux.ru> 1.0-alt35.25669.1
- new SVN snapshot (revision 25669)
- updated:
  + %lname-svn-r25669-gui_nls.patch
  + %lname-svn-r25669-ext_ffmpeg.patch

* Tue Dec 25 2007 Led <led@altlinux.ru> 1.0-alt35.25498.1
- new SVN snapshot (revision 25498)
- removed %lname-svn-r25454-dvdnav.patch
- updated %lname-svn-r25505-configure.patch (fixed #13791)

* Sat Dec 22 2007 Led <led@altlinux.ru> 1.0-alt35.25487.1
- new SVN snapshot (revision 25487)
- updated:
  + ffmpeg-svn-r11263-dirac-0.8.x.patch
  + %lname-svn-r25454-dirac-0.8.x.patch
  + %lname-svn-r25454-vo_vidix.patch
  + %lname-svn-r25454-configure.patch
  + %lname-svn-r25487-ext_ffmpeg.patch
- added %lname-svn-r25454-dvdnav.patch

* Mon Nov 12 2007 Led <led@altlinux.ru> 1.0-alt35.25029.1
- new SVN snapshot (revision 25029)
- fixed %%changelog

* Sun Nov 11 2007 Led <led@altlinux.ru> 1.0-alt35.25023.1
- new SVN snapshot (revision 25023)
- updated ffmpeg-svn-r11000-dirac-0.8.x.patch

* Sun Nov 11 2007 Led <led@altlinux.ru> 1.0-alt35.25017.1
- new SVN snapshot (revision 25017):
  + support for wavpack in matroska
  + add vf_scaletempo
  + rewrite dec_audio to support more filters
  + Nellymoser audio decoding via lavc
  + Basic support for Closed Captioning Roll-up mode
- updated:
  + %lname-svn-r25014-dirac-0.8.x.patch
  + %lname-svn-r25014-ext_ffmpeg.patch
- removed:
  + %lname-svn-r19389-polyp0.8.patch
  + mplayer-svn-r21128-pulseaudio.patch

* Fri Oct 12 2007 Led <led@altlinux.ru> 1.0-alt35.24764.1
- new SVN snapshot (revision 24764)
- updated ffmpeg-svn-r10703-dirac-0.8.x.patch

* Wed Oct 03 2007 Led <led@altlinux.ru> 1.0-alt35.24688.1
- new SVN snapshot (revision 24688):
  + support H.263-2000 over RTSP
  + support AMR over RTSP
  + support H.264 over RTSP
  + channel scanner for tv://
  + fine tuning for tv://
  + driver autodetection for tv://
  + libnemesi RTSP/RTP support
- updated
  + %lname-svn-r24688-configure.patch
  + %lname-svn-r24688-ext_ffmpeg.patch
  + %lname-svn-r24688-dirac-0.8.x.patch
  + ffmpeg-svn-r10636-dirac-0.8.x.patch
  + ffmpeg-uni-svn-r10644.patch
  + ffmpeg-svn-r10644-amr.patch

* Mon Aug 27 2007 Led <led@altlinux.ru> 1.0-alt35.24247.1
- new SVN snapshot (revision 24247)
- updated %lname-svn-r24244-ext_ffmpeg.patch

* Mon Aug 27 2007 Led <led@altlinux.ru> 1.0-alt35.24127.1
- new SVN snapshot (revision 24127)
- updated %lname-svn-r24244-dirac-0.7.x.patch (fixed #12627)
- updated ffmpeg-svn-r10237-dirac-0.7.x.patch
- updated %lname-svn-r24127-ext_ffmpeg.patch

* Fri Aug 17 2007 Led <led@altlinux.ru> 1.0-alt35.24081.1
- new SVN snapshot (revision 24081)
- updated mplayer-svn-r24081-nls.patch
- updated %lname-svn-r24081-ext_ffmpeg.patch

* Mon Jul 23 2007 Led <led@altlinux.ru> 1.0-alt35.23844.1
- new SVN snapshot (revision 23844)
- updated %lname-svn-r23810-configure.patch
- updated %lname-svn-r23726-gui_nls.patch
- updated %lname-svn-r23726-ext_ffmpeg.patch
- added ffmpeg-svn-r9777-dirac-0.7.x.patch
- added ffmpeg-svn-r9777-amr.patch
- removed %lname-svn-r22092-dirac.patch
- added %lname-svn-r23840-dirac-0.7.x.patch

* Fri Jul 06 2007 Led <led@altlinux.ru> 1.0-alt35.23722.1
- new SVN snapshot (revision 23722)
- updated %lname-svn-r23664-ext_ffmpeg.patch
- updated BuildRequires
- added %lname-svn-r23722-VIDM-win32-codec.patch (by icesik@ FR #12211)

* Sat Jun 23 2007 Led <led@altlinux.ru> 1.0-alt35.23606.1
- new SVN snapshot (revision 23606)
- updated %lname-svn-r23600-ext_ffmpeg.patch
- updated %lname-svn-r23592-configure.patch
- added %lname-svn-r23606-desktop.patch
- fixed %lname.desktop

* Sat Jun 16 2007 Led <led@altlinux.ru> 1.0-alt35.23560.1
- new SVN snapshot (revision 23560)
- updated %lname-svn-r23560-configure.patch

* Wed Jun 13 2007 Led <led@altlinux.ru> 1.0-alt35.23550.1
- new SVN snapshot (revision 23550):
  + Teletext support for tv:// (v4l and v4l2 only)
- cleaned up spec
- cleaned up BuildRequires
- updated %lname-svn-r23545-ext_ffmpeg.patch
- updated %lname-svn-r23547-gui.patch
- updated %lname-svn-r23545-nls.patch
- added it docs

* Sat May 19 2007 Led <led@altlinux.ru> 1.0-alt35.23340.1
- new SVN snapshot (revision 23340)
- updated %lname-svn-r23340-configure.patch

* Fri May 18 2007 Led <led@altlinux.ru> 1.0-alt35.23331.1
- new SVN snapshot (revision 23331)
- updated %lname-svn-r23331-configure.patch
- updated %lname-svn-r23331-ext_ffmpeg.patch
- cleaned up spec

* Thu May 17 2007 Led <led@altlinux.ru> 1.0-alt35.23322.1
- new SVN snapshot (revision 23322)

* Mon May 14 2007 Led <led@altlinux.ru> 1.0-alt35.23311.1
- new SVN snapshot (revision 23311):
  + Renderware TeXture Dictionary video via lavc
- updated %lname-svn-r23304-ext_ffmpeg.patch
- updated %lname-svn-r23304-configure.patch
- updated ffmpeg-uni-svn-r8990.patch
- cleaned up spec

* Tue May 08 2007 Led <led@altlinux.ru> 1.0-alt35.23272.1
- new SVN snapshot (revision 23272):
  + support for channel navigation with PVR input
- updated %lname-svn-r23272-ext_ffmpeg.patch

* Mon May 07 2007 Led <led@altlinux.ru> 1.0-alt35.23241.1
- new SVN snapshot (revision 23241)

* Sun May 06 2007 Led <led@altlinux.ru> 1.0-alt35.23238.1
- new SVN snapshot (revision 23238)
- updated %lname-uni-svn23235.diff
- updated %lname-svn-r23235-ext_ffmpeg.patch
- updated %lname-svn-r23235-configure.patch
- fixed build with mainstream libdvdnav

* Thu Apr 26 2007 Led <led@altlinux.ru> 1.0-alt35.23114.1
- new SVN snapshot (revision 23114)
- updated %lname-svn-r23114-ext_ffmpeg.patch

* Wed Apr 25 2007 Led <led@altlinux.ru> 1.0-alt35.23104.1
- new SVN snapshot (revision 23104)

* Mon Apr 23 2007 Led <led@altlinux.ru> 1.0-alt35.23099.1
- new SVN snapshot (revision 23099)
- updated %lname-svn-r23099-gui.patch
- updated %lname-svn-r23099-gui_nls.patch
- updated %lname-svn-r23099-ext_ffmpeg.patch
- updated %lname-svn-r23099-configure.patch
- added %lname-svn-r23099-demux_nut.patch

* Thu Apr 19 2007 Led <led@altlinux.ru> 1.0-alt35.23023.1
- new SVN snapshot (revision 23023)

* Mon Apr 16 2007 Led <led@altlinux.ru> 1.0-alt35.23002.1
- new SVN snapshot (revision 23002):
  + THP audio and video via lavc
- fixed %%changelog

* Tue Apr 10 2007 Led <led@altlinux.ru> 1.0-alt35.22963.1
- new SVN snapshot (revision 22963):
  + AAC-LATM, H.263-2000, AMR, H.264 over RTSP
- removed %lname-svn-r22753-libdha.patch (due upstream)
- updated %lname-uni-svn22915.diff
- updated %lname-svn-r22963-ext_ffmpeg.patch
- removed %lname-svn-r22518-mwallp.patch (due upstream)
- updated %lname-svn-r22915-configure.patch
- removed %name-fontutils package (due upstream)
- added %lname-svn-r22963-gui.patch

* Tue Mar 20 2007 Led <led@altlinux.ru> 1.0-alt35.22753.1
- new SVN snapshot (revision 22753)
- updated %lname-svn-r22753-libdha.patch
- updated %lname-svn-r22753-ext_ffmpeg.patch
- updated %lname-svn-r22753-configure.patch

* Thu Mar 15 2007 Led <led@altlinux.ru> 1.0-alt35.22590.1
- new SVN snapshot (revision 22590)
- updated %lname-svn-r22590-libdha.patch

* Wed Mar 14 2007 Led <led@altlinux.ru> 1.0-alt35.22550.1
- new SVN snapshot (revision 22550)

* Mon Mar 12 2007 Led <led@altlinux.ru> 1.0-alt35.22535.1
- new SVN snapshot (revision 22535)
- updated %lname-svn-r22518-nls.patch
- updated %lname-svn-r22518-ext_ffmpeg.patch
- updated %lname-svn-r22518-configure.patch
- updated %lname-svn-r22518-builddocs.patch
- updated ffmpeg-uni-svn-r7650.patch
- updated %lname-svn-r22518-mwallp.patch

* Wed Feb 28 2007 Led <led@altlinux.ru> 1.0-alt35.22358.1
- new SVN snapshot (revision 22358)

* Fri Feb 23 2007 Led <led@altlinux.ru> 1.0-alt35.22324.1
- new SVN snapshot (revision 22324):
  + ffmpeg video decoder handles aspect ratio changes
  + smil playlist over Real RTSP
- updated %lname-svn-r22324-gui_nls.patch
- used liblzo2
- updated %lname-svn-r22324-ext_ffmpeg.patch

* Fri Feb 16 2007 Led <led@altlinux.ru> 1.0-alt35.22230.1
- new SVN snapshot (revision 22230)
- added subpackages %name-i18n-ru, %name-i18n-uk,
  %name-i18n-world, %name-doc-world, %name-docs
- fixed configure parameters (%%build section)
- %name-i18n-ru requires man-pages-ru (#10819)
- cleaned up BuildRequires

* Thu Feb 15 2007 Led <led@altlinux.ru> 1.0-alt35.22223.1
- new SVN snapshot (revision 22223)
- updated %lname-svn-r22217-configure.patch
- added mplayer-svn-r22221-subreader.patch (fixed #10844)
- fixed BuildRequires

* Mon Feb 12 2007 Led <led@altlinux.ru> 1.0-alt35.22210.1
- new SVN snapshot (revision 22210):
  + Russian man page translation finished
  + GIF demuxer improvement
  + support for VC1 in MPEG-TS and MPEG-PS files (bd,hd)-dvd
  + support for doubleclick as input event
  + select libavformat demuxer (-lavfdopts format=)
  + MEncoder support -ffourcc with -of lavf
- enabled Dirac
- removed %Name-svn-20060707_dirac-0.5.x.patch
- cleaned up spec

* Thu Feb 08 2007 Led <led@altlinux.ru> 1.0-alt35.22173.1
- new SVN snapshot (revision 22173)
- turned off joystick and LIRC support by default in %_sysconfdir/%lname.conf
- enabled LADSPA
- updated %lname-svn-r22173-ext_ffmpeg.patch

* Mon Feb 05 2007 Led <led@altlinux.ru> 1.0-alt35.22138.1
- new SVN snapshot (revision 22138)
- fixed %lname.conf (#10770)

* Mon Feb 05 2007 Led <led@altlinux.ru> 1.0-alt35.22092.2
- added %lname-svn-r22092-dirac.patch

* Wed Jan 31 2007 Led <led@altlinux.ru> 1.0-alt35.22092.1
- new SVN snapshot (revision 22092)
- removed %lname-svn-r22020-makefile.patch
- updated %lname-svn-r22092-libdha.patch
- updated %lname-svn-r22092-configure.patch

* Fri Jan 26 2007 Led <led@altlinux.ru> 1.0-alt35.22020.1
- new SVN snapshot (revision 22020)
- fixed %%changelog
- updated %lname-svn-r22020-makefile.patch
- removed %lname-svn-r22004-doc_hu.patch (fixed in upstream)

* Wed Jan 24 2007 Led <led@altlinux.ru> 1.0-alt35.22004.1
- new SVN snapshot (revision 22004)
- added %lname-svn-r22004-doc_hu.patch

* Wed Jan 24 2007 Led <led@altlinux.ru> 1.0-alt35.21995.1
- new SVN snapshot (revision 21995):
  + Russian documentation translation finished
- updated %lname-svn-r21995-makefile.patch
- updated %lname-svn-r21995-libdha.patch
- updated %lname-svn-r21995-ext_ffmpeg.patch

* Wed Jan 10 2007 Led <led@altlinux.ru> 1.0-alt35.21839.1
- new SVN snapshot (revision 21839)
- updated %lname-svn-r21839-ext_ffmpeg.patch
- updated %lname-svn-r21858-configure.patch
- fixed buffer overflow in realrtsp (upstream)

* Fri Dec 29 2006 Led <led@altlinux.ru> 1.0-alt35.21781.1
- new SVN snapshot (revision 21781)

* Fri Dec 29 2006 Led <led@altlinux.ru> 1.0-alt35.21766.2
- fixed x86_64 build:
  + fixed %lname-svn-r21766-configure.patch

* Mon Dec 25 2006 Led <led@altlinux.ru> 1.0-alt35.21766.1
- new SVN snapshot (revision 21766):
  + mencoder now can write to output streams file:// and smb://
- updated %lname-svn-r21765-configure.patch
- fixed BuildRequires
- fixed docs installing
- removed %name-doc-it, replaced %name-doc-zh with %name-doc-zh_CN

* Thu Dec 14 2006 Led <led@altlinux.ru> 1.0-alt35.21614.1
- new SVN snapshot (revision 21614)
- updated %lname-svn-r21611-ext_ffmpeg.patch
- removed %lname-svn-r20777-bmovl-test.patch

* Sat Dec 02 2006 Led <led@altlinux.ru> 1.0-alt35.21402.3
- added %lname-svn-r21402-gui_nls.patch

* Thu Nov 30 2006 Led <led@altlinux.ru> 1.0-alt35.21402.2
- fixed %lname-uni-svn21402.diff
- fixed BuildRequires
- added %lname-svn-r21402-makefile.patch
- fixed spec

* Thu Nov 30 2006 Led <led@altlinux.ru> 1.0-alt35.21402.1
- new SVN snapshot (revision 21402)

* Thu Nov 30 2006 Led <led@altlinux.ru> 1.0-alt35.21399.1
- new SVN snapshot (revision 21399)
- fixed %%changelog
- updated %lname-svn-r21398-ext_ffmpeg.patch
- removed %lname-svn-r20837-generic-x86_64.patch (fixed in upstream)

* Wed Nov 29 2006 Led <led@altlinux.ru> 1.0-alt35.21374.1
- new SVN snapshot (revision 21374)
- forced --enable-mplayer
- fixed BuildRequires
- updated %lname-svn-r21374-ext_ffmpeg.patch

* Tue Nov 28 2006 Led <led@altlinux.ru> 1.0-alt35.21357.1
- new SVN snapshot (revision 21352)
- updated %lname-svn-r21352-libdha.patch
- updated %lname-uni-svn21352.diff
- removed %lname-svn-r21352-xmmslibs_fix.patch
- updated %lname-svn-r21352-ext_ffmpeg.patch
- updated %lname-svn-r21357-configure.patch
- removed %Name-svn-20060607-vf_mcdeint.patch

* Mon Nov 20 2006 Led <led@altlinux.ru> 1.0-alt35.21093.1
- new SVN snapshot (revision 21093):
  + obsolete XviD 3 support removed
  + video stream switching
- updated %lname-uni-svn21093.diff
- updated %lname-svn-r21093-ext_ffmpeg.patch
- updated %lname-svn-r21093-configure.patch

* Mon Nov 13 2006 Led <led@altlinux.ru> 1.0-alt35.20885.1
- new SVN snapshot (revision 20885)

* Fri Nov 10 2006 Led <led@altlinux.ru> 1.0-alt35.20837.1
- new SVN snapshot (revision 20837)
- updated %lname-svn-r20837-pulseaudio.patch
- changed %lname-svn-r20837-generic-x86_64.patch
- updated %lname-svn-r20837-ext_ffmpeg.patch

* Thu Nov 09 2006 Led <led@altlinux.ru> 1.0-alt35.20777.1
- new SVN snapshot (revision 20777)
- removed %lname-1.0rc1-mp3lib-amd.patch (fixed in upstream)
- removed %Name-svn-20060710-alt-external_fame.patch (removed libfame
  support in upstream)
- updated %lname-svn-r20777-generic-x86_64.patch
- updated %lname-svn-r20777-nls.patch
- updated %lname-uni-svn20777.diff
- updated %lname-svn-r20777-pulseaudio.patch
- updated %lname-svn-r20777-bmovl-test.patch
- updated %lname-svn-r20777-configure.patch
- fixed %lname-svn-r20777-builddocs.patch
- cleaned up spec

* Tue Nov 07 2006 Led <led@altlinux.ru> 1.0-alt35
- build docs with xsltproc instead of openjade
  + updated %lname-svn-r20544-builddocs.patch
  + fixed BuildRequires
- added %name-tools package
- fixed %lname-1.0rc1-ext_ffmpeg.patch

* Tue Oct 31 2006 Led <led@altlinux.ru> 1.0-alt34
- fixed spec
- updated %lname-1.0rc1-ext_ffmpeg.patch
- added --enable-libswscale[_so] configure options
- added %lname-mwallp.patch
- added %lname-bmovl-test.patch
- fixed mp_msg2po.awk
- updated %lname-1.0rc1-configure.patch (fixed #4108)
- added %lname-1.0rc1-mp3lib-amd.patch (disabled broken asm-code)

* Mon Oct 30 2006 Led <led@altlinux.ru> 1.0-alt34.20523.1
- new SVN snapshot (revision 20523)
- fixed spec
- updated %lname-svn-r20448-ext_ffmpeg.patch
- added --enable-libswscale[_so] configure options
- added %lname-mwallp.patch
- added %lname-bmovl-test.patch
- fixed mp_msg2po.awk
- updated %lname-1.0rc1-configure.patch (fixed #4108)

* Mon Oct 23 2006 Led <led@altlinux.ru> 1.0-alt33
- 1.0rc1
- removed %Name-1.0pre8-udev.patch (fixed in upstream)
- cleaned up and fixed spec
- updated %lname-1.0rc1-configure.patch

* Thu Oct 19 2006 Led <led@altlinux.ru> 1.0-alt32.20300.1
- new SVN snapshot (revision 20300):
  + Russian documentation translation synced and almost finished
  + bicubic OpenGL scaling works with ATI cards
  + md5sum switched to use libavutil md5 implementation
  + support for libcaca 1.0 via compatibility layer
  + audio stream switching between streams with different codecs
  + fixed seeking to absolute and percent position for libavformat
    demuxer
  + NUT demuxer using libnut
  + Matroska SimpleBlock support
  + -correct-pts option
  + UTF-8 used for OSD and subtitles, some bitmap fonts will no longer
    work correctly and -subcp must be set for all non-UTF-8 subtitles
  + more audio-truncation fixes
  + libavutil mandatory for MPlayer compilation
  + more intuitive -edlout behaviour
  + -nortc is now default since -rtc has only disadvantages with recent
    kernels
  + MMX-optimizations for -vf yadif
  + MMX-optimizations for -vf zrmjpeg
  + GUI:
    drag-and-drop ignored last file
    save and load cache setting correctly
    working audio stream selection for Ogg and Matroska files
    xinerama fixes
- cleaned up spec
- fixed Provides for %lname-gui package
- enabled nut
- updated %lname-svn-r20300-configure.patch

* Fri Oct 13 2006 Led <led@altlinux.ru> 1.0-alt31.20190.1
- new SVN snapshot (revision 20190):
  + -endpos option for %lname

* Mon Oct 09 2006 Led <led@altlinux.ru> 1.0-alt31.20117.1
- new SVN snapshot (revision 20117)
- updated %lname-svn-r20117-ext_ffmpeg.patch
- returned %name's mans
- removed %lname-svn-r19982-doc-cs.patch (fixed in upstream)
- fixed %lname.conf (used default utf8 subtitles encoding)
- fixed spec

* Wed Oct 04 2006 Led <led@altlinux.ru> 1.0-alt30.20022.1
- new SVN snapshot (revision 20022)
- fixed console control:
  + updated %lname-svn-r20022-configure.patch
  + enabled termios

* Mon Oct 02 2006 Led <led@altlinux.ru> 1.0-alt29.20016.1
- new SVN snapshot (revision 20016)
- fixed Conflicts in mencoder package
- added %lname-svn-r19982-doc-cs.patch

* Mon Sep 25 2006 Led <led@altlinux.ru> 1.0-alt28.19912.1
- rebuild for Sisyphus

* Wed Sep 20 2006 Led <led@altlinux.ru> 1:1.0-alt1.19912.1
- new SVN snapshot (revision 19912)
- merged %lname-svn-r19389-ext_libswscale.patch to
  %lname-svn-r19912-ext_ffmpeg.patch
- cleaned up spec

* Fri Sep 15 2006 Led <led@altlinux.ru> 1:1.0-alt1.19838.1
- new SVN snapshot (revision 19838)
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
