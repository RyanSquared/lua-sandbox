#define _GNU_SOURCE

#include <sys/prctl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <sched.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define RLIM(resource, rlim, size) rlim.rlim_max = size; rlim.rlim_cur = size; setrlimit(resource, &rlim);

int sandbox_protect(lua_State *L);

int luaopen_sandbox(lua_State *L);
