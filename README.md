# lua-sandbox

A very quick sandbox module written for Lua 5.3, Linux compatible

## API - `sandbox`

`sandbox.protect()` - Restricts access to resources.

`sandbox.kill(pid)` - Terminates process with PID.

`sandbox.fork()` - Forks and returns child PID or 0.

## API - `sandbox.cqueues`

`sandbox_cqueues.fork()` - Forks and returns a PID or 0 and a socket pair.
