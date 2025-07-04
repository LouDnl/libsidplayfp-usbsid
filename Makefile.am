
ACLOCAL_AMFLAGS = -I m4

AUTOMAKE_OPTIONS = foreign subdir-objects

SUBDIRS = tests

DISTCHECK_CONFIGURE_FLAGS = --enable-tests


if MINGW32
  W32_CPPFLAGS = -DWIN32_LEAN_AND_MEAN
  W32_LDFLAGS = -no-undefined
endif

AM_CPPFLAGS = \
-I $(top_builddir)/src/builders/residfp-builder \
-I $(top_builddir)/src/builders/residfp-builder/residfp \
-I $(top_builddir)/src/builders/residfpII-builder \
-I $(top_builddir)/src/builders/residfpII-builder/residfpII \
-I $(top_builddir)/src \
-I $(top_builddir)/src/sidtune \
-I $(top_srcdir)/src \
${W32_CPPFLAGS} \
$(EXSID_CFLAGS) \
$(USBSID_CFLAGS) \
$(PTHREAD_CFLAGS) \
$(FTDI_CFLAGS) \
@debug_flags@

#=========================================================
EXTRA_DIST = \
docs/mainpage.dox \
src/psiddrv.a65 \
src/sidtune/sidplayer1.a65 \
src/sidtune/sidplayer2.a65 \
src/builders/residfp-builder/residfp/AUTHORS \
src/builders/residfp-builder/residfp/COPYING \
src/builders/residfp-builder/residfp/README \
src/builders/residfpII-builder/residfpII/AUTHORS \
src/builders/residfpII-builder/residfpII/COPYING \
src/builders/residfpII-builder/residfpII/README \
src/builders/exsid-builder/driver/docs \
src/builders/exsid-builder/driver/m4 \
$(noinst_DATA) \
$(noinst_SCRIPTS) \
test/testsuite.sh \
test/testlist

#=========================================================
# Libraries
lib_LTLIBRARIES = \
src/libsidplayfp.la \
src/libstilview.la

noinst_LTLIBRARIES = \
src/builders/residfp-builder/residfp/libresidfp.la \
src/builders/residfpII-builder/residfpII/libresidfpII.la \
src/builders/residfp-builder/libsidplayfp-residfp.la \
src/builders/residfpII-builder/libsidplayfp-residfpII.la

if USBSID_SUPPORT
  noinst_LTLIBRARIES += src/builders/usbsid-builder/libsidplayfp-usbsid.la
endif

if EXSID_SUPPORT
  noinst_LTLIBRARIES += src/builders/exsid-builder/libsidplayfp-exsid.la
endif

#=========================================================
# libsidplayfp

if LIBGCRYPT
   MD5SRC = \
src/utils/md5Gcrypt.h
else
   MD5SRC = \
src/utils/md5Internal.h \
src/utils/MD5/MD5.cpp \
src/utils/MD5/MD5.h \
src/utils/MD5/MD5_Defs.h
endif

