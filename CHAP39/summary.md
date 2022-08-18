
We can make hardlink and softlink by using command "in" 
ln <source> <hardlink_file>
-s option with command "ln" can make file softlink for a file

hardlink : same inode number
softlink : another inode number (reference)
(the number of softlink files does not counted to the number of links of source file of other hardlink files)
