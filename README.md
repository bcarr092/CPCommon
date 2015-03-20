Synopsis
========
This is the cross-platform common library (cpcommon) that allows for cross-platform (e.g. Windows, Mac OS X, iOS, and Android) development in a cross-architecture way. Currently supported architectures are x86, x64, ARM and ARM64. 

The goal of this library is to provide an abstraction to the platform specific system-level API calls and provide a unified interface that cross-platform code can be written on top of without making platform-specific system-level calls.

Code Example
============

Motivation
==========
This library was designed to make it easier to write cross-platform applications on both desktop and mobile platforms.

Installation
============
Cmake is required to build this project

API Reference
=============
Using Cmake Doxygen style documentation can be generate by executing the 'make doc' command.

Tests
=====
Full API tests are available on all platforms and are supported using Python and the unittest framework. To execute tests run the 'make test' command in the build directory.

Contributors
============
Brent Carrara (bcarr092@uottawa.ca)

License
=======
A licensing model needs to be established for this library.
