# Notes

A simple note-keeping program for the command line.

## Usage:

`notes <flag> key note_string`

Flags:
`-d	delete	notes -d key`
Deletes the note corresponding to 'key'
`-h	help	notes -h`
Displays the program usage and flags (equivalent to running the program without parameters)
`-k	keys	notes -k`
Prints a list of every key to the screen
`-p	print	notes -p`
Prints a list of every key, note, and the date they were added to the screen
`-w	write	notes -w key note_string`
Adds a note (`note_string`) accessible through `key`
