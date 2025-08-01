> [!CAUTION]
> The project is still in development. Check [Issue 2](https://github.com/tanishqdaiya/dhanavraksha/issues/2) before proceeding.

dhanavraksha
============

This project keeps a log of all your transactions. It resembles a bank statement
where you can look into your withdrawls and deposits. I specifically designed
this to cater to my needs -- which was to have your my own finance tracker that
works on the CLI.

The work for this project is in progress. However, this project does not try to
guarantee any further development due to its nature as a throwaway hobby project
but the project is licensed by GNU General Public License v3.0, which makes it a
free software. Read more about licensing in the file named "LICENSE" on the repo.

Usage
=====

The project is still in development. Usage is bound to change. Obtain the
latest copy of the project on https://github.com/tanishqdaiya/dhanavraksha

-h, --help	Show help message
-v, --version	Show version information

view		View transaction records
entry		Enter a new transaction record

The view and entry commands reads from "data.expf" located in the same
directory, unless changed explicitly during compilation.

Internals
=========

Working procedure of the project is simple. It stores the data in a madeup
extension .expf, which expands to "expense file". This file contains plaintext
data with fixed tab-separated columns.

Every instance of this program, except for printing help or version, reads the
file and stores it into the program memory for futher operations. This is
achieved by the simplicity of the .expf file and the parser that easily converts
the format into tokens. Since the columns are fixed and the syntax is easy, it
makes it very easy to parse such formats.

We don't use any special datastructures to manage the data because of two
reasons:
1) The project is small and thus an array datastructure works fast enough.
2) This is a throwaway project. This isn't serious development. This project
is equivalent of a python developer writing a small script to solve their
problem -- It isn't meant to be elegant; just to solve problems.

Direction
=========

This project is currently focused (but not guaranteed) to include the following
features:
1) Export to CSV support (that is actually easier than actually parsing a CSV).
2) Better interface.
3) Ability to perform simple statistics
(for advanced statistics: export to csv -> excel -> do your magic there)
4) Support for grouping and searching.
5) Add a pager support.
