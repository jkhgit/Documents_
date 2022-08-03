addr2line
==================

convert addr to line.

[option]
f: print function name
e: target binary file

::

  $ addr2line -fe ./binary 0x8048707

addr2line [options] [file name] [address]

to know address, use "backtrace"

backtrace
==================

GNC C API, need "execinfo.h"

.. code-block:: C

  #include <execinfo.h>

  static int function {
      void *array[10];
      size_t size;
      char **strings;
      size_t i;

      ...

      size = backtrace(array, 10);
      printf("obtained %zd stack frames\n", size); //%zd: print "size_t integer".
      strings = backtrace_symbols(array, size);

      for (i = 0; i < size ; i++)
      printf(%d %s\n", i, string[i]);
      free(string);

      ...
  }

objdump
==================

reverse assembly C.::

  $ objdump -d ./binary
