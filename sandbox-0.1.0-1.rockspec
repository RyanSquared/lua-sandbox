package = "sandbox"
version = "0.1.0-1"
source = {
	url = "..."
}
build = {
	type = "builtin",
	modules = {
		sandbox = {
			sources = {"sandbox.c"}
		};
		["sandbox.cqueues"] = "cqueues/init.lua";
	}
}
