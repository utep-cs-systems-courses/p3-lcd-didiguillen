	.data
	.align 2
	.global state
state:
	.word 0
jt:
	.word default
	.word case1
	.word case2
	.word case3

	.extern drawCarrot
	.extern mouth
	.extern happy
	.extern sec_carrot
	.extern sec_soap
	.extern chewing
	.extern drawSoap
	.extern open_eyes
	.extern soap
	.extern carrot
	.extern ball
	.extern drawBall
	.extern sec_ball
	.extern sleep
	.extern drawSleep
	.extern sec_sleep
	.extern drawOpenSmile
	
	.text
	.align 2
	.global state_select
state_select:
	cmp #4, r12
	jc default
	mov #0, &soap
	add r12, r12
	mov jt(r12), r0

case1:
	mov #1, &state
	mov #3, &mouth
	mov #1, &happy
	mov #1, &carrot
	mov #0, &sec_carrot
	call #drawCarrot
	jmp esac
case2:
	mov #2, &state
	mov #2, &mouth
	mov #1, &happy
	mov #1, &soap
	mov #0, &sec_soap
	mov #0, &open_eyes
	call #drawSoap
	jmp esac
case3:
	mov #3, &state
	mov #2, &mouth
	mov #1, &happy
	mov #1, &ball
	mov #0, &sec_ball
	call #drawBall
	call #drawOpenSmile
	jmp esac
default:	
	mov #4, &state
	mov #3, &mouth
	mov #0, &open_eyes
	mov #1, &happy
	mov #1, &sleep
	mov #0, &sec_sleep
	call #drawSleep
	jmp esac

esac:
	pop r0
