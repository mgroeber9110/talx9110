include stdapp.def              ; Standard Geos stuff
include timer.def               ; Timer, sleeping etc.
include thread.def
include Objects/inputC.def
include Internal/im.def         ; Input Manager internals

include macroeng.def

global _KeyPressed:far


                SetGeosConvention       ; set calling convention


idata           segment
  myMonitorData   Monitor
  myGeodeHandle   word                  ; Geode handle of Monitor application

  hotkeyList      fptr                  ; pointer to current hotkey list
  defaultHotkey	  MacroHotkeyList	; default target for key messages
  macroMode	  word MACRO_MODE_NORMAL
idata           ends


ASM_FIXED	segment resource

                assume  ds:dgroup       ; dgroup loaded on call of MyMonitor

;
;       MyMonitor
;
MyMonitor       proc    far
                cmp     di,MSG_META_KBD_CHAR
                je      key_event
nohot_event:	ret

		; "Pass" mode is only effective for one key
pass_event:	mov	ds:macroMode,MACRO_MODE_NORMAL
		jmp	nohot_event

key_event:      test    dl,mask CF_RELEASE
                jnz     nohot_event     ; not looking for releases of hotkey

		cmp	ds:macroMode,MACRO_MODE_PASS
		je	pass_event	; pass key through if requested

                push    ax,dx,di,es

                ; convert key to KeyboardShortcut format for convenient
                ; comparison with table entries

                mov     ax,cx           ; get character
                and     ax,0fffh        ; mask out upper 4 bits of charset

                test    dh,mask SS_LSHIFT or mask SS_RSHIFT
                jz      noshift         ; both shifts are equal
                or      ax,mask KS_SHIFT
noshift:
                test    dh,mask SS_LALT or mask SS_RALT
                jz      noalt           ; both alts are equal
                or      ax,mask KS_ALT
noalt:
                test    dh,mask SS_LCTRL or mask SS_RCTRL
                jz      noctrl          ; both ctrls are equal
                or      ax,mask KS_CTRL
noctrl:
		cmp	cx, ((CS_CONTROL shl 8) or VC_CAPSLOCK)
		jne	nocapslock
		test	bp, mask TS_CAPSLOCK
		jz	nocapslock
		; Mark Capslock enable by setting Ctrl/Alt flags
		or	ax,mask KS_CTRL or mask KS_ALT
nocapslock:

		cmp	ds:macroMode,MACRO_MODE_HOTKEY
		jne	nohotkey

		; Ignore Shift,Ctrl keys while waiting for hotkey, to allow
		; for combinations
		cmp	cx, ((CS_CONTROL shl 8) or VC_LCTRL)
		stc			; pass Ctrl keys on
		je	badhotkey_x
		cmp	cx, ((CS_CONTROL shl 8) or VC_RCTRL)
		stc			; pass Ctrl keys on
		je	badhotkey_x
		cmp	cx, ((CS_CONTROL shl 8) or VC_LSHIFT)
		stc			; pass Ctrl keys on
		je	badhotkey_x
		cmp	cx, ((CS_CONTROL shl 8) or VC_RSHIFT)
		stc			; pass Ctrl keys on
		je	badhotkey_x

                ;       Hotkey handling

		; Hotkey mode is only active for one key
		mov	ds:macroMode,MACRO_MODE_NORMAL

                test    {word}ds:hotkeyList+2,0ffffh
		clc
                jz      badhotkey	; no hotkey list: don't scan

                ; start scanning from start of hotkey list
                les     di,ds:hotkeyList
                jmp     start_scan

hotkey_scan:    cmp     es:[di].MHL_keyboardShortcut,ax
		clc			; don't pass on hotkeys to app
                je      hotkey_found

                ; advance to next entry in list
		add     di,size MacroHotkeyList

start_scan:     cmp     es:[di].MHL_keyboardShortcut,0
                jne     hotkey_scan     ; not reached end of list: continue
		clc			; don't pass on key anyway
badhotkey_x:	jmp	badhotkey

nohotkey:	
		; in "absorb" mode, send message, but don't pass on or
		; interpret hotkeys
		cmp	ds:macroMode,MACRO_MODE_ABSORB
		jne	noabsorb
		clc			; Do not pass on
		jmp	absorb_key

