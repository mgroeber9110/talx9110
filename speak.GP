name speak.app

longname "TALX 9110"

tokenchars "TALX"
tokenid 16424

type    appl, process, single
class   SpeakProcessClass
appobj  SpeakApp

export  SpeakApplicationClass

library geos
library	ui
library ansic
library text
library streamc

library eci
library foam
library vrecui
library security
library respondr

heapspace 128k
stack 4096

resource APPRESOURCE object
resource INTERFACE object
resource SYNTHSETTINGS object
resource DIALOGS object
resource ASM_FIXED code read-only shared fixed