src_libsidplayfp_la_SOURCES = \
src/Event.h \
src/EventCallback.h \
src/EventScheduler.cpp \
src/EventScheduler.h \
src/player.cpp \
src/player.h \
src/psiddrv.cpp \
src/psiddrv.h \
src/psiddrv.bin \
src/poweron.bin \
src/properties.h \
src/reloc65.cpp \
src/reloc65.h \
src/sidcxx11.h \
src/sidmd5.h \
src/sidmemory.h \
src/SidInfoImpl.h \
src/simpleMixer.cpp \
src/simpleMixer.h \
src/romCheck.h \
src/sidemu.cpp \
src/sidemu.h \
src/sidendian.h \
src/sidrandom.h \
src/stringutils.h \
src/c64/Banks/Bank.h \
src/c64/c64cpu.h \
src/c64/c64cia.h \
src/c64/c64env.h \
src/c64/c64sid.h \
src/c64/c64vic.h \
src/c64/c64.cpp \
src/c64/c64.h \
src/c64/mmu.cpp \
src/c64/mmu.h \
src/c64/Banks/ColorRAMBank.h \
src/c64/Banks/DisconnectedBusBank.h \
src/c64/Banks/ExtraSidBank.h \
src/c64/Banks/IOBank.h \
src/c64/Banks/NullSid.h \
src/c64/Banks/pla.h \
src/c64/Banks/SidBank.h \
src/c64/Banks/SystemRAMBank.h \
src/c64/Banks/SystemROMBanks.h \
src/c64/Banks/ZeroRAMBank.h \
src/c64/VIC_II/mos656x.cpp \
src/c64/VIC_II/mos656x.h \
src/c64/VIC_II/lightpen.h \
src/c64/VIC_II/sprites.h \
src/c64/CPU/flags.h \
src/c64/CPU/mos6510.cpp \
src/c64/CPU/mos6510.h \
src/c64/CPU/mos6510debug.cpp \
src/c64/CPU/mos6510debug.h \
src/c64/CPU/opcodes.h \
src/c64/CIA/interrupt.cpp \
src/c64/CIA/interrupt.h \
src/c64/CIA/mos652x.cpp \
src/c64/CIA/mos652x.h \
src/c64/CIA/SerialPort.h \
src/c64/CIA/SerialPort.cpp \
src/c64/CIA/timer.cpp \
src/c64/CIA/timer.h \
src/c64/CIA/tod.cpp \
src/c64/CIA/tod.h \
src/sidplayfp/sidplayfp.cpp \
src/sidplayfp/sidbuilder.cpp \
src/sidplayfp/SidConfig.cpp \
src/sidplayfp/SidInfo.cpp \
src/sidplayfp/SidTune.cpp \
src/sidplayfp/SidTuneInfo.cpp \
src/sidtune/MUS.cpp \
src/sidtune/MUS.h \
src/sidtune/p00.cpp \
src/sidtune/p00.h \
src/sidtune/prg.cpp \
src/sidtune/prg.h \
src/sidtune/PSID.cpp \
src/sidtune/PSID.h \
src/sidtune/sidplayer1.bin \
src/sidtune/sidplayer2.bin \
src/sidtune/SidTuneBase.cpp \
src/sidtune/SidTuneBase.h \
src/sidtune/SidTuneCfg.h \
src/sidtune/SidTuneInfoImpl.h \
src/sidtune/SidTuneTools.cpp \
src/sidtune/SidTuneTools.h \
src/sidtune/SmartPtr.h \
src/utils/iMd5.h \
src/utils/iniParser.cpp \
src/utils/iniParser.h \
src/utils/md5Factory.cpp \
src/utils/md5Factory.h \
src/utils/SidDatabase.cpp \
$(MD5SRC)

src_libsidplayfp_la_LDFLAGS = -version-info $(LIBSIDPLAYVERSION) $(W32_LDFLAGS) $(USBSID_LDFLAGS)

src_libsidplayfp_ladir = $(includedir)/sidplayfp

src_libsidplayfp_la_HEADERS = \
src/sidplayfp/siddefs.h \
src/sidplayfp/SidConfig.h \
src/sidplayfp/SidInfo.h \
src/sidplayfp/SidTuneInfo.h \
src/sidplayfp/sidbuilder.h \
src/sidplayfp/sidplayfp.h \
src/sidplayfp/SidTune.h \
src/utils/SidDatabase.h

nodist_src_libsidplayfp_la_HEADERS = \
src/sidplayfp/sidversion.h

src_libsidplayfp_la_LIBADD = \
src/builders/residfp-builder/libsidplayfp-residfp.la \
src/builders/residfpII-builder/libsidplayfp-residfpII.la \
$(LIBGCRYPT_LIBS) \
$(PTHREAD_LIBS)

src_libsidplayfp_la_CPPFLAGS = $(LIBGCRYPT_CFLAGS) $(AM_CPPFLAGS)

if USBSID_SUPPORT
  src_libsidplayfp_la_LIBADD += src/builders/usbsid-builder/libsidplayfp-usbsid.la
endif