noabsorb:	cmp	ax,(((CS_UI_FUNCS and 15) shl 8) or UC_ZOOM)
		jne	no_zoom
		mov	ds:macroMode,MACRO_MODE_HOTKEY
		clc
		jmp	badhotkey
no_zoom:
		cmp	ax,(((CS_UI_FUNCS and 15) shl 8) or UC_BACKLIGHT)
		jne	no_backlight
		mov	ds:macroMode,MACRO_MODE_PASS
		clc
		jmp	badhotkey
no_backlight:
		stc			; don't kill non-hotkeys
absorb_key:	push	ds
		pop	es
		mov	di,offset defaultHotkey

                ; found hotkey: send message to destination
hotkey_found:	pushf
		push    bx,cx,si,bp
                mov     bp,ax		; bp: KeyboardShortcut
		call	TimerGetCount
		mov	cx,bx
		mov	dx,ax
                mov     ax,es:[di].MHL_message
                mov     si,{word}es:[di].MHL_destination
                mov     bx,{word}es:[di].MHL_destination+2
		mov     di,0            ; MessageFlags
                call    ObjMessage

		; For fast reactions...
                push    bp
		call	_KeyPressed
                add     sp,2
		
                pop     bx,cx,si,bp
		popf

badhotkey:	pop     ax,dx,di,es
		jc	nokill
		push	ax
		mov	ax, SST_KEY_CLICK
		call	UserStandardSound
		pop	ax
                xor     al,al           ; kill message
nokill:         ret

MyMonitor       endp

ASM_FIXED	ends


MACROENG_TEXT   segment resource

;------------------------------------------------------------------------------
; void _pascal MacroInit(void);
;------------------------------------------------------------------------------
                global MACROINIT:far

MACROINIT       proc    far
                uses    bp
                .enter

                call    GeodeGetProcessHandle
                mov     ds:myGeodeHandle,bx

                mov     al,ML_DRIVER+1
                mov     bx,offset myMonitorData
                mov     cx,segment MyMonitor
                mov     dx,offset MyMonitor
                call    ImAddMonitor

                .leave
                ret
MACROINIT       endp


;------------------------------------------------------------------------------
; void _pascal MacroDeinit(void);
;------------------------------------------------------------------------------
                global MACRODEINIT:far

MACRODEINIT     proc    far
                .enter

                mov     al,mask MF_REMOVE_IMMEDIATE
                mov     bx,offset myMonitorData
                call    ImRemoveMonitor

                .leave
                ret
MACRODEINIT     endp


;------------------------------------------------------------------------------
; void _pascal MacroSetHotkeys(MacroHotkeyList *hot, optr target, word msg);
;------------------------------------------------------------------------------
                global  MACROSETHOTKEYS:far

MACROSETHOTKEYS proc far _hot:fptr, _target:dword, _msg:word
                .enter

                ; store new hotkey list
                mov     ax,{word}_hot
                mov     dx,{word}_hot+2
                mov     {word}ds:hotkeyList,ax
                mov     {word}ds:hotkeyList+2,dx

		; store new default message
                mov     ax,{word}_target
		mov	ds:{word}defaultHotkey.MHL_destination,ax
                mov     ax,{word}_target+2
		mov	ds:{word}defaultHotkey.MHL_destination+2,ax
                mov     ax,_msg
		mov	ds:defaultHotkey.MHL_message,ax

                .leave
                ret
MACROSETHOTKEYS endp


;------------------------------------------------------------------------------
; void _pascal MacroSetAbsorbMode(Boolean enable);
;------------------------------------------------------------------------------
                global  MACROSETABSORBMODE:far

MACROSETABSORBMODE	proc far _enable:word
                .enter

                ; store new key mode
		test	_enable,0ffffh
		jnz	do_absorb
		
		mov	ax,MACRO_MODE_NORMAL
		jmp	set_mode

do_absorb:	mov	ax,MACRO_MODE_ABSORB

set_mode:	mov	ds:macroMode,ax

                .leave
                ret
MACROSETABSORBMODE	endp


;------------------------------------------------------------------------------
; word _pascal MacroGetInputProcess(void);
;------------------------------------------------------------------------------
                global  MACROGETINPUTPROCESS:far

MACROGETINPUTPROCESS	proc far
                .enter

		call    ImInfoInputProcess  ; returns: bx <- process handle
		mov	ax,bx
		
                .leave
                ret
MACROGETINPUTPROCESS	endp

MACROENG_TEXT   ends
