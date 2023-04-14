set_project("Lithium")

set_version("0.1.0")

add_rules("mode.debug", "mode.release")

target("lithium-logger")
    set_kind("static")
    add_files("Logger/src/*.cpp")

-- target("lithium-layout")
--     set_kind("static")
--     add_files("Layout/src/*.cpp")

