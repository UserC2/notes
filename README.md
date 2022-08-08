# Notes

A simple note-keeping program for the command line.

## Usage:

`notes <flag> key note_string`

|Flag	|Meaning|Example|Explanation|
|-------|-------|-------|-----------|
|-d	|delete	|`notes -d key`|Deletes the note corresponding to `key`|
|-h	|help	|`notes -h`|Displays the program usage and flags|
|-k	|keys	|`notes -k`|Prints a list of every key|
|-p	|print	|`notes -p`|Prints a list of every key, note, and date they were taken|
|-w	|write	|`notes -w key note_string`|Adds a note (`note_string`) accessible through `key`|
