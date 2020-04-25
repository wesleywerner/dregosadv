@echo off
@call w:\coding\i6\setvars.bat
kdiff3 catch_fish.actual   catch_fish.expected   -o catch_fish.expected
kdiff3 compass.actual      compass.expected      -o compass.expected
kdiff3 garden.actual       garden.expected       -o garden.expected
kdiff3 monkey.actual       monkey.expected       -o monkey.expected
kdiff3 movement.actual     movement.expected     -o movement.expected