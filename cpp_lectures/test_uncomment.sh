#!/bin/bash

g++ --no-exceptions uncomment.cpp -o uncomment 

do_test() {
  sed -E 's/\/\/.*|(\/\*.*\*\/)//g' < test_input.c > expected_output.c

  ./uncomment < test_input.cpp > actual_output.c

  # Compare the actual output with the expected output
  diff expected_output.c actual_output.c

  # Exit script with an error code if the diff fails
  if [ $? -ne 0 ]; then
    echo "Error: Outputs differ!"
    exit 1
  fi
}

# cat > test_input.c <<EOF 
# This is a multi-line comment
# /* Another multi-line comment */
# Some code without comments
# EOF
# do_test

cat > test_input.c <<EOF 
This is a multi-line comment
/* Another multi-line comment */
Middle line
/* Another multi-line comment */
Some code without comments
EOF
do_test

rm -f test_input.c expected_output.c actual_output.c
echo "Test passed! Outputs are identical."

