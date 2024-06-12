include geos.def        ; standard macros
include resource.def    ; idata/udata, ProcCallFixedOrMovable etc.
include gstring.def

; public routines defined in this module
global MY_GRPARSEGSTRING:far

        SetGeosConvention               ; set calling convention

ASM_FIXED                segment resource

callback	fptr				; virtual pointer to callback routine

_MYPARSEGSTRING_callback proc far
        uses    bx,cx,dx,si,di,ds,es		; routine may destroy anything
        .enter
                push ds                         ; push ptr argument for routine
                push si
                push di                         ; push gstate argument
                segmov ds,ss                    ; load dgroup to ds
                movdw bxax,cs:callback          ; load vptr to callback routine
                call ProcCallFixedOrMovable     ; jump to routine (not fixed!)
						; return value in AX
        .leave
        ret
_MYPARSEGSTRING_callback endp
ASM_FIXED                ends

ASM_TEXT          segment resource
MY_GRPARSEGSTRING proc far _gstate:word, _gstring:word, _flags:word, _callback:fptr
        uses    bx,cx,dx,si,di
        .enter
		push ds
		mov dx,segment callback
		mov ds,dx
                movdw ds:callback,_callback,dx  ; store vptr to callback
		pop ds
                mov di,_gstate                  ; load arguments
                mov si,_gstring
                mov dx,_flags
                mov bx,segment _MYPARSEGSTRING_callback
                mov cx,offset _MYPARSEGSTRING_callback
                                                ; pointer to callback thunk
                call GrParseGString             ; do it!
        .leave
	ret
MY_GRPARSEGSTRING endp
ASM_TEXT          ends

        SetDefaultConvention            ;restore calling conventions