if EXSID_SUPPORT
  src_libsidplayfp_la_LIBADD += src/builders/exsid-builder/libsidplayfp-exsid.la
endif

#=========================================================
# residfp

src_builders_residfp_builder_residfp_libresidfp_la_SOURCES = \
src/builders/residfp-builder/residfp/array.h \
src/builders/residfp-builder/residfp/Dac.cpp \
src/builders/residfp-builder/residfp/Dac.h \
src/builders/residfp-builder/residfp/EnvelopeGenerator.cpp \
src/builders/residfp-builder/residfp/EnvelopeGenerator.h \
src/builders/residfp-builder/residfp/ExternalFilter.cpp \
src/builders/residfp-builder/residfp/ExternalFilter.h \
src/builders/residfp-builder/residfp/Filter.cpp \
src/builders/residfp-builder/residfp/Filter.h \
src/builders/residfp-builder/residfp/Filter6581.cpp \
src/builders/residfp-builder/residfp/Filter6581.h \
src/builders/residfp-builder/residfp/Filter8580.cpp \
src/builders/residfp-builder/residfp/Filter8580.h \
src/builders/residfp-builder/residfp/FilterModelConfig.cpp \
src/builders/residfp-builder/residfp/FilterModelConfig.h \
src/builders/residfp-builder/residfp/FilterModelConfig6581.cpp \
src/builders/residfp-builder/residfp/FilterModelConfig6581.h \
src/builders/residfp-builder/residfp/FilterModelConfig8580.cpp \
src/builders/residfp-builder/residfp/FilterModelConfig8580.h \
src/builders/residfp-builder/residfp/Integrator.h \
src/builders/residfp-builder/residfp/Integrator6581.cpp \
src/builders/residfp-builder/residfp/Integrator6581.h \
src/builders/residfp-builder/residfp/Integrator8580.cpp \
src/builders/residfp-builder/residfp/Integrator8580.h \
src/builders/residfp-builder/residfp/OpAmp.cpp \
src/builders/residfp-builder/residfp/OpAmp.h \
src/builders/residfp-builder/residfp/Potentiometer.h \
src/builders/residfp-builder/residfp/SID.cpp \
src/builders/residfp-builder/residfp/SID.h \
src/builders/residfp-builder/residfp/Spline.cpp \
src/builders/residfp-builder/residfp/Spline.h \
src/builders/residfp-builder/residfp/Voice.h \
src/builders/residfp-builder/residfp/WaveformCalculator.cpp \
src/builders/residfp-builder/residfp/WaveformCalculator.h \
src/builders/residfp-builder/residfp/WaveformGenerator.cpp \
src/builders/residfp-builder/residfp/WaveformGenerator.h \
src/builders/residfp-builder/residfp/resample/Resampler.h \
src/builders/residfp-builder/residfp/resample/ZeroOrderResampler.h \
src/builders/residfp-builder/residfp/resample/SincResampler.cpp \
src/builders/residfp-builder/residfp/resample/SincResampler.h \
src/builders/residfp-builder/residfp/resample/TwoPassSincResampler.h \
src/builders/residfp-builder/residfp/version.cc

#=========================================================
# residfpII

