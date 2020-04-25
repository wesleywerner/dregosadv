@echo off
@call w:\coding\i6\setvars.bat

::REM Run Tests
cat find_the_way.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > find_the_way.actual
cat catch_fish.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > catch_fish.actual
cat compass.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > compass.actual
cat garden.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > garden.actual
cat monkey.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > monkey.actual

::REM Diff Results
if exist test_results.txt del test_results.txt
echo [ Puzzle: Find The Way ----------------------------------------------] >> test_results.txt
diff --ignore-space-change find_the_way.expected find_the_way.actual >> test_results.txt
echo [ Catch Fish --------------------------------------------------------] >> test_results.txt
diff --ignore-space-change catch_fish.expected catch_fish.actual >> test_results.txt
echo [ Compass -----------------------------------------------------------] >> test_results.txt
diff --ignore-space-change compass.expected compass.actual >> test_results.txt
echo [ Garden ------------------------------------------------------------] >> test_results.txt
diff --ignore-space-change garden.expected garden.actual >> test_results.txt
echo [ Monkey ------------------------------------------------------------] >> test_results.txt
diff --ignore-space-change monkey.expected monkey.actual >> test_results.txt

::REM Output Results
cat test_results.txt