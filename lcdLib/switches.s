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
	.extern chewing
	
	.text
	.align 2
	.global state_select
state_select:
	cmp #4, r12
	jc default

	add r12, r12
	mov jt(r12), r0

case1:
	mov #1, &state
	mov #3, &mouth
	mov #1, &happy
	mov #0, &sec_carrot
	mov #1, &chewing
	call #drawCarrot
	jmp esac
case2:
	mov #2, &state
	jmp esac
case3:
	mov #3, &state
	jmp esac
default:	
	mov #4, &state
	jmp esac

esac:
	pop r0
