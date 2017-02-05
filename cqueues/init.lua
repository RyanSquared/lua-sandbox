local sandbox = require("sandbox")
local socket = require("cqueues.socket")

local function fork()
	local s1, s2 = socket.pair()
	local pid, errn, errs = assert(sandbox.fork())
	if not pid then
		return errn, errs
	else
		return pid, s1, s2
	end
end

return {
	fork = fork
}
