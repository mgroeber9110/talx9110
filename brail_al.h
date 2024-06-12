// ALVA serial port format
#define AL_FORMAT    ((SERIAL_PARITY_NONE << SERIAL_FORMAT_PARITY_OFFSET) | \
                        (SERIAL_LENGTH_8 << SERIAL_FORMAT_LENGTH_OFFSET))
#define AL_BAUD      SERIAL_BAUD_9600


#define AL_CODE_GET_ID      {0x1b, 'F','U','N', 0x06, 0x0d}
#define AL_REPLY_ID         {0x1b, 'I','D','='}
#define AL_REPLY_START      0x1b
#define AL_REPLY_END        0x0d

#define AL_CODE_GET_CONFIG  {0x1b, 'F','U','N', 0x07, 0x0d}

/* Components of code for sending a braille pattern */
#define AL_CODE_WRITE1      0x1b
#define AL_CODE_WRITE2      'B'
#define AL_CODE_WRITE_POST  0x0d

/* Group codes. These are followed by a make/break code */
#define AL_GROUP_STANDARD   0x71
#define AL_GROUP_TC         0x72
#define AL_GROUP_DTC        0x75
#define AL_GROUP_SATELLITE  0x77
#define AL_GROUP_REP_START  0x7F
#define AL_GROUP_REP_DATA   0x7E
#define AL_IS_GROUP(c)      (((c) & 0xF0)==0x70)

#define AL_RELEASE_FLAG     0x80

#define AL_STD_PROG1        0x00
#define AL_STD_HOME1        0x01
#define AL_STD_CUR1         0x02
#define AL_STD_UP           0x03
#define AL_STD_LEFT         0x04
#define AL_STD_RIGHT        0x05
#define AL_STD_DOWN         0x06
#define AL_STD_CUR2         0x07
#define AL_STD_HOME2        0x08
#define AL_STD_PROG2        0x09

#define AL_SAT_BTAB         0x00
#define AL_SAT_LEFTPAD      0x02
#define AL_SAT_UPPAD        0x01
#define AL_SAT_DOWNPAD      0x03
#define AL_SAT_RIGHTPAD     0x04
#define AL_SAT_FTAB         0x05
#define AL_SAT_BEAR         0x20
#define AL_SAT_WESTPAD      0x22
#define AL_SAT_NORTHPAD     0x21
#define AL_SAT_SOUTHPAD     0x23
#define AL_SAT_EASTPAD      0x24
#define AL_SAT_FEAR         0x25

#define BRK_PROG1           1
#define BRK_HOME1           2
#define BRK_CUR1            3
#define BRK_UP              4
#define BRK_LEFT            5
#define BRK_RIGHT           6
#define BRK_DOWN            7
#define BRK_CUR2            8
#define BRK_HOME2           9
#define BRK_PROG2           10
#define BRK_BTAB            11
#define BRK_LEFTPAD         12
#define BRK_UPPAD           13
#define BRK_DOWNPAD         14
#define BRK_RIGHTPAD        15
#define BRK_FTAB            16
#define BRK_BEAR            17
#define BRK_WESTPAD         18
#define BRK_NORTHPAD        19
#define BRK_SOUTHPAD        20
#define BRK_EASTPAD         21
#define BRK_FEAR            22

const struct { 
  byte group;               byte code;        byte flag;
} brALKeyTable[] = {
  AL_GROUP_STANDARD       , AL_STD_PROG1    , BRK_PROG1,
  AL_GROUP_STANDARD       , AL_STD_HOME1    , BRK_HOME1,
  AL_GROUP_STANDARD       , AL_STD_CUR1     , BRK_CUR1,
  AL_GROUP_STANDARD       , AL_STD_UP       , BRK_UP,
  AL_GROUP_STANDARD       , AL_STD_LEFT     , BRK_LEFT,
  AL_GROUP_STANDARD       , AL_STD_RIGHT    , BRK_RIGHT,
  AL_GROUP_STANDARD       , AL_STD_DOWN     , BRK_DOWN,
  AL_GROUP_STANDARD       , AL_STD_CUR2     , BRK_CUR2,
  AL_GROUP_STANDARD       , AL_STD_HOME2    , BRK_HOME2,
  AL_GROUP_STANDARD       , AL_STD_PROG2    , BRK_PROG2,

  AL_GROUP_SATELLITE      , AL_SAT_BTAB     , BRK_BTAB,
  AL_GROUP_SATELLITE      , AL_SAT_LEFTPAD  , BRK_LEFTPAD,
  AL_GROUP_SATELLITE      , AL_SAT_UPPAD    , BRK_UPPAD,
  AL_GROUP_SATELLITE      , AL_SAT_DOWNPAD  , BRK_DOWNPAD,
  AL_GROUP_SATELLITE      , AL_SAT_RIGHTPAD , BRK_RIGHTPAD,
  AL_GROUP_SATELLITE      , AL_SAT_FTAB     , BRK_FTAB,
  AL_GROUP_SATELLITE      , AL_SAT_BEAR     , BRK_BEAR,
  AL_GROUP_SATELLITE      , AL_SAT_WESTPAD  , BRK_WESTPAD,
  AL_GROUP_SATELLITE      , AL_SAT_NORTHPAD , BRK_NORTHPAD,
  AL_GROUP_SATELLITE      , AL_SAT_EASTPAD  , BRK_EASTPAD,
  AL_GROUP_SATELLITE      , AL_SAT_SOUTHPAD , BRK_SOUTHPAD,
  AL_GROUP_SATELLITE      , AL_SAT_FEAR     , BRK_FEAR,
};
