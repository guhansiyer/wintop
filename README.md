# wintop

`wintop` is a light-weight, terminal-based thread and process inspector for Windows systems, inspired by similar tools on Linux such as `top` and `ps`.

Currently only a few options are avaiable, such as basic process inspection and real-time diagnostics. I'm currently working on adding more information such as thread addresses and execution state.

## Usage

Available options can be obtained by running `wintop -h` or `wintop --help`:

```
wintop - Windows Thread and Process Inspector

Usage: wintop [options]
  -p, --pid <pid>       Filter threads by process ID
  -r, --refresh <sec>   Set refresh interval in seconds
  -s, --summary         Show summary only
  -h, --help            Show this help message
```

## Building `wintop`

To build wintop from source, you will need:
* CMake
* Visual Studio 2022, with Microsoft Visual C++ (MSVC) installed



Clone the `wintop` repository with your preferred method and open `Developer Command Prompt for Visual Studio 2022`. Ensure you are in the `wintop` directory and enter the following commands:
* `mkdir build && cd build`
* `cmake .. -G "NMake Makefiles"`
* `nmake`

This will create a `wintop` executable in the `/build`/ directory, from which the tool can be used.