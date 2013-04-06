Assignment for Object-Oriented Programming and Data Structures
==============================================================

This is an assignment I did for a class called "Object-Oriented
Programming and Data Structures" at the university where I'm studying.

The assignment consists of two parts, one for Object-Oriented Programming
and the other part for Data Structures. The names I've used for each part
is "Cineman" and "SimQueue" respectively.

In each folder is each part of the assignment. Contained in the folder
are the assignment's source code and two files, "make.sh" and "make.bat",
used for compiling the program on Linux and Windows respectively. The scripts
will compile the program, then run it if the compilation is successful.
GNU G++ is required to be in your PATH.

The code is licensed under the New BSD License, which can be refered to in the
LICENSE file.

Cineman
-------
Cineman is built as a simple ticketing and member management system for a cinema.
It is meant as an application of object-oriented programming.
People can register as two different kinds of members, each with it's own discount
and freebies. Tickets can then be purchased as a member, or as a non-member.
Returning change is supported, and all transactions are logged. Transaction and
member display can be displayed as a table in the terminal. All data is stored
in a database file for future use.

SimQueue
--------
SimQueue is built as a simple queue simulator. It is meant as an application of
data structures, notably the queue. There are two queues in the simulation
and people can either be added to back of the queue, or be removed from the front to
be served at a counter. The people who have been served by either counter is also
kept track of. Commands entered can also be chained.