@echo off
@call w:\coding\i6\setvars.bat

::REM Run Tests
cat find_the_way.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > find_the_way.actual
cat get_bananas.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > get_bananas.actual
cat distract_monkey.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > distract_monkey.actual
cat deadly_drop.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > deadly_drop.actual
cat catch_fish.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > catch_fish.actual
cat compass.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > compass.actual

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

echo [ Catch Fish --------------------------------------------------------] >> test_results.txt
diff --ignore-space-change catch_fish.expected catch_fish.actual >> test_results.txt

echo [ Compass -----------------------------------------------------------] >> test_results.txt
diff --ignore-space-change compass.expected compass.actual >> test_results.txt

::REM Output Results
cat test_results.txt