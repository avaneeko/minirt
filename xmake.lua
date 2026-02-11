set_project("miniRT")
set_version("0.0.0")

-- Common modes: xmake f -m debug|release
add_rules("mode.debug", "mode.release")

-- Put the final binary in the repo root (like your Makefile)
set_targetdir("$(projectdir)")

-- Optional: keep objects out of the way
set_objectdir("build/.objs")

-- Configurable path to your MLX checkout
option("mlxdir")
    set_default("minilibx-linux")
    set_showmenu(true)
    set_description("Path to minilibx-linux directory")
option_end()

-- A helper "target" that ensures libmlx.a exists in project root
target("mlx")
    set_kind("phony")

    on_build(function ()
        local mlxdir = get_config("mlxdir") or "minilibx-linux"

        if not os.isdir(mlxdir) then
            print("minilibx not found, cloning into: %s", mlxdir)
            os.exec("git clone --recursive https://github.com/42paris/minilibx-linux %s", mlxdir)
        end

        -- Build MLX using its own Makefile
        os.exec("make -C %s", mlxdir)

        -- Copy resulting lib to project root as ./libmlx.a (same as your Makefile)
        local libsrc = path.join(mlxdir, "libmlx.a")
        local libdst = path.join(os.projectdir(), "libmlx.a")
        if not os.isfile(libsrc) then
            raise("Expected %s but it wasn't produced by minilibx build.", libsrc)
        end
        os.cp(libsrc, libdst)
    end)

    on_clean(function ()
        local mlxdir = get_config("mlxdir") or "minilibx-linux"
        if os.isdir(mlxdir) then
            os.exec("$(make) -C %s clean", mlxdir)
        end
        os.tryrm(path.join(os.projectdir(), "libmlx.a"))
    end)

target("miniRT")
    set_kind("binary")
    add_deps("mlx")

    set_languages("c11")
    set_warnings("all", "extra")

    add_files("src/*.c")

    -- Includes match: -Isrc -Iminilibx-linux
    on_load(function (t)
        local mlxdir = get_config("mlxdir") or "minilibx-linux"
        t:add("includedirs", "src", mlxdir)

        -- Link the produced static lib explicitly (no -L./ -lmlx guessing)
		-- Replace the linkfiles approach with -L + -l
		t:add("linkdirs", os.projectdir())
		t:add("links", "mlx")

        -- Optional: honor your Makefile's env extensions (CF/LDF) if you used them
        local cf  = os.getenv("CF")
        local ldf = os.getenv("LDF")
        if cf and #cf > 0 then
            t:add("cxflags", table.unpack(os.argv(cf)))
        end
        if ldf and #ldf > 0 then
            t:add("ldflags", table.unpack(os.argv(ldf)))
        end
    end)

    -- Linux MLX deps (same as your LDFLAGS)
    if is_plat("linux") then
        add_syslinks("Xext", "X11", "m")
    end