src_builders_residfpII_builder_residfpII_libresidfpII_la_SOURCES = \
src/builders/residfpII-builder/residfpII/array.h \
src/builders/residfpII-builder/residfpII/Dac.cpp \
src/builders/residfpII-builder/residfpII/Dac.h \
src/builders/residfpII-builder/residfpII/EnvelopeGenerator.cpp \
src/builders/residfpII-builder/residfpII/EnvelopeGenerator.h \
src/builders/residfpII-builder/residfpII/ExternalFilter.cpp \
src/builders/residfpII-builder/residfpII/ExternalFilter.h \
src/builders/residfpII-builder/residfpII/Filter.cpp \
src/builders/residfpII-builder/residfpII/Filter.h \
src/builders/residfpII-builder/residfpII/Filter6581.cpp \
src/builders/residfpII-builder/residfpII/Filter6581.h \
src/builders/residfpII-builder/residfpII/Filter8580.cpp \
src/builders/residfpII-builder/residfpII/Filter8580.h \
src/builders/residfpII-builder/residfpII/FilterModelConfig.cpp \
src/builders/residfpII-builder/residfpII/FilterModelConfig.h \
src/builders/residfpII-builder/residfpII/FilterModelConfig6581.cpp \
src/builders/residfpII-builder/residfpII/FilterModelConfig6581.h \
src/builders/residfpII-builder/residfpII/FilterModelConfig8580.cpp \
src/builders/residfpII-builder/residfpII/FilterModelConfig8580.h \
src/builders/residfpII-builder/residfpII/Integrator.h \
src/builders/residfpII-builder/residfpII/Integrator6581.cpp \
src/builders/residfpII-builder/residfpII/Integrator6581.h \
src/builders/residfpII-builder/residfpII/Integrator8580.cpp \
src/builders/residfpII-builder/residfpII/Integrator8580.h \
src/builders/residfpII-builder/residfpII/OpAmp.cpp \
src/builders/residfpII-builder/residfpII/OpAmp.h \
src/builders/residfpII-builder/residfpII/Potentiometer.h \
src/builders/residfpII-builder/residfpII/SID.cpp \
src/builders/residfpII-builder/residfpII/SID.h \
src/builders/residfpII-builder/residfpII/Spline.cpp \
src/builders/residfpII-builder/residfpII/Spline.h \
src/builders/residfpII-builder/residfpII/Voice.h \
src/builders/residfpII-builder/residfpII/WaveformCalculator.cpp \
src/builders/residfpII-builder/residfpII/WaveformCalculator.h \
src/builders/residfpII-builder/residfpII/WaveformGenerator.cpp \
src/builders/residfpII-builder/residfpII/WaveformGenerator.h \
src/builders/residfpII-builder/residfpII/resample/Resampler.h \
src/builders/residfpII-builder/residfpII/resample/ZeroOrderResampler.h \
src/builders/residfpII-builder/residfpII/resample/SincResampler.cpp \
src/builders/residfpII-builder/residfpII/resample/SincResampler.h \
src/builders/residfpII-builder/residfpII/resample/TwoPassSincResampler.h \
src/builders/residfpII-builder/residfpII/version.cc

#=========================================================
# builders
src_builders_residfp_builder_libsidplayfp_residfp_ladir = $(includedir)/sidplayfp/builders
src_builders_residfp_builder_libsidplayfp_residfp_la_HEADERS = \
src/builders/residfp-builder/residfp.h

src_builders_residfp_builder_libsidplayfp_residfp_la_SOURCES = \
src/builders/residfp-builder/residfp-builder.cpp \
src/builders/residfp-builder/residfp-emu.cpp \
src/builders/residfp-builder/residfp-emu.h

src_builders_residfp_builder_libsidplayfp_residfp_la_LIBADD = \
src/builders/residfp-builder/residfp/libresidfp.la


src_builders_residfpII_builder_libsidplayfp_residfpII_ladir = $(includedir)/sidplayfp/builders
src_builders_residfpII_builder_libsidplayfp_residfpII_la_HEADERS = \
src/builders/residfpII-builder/residfpII.h

src_builders_residfpII_builder_libsidplayfp_residfpII_la_SOURCES = \
src/builders/residfpII-builder/residfpII-builder.cpp \
src/builders/residfpII-builder/residfpII-emu.cpp \
src/builders/residfpII-builder/residfpII-emu.h

src_builders_residfpII_builder_libsidplayfp_residfpII_la_LIBADD = \
src/builders/residfpII-builder/residfpII/libresidfpII.la

if USBSID_SUPPORT

usbsid_src = \
  src/builders/usbsid-builder/driver/USBSID.cpp \
  src/builders/usbsid-builder/driver/USBSID.h

  # src/builders/usbsid-builder/driver/USBSIDInterface.cpp \
  # src/builders/usbsid-builder/driver/USBSIDInterface.h

