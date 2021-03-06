#ifndef EXTRA_DEFINES_H
#define EXTRA_DEFINES_H

/*
#ifdef WINDOWS
#include <Windows.h>
#undef _WIN32
#undef WIN32
#undef WCHAR
#endif
*/

// #include "tchar.h"
// rename init_audio to make init_audio available

#define init_audio uae_init_audio

#include "uae/log.h"

// we are using our own main function, not the one from UAE...

#define NO_MAIN_IN_MAIN_C

#ifndef WINDOWS
#define CAN_PRINTF_LONG_LONG
#endif

// UAE code must use this instead of RAND_MAX, and use uaerand for all
// random number generation
#define UAE_RAND_MAX 2147483647

/*
unsigned int uaerand_impl (void);
static inline unsigned int uaerand (void) {
    printf("   >>>>    uaerand    <<<< %s:%d:%s\n",  __BASE_FILE__, __LINE__,
            __func__);
    return uaerand_impl();
}
*/

#define DEBUG_SYNC
//#define DEBUG_SYNC_MEMORY
#ifdef DEBUG_SYNC
#include <stdio.h>
extern FILE *g_fs_uae_sync_debug_file;
#define write_sync_log(format, ...) \
    if (g_fs_uae_sync_debug_file) { \
        fprintf(g_fs_uae_sync_debug_file, format, __VA_ARGS__); \
    }
#endif

// needed to include functions in include/debug.h, which in turn
// is needed by code

#define DEBUGGER 1

//#define A2065
#define AGA
//#define AHI
#define ARCADIA
#define AUTOCONFIG

#if !defined(ANDROID) && !defined(__LSB_VERSION__)
#define BSDSOCKET
#endif

#define ECS_DENISE
#define CPUEMU_0 /* generic 680x0 emulation with direct memory access */
#define CPUEMU_11 /* 68000/68010 prefetch emulation */
#define CPUEMU_13 /* 68000/68010 cycle-exact cpu&blitter */
#define CPUEMU_20 /* 68020 prefetch */
#define CPUEMU_21 /* 68020 "cycle-exact" + blitter */
#define CPUEMU_22 /* 68030 prefetch */
#define CPUEMU_23 /* 68030 "cycle-exact" + blitter */
#define CPUEMU_24 /* 68060 "cycle-exact" + blitter */
#define CPUEMU_25 /* 68040 "cycle-exact" + blitter */
#define CPUEMU_31 /* Aranym 68040 MMU */
#define CPUEMU_32 /* Previous 68030 MMU */
#define CPUEMU_33 /* 68060 MMU */
#define CPUEMU_40 /* generic 680x0 with indirect memory access */
//#define DEBUGGER
//#define ENFORCER
#define FDI2RAW
#define FILESYS
#define GFXFILTER

#define MMU
#define MMUEMU /* Aranym 68040 MMU */
//#define MULTIDISPLAY 1
#define NATMEM_OFFSET natmem_offset
#define NCR
#define FULLMMU /* Aranym 68040 MMU */
#define PARALLEL_PORT
#define SAVESTATE
#define SCP
#define SCSIEMU
#define SUPPORT_THREADS
#define UAESERIAL
#define UAE_FILESYS_THREADS
//#define UAE_FILESYS_ASYNCHRONOUS
//#define USE_SDL

#ifdef LINUX
#define WITH_SCSI_IOCTL
#endif

#define XARCADE
#define GNU_SOURCE 1

#include "uae/limits.h"

// needed by serial.cpp
#ifdef WINDOWS
// FIXME: DUMMY
#define O_NDELAY 0
#endif

// These should be valid on all supported systems, also Windows
#define FSDB_DIR_SEPARATOR '/'
#define FSDB_DIR_SEPARATOR_S "/"

// FIXME: OK?
//#define _stat64 stat

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif
#ifdef WINDOWS
typedef uintptr_t SOCKET;
#else
typedef int SOCKET;
#endif

typedef unsigned short USHORT;


#ifndef DO_NOT_INCLUDE_WINUAE_COMPAT_H
// we do not always want to include these, especially not in uae_host.cpp
// were we actually need access to some of the underlying function names
#include "winuae_compat.h"
#endif

// Some WinUAE-derived code which must not be used is guarded by _WIN32
// defines. The code is fixed so compiling without _WIN32 defined works
// when compiling FS-UAE for Windows. FS-UAE code use the WINDOWS define
// instead to avoid collision with WinUAE.

//#undef _WIN32
//#undef WIN32

#include "../include/sysdeps.h"

#undef ENUMNAME
#undef ENUMDECL

#include "uae/enum.h"

#include "machdep/machdep.h"

// some code needs uae_sem_t but does not include thread.h properly
// (include/bsdsocket.h)

#include "threaddep/thread.h"

// FIXME: IMPLEMENT
//void _stprintf(wchar_t* buffer, wchar_t* format, ...);

extern TCHAR start_path_data[];
extern void picasso_reset (void);
extern void picasso_handle_hsync (void);
extern void init_hz_p96 (void);
int GetDriveType(TCHAR* vol);

void sleep_millis(int ms);
//void install_driver(int flags);

extern int uae_start_thread_fast (void *(*f)(void *), void *arg,
        uae_thread_id *thread);

#ifdef WINDOWS

#else
#endif

#define FILEFLAG_WRITE S_IWUSR
#define FILEFLAG_READ S_IRUSR
#define FILEFLAG_EXECUTE S_IXUSR
#define FILEFLAG_DIR S_IFDIR


#define Sleep sleep_millis

// needed to compile gencpu.cpp as C code (which is needed because
// of int to enum conversions (illegal in C++)
#ifndef __cplusplus
// FIXME:
//typedef int bool
#define bool int
#define true 1
#define false 0
#endif


// -------------------------- windows temp --------------------------
// FIXME: THESE ARE HERE IN ORDER TO COMPILE blkdev.cpp
#define UAESCSI_CDEMU 0
#define UAESCSI_SPTI 1
#define UAESCSI_SPTISCAN 2
#define UAESCSI_ASPI_FIRST 3
#define UAESCSI_ADAPTECASPI 3
#define UAESCSI_NEROASPI 4
#define UAESCSI_FROGASPI 5

#ifndef WINDOWS
// just setting DRIVE_CDROM to something here..
#define DRIVE_CDROM 0
#endif

#include <stddef.h>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include "uae/jitconfig.h"

#ifndef NORETURN
#ifdef __GNUC__
#define NORETURN __attribute__((__noreturn__))
#else
#define NORETURN
#endif
#endif

#ifdef WINDOWS
#ifdef __MINGW64_VERSION_MAJOR
#define _argc __argc
#define _argv __argv
#endif
extern int _argc;
extern char** _argv;
#undef main
// prevent later imports of SDL to overwrite main
#define _SDL_main_h
int _uae_main(int argc, char* argv[]);
#define main(a, b) WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { \
    return _uae_main(_argc, _argv); \
} \
int _uae_main(int argc, char* argv[])
#endif

#endif // EXTRA_DEFINES_H
