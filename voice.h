/*
 * Header for 1.0 voice files
 */
typedef struct {
  unsigned long ndir;                   // Number of directory entries  
} VoiceHeader;

/*
 * Additional header for post-1.0 voice files
 */
#define VOICE_DESC_BUFSIZE 32
#define VOICE_MAGIC 0xABCD1234          // Magic ndir value to indicate version  

typedef struct {
  unsigned char langugage[2];           // Language code
  unsigned char desc[VOICE_DESC_BUFSIZE];
  unsigned long ndir;                   // Number of directory entries
  unsigned short flags;                 // Attributes for normalization
    #define VOICE_FLAG_CASE 0x01        //   if set, upcase first letter
    #define VOICE_FLAG_UMALUT 0x02      //   if set, normalize umlauts
  unsigned dealerCode;                  // Second half of key
    #define DEALER_CODE_MASK 0x209FAD08 //   constant XOR mask
} VoiceHeaderNew;

#define isword(c) (isalpha((byte)(c)) || isdigit((byte)(c)) || (c)=='\'')
#define talx_isupper(c) (isupper((byte)(c)) && c!=0xA7)
