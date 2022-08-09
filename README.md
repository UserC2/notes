# Notes

A simple note-keeping program for the command line.

Notes are stored in `~/.notes.txt`

## Usage:

`notes <flag> key note_string`

|Flag	|Meaning|Example|Explanation|
|-------|-------|-------|-----------|
|-d	|delete	|`notes -d key`|Deletes the note corresponding to `key`|
|-h	|help	|`notes -h`|Displays the program usage and flags|
|-k	|keys	|`notes -k`|Prints a list of every key|
|-p	|print	|`notes -p`|Prints a list of every key, note, and date they were taken|
|-r	|recall	|`notes -r key`|Prints the note corresponding to `key`|
|-w	|write	|`notes -w key note_string`|Adds a note (`note_string`) accessible through `key`|
