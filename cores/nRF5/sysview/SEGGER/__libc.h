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

#ifndef __libc_H
#define __libc_H

#include "__crossworks.h"

#ifdef __cplusplus
extern "C" {
#endif

int __getchar(void);
#ifndef __PRINTF_TAG_PTR_DEFINED
#define __PRINTF_TAG_PTR_DEFINED
typedef struct __printf_tag *__printf_tag_ptr;
#endif
int __putchar(int, __printf_tag_ptr);
int __stdin_ungetc(int);

char *__xtoa(unsigned __val, char *__buf, unsigned __radix, int __neg);
char *__xltoa(unsigned long __val, char *__buf, unsigned __radix, int __neg);
char *__xlltoa(unsigned long long __val, char *__buf, unsigned __radix, int __neg);
int __digit(int __ch, int __radix);
unsigned long __strtoul(const char *__nsptr, char **__endptr, int __base);
unsigned long long __strtoull(const char *__nsptr, char **__endptr, int __base);
double __RAL_pow10(int __e);

void __heap_lock(void);
void __heap_unlock(void);
void __printf_lock(void);
void __printf_unlock(void);
void __scanf_lock(void);
void __scanf_unlock(void);
void __debug_io_lock(void);
void __debug_io_unlock(void);

int __open(const char *__filename, const char *__mode);
int __close(int __fildes);
int __flush(int __fildes);
int __write(int __fildes, const unsigned char *__buf, unsigned __len);
int __read(int __fildes, unsigned char *__buf, unsigned __len);
long __seek(int __fildes, long __offset, int __whence);

#ifdef __cplusplus
}
#endif

#endif

