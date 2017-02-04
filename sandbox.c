#include "sandbox.h"
#include <stdio.h>

int sandbox_protect(lua_State *L) {
	prctl(PR_SET_NO_NEW_PRIVS, true); // disable privilege escalation

	unshare(CLONE_FILES | CLONE_FS | CLONE_NEWIPC | CLONE_NEWNET |
		CLONE_NEWNS | CLONE_NEWUTS | CLONE_SYSVSEM);
	// make unable to clone() into external things

	struct rlimit rl;
	RLIM(RLIMIT_AS, rl, 8 * 1024 * 1024); // memory, 8 MB
	RLIM(RLIMIT_CORE, rl, 0); // core dump, 0 bytes
	RLIM(RLIMIT_CPU, rl, 3); // CPU time limit, 3 seconds
	RLIM(RLIMIT_FSIZE, rl, 0); // File size allowed to write, 0 bytes
	RLIM(RLIMIT_MSGQUEUE, rl, 0); // POSIX message queues, 0
	RLIM(RLIMIT_NOFILE, rl, 1); // File descriptors, 1
	RLIM(RLIMIT_NPROC, rl, 0); // Forks and threads, 0

	prctl(PR_SET_DUMPABLE, false); // disable core dumps

	return 0;
}

luaL_Reg sandbox[] = {
	{"protect", sandbox_protect},
	{NULL, NULL}
};

int luaopen_sandbox(lua_State *L) {
	luaL_newlib(L, sandbox);
	return 1;
}
