#!/bin/bash

echo -e 'test_01 script was run\n' 

#Run test application with ORDINARY
./testapp.exe ./tests/logtest_01.txt ORDINARY < ./tests/test_01.txt

echo -e "Сheck messages in ./tests/logtest_01.txt \n"

if [[ !$(grep -c "incoorect: 4th message" ./tests/logtest_01.txt) &&
       $(grep -c "ORDINARY:  1st message" ./tests/logtest_01.txt) &&
       $(grep -c "IMPORTANT: 2nd message" ./tests/logtest_01.txt) &&
       $(grep -c "EMERGANCY: 3rd message" ./tests/logtest_01.txt) &&
       $(grep -c "ORDINARY: no importance text message" ./tests/logtest_01.txt) ]]
then echo -e "Test result: \033[32m passed\033[0m\n"
else echo -e "Test result: \033[31m not passed\033[0m\n"
fi

exit 0
