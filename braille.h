#include <streamC.h>

/* Define to enable logging */
//#define LOG

#define BRAILLE_PORT      SERIAL_COM1
#define BRAILLE_IBUF_SIZE 512
#define BRAILLE_OBUF_SIZE 512

#define BRAILLE_TIMEOUT 30

#define BRAILLE_BUFSIZE 85

extern GeodeHandle brSerialDriver;
extern word G_brailleWidth, brStatus;
extern byte brCharset[256];
extern Boolean brCursorChange;

extern word brState;
  #define BR_IDLE                   0
  #define BR_ERROR                  255
extern Boolean brLinePending;

extern dword brPressedKeys;
extern dword brChordKeys;
  #define BRK_MASK(_bit)      (1L<<(_bit))
extern dword brPrevChord;

extern Boolean brTypewriter;

void LoadHTBraille(void);
void SpeakSentenceHTBraille(byte *buf);
void UnloadHTBraille(void);

void LoadALBraille(void);
void SpeakSentenceALBraille(byte *buf);
void UnloadALBraille(void);

void BrailleSetCursor(word pos, word pos2);

void LogPrintf(char *fmt, ...);
Boolean BrailleLoad(void);
void BrailleUnload(void);
word BrailleWriteByte(byte by);
word BrailleWriteString(byte *str, word len);
Boolean BrailleReadByte(byte *by);
void BrailleSendLine(byte *strPre, int nPre, byte *strPost, int nPost);
void BrailleToggleCursor(Boolean repeat);
Boolean BrailleUpdate(byte *buf);
