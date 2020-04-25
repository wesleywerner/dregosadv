@echo off
@call w:\coding\i6\setvars.bat
kdiff3 find_the_way.expected find_the_way.actual -o find_the_way.expected
kdiff3 catch_fish.expected   catch_fish.actual   -o catch_fish.expected
kdiff3 compass.expected      compass.actual      -o compass.expected
kdiff3 garden.expected       garden.actual       -o garden.expected
kdiff3 monkey.expected       monkey.actual       -o monkey.expected
