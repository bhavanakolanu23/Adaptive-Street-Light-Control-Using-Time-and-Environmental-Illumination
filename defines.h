// Macro to write an 8-bit value into a register starting from STARTBIT
#define WRITEBYTE(WORD,STARTBIT,BYTE) \
		WORD =((WORD &~(0XFF<<STARTBIT)) | \
		(BYTE<<STARTBIT))
		
// Macro to read a single bit from a register		
#define READBIT(WORD,BIT) ((WORD>>BIT)&1)

// Macro to set a particular bit in a register
#define SETBIT(WORD,BIT)  WORD = (WORD&~(1<<BIT) | (1<<BIT))

// Macro to write a 4-bit value (nibble) into a register
#define WRITENIBBLE(WORD,STARTBIT,BYTE) \
		WORD=(WORD &~(0XF<<STARTBIT)) | \
		(BYTE<<STARTBIT)
		
// Macro to read a 4-bit value (nibble) from a register		
#define READNIBBLE(WORD,BIT) ((WORD>>BIT)&0XF)
