# Notes

A simple note-keeping program for the command line.

Notes are stored in `~/.notes.txt`

## Usage:

`notes <flag> key note_string`

|Flag	|Meaning|Example|Explanation|
|-------|-------|-------|-----------|
|-c	|clear	|`notes -c`|Deletes **ALL** notes|
|-c	|clear	|`notes -c key`|Deletes **ALL** notes corresponding to `key`|
|-d	|delete	|`notes -d key`|Deletes the note corresponding to `key`|
|-h	|help	|`notes -h`|Displays the program usage and flags|
|-k	|keys	|`notes -k`|Prints a list of every key|
|-p	|print	|`notes -p`|Prints a list of every key, note, and date they were taken|
|-r	|recall	|`notes -r key`|Prints the note corresponding to `key`|
|-w	|write	|`notes -w key note_string`|Adds a note (`note_string`) accessible through `key`|

`notes -p key` is equivalent to `notes -r key`.

A `:` prompt is displayed when there are more than 10 notes to be displayed.
Press enter to continue displaying notes or type `q` then press enter to exit.
