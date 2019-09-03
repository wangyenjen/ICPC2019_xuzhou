General
-------
Don't push to master.

Add Makefile or build.ninja so your binaries can be built easily.
* With Makefile, use `make -j` to build everything,
  and `make clean` to delete built files
  (listed explicitly in Makefile).
* With build.ninja, use `ninja` to build everything,
  and `ninja -t clean` to delete built files.

Problem Description
-------------------
Use plain-text formats (e.g. Markdown or TeX) for description.txt.
Don't use pdf or (Microsoft) docx.

Aside from this,
there is no hard requirement on formats.
However, if you speak Tex or MathJax,
please typeset your numbers/variables/equations in such formats.

Validator
---------
Ensure your input conforms to the problem description.
You should use testlib.h rather than scanf.

Solution
--------
Describe your solution with comment.

Generators
----------
Use testlib.h rather than standard random generators in C++,
because they are not portable across implementations
