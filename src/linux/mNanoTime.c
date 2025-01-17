/*$
Copyright (c) 2017, Azel
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
$*/

/*****************************************
 * <Linux> mNanoTime
 *****************************************/

/* glibc 2.17 以前では、clock_gettime() を使う場合 librt のリンクが必要 */


#include <unistd.h>

#if defined(_POSIX_TIMERS) && _POSIX_TIMERS > 0
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "mDef.h"
#include "mNanoTime.h"


/**
@addtogroup nanotime
 
@{
*/

/** 現在のナノ時間を取得 */

void mNanoTimeGet(mNanoTime *nt)
{
#if defined(_POSIX_TIMERS) && _POSIX_TIMERS > 0

	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	nt->sec  = ts.tv_sec;
	nt->nsec = ts.tv_nsec;

#else

	struct timeval tv;

	gettimeofday(&tv, NULL);

	nt->sec  = tv.tv_sec;
	nt->nsec = tv.tv_usec * 1000;

#endif
}

/** @} */
