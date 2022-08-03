File system
==================

::
  +------------------------+--------------------------------------------------------------------------------+
  | directory              | info                                                                           |
  +========================+================================================================================+
  | /                      | start of file system, root directory.                                          |
  +------------------------+--------------------------------------------------------------------------------+
  | /boot                  | linux kernel, bootloader. kernel: vmlinuz-*                                    |
  +------------------------+--------------------------------------------------------------------------------+
  | /etc                   | system environment setting files. almost text files.                           |
  |                        |                                                                                |
  |                        | /etc/passwd: info of user.                                                     |
  |                        |                                                                                |
  |                        | /etc/shadow: password of user. (encrypted)                                     |
  |                        |                                                                                |
  |                        | /etc/fstab: file system table.                                                 |
  |                        |                                                                                |
  |                        | - save mounting device table at booting.                                       |
  |                        |                                                                                |
  |                        | /etc/host: save network host and ip address.                                   |
  |                        |                                                                                |
  |                        | /etc/init.d: system service scripts. at booting.                               |
  |                        |                                                                                |
  |                        | /etc/resolve.conf: save name server when connect system to outside.            |
  +------------------------+--------------------------------------------------------------------------------+
  | /bin, /usr/bin         | save executable programs.                                                      |
  |                        |                                                                                |
  |                        | /bin: basic executable programs.                                               |
  |                        |                                                                                |
  |                        | /usr/bin: executable programs of user.                                         |
  +------------------------+--------------------------------------------------------------------------------+
  | /sbin, /usr/sbin       | /sbin: programs for system manager. (alomost for root)                         |
  +------------------------+--------------------------------------------------------------------------------+
  | /usr                   | files for support user applications.                                           |
  |                        |                                                                                |
  |                        | /usr/share/X11: X Windows support.                                             |
  |                        |                                                                                |
  |                        | /usr/share/dict: spelling check.                                               |
  |                        |                                                                                |
  |                        | /usr/share/doc: documents.                                                     |
  |                        |                                                                                |
  |                        | /usr/share/man: man page files.                                                |
  |                        |                                                                                |
  |                        | /usr/src: source files. (kernel source code package)                           |
  +------------------------+--------------------------------------------------------------------------------+
  | /usr/local             | install software or use files in local machine.                                |
  |                        |                                                                                |
  |                        | executable file path: /usr/local/bin                                           |
  +------------------------+--------------------------------------------------------------------------------+
  | /var                   | check difference during operate system.                                        |
  |                        |                                                                                |
  |                        | /var/log: log files. (system log)                                              |
  |                        |                                                                                |
  |                        | /var/spool: queue for mail message or print work.                              |
  |                        |                                                                                |
  |                        | - if i use "Sendmail MTA" mail messages are saved in /var/spool/mail           |
  +------------------------+--------------------------------------------------------------------------------+
  | /lib                   | shared libraries. (like dll files in Windows)                                  |
  +------------------------+--------------------------------------------------------------------------------+
  | /home                  | user's home directory.                                                         |
  +------------------------+--------------------------------------------------------------------------------+
  | /root                  | supoer user's home.                                                            |
  +------------------------+--------------------------------------------------------------------------------+
  | /tmp                   | save temporary files.                                                          |
  +------------------------+--------------------------------------------------------------------------------+
  | /dev                   | device files. read and write device in "/dev".                                 |
  +------------------------+--------------------------------------------------------------------------------+
  | /proc                  | don't include files. info of kernel                                            |
  |                        |                                                                                |
  |                        | e.g.                                                                           |
  |                        |                                                                                |
  |                        | $ cat /proc/cpuinfo                                                            |
  |                        |                                                                                |
  |                        | $ cat /proc/meminfo                                                            |
  +------------------------+--------------------------------------------------------------------------------+
  | /media, /mnt           | directory for mount point.                                                     |
  |                        |                                                                                |
  |                        | mount: connecting a device with a process to use it.                           |
  |                        |                                                                                |
  |                        | I can check mount list. $ mount                                                |
  +------------------------+--------------------------------------------------------------------------------+

