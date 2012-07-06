function handler_nihao(args)
	return true, "zhejiushiniyaodenihao"
end

local fun_table = {
	["/nihao"] = handler_nihao
}

cnt = 1
function http_request_handler(args)
	return true, "buduiba"
	local host = args.host
	local code = args.code
	local uri = args.uri

	print(string.format("get request(%d) uri(%s) from %s", cnt, uri, host))
	cnt = cnt + 1

	for k, v in pairs(fun_table) do
		if uri:find(k) then
			return v(args)
		end
	end

	--engine.http_request("192.0.0.1", 8050)

	return true, "buduiba"
end
