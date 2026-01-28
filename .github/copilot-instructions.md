# MiniRT AI Coding Instructions

## Project Overview
**miniRT** is a ray tracing renderer written in C that parses scene description files (`.rt` format) to generate rendered output. The project is in early development with a foundation for parsing scene elements (ambient lighting, camera, lights, spheres, planes, cylinders).

## Architecture & Data Flow

### Core Components
- **Main Entry** ([src/main.c](src/main.c)): Initializes `t_scene` struct and triggers parsing
- **Parsing Pipeline** ([src/parsing/parsing.c](src/parsing/parsing.c)): Reads `.rt` files line-by-line, dispatches to element-specific parsers
- **Utilities** ([src/utils/string_utils.c](src/utils/string_utils.c)): Custom string helpers (`ft_strlen`, `ft_strcmp`)
- **File I/O** ([get_next_line/](get_next_line/)): Custom GNL implementation for line-by-line file reading

### Data Flow
1. `main()` validates arguments and creates empty `t_scene` struct
2. `parsing()` validates `.rt` extension, opens file, reads lines via `get_next_line()`
3. `parse_line()` dispatches to element parsers based on first character(s):
   - `A` → ambient lighting
   - `C` → camera  
   - `L` → light
   - `sp` → sphere
   - (plane, cylinder parsers planned but unimplemented)

### Key Struct
```c
typedef struct s_scene
{
	// TODO: populated by parsing functions
}	t_scene;
```
Currently empty—parsers need to populate this with parsed data.

## Build System

**Build commands:**
- `make` / `make all`: Compile to binary `miniRT`
- `make clean`: Remove object files
- `make fclean`: Remove objects and binary
- `make re`: Full rebuild

**Build details:**
- Compiler: `cc` with flags `-Wall -Wextra -Werror -MMD -MP`
- Include paths: `get_next_line/include`, `src`
- Dependency tracking enabled (`-MMD -MP` generates `.d` files in `obj/`)
- Object structure mirrors source: `obj/src/parsing/parsing.o` for `src/parsing/parsing.c`

## Code Patterns & Conventions

### Error Handling
- Use `parse_error(int code, string message)` for fatal validation failures
- Pass `EXIT_FAILURE` as code, descriptive string as message
- Example: `parse_error(EXIT_FAILURE, "file must end with .rt")`

### File Validation
- Always check file extension with custom validator (see `file_end_with_rt()`)
- Open file, check `fd < 0` for errors
- Use `get_next_line()` for reading (handles buffers internally)

### String Utilities
- **Custom implementations only**—no standard libc string functions
- Available: `ft_strlen()`, `ft_strcmp()` (returns difference like `strcmp`)
- Add new helpers to `src/utils/string_utils.c` (import in `minirt.h`)

### Parsing Pattern
- Single-character dispatch (or two-char for "sp")
- Each element type has dedicated `parse_*()` function (declared in headers, stubs need implementation)
- Functions receive raw line string, must extract and validate values

### Type System
- Use `typedef struct s_name` pattern for all structures
- No STL/advanced data structures—build custom linked lists or arrays if needed

## Development Workflow

1. **Add features**: Implement `parse_*()` functions in [src/parsing/parsing.c](src/parsing/parsing.c)
2. **Test parsing**: Use `maps/first.rt` as reference scene format
3. **Build & validate**: `make clean && make`—catches compilation errors immediately
4. **Dependency cleanup**: `make fclean` before committing if `.d` files changed

## File Organization
```
src/
  main.c              # Entry point
  minirt.h            # Central header, all struct defs & declarations
  parsing/parsing.c   # Line dispatcher, element parsers
  utils/string_utils.c # Custom string functions
maps/
  first.rt            # Example scene (A, C elements)
get_next_line/        # Custom file reading library
```

## Important Notes
- **No external libraries**: All utilities custom-implemented or from GNL
- **Early-stage**: Parser stubs exist but most `parse_*()` functions are unimplemented
- **Return values**: Main currently returns no value—add proper return logic when complete
- **Memory management**: Ensure all `get_next_line()` allocations are freed (check GNL bonus usage)
