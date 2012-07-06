function handler_nihao(args)
	return true, "zhejiushiniyaodenihao"
end

function dump_base(args)
	http.dump()
	return true, "dump ok"
end

function show_args(args)

	local a = {123,3245, 2134123, 24134123, "sfasdfdasf", nil,{12314}}
	local b = {123,3245, 2134123, ["adsfsda"] = 24134123, "sfasdfdasf", {12314}}

	print("a ".. tostring(http.is_array(a)));
	print("b ".. tostring(http.is_array(b)));

	return true, http.encode_header(args);
end

local fun_table = {
	["/nihao"] = handler_nihao,
	["/dump"] = dump_base,
	["/show"] = show_args,
}

cnt = 1
function http_request_handler(args)
	--return true, "buduiba"
	local host = args.host
	local code = args.code
	local path = args.path

	print(string.format("get request(%d) path(%s) from %s", cnt, path, host))
	print("query:" ..tostring(args.query));
	cnt = cnt + 1

	http.get("220.181.112.143", 80 ,"/")

	for k, v in pairs(fun_table) do
		if path:find(k) then
			return v(args)
		end
	end

	--engine.http_request("192.0.0.1", 8050)

	return true, "buduiba"
end
