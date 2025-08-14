/*
 * wepoll - epoll for Windows
 * https://github.com/piscisaureus/wepoll
 *
 * Copyright 2012-2020, Bert Belder <bertbelder@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WEPOLL_H_
#define WEPOLL_H_
#pragma once

#ifndef WEPOLL_EXPORT
#define WEPOLL_EXPORT
#endif

#include <stdint.h>

enum EPOLL_EVENTS {
  EPOLLIN          = (unsigned) (1U <<  0),
  EPOLLPRI         = (unsigned) (1U <<  1),
  EPOLLOUT         = (unsigned) (1U <<  2),
  EPOLLERR         = (unsigned) (1U <<  3),
  EPOLLHUP         = (unsigned) (1U <<  4),
  EPOLLNVAL        = (unsigned) (1U <<  5),
  EPOLLRDNORM      = (unsigned) (1U <<  6),
  EPOLLRDBAND      = (unsigned) (1U <<  7),
  EPOLLWRNORM      = (unsigned) (1U <<  8),
  EPOLLWRBAND      = (unsigned) (1U <<  9),
  EPOLLMSG         = (unsigned) (1U << 10), /* Never reported. */
  EPOLLRDHUP       = (unsigned) (1U << 13),
  EPOLL_URING_WAKE = (unsigned) (1U << 27),
  EPOLLEXCLUSIVE   = (unsigned) (1U << 28),
  EPOLLWAKEUP      = (unsigned) (1U << 29),
  EPOLLONESHOT     = (unsigned) (1U << 30),
  EPOLLET          = (unsigned) (1U << 31)
};

#define EPOLLIN          (1U <<  0)
#define EPOLLPRI         (1U <<  1)
#define EPOLLOUT         (1U <<  2)
#define EPOLLERR         (1U <<  3)
#define EPOLLHUP         (1U <<  4)
#define EPOLLNVAL        (1U <<  5)
#define EPOLLRDNORM      (1U <<  6)
#define EPOLLRDBAND      (1U <<  7)
#define EPOLLWRNORM      (1U <<  8)
#define EPOLLWRBAND      (1U <<  9)
#define EPOLLMSG         (1U << 10)
#define EPOLLRDHUP       (1U << 13)
#define EPOLL_URING_WAKE (1U << 27)
#define EPOLLEXCLUSIVE   (1U << 28)
#define EPOLLWAKEUP      (1U << 29)
#define EPOLLONESHOT     (1U << 30)
#define EPOLLET          (1U << 31)

#define EPOLL_CTL_ADD    1
#define EPOLL_CTL_DEL    2
#define EPOLL_CTL_MOD    3
#define EPOLL_CLOEXEC    02000000

typedef void* HANDLE;
typedef uintptr_t SOCKET;

typedef union epoll_data {
  void* ptr;
  int fd;
  uint32_t u32;
  uint64_t u64;
  SOCKET sock; /* Windows specific */
  HANDLE hnd;  /* Windows specific */
} epoll_data_t;

struct epoll_event {
  uint32_t events;   /* Epoll events and flags */
  epoll_data_t data; /* User data variable */
};

#ifdef __cplusplus
extern "C" {
#endif

WEPOLL_EXPORT HANDLE epoll_create(int size);
WEPOLL_EXPORT HANDLE epoll_create1(int flags);

WEPOLL_EXPORT int epoll_close(HANDLE ephnd);

WEPOLL_EXPORT int epoll_ctl(HANDLE ephnd,
                            int op,
                            SOCKET sock,
                            struct epoll_event* event);

WEPOLL_EXPORT int epoll_wait(HANDLE ephnd,
                             struct epoll_event* events,
                             int maxevents,
                             int timeout);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* WEPOLL_H_ */
