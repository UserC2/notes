# Notes

A simple note-keeping program for the command line.

Notes are stored in `~/.notes.txt`

## Usage:

`notes <flag> key note_string`

|Flag	|Meaning|Example|Explanation|
|-------|-------|-------|-----------|
|-c	|clear	|`notes -c`|Delete **ALL** notes|
|-c	|clear	|`notes -c key`|Delete **ALL** notes corresponding to `key`|
|-d	|delete	|`notes -d key`|Delete the note(s) corresponding to `key`|
|-h	|help	|`notes -h`|Display the program usage and flags|
|-k	|keys	|`notes -k`|Print a list of every key|
|-p	|print	|`notes -p`|Print a list of every key, note, and the date each note was taken|
|-p	|print	|`notes -p key`|Equivalent to `notes -r key`|
|-r	|recall	|`notes -r key`|Print the note(s) corresponding to `key`|
|-s	|sort	|`notes -s date`|Sort notes from oldest to newest, and alphabetically when dates are the same|
|-s	|sort	|`notes -s key`|Sort notes alphabetically according to key, and from oldest to newest when keys are the same|
|-w	|write	|`notes -w key note_string`|Add a note (`note_string`) accessible through `key`|

A `:` prompt is displayed when there are more than 10 notes to be displayed.
Press enter to continue displaying notes or type `q` then press enter to exit.
