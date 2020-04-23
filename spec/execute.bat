@call w:\coding\i6\setvars.bat

::REM Run Tests
if exist catch_fish.actual del catch_fish.actual
cat catch_fish.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > catch_fish.actual
cat compass.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > compass.actual
cat movement.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > movement.actual
cat garden.spec c | dfrotz -s 0 -p ..\DrEgoAdv.z5 > garden.actual

::REM Diff Results
if exist test_results.txt del test_results.txt
echo [ Catch Fish --------------------------------------------------------] >> test_results.txt
diff --ignore-space-change catch_fish.expected catch_fish.actual >> test_results.txt
echo [ Compass -----------------------------------------------------------] >> test_results.txt
diff --ignore-space-change compass.expected compass.actual >> test_results.txt
echo [ Movement ----------------------------------------------------------] >> test_results.txt
diff --ignore-space-change movement.expected movement.actual >> test_results.txt
echo [ Garden ------------------------------------------------------------] >> test_results.txt
diff --ignore-space-change garden.expected garden.actual >> test_results.txt
