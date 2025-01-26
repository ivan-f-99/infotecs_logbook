#!/bin/bash

echo -e 'test_03 script was run\n' 

#Run test application with ORDINARY
./testapp.exe ./tests/logtest_03.txt ORDINARY < ./tests/test_03.txt

echo -e "Сheck messages in ./tests/logtest_03.txt \n"

if [[ $(grep -c "ORDINARY:  1 message" ./tests/logtest_03.txt) &&
      $(grep -c "IMPORTANT: 2 message" ./tests/logtest_03.txt) &&
      $(grep -c "EMERGANCY: 3 message" ./tests/logtest_03.txt) &&
      $(grep -c "ORDINARY:  4 message" ./tests/logtest_03.txt) &&
      $(grep -c "IMPORTANT: 5 message" ./tests/logtest_03.txt) &&
      $(grep -c "EMERGANCY: 6 message" ./tests/logtest_03.txt) &&
      $(grep -c "ORDINARY:  7 message" ./tests/logtest_03.txt) &&
      $(grep -c "IMPORTANT: 8 message" ./tests/logtest_03.txt) &&
      $(grep -c "EMERGANCY: 9 message" ./tests/logtest_03.txt) &&
      $(grep -c "ORDINARY:  10 message" ./tests/logtest_03.txt) &&
      $(grep -c "IMPORTANT: 11 message" ./tests/logtest_03.txt) &&
      $(grep -c "EMERGANCY: 12 message" ./tests/logtest_03.txt) ]]
then echo -e "Test result: \033[32m passed\033[0m\n"
else echo -e "Test result: \033[31m not passed\033[0m\n"
fi

exit 0
