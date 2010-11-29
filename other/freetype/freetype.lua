FreeType = {
	basepath = PathDir(ModuleFilename()),
	
	OptFind = function (name, required)	
		local check = function(option, settings)
			option.value = false
			option.use_ftconfig = false
			option.use_win32lib = false
			option.use_staticft = false
			option.lib_path = nil

			if ExecuteSilent("freetype-config") > 0 and ExecuteSilent("freetype-config --cflags") == 0 then
				option.value = true
				option.use_ftconfig = true
			end
			
			if platform == "win32" then
				option.value = true
				option.use_win32lib = true
			end

			if platform == "macosx" then
				option.value = true
				option.use_ftconfig = false
				option.use_staticft = true
			end
		end
		
		local apply = function(option, settings)
			-- include path
			settings.cc.includes:Add(FreeType.basepath .. "/include")
			
			if option.use_staticft == true then
				settings.cc.includes:Add("other/freetype/include")
				client_settings.link.libpath:Add("other/freetype/lib")
				client_settings.link.libs:Add("freetype243")
			elseif option.use_ftconfig == true then
				settings.cc.flags:Add("`freetype-config --cflags`")
				settings.link.flags:Add("`freetype-config --libs`")
			elseif option.use_win32lib == true then
				if settings.debug > 0 then
					settings.link.libs:Add(FreeType.basepath .. "/lib/freetype243MT_D")
				else
					settings.link.libs:Add(FreeType.basepath .. "/lib/freetype243MT")
				end
			end
		end
		
		local save = function(option, output)
			output:option(option, "value")
			output:option(option, "use_ftconfig")
			output:option(option, "use_win32lib")
			output:option(option, "use_staticft")
		end
		
		local display = function(option)
			if option.value == true then
				if option.use_ftconfig == true then return "using freetype-config" end
				if option.use_win32lib == true then return "using supplied win32 libraries" end
				if option.use_staticft == true then return "using static freetype library" end
				return "using unknown method"
			else
				if option.required then
					return "not found (required)"
				else
					return "not found (optional)"
				end
			end
		end
		
		local o = MakeOption(name, 0, check, save, display)
		o.Apply = apply
		o.include_path = nil
		o.lib_path = nil
		o.required = required
		return o
	end
}
