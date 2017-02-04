# lua-sandbox

A very quick sandbox module written for Lua 5.3, Linux compatible

## Usage

```lua
-- luacheck: ignore
local sandbox = require("sandbox")
local cqueues = require("cqueues")
local socket = require("cqueues.socket")
local sockets = {
	parent = {socket.pair("stream")};
	child = {socket.pair("stream")};
}

W, R = 1, 2

pid = sandbox.fork()
if pid ~= 0 then -- parent, send to child queue
	sockets.child[W]:write("message")
	local cq = cqueues.new()
	local is_dead = false
	cq:wrap(function()
		print('waiting')
		print('received:', sockets.parent[R]:read())
		is_dead = true
	end)
	cq:loop(3)
	if not is_dead then
		print('terminating')
		if not sandbox.kill(pid, sandbox.SIGTERM) then
			print('killing')
			print(sandbox.kill(pid, sandbox.SIGKILL))
		end
	end
else
	print(sockets.child[R]:read())
	for i=1, 5 do
		cqueues.sleep(1)
	end
end
```
