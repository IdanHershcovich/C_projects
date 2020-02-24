This program is made to search for every file with a .txt extension in the same directory. 
The program needs to be supplied with 3 arguments in the comamand line in order to work.
The first argument is the "find" parameter, second one is "replace" param and third one is "prefix parameter"
The program will output any changes it does, or if it didn't have the need to make changes.

SAMPLE RUN:

./hw3 really replace Prefix
Program initiated

 No instances of 'really' or 'Prefix' within file: 'test4.txt'. Nothing to do

 No instances of 'really' or 'Prefix' within file: 'test1.txt'. Nothing to do

 No instances of 'really' or 'Prefix' within file: 'test2.txt'. Nothing to do

 No instances of 'really' within file: 'test3.txt'. Looking for Prefix

Successfully prepended all occurrences of 'Prefix' with 'really' in file 'test3.txt'.