add_rules("mode.debug", "mode.release")
set_warnings("all", "extra", "pedantic")
set_languages("c17", "c++23")
set_optimize("fastest")
add_rules("c++.unity_build")
set_exceptions("no-cxx")
set_runtimes("c++_static")

target("fmt")
    set_kind("binary")
    add_includedirs("include")
    add_files("src/*.cpp")
    set_policy("build.sanitizer.address", true)
    set_policy("build.sanitizer.undefined", true)