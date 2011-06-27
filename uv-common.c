/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "uv.h"

#include <assert.h>
#include <stddef.h> /* NULL */
#include <string.h> /* memset */

/* use inet_pton from c-ares if necessary */
#include "ares_config.h"
#include "c-ares/inet_net_pton.h"


static uv_counters_t counters;


uv_counters_t* uv_counters() {
  return &counters;
}


const char* uv_err_name(uv_err_t err) {
  switch (err.code) {
    case UV_UNKNOWN: return "UNKNOWN";
    case UV_OK: return "OK";
    case UV_EOF: return "EOF";
    case UV_EACCESS: return "EACCESS";
    case UV_EAGAIN: return "EAGAIN";
    case UV_EADDRINUSE: return "EADDRINUSE";
    case UV_EADDRNOTAVAIL: return "EADDRNOTAVAIL";
    case UV_EAFNOSUPPORT: return "EAFNOSUPPORT";
    case UV_EALREADY: return "EALREADY";
    case UV_EBADF: return "EBADF";
    case UV_EBUSY: return "EBUSY";
    case UV_ECONNABORTED: return "ECONNABORTED";
    case UV_ECONNREFUSED: return "ECONNREFUSED";
    case UV_ECONNRESET: return "ECONNRESET";
    case UV_EDESTADDRREQ: return "EDESTADDRREQ";
    case UV_EFAULT: return "EFAULT";
    case UV_EHOSTUNREACH: return "EHOSTUNREACH";
    case UV_EINTR: return "EINTR";
    case UV_EINVAL: return "EINVAL";
    case UV_EISCONN: return "EISCONN";
    case UV_EMFILE: return "EMFILE";
    case UV_ENETDOWN: return "ENETDOWN";
    case UV_ENETUNREACH: return "ENETUNREACH";
    case UV_ENFILE: return "ENFILE";
    case UV_ENOBUFS: return "ENOBUFS";
    case UV_ENOMEM: return "ENOMEM";
    case UV_ENONET: return "ENONET";
    case UV_ENOPROTOOPT: return "ENOPROTOOPT";
    case UV_ENOTCONN: return "ENOTCONN";
    case UV_ENOTSOCK: return "ENOTSOCK";
    case UV_ENOTSUP: return "ENOTSUP";
    case UV_EPROTO: return "EPROTO";
    case UV_EPROTONOSUPPORT: return "EPROTONOSUPPORT";
    case UV_EPROTOTYPE: return "EPROTOTYPE";
    case UV_ETIMEDOUT: return "ETIMEDOUT";
    default:
      assert(0);
      return NULL;
  }
}


struct sockaddr_in uv_ip4_addr(const char* ip, int port) {
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(struct sockaddr_in));

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);

  return addr;
}


struct sockaddr_in6 uv_ip6_addr(const char* ip, int port) {
  struct sockaddr_in6 addr;

  memset(&addr, 0, sizeof(struct sockaddr_in6));

  addr.sin6_family = AF_INET6;
  addr.sin6_port = htons(port);
  ares_inet_pton(AF_INET6, ip, &addr.sin6_addr);

  return addr;
}
