An efficient and encrypted transmission of text messages vi TCP/IP. Using a Huffman encoding system a text message is encrypted, letter by letter, 
by compacting the bits as much as possible into a 32-bit word. The 32-bit word is then transmitted via TCP/IP. A decoding system is developed that listens 
to the transmission, decodes the compact 32-bit word, and converts the bits back into text using the same Huffman encoding system. 
The encoder may hook up to a breadboard using a Raspberry Pi and drive the on/off or red/green LED lights to indicate the 0/1 bit received.
