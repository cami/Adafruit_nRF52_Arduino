// **********************************************************************
// *                    SEGGER Microcontroller GmbH                     *
// *                        The Embedded Experts                        *
// **********************************************************************
// *                                                                    *
// *            (c) 2014 - 2019 SEGGER Microcontroller GmbH             *
// *            (c) 2001 - 2019 Rowley Associates Limited               *
// *                                                                    *
// *           www.segger.com     Support: support@segger.com           *
// *                                                                    *
// **********************************************************************
// *                                                                    *
// * All rights reserved.                                               *
// *                                                                    *
// * Redistribution and use in source and binary forms, with or         *
// * without modification, are permitted provided that the following    *
// * conditions are met:                                                *
// *                                                                    *
// * - Redistributions of source code must retain the above copyright   *
// *   notice, this list of conditions and the following disclaimer.    *
// *                                                                    *
// * - Neither the name of SEGGER Microcontroller GmbH                  *
// *   nor the names of its contributors may be used to endorse or      *
// *   promote products derived from this software without specific     *
// *   prior written permission.                                        *
// *                                                                    *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
// * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
// * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
// * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
// * DISCLAIMED.                                                        *
// * IN NO EVENT SHALL SEGGER Microcontroller GmbH BE LIABLE FOR        *
// * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
// * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
// * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
// * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
// * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
// * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
// * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
// * DAMAGE.                                                            *
// *                                                                    *
// **********************************************************************

#ifndef __debug_stdio_H
#define __debug_stdio_H

#include <debugio.h>

#define FILE     DEBUG_FILE

#ifndef SEEK_CUR
#define SEEK_CUR DEBUG_SEEK_CUR
#define SEEK_END DEBUG_SEEK_END
#define SEEK_SET DEBUG_SEEK_SET
#endif

#define stdin    DEBUG_STDIN
#define stdout   DEBUG_STDOUT
#define stderr   DEBUG_STDERR

#define fopen    debug_fopen
#define fflush   debug_fflush
#define fclose   debug_fclose
#define fprintf  debug_fprintf
#define vfprintf debug_vfprintf
#define printf   debug_printf
#define vprintf  debug_vprintf
#define fscanf   debug_fscanf
#define scanf    debug_scanf
#define vscanf   debug_vscanf
#define vfscanf  debug_vfscanf
#define getchar  debug_getchar
#define getc     debug_fgetc
#define gets     debug_gets
#define fgetc    debug_fgetc
#define fgets    debug_fgets
#define fputc    debug_fputc
#define fputs    debug_fputs
#ifndef putchar
#define putchar  debug_putchar
#endif
#define puts     debug_puts
#define fread    debug_fread
#define fwrite   debug_fwrite
#define fseek    debug_fseek
#define ftell    debug_ftell
#define rewind   debug_rewind
#define filesize debug_filesize
#define clearerr debug_clearerr
#define feof     debug_feof
#define ferror   debug_ferror
#define exit     debug_exit
#define time     debug_time

#endif

