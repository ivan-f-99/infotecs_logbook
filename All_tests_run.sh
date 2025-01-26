#!/bin/bash

echo -e 'All test\n' 

#Run test application with ORDINARY
echo -e 'Run ./tests/test_01.sh\n'
bash ./tests/test_01.sh
echo -e 'Run ./tests/test_02.sh\n'
bash ./tests/test_02.sh
echo -e 'Run ./tests/test_03.sh\n'
bash ./tests/test_03.sh

rm -rf ./tests/logtest_01.txt
rm -rf ./tests/logtest_02.txt
rm -rf ./tests/logtest_03.txt
echo -e './tests/logtest_01.txt\n./tests/logtest_02.txt\n./tests/logtest_03.txt\nwas removed'

exit 0
