awk
==================

awk in linux, it is symbolic linked gawk

refer to
::
	$ awk

Usage
::
	$ awk 'pattern' filename
	$ awk '{action}' filename
	$ awk 'pattern {action}' filename

Usage 2
::
	$ command | awk 'pattern'
	$ command | awk '{action}'
	$ command | awk 'pattern {action}'

how-to-execute
------------------

ex-text
::
	CentOS linux 100
	fedora linux 200
	ubuntu linux 300

command
::
	$ awk '{print $1, $3}' ex-text

output
::
	CentOS 100
	fedora 200
	ubuntu 300

*why print with space: "," in command "," is mapped OFS that is internal var*

internal-vars

- $0: CentOS linux 100
- $1: CentOS
- $2: linux
- $3: 100

at end of line, overwrite next line to $0

- $0: fedora linux 200
- $1: fedora
- $2: linux
- $3: 100

...

**Repeat this process until the end.**

functions
==================

match
------------------

search match pattern in record or field.
match operator *"~"*
::
	$ awk '$2 ~ /[Kk]ill/' awkfile

1. search pattern that "Kill" or "kill" in $2 field.
2. print matching line.

metaformat
------------------

with awk
::
	$ awk '/^star/{print $1, $2, $3}' file

1. find record line that is start with "star" in file.
2. print 1,2,3 fields in records

value compare
------------------

equal
::
	$ awk '$3 == 8683' awkfile	

over
::
	$ awk '$3 > 7000' awkfile

match
::
	$ awk '$2 ~ /force/' awkfile	
	$ awk '$2 !~ /force/' awkfile # not

if-oneline
::
	$ awk '{max=($1 > $2) ? $1 : $2; print max}' awkfile

math
::
	$ awk '$3 * $4 > 100' awkfile

logic-operator
::
	$ awk '$3 > $5 && $3 <= 100' awkfile
	$ awk '$3 == 100 || $5 > 100' awkfile
	$ awk '!($3 < 100 && $5 < 100)' awkfile

etc
------------------

- redirection

- args

- if/else

- loop

...

print
==================

**examples: file**

text **name_table**
::
	Hong gildong 3324 5/11/96 50354
	lim taeyang 5246 15/9/66 287650
	lee seonggye 7563 6/20/58 60000
	jung yakyong 8663 9/40/48 365000

using command
::
	$ awk '/a/{print "\t\thello? " $1, $2"."}' name_table	

result
::
	hello? lim taeyang.
	hello? jung yakyong.

**examples: command**

command **df**
::
	Filesystem     1K-blocks     Used Available Use% Mounted on
	udev             3902932        0   3902932   0% /dev
	tmpfs             787692     3584    784108   1% /run
	/dev/sda5       95788444 36975556  53904040  41% /
	tmpfs            3938452    35032   3903420   1% /dev/shm
	tmpfs               5120        4      5116   1% /run/lock
	tmpfs            3938452        0   3938452   0% /sys/fs/cgroup
	/dev/loop0           128      128         0 100% /snap/bare/5
	/dev/loop1         56960    56960         0 100% /snap/core18/2344
	/dev/loop2        224256   224256         0 100% /snap/gnome-3-34-1804/77
	/dev/loop5        224256   224256         0 100% /snap/gnome-3-34-1804/72
	/dev/loop4         56960    56960         0 100% /snap/core18/2409
	/dev/loop6        260224   260224         0 100% /snap/gnome-3-38-2004/106
	/dev/loop7         63488    63488         0 100% /snap/core20/1518
	/dev/loop8         83328    83328         0 100% /snap/gtk-common-themes/1534
	/dev/loop9         52224    52224         0 100% /snap/snap-store/547
	/dev/loop11        55552    55552         0 100% /snap/snap-store/558
	/dev/loop12        63488    63488         0 100% /snap/core20/1494
	/dev/loop13        45824    45824         0 100% /snap/snapd/15904
	/dev/loop14        48128    48128         0 100% /snap/snapd/16010
	/dev/sda1         523248    33420    489828   7% /boot/efi
	tmpfs             787688       52    787636   1% /run/user/1000
	/dev/loop15        93952    93952         0 100% /snap/gtk-common-themes/1535
	/dev/loop10       410496   410496         0 100% /snap/gnome-3-38-2004/112
	----$1----     ---$2---- ---$3---  ---$4--- -$5- ----------$6-----------

command **date**

"date" output
::
	Mon 11 Jul 2022 09:49:27 PM KST

using command
::
	$ date | awk '{print "Today is" $1 "day" "\n current-time: " $4}'

result
::
	Today is Monday
	current-time: 09:49:27

**examples: command 2**

command **df**
::
	Filesystem     1K-blocks     Used Available Use% Mounted on
	udev             3902932        0   3902932   0% /dev
	tmpfs             787692     3584    784108   1% /run
	/dev/sda5       95788444 36975556  53904040  41% /
	tmpfs            3938452    35032   3903420   1% /dev/shm
	tmpfs               5120        4      5116   1% /run/lock
	tmpfs            3938452        0   3938452   0% /sys/fs/cgroup
	/dev/loop0           128      128         0 100% /snap/bare/5
	/dev/loop1         56960    56960         0 100% /snap/core18/2344
	/dev/loop2        224256   224256         0 100% /snap/gnome-3-34-1804/77
	/dev/loop5        224256   224256         0 100% /snap/gnome-3-34-1804/72
	/dev/loop4         56960    56960         0 100% /snap/core18/2409
	/dev/loop6        260224   260224         0 100% /snap/gnome-3-38-2004/106
	/dev/loop7         63488    63488         0 100% /snap/core20/1518
	/dev/loop8         83328    83328         0 100% /snap/gtk-common-themes/1534
	/dev/loop9         52224    52224         0 100% /snap/snap-store/547
	/dev/loop11        55552    55552         0 100% /snap/snap-store/558
	/dev/loop12        63488    63488         0 100% /snap/core20/1494
	/dev/loop13        45824    45824         0 100% /snap/snapd/15904
	/dev/loop14        48128    48128         0 100% /snap/snapd/16010
	/dev/sda1         523248    33420    489828   7% /boot/efi
	tmpfs             787688       52    787636   1% /run/user/1000
	/dev/loop15        93952    93952         0 100% /snap/gtk-common-themes/1535
	/dev/loop10       410496   410496         0 100% /snap/gnome-3-38-2004/112
	----$1----     ---$2---- ---$3---  ---$4--- -$5- ----------$6-----------

vars
==================

built-in vars
------------------

I'm going to add it ...

normal vars
------------------

input value with **"="**

name="Tom": "name" var is string.

x++: "x" var is number, init 0 or NULL and increase ++. (x = x+1)

number=100: "number" var is number.

e.g.
::
	$ awk '$1 ~ /stone/ {sum=$3 + $5; print sum}' awkfile

e.g 2.
::
	$ awk 'BEGIN{x=1; y=x++; print x,y}'

- result: 2 1

e.g 3.
::
	$ awk 'BEGIN{x=1; y=++x; print x,y}'

- result: 2 2

BEGIN & END pattern
------------------

- BEGIN: before processing the input file line. You don't need an input file.

- END: Runs after all lines have been processed.

