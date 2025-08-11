local U = require('common.utils')
local debug = require("debug")

local function checkCGTVersion()
  local cgt_install_dir = 'C:/Users/vicen/AppData/Local/Programs/PLECS C2000 TSP/cgt/ti-cgt-c2000_22.6.1.LTS'
  local min_version = '22.6.0'
  local cgt_version_file = 'C:/Users/vicen/Documents/motor-drive-plecs/Delfino/Blinky_codegen/TI2837x_cpu1_cgt_version.txt'

  -- determine CGT version in file that was created by 'cl2000 -version'
  local file, e = io.open(cgt_version_file, "r") 
  if file == nil then
    U.error("Unable to verify CGT version (version file not found).")
  end
  -- look for line with "TMS320C2000 C/C++ Compiler              v20.2.1.LTS"
  local key = 'TMS320C2000 C/C++ Compiler'
  local version = {}
  for l in file:lines() do
    if string.sub(l,1,#key) == key then
      -- parse version number
      local text = string.sub(l, #key+1, -1)
      text = text:gsub("%s+", "") -- drop spaces
      text = text:sub(2,-1) -- drop 'v'
      for v in string.gmatch(text, "[^.]+") do
        table.insert(version, tonumber(v))
      end      
      break
    end
  end
  -- now check version
  local i=1
  for v in string.gmatch(min_version, "[^.]+") do
    if version[i] == nil then
      break
    end
    if tonumber(v) > version[i] then
      -- assemble string of detected version for error message
      local version_str = ""
      for i,v in ipairs(version) do
        version_str = "%s%i" % {version_str, version[i]} 
        if i < #version then
          version_str = version_str .. "."
        end
      end
      U.error([[
        The TI CGT must be of version %(min_version)s or more recent.

        - Version detected: %(version)s
        - Installation directory: %(install_dir)s]] % {
        min_version = min_version,
        version = version_str,
        install_dir = cgt_install_dir,
      })
    elseif tonumber(v) < version[i] then
      break
    end 
    i = i+1
  end
end

local function prebuildFunction()
  checkCGTVersion()
end

local ok, res = xpcall(prebuildFunction, debug.traceback)

if ok then 
  U.dumpLog()
  return res
else -- there was an error, res will be an error including the stack trace
  -- prepend newline for better visual separation
  error("\n%s" % {U.stripTraceOrRethrowError(res)}, 0) -- must use error to halt execution of build here.
end

