vim
==================

*vim setting based on "https://github.com/jkhgit/workspace"*

**vi modes**

1. input
::
  a
  i
  o

- a: input at next of cursor
- i: input at cursor
- o: input at next line from cursor

2. visual
::
  v
  ctrl + v # vertical

**vi utils**

1. cursor
::
  hjkl

- h: left
- j: down 
- k: up
- l: right

2. copy & paste
::
  y
  p

- y: copy
- p: paste

3. vi commands
::
  :bd
  :q
  :%s
  :w

- bd: exit vi's tab
- q: exit
- %s: change word *:%s/{before}/{after}/g*
- w: save

4. vi hot keys
::
  ctrl + w + f
  ctrl + w + g + f

- ctrl + w + f: open header file 1 
- ctrl + w + g + f: open header file 2
