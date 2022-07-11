sed
==================

*stream editor*

use standard input & output

Usage
::
	sed [OPTION] ... {script-only-if-no-other-script} [input-file] ...

options
------------------

refer to *sed --help*

using examples
------------------

e.g.
::
	sed -i 8d
	sed -i '/^$/d
	sed -i '1,/^$/d'
	sed -n '/jones/p'
	sed -i 's/Windows/Linux/'
	sed -i 's/Windows/Linux/g'
	sed -i '/ *$//'

e.g 2.
::
	sed -i '/generic/,/overlays/ s/overlays=.*$/overlays=\"rknpu\"/' /boot/config.ini
