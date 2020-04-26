@echo off
@call w:\coding\i6\setvars.bat
kdiff3 find_the_way.expected        find_the_way.actual     -o find_the_way.expected
kdiff3 get_bananas.expected         get_bananas.actual      -o get_bananas.expected
kdiff3 distract_monkey.expected     distract_monkey.actual  -o distract_monkey.expected
kdiff3 deadly_drop.expected         deadly_drop.actual      -o deadly_drop.expected
kdiff3 find_the_alcove.expected     find_the_alcove.actual  -o find_the_alcove.expected
kdiff3 catch_fish.expected          catch_fish.actual       -o catch_fish.expected
kdiff3 compass.expected             compass.actual          -o compass.expected
