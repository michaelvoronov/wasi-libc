// Copyright (c) 2015-2016 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <common/time.h>

#include <sys/times.h>

#include <assert.h>
#include <wasi/api.h>

static_assert(CLOCKS_PER_SEC == NSEC_PER_SEC,
              "Timestamp should need no conversion");

clock_t times(struct tms *buffer) {
  // Obtain user time.
  __wasi_timestamp_t usertime = 0;
#ifdef __wasilibc_unmodified_upstream // generated constant names
  (void)__wasi_clock_time_get(__WASI_CLOCK_PROCESS_CPUTIME_ID, 0, &usertime);
#else
  (void)__wasi_clock_time_get(__WASI_CLOCKID_PROCESS_CPUTIME_ID, 0, &usertime);
#endif
  *buffer = (struct tms){.tms_utime = usertime};

  // Obtain real time.
  __wasi_timestamp_t realtime = 0;
#ifdef __wasilibc_unmodified_upstream // generated constant names
  (void)__wasi_clock_time_get(__WASI_CLOCK_MONOTONIC, 0, &realtime);
#else
  (void)__wasi_clock_time_get(__WASI_CLOCKID_MONOTONIC, 0, &realtime);
#endif
  return realtime;
}
