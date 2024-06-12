typedef struct {
  KeyboardShortcut      MHL_keyboardShortcut;
  optr                  MHL_destination;
  word                  MHL_message;
} MacroHotkeyList;

void _pascal MacroInit(void);
void _pascal MacroDeinit(void);

void _pascal MacroSetHotkeys(MacroHotkeyList *hot, optr target, word msg);

void _pascal MacroSetAbsorbMode(Boolean enable);

word _pascal MacroGetInputProcess(void);

#define MAKE_SHORTCUT(cs, key) ((((cs) & 0x0f)<<8) | (key))
#define ANY_KS(sc) ((sc) & 0xfff)