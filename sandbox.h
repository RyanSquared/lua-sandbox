#define _GNU_SOURCE

// protect()
#include <sys/prctl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <sched.h>

// fork()
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define RLIM(resource, rlim, size) rlim.rlim_max = size; rlim.rlim_cur = size; setrlimit(resource, &rlim);

int sandbox_protect(lua_State *L);
int sandbox_fork(lua_State *L);

int luaopen_sandbox(lua_State *L);
