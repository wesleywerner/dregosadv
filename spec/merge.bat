@echo off
@call ..\tools\setvars.bat

kdiff3 find_the_way.expected        find_the_way.actual     -o find_the_way.expected
kdiff3 get_bananas.expected         get_bananas.actual      -o get_bananas.expected
kdiff3 distract_monkey.expected     distract_monkey.actual  -o distract_monkey.expected
kdiff3 deadly_drop.expected         deadly_drop.actual      -o deadly_drop.expected
kdiff3 find_the_alcove.expected     find_the_alcove.actual  -o find_the_alcove.expected
kdiff3 make_a_torch.expected        make_a_torch.actual     -o make_a_torch.expected
kdiff3 catch_fish.expected          catch_fish.actual       -o catch_fish.expected
kdiff3 catch_chicken.expected       catch_chicken.actual    -o catch_chicken.expected
kdiff3 bribing_the_carver.expected  bribing_the_carver.actual -o bribing_the_carver.expected
kdiff3 compass.expected             compass.actual          -o compass.expected
kdiff3 ending.expected              ending.actual           -o ending.expected
kdiff3 pressure_plate_trap.expected pressure_plate_trap.actual -o pressure_plate_trap.expected
kdiff3 weather.expected             weather.actual          -o weather.expected
kdiff3 help.expected                help.actual             -o help.expected
kdiff3 hints.expected               hints.actual            -o hints.expected
kdiff3 torch_variation.expected     torch_variation.actual  -o torch_variation.expected
kdiff3 xyzzy.expected               xyzzy.actual            -o xyzzy.expected