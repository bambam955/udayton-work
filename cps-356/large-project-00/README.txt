# NOTES ON ZIP FILE:
I cannot open the zip file on Windows. I don't know if this is from the assembly files or something...?
Maybe you do this already, but open the zip in Linux to see my changes.

# INSTRUCTIONS FOR TEsTING DEVICE DRIVERS:
I have implemented a "testdrivers" application for testing each of the 3 drivers.
Running this command in xv6 will show output proving all 3 of the drivers are working.

Doing additional tests is somewhat difficult because we don't have the "head" command
to limit how much data is read, but it can still work.

To test /dev/null, run "echo <any-random-string> > /dev/null" and...nothing happens!! Perfect.

To test /dev/zero, run "cat /dev/zero" and watch the console go crazy with nothing characters.

To test /dev/ticks, run "cat /dev/ticks" and watch the console start spamming tick counts.

These spamming behaviors happen because we have no concept of returning an EOF, so the cat()
program will just keep reading for eternity.
