::REM Run Tests
if exist catch_fish.actual del catch_fish.actual
cat catch_fish.spec | dfrotz -s 0 -p ..\DrEgoAdv.z5 > catch_fish.actual

::REM Diff Results
if exist test_results.txt del test_results.txt
echo [ Test catch_fish --------------------------------------------------------] >> test_results.txt
diff --ignore-space-change catch_fish.expected catch_fish.actual >> test_results.txt