src_builders_usbsid_builder_libsidplayfp_usbsid_ladir = $(includedir)/sidplayfp/builders
src_builders_usbsid_builder_libsidplayfp_usbsid_la_HEADERS = \
src/builders/usbsid-builder/usbsid.h

src_builders_usbsid_builder_libsidplayfp_usbsid_la_SOURCES = \
src/builders/usbsid-builder/usbsid-builder.cpp  \
src/builders/usbsid-builder/usbsid-emu.cpp \
src/builders/usbsid-builder/usbsid-emu.h \
$(usbsid_src)

src_builders_usbsid_builder_libsidplayfp_usbsid_la_LIBADD = \
    $(USBSID_LIBS) \
    $(PTHREAD_LIBS)

endif

if EXSID_SUPPORT

if EXSID_DRIVER
  exsid_src = \
src/builders/exsid-builder/driver/exSID.c \
src/builders/exsid-builder/driver/exSID.h \
src/builders/exsid-builder/driver/exSID_defs.h \
src/builders/exsid-builder/driver/exSID_ftdiwrap.c \
src/builders/exsid-builder/driver/exSID_ftdiwrap.h
endif

src_builders_exsid_builder_libsidplayfp_exsid_ladir = $(includedir)/sidplayfp/builders
src_builders_exsid_builder_libsidplayfp_exsid_la_HEADERS = \
src/builders/exsid-builder/exsid.h

src_builders_exsid_builder_libsidplayfp_exsid_la_SOURCES = \
src/builders/exsid-builder/exsid-builder.cpp  \
src/builders/exsid-builder/exsid-emu.cpp \
src/builders/exsid-builder/exsid-emu.h \
$(exsid_src)

src_builders_exsid_builder_libsidplayfp_exsid_la_LIBADD = \
$(EXSID_LIBS) \
$(PTHREAD_LIBS)
endif

#=========================================================
# libstilview
src_libstilview_la_SOURCES = \
src/utils/STILview/stil.cpp

src_libstilview_la_LDFLAGS = -version-info $(LIBSTILVIEWVERSION) $(W32_LDFLAGS)

src_libstilview_ladir = $(includedir)/stilview

src_libstilview_la_HEADERS = \
src/utils/STILview/stil.h \
src/utils/STILview/stildefs.h

#=========================================================
# docs
if HAVE_DOXYGEN
doc:
	$(DOXYGEN) Doxyfile

clean-local:
	rm -fr $(builddir)/docs/html
endif

#=========================================================
# test
if TESTSUITE

if MINGW32
DEMO_SRC =
else
DEMO_SRC = test/demo
endif

noinst_PROGRAMS = \
$(DEMO_SRC) \
test/test \
src/builders/residfp-builder/residfp/resample/test

test_demo_SOURCES = test/demo.cpp

test_demo_LDADD = src/libsidplayfp.la

test_test_SOURCES = test/test.cpp

test_test_LDADD = src/libsidplayfp.la

src_builders_residfp_builder_residfp_resample_test_SOURCES = src/builders/residfp-builder/residfp/resample/test.cpp

src_builders_residfp_builder_residfp_resample_test_LDADD = src/builders/residfp-builder/residfp/resample/SincResampler.lo
endif

#=========================================================

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libsidplayfp.pc libstilview.pc

#=========================================================

BUILT_SOURCES = \
$(noinst_DATA:.dat=.h) \
src/psiddrv.bin \
src/sidtune/sidplayer1.bin \
src/sidtune/sidplayer2.bin

#=========================================================
# Recreate psiddrv.bin, needs xa65

MAINTAINERCLEANFILES = $(BUILT_SOURCES)

.a65.bin:
	o65file=`echo $@ | sed 's/bin/o65/'`;\
	[ -n "$(OD)" ] || { echo "od not found"; false; } &&\
	[ -n "$(XA)" ] || { echo "xa not found"; false; } &&\
	${XA} -R -G $< -o $$o65file &&\
	${OD} -v -An -w8 -tx1 $$o65file | sed -re 's/[[:alnum:]]+/0x&,/g' > $@ &&\
	${RM} $$o65file
