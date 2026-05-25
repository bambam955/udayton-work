#!/usr/bin/bash

# Output header
echo "BUFFER OVERFLOW DETECTOR (by Bennett Moore)"

# First argument is the command to run
readonly PROG=$1

# Start with just one byte and go until the buffer size is detected...
COUNT=1
echo "Input size (bytes):"
while true; do
	# Clean status output using carriage return :)
	echo -en "\r${COUNT}\t"
	
	# Give PROG an input of size COUNT bytes
	res="$("$1" $(perl -e "print 'A'x$COUNT") >/dev/null)"
	# If the PROG run fails (nonzero exit code), we know we found the buffer size
	if [[ $? -ne 0 ]]; then
		# The buffer size is one less than the value that overflowed
		echo -e "\nBuffer size is $((COUNT - 1))"
		exit
	fi
	# Iterate like a for loop
	COUNT=$((COUNT + 1))
done
