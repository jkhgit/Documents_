/etc/profile (global vars, init system)
==================

.. code-block:: bash

  ...

  for i in /etc/profile.d/*.sh; do
    if [ -r $i ]; then
    . $i
    fi
  done

~/.bashrc (local vars)

~/.bash_logout (config logout from shell)

source vs .
==================

::
  $ source

- current shell, Non-volatile

::
  $ .

- volatile
