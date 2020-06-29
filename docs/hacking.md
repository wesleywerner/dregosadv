# Compiler Environment

The compile the story you need the Inform compiler and standard library. Find these resources on this page: http://www.ifarchive.org/indexes/if-archiveXinfocomXcompilersXinform6.html

You need:

1. inform633_win32.zip from the "executables" index (or a newer version as available)
2. inform6lib-6.12.3.zip from the "library" index (or a newer version as available)

```
C:\I6
|
+---bin
|   (inform6.exe, library files)
+---contrib
    (other third-party extensions, currently empty)
```

* Extract all files (compiler executable, and library definitions) into "bin".
* Create an empty "contrib" sibling directory, where you can drop extensions in the future.

Next update the first line in `tools\setvars.bat` to match your `I6` path.

You are now ready to compile the story.

## Building the story

Run `tools\build_dbg.bat` to make a `Debug.z5` story file, and `tools\build_rel.bat` to make a release of `DrEgoAdv.z5`. These tools need to be run from within the `tools` directory. Running directly from your file manager also works.

## Unit Testing

There are a bunch of test specifications defined in the `spec` directory. To run these you need to set up some additional tooling. I will forgo the details and leave the download/extraction of these tools up to you.

You need a pipe redirector like cat, see [UnxUtils](https://sourceforge.net/projects/unxutils/) for this, which also includes the diff tool used in automated testing. Update the `UNX` parameter in `setvars.bat` to match where you extract these tools.

Dumb frotz is a special build that reads/writes stdin/stdout to automate transcript testing. Find dfrotz.zip [on this page](http://www.ifarchive.org/indexes/if-archiveXinfocomXinterpretersXfrotz.html). Update the `DFROTZ` parameter in `setvars.bat` to match where you extract this tool.

Run `spec\execute.bat`.

_Example output from a test run:_
```
[ Puzzle: Find The Way ----------------------------------------------] 
[ Puzzle: Get Bananas -----------------------------------------------] 
[ Puzzle: Distract The Monkey ---------------------------------------] 
[ Puzzle: Deadly Drop -----------------------------------------------] 
[ Puzzle: Find the Alcove -------------------------------------------] 
[ Puzzle: Make a Torch ----------------------------------------------] 
[ Puzzle: Pressure Plate Trap ---------------------------------------] 
[ Amusing: Catch Fish -----------------------------------------------] 
[ Device: Compass ---------------------------------------------------] 
[ Ending ------------------------------------------------------------] 
[ Weather -----------------------------------------------------------] 
```