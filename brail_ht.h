// Handy Tech serial port format
#define HT_FORMAT    ((SERIAL_PARITY_ODD << SERIAL_FORMAT_PARITY_OFFSET) | \
                        (SERIAL_LENGTH_8 << SERIAL_FORMAT_LENGTH_OFFSET))
#define HT_BAUD      SERIAL_BAUD_19200


// Handy Tech braille codes/replies
#define HT_CODE_RESET         0xFF
#define HT_CODE_RESET_REPLY   0xFE
#define HT_CODE_LINE          0x01
#define HT_CODE_LINE_END      0x16
#define HT_CODE_LINE_ANSWER   0x7E

// Handy Tech key codes sent from the braille display
// Arranged so that casting the flag dword to byte yields the
// keys used for braille typing.
#define HT_CODE_RELEASE_FLAG  0x80    // set to indicate key release
#define HT_CODE_b1            0x03
#define HT_CODE_b2            0x07
#define HT_CODE_b3            0x0B
#define HT_CODE_b4            0x0F
#define HT_CODE_b5            0x13
#define HT_CODE_b6            0x17
#define HT_CODE_b7            0x1B
#define HT_CODE_b8            0x1F
#define HT_CODE_b9            0x12
#define HT_CODE_b10           0x02
#define HT_CODE_b11           0x11
#define HT_CODE_b12           0x01
#define HT_CODE_b13           0x09
#define HT_CODE_b14           0x0D
#define HT_CODE_0             0x05
#define HT_CODE_1             0x15
#define HT_CODE_2             0x19
#define HT_CODE_3             0x1D
#define HT_CODE_4             0x06
#define HT_CODE_5             0x0A
#define HT_CODE_6             0x0E
#define HT_CODE_7             0x16
#define HT_CODE_8             0x1A
#define HT_CODE_9             0x1E
#define HT_CODE_Left          0x04
#define HT_CODE_Right         0x08
#define HT_CODE_NLEFT         0x0C
#define HT_CODE_SPACE         0x10
#define HT_CODE_NRIGHT        0x14
#define HT_CODE_ROUTING1      0x20
#define HT_CODE_ROUTING80     0x6f

// Bit maks for "Bookworm"/"Buchwurm" device combined keycodes
#define HT_CODE_K1            0x01
#define HT_CODE_K2            0x02
#define HT_CODE_K3            0x04
#define HT_CODE_K4            0x08

// Flag bits for braille keys
#define BRK_b1            6
#define BRK_b2            2
#define BRK_b3            1 
#define BRK_b4            0
#define BRK_b5            3
#define BRK_b6            4
#define BRK_b7            5
#define BRK_b8            7

#define BRK_b9            8
#define BRK_b10           9
#define BRK_b11           10
#define BRK_b12           11
#define BRK_b13           12
#define BRK_b14           13
#define BRK_0             14
#define BRK_1             15
#define BRK_2             16
#define BRK_3             17
#define BRK_4             18
#define BRK_5             19
#define BRK_6             20
#define BRK_7             21
#define BRK_8             22
#define BRK_9             23
#define BRK_Left          24
#define BRK_Right         25
#define BRK_NLEFT         26
#define BRK_SPACE         27
#define BRK_NRIGHT        28
#define BRK_Routing       29

// Alternative names, corresponding to masks for braille dots
#define DOT7              BRK_MASK(BRK_b1)
#define DOT3              BRK_MASK(BRK_b2)
#define DOT2              BRK_MASK(BRK_b3)
#define DOT1              BRK_MASK(BRK_b4)
#define DOT4              BRK_MASK(BRK_b5)
#define DOT5              BRK_MASK(BRK_b6)
#define DOT6              BRK_MASK(BRK_b7)
#define DOT8              BRK_MASK(BRK_b8)
#define CHRD              BRK_MASK(BRK_SPACE)

const struct { 
  byte code;            byte flag;
} brKeyTable[] = {
  HT_CODE_b1          , BRK_b1          ,
  HT_CODE_b2          , BRK_b2          ,
  HT_CODE_b3          , BRK_b3          ,
  HT_CODE_b4          , BRK_b4          ,
  HT_CODE_b5          , BRK_b5          ,
  HT_CODE_b6          , BRK_b6          ,
  HT_CODE_b7          , BRK_b7          ,
  HT_CODE_b8          , BRK_b8          ,
  HT_CODE_b9          , BRK_b9          ,
  HT_CODE_b10         , BRK_b10         ,
  HT_CODE_b11         , BRK_b11         ,
  HT_CODE_b12         , BRK_b12         ,
  HT_CODE_b13         , BRK_b13         ,
  HT_CODE_b14         , BRK_b14         ,
  HT_CODE_0           , BRK_0           ,
  HT_CODE_1           , BRK_1           ,
  HT_CODE_2           , BRK_2           ,
  HT_CODE_3           , BRK_3           ,
  HT_CODE_4           , BRK_4           ,
  HT_CODE_5           , BRK_5           ,
  HT_CODE_6           , BRK_6           ,
  HT_CODE_7           , BRK_7           ,
  HT_CODE_8           , BRK_8           ,
  HT_CODE_9           , BRK_9           ,
  HT_CODE_Left        , BRK_Left        ,
  HT_CODE_Right       , BRK_Right       ,
  HT_CODE_NLEFT       , BRK_NLEFT       ,
  HT_CODE_SPACE       , BRK_SPACE       ,
  HT_CODE_NRIGHT      , BRK_NRIGHT      ,
};

const struct {
  byte code;                              byte key;
} brBookwormMap[] = {
  HT_CODE_K1                            , BRK_Left,
  HT_CODE_K2                            , BRK_b1,
  HT_CODE_K3                            , BRK_Routing,
  HT_CODE_K4                            , BRK_Right,
  HT_CODE_K1 | HT_CODE_K2               , BRK_b2,
  HT_CODE_K2 | HT_CODE_K3               , BRK_b4,
  HT_CODE_K1 | HT_CODE_K4               , BRK_b6,
  HT_CODE_K2 | HT_CODE_K4               , BRK_b5,
  HT_CODE_K1 | HT_CODE_K2 | HT_CODE_K4  , BRK_b7,
};
