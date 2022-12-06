# Run a program in windows as a different user

## a bit of history
The reason for this little tool for me was that in the company I was working we had
use two different active directory users for our work. Most tasks could be done by the
main user account but all development tasks had to be executed as a different user.
So we had to start Visual Studio another dev tools as a different user every time.
Even though, it's possible to start a program as a different user by right-clicking
and selecting 'Run as different user', I kind of find the usability of this approach
unsatisfactory. The same is with the built-in command 'runas'.

Both the above options are far more sophisticated, sanitised and generally bullet
prove than this little project. I just wanted to be able to start a program without
any parameters but with a username and password in one command. That's what it
currently does.

This project needs cleanup and more documentation. Let's say it's on my todo list.

Handle with care and (more importantly) HAVE FUN!

Cheers! Oli