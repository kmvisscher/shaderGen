local root = "../../"
VERBOSE=1

solution "ShaderGen"

    location( root .. "shadergen/" )
    targetdir ( root .. "bin/" )
    objdir( root .. "bin/obj/" )
    
    configurations { "Release","Debug", "Coverage" }

    platforms { "x64", "x32" }

    vectorextensions "SSE2"

    flags "Unicode" 

    configuration "x32"
        targetdir( root .. "bin/x32/" )
        debugdir( root .. "bin/x32/" )
        architecture "x32"

    configuration "x64"
        targetdir( root .. "bin/x64/" )
        debugdir( root .. "bin/x64/" )
        architecture "x64"
        
    configuration "Debug"
        targetsuffix "d"
        defines "DEBUG"
        flags "Symbols"
        optimize "Off"

    configuration "Release"     
        flags "LinkTimeOptimization"
        optimize "Speed"
        
    configuration "Coverage"
        targetsuffix "cd"
        flags "Symbols"
        links "gcov"
        buildoptions "-coverage"
                
    configuration {}

    --[[
    project "LLVM"
    
        targetname "LLVM"   
        kind "StaticLib"
        
        defines "_GNU_SOURCE"
        defines { "__STDC_CONSTANT_MACROS", 
       	          "__STDC_FORMAT_MACROS", 
                  "__STDC_LIMIT_MACROS" }

        includedirs {
            root .. "extern/llvm37/include/"
            }   
        
        files {
            root .. "extern/llvm37/**.h",
            root .. "extern/llvm37/**.cpp"
            } 
        
        --excludes { 
         --   root .. "extern/llvm37/lib/DebugInfo/**.cpp",
          --  root .. "extern/llvm37/lib/AsmParser/**.cpp",
           -- root .. "extern/llvm37/lib/ExecutionEngine/**.cpp",
           -- root .. "extern/llvm37/lib/Fuzzer/**.cpp",
           -- root .. "extern/llvm37/lib/Target/**.cpp",
           -- root .. "extern/llvm37/tools/**.cpp",
           -- root .. "extern/llvm37/utils/**.cpp"
           -- }  
    --]]

    project "Boost"
    
        targetname "Boost"
        kind "StaticLib"        
	
        defines { "BOOST_ALL_NO_LIB",
		  "_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS" }        

	includedirs {
            root .. "extern/boost/include/" 
            }   
        
        files { 
            root .. "extern/boost/libs/*/src/**.cpp"
            } 

    project "StaticShaderCompiler"
 
        kind "ConsoleApp"
        flags "WinMain"
        --links "LLVM"
	links "Boost"

        warnings "Extra"
        
	defines { "BOOST_ALL_NO_LIB",
		  "_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS" } 

        includedirs {
            root .. "shaderGen/source/",
            root .. "shaderGen/include/",
            
            root .. "extern/llvm-37/include/",
     
            root .. "extern/boost/include/" 
            }   
        
        files { 
	    root .. "shaderGen/include/**.h",
            root .. "shaderGen/source/**.cpp",
	    root .. "shaderGen/source/**.h"
            }            
			
	configuration "gmake"
	    links "pthread"
            buildoptions "-std=c++11"
            
        configuration { "Debug", "x32" }
            defines "PREFIX=X32D_"
        
        configuration { "Debug", "x64" }
            defines "PREFIX=X64D_"
        
        configuration { "Release", "x32" }
            defines "PREFIX=X32R_"
        
        configuration { "Release", "x64" }
            defines "PREFIX=X64R_"
