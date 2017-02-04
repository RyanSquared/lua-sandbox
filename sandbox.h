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

// kill()
#include <signal.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define RLIM(resource, rlim, size) rlim.rlim_max = size; rlim.rlim_cur = size; setrlimit(resource, &rlim);
#define SETF(name, value) lua_pushstring(L, name); lua_pushinteger(L, value); lua_settable(L, -3);

int sandbox_pusherror(lua_State *L, int value);
int sandbox_protect(lua_State *L);
int sandbox_fork(lua_State *L);

int luaopen_sandbox(lua_State *L);
