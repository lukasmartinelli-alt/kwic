# KWIC - Keyword in Context

The KWIC index system accepts an ordered set of lines, each line is an ordered set of words, and each word is an ordered set of characters. Any line may be "circularly shifted" by repeatedly removing the first word and appending it at the end of the line. The KWIC index system outputs a listing of all circular shifts of all lines in alphabetical order. 


## Project Setup for Cevelop

1. Install [Cevelop](http://cevelop.com/)
2. Open the repository as a workspace
3. Import as existing projects into workspace

## Build Project

You can use Eclipse to build the project or the provided makefile.

```
make
```

## Run Tests

We use [CUTE](http://cute-test.com/) for our unit tests.
To run the tests you need to compile the tests and then simply run the
executable. This will output the test results to the console
and a XML file.

```
make test
```

## Example:

Input:

```
this is a test
this is another test
```

Result:

```
a test this is
another test this is
is a test this
is another test this
test this is a
test this is another
this is a test
this is another test
```
