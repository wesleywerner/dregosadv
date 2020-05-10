@echo off
@call w:\coding\i6\setvars.bat

::REM Run Tests
cat find_the_way.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > find_the_way.actual
cat get_bananas.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > get_bananas.actual
cat distract_monkey.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > distract_monkey.actual
cat deadly_drop.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > deadly_drop.actual
cat find_the_alcove.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > find_the_alcove.actual
cat make_a_torch.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > make_a_torch.actual
cat pressure_plate_trap.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > pressure_plate_trap.actual
cat catch_fish.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > catch_fish.actual
cat compass.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > compass.actual
cat ending.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > ending.actual

::REM Diff Results
if exist test_results.txt del test_results.txt

echo [ Puzzle: Find The Way ----------------------------------------------] >> test_results.txt
diff --ignore-space-change find_the_way.expected find_the_way.actual >> test_results.txt

echo [ Puzzle: Get Bananas -----------------------------------------------] >> test_results.txt
diff --ignore-space-change get_bananas.expected get_bananas.actual >> test_results.txt

echo [ Puzzle: Distract The Monkey ---------------------------------------] >> test_results.txt
diff --ignore-space-change distract_monkey.expected distract_monkey.actual >> test_results.txt

echo [ Puzzle: Deadly Drop -----------------------------------------------] >> test_results.txt
diff --ignore-space-change deadly_drop.expected deadly_drop.actual >> test_results.txt

echo [ Puzzle: Find the Alcove -------------------------------------------] >> test_results.txt
diff --ignore-space-change find_the_alcove.expected find_the_alcove.actual >> test_results.txt

echo [ Puzzle: Make a Torch ----------------------------------------------] >> test_results.txt
diff --ignore-space-change make_a_torch.expected make_a_torch.actual >> test_results.txt

echo [ Puzzle: Pressure Plate Trap ---------------------------------------] >> test_results.txt
diff --ignore-space-change pressure_plate_trap.expected pressure_plate_trap.actual >> test_results.txt

echo [ Amusing: Catch Fish -----------------------------------------------] >> test_results.txt
diff --ignore-space-change catch_fish.expected catch_fish.actual >> test_results.txt

echo [ Device: Compass ---------------------------------------------------] >> test_results.txt
diff --ignore-space-change compass.expected compass.actual >> test_results.txt

echo [ Ending ------------------------------------------------------------] >> test_results.txt
diff --ignore-space-change ending.expected ending.actual >> test_results.txt

::REM Output Results
cat test_results.txt