-- luacheck: ignore
local sandbox = require("sandbox")
local cqueues = require("cqueues")
local fork = require("sandbox.cqueues").fork

pid, parent, child = fork()
if pid ~= 0 then -- parent, send to child queue
	child:write("message\n")
	local cq = cqueues.new()
	local is_dead = false
	cq:wrap(function()
		print('waiting')
		print('received:', child:read())
		is_dead = true
	end)
	cq:loop(2)
	if not is_dead then
		print('terminating')
		if not sandbox.kill(pid, sandbox.SIGTERM) then
			print('killing')
			print(sandbox.kill(pid, sandbox.SIGKILL))
		end
	end
else
	print(parent:read())
	for i=1, 1 do
		cqueues.sleep(1)
	end
	parent:write("msg\n")
end
