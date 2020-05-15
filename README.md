# word_stemming_and_matching
A program that finds the common stem of two words and matches them. Uses common suffixes, prefixes and root words to identify the correct match.

Written when I was doing a summer job and my boss asked me to identify words with the same root in English textbooks. I decided to write a program for it and it worked.
Uses a hash table for performance. Finishes on text file with tens of thousands of words in reasonable time.

code is in /core
lanuage is the language processing part, used to identify word roots. The prefixes and suffixes are in /processeddata
wordGraph is the hash table structure used
wordData is a representation for the specific data my boss asked me to work on
