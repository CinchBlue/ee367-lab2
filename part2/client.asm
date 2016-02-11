	.file	"client_main.c"
	.intel_syntax noprefix
	.text
.Ltext0:
	.section	.rodata
.LC0:
	.string	"list"
.LC1:
	.string	"check"
.LC2:
	.string	"display"
.LC3:
	.string	"download"
	.text
	.globl	parse_client_choice
	.type	parse_client_choice, @function
parse_client_choice:
.LFB0:
	.file 1 "client_main.c"
	.loc 1 30 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi
	.loc 1 35 0
	jmp	.L2
.L4:
	.loc 1 37 0
	add	QWORD PTR [rbp-8], 1
.L2:
	.loc 1 35 0 discriminator 1
	mov	rax, QWORD PTR [rbp-8]
	movzx	eax, BYTE PTR [rax]
	movsx	eax, al
	mov	edi, eax
	call	isalpha
	test	eax, eax
	jne	.L3
	.loc 1 35 0 is_stmt 0 discriminator 2
	mov	rax, QWORD PTR [rbp-8]
	movzx	eax, BYTE PTR [rax]
	test	al, al
	jne	.L4
.L3:
	.loc 1 41 0 is_stmt 1
	mov	rax, QWORD PTR [rbp-8]
	movzx	eax, BYTE PTR [rax]
	test	al, al
	jne	.L5
	.loc 1 42 0
	mov	eax, 0
	jmp	.L6
.L5:
	.loc 1 57 0
	mov	rax, QWORD PTR [rbp-8]
	mov	edx, 5
	mov	esi, OFFSET FLAT:.LC0
	mov	rdi, rax
	call	strncmp
	test	eax, eax
	jne	.L7
	.loc 1 58 0
	mov	eax, 1
	jmp	.L6
.L7:
	.loc 1 59 0
	mov	rax, QWORD PTR [rbp-8]
	mov	edx, 6
	mov	esi, OFFSET FLAT:.LC1
	mov	rdi, rax
	call	strncmp
	test	eax, eax
	jne	.L8
	.loc 1 60 0
	mov	eax, 2
	jmp	.L6
.L8:
	.loc 1 61 0
	mov	rax, QWORD PTR [rbp-8]
	mov	edx, 8
	mov	esi, OFFSET FLAT:.LC2
	mov	rdi, rax
	call	strncmp
	test	eax, eax
	jne	.L9
	.loc 1 62 0
	mov	eax, 3
	jmp	.L6
.L9:
	.loc 1 63 0
	mov	rax, QWORD PTR [rbp-8]
	mov	edx, 9
	mov	esi, OFFSET FLAT:.LC3
	mov	rdi, rax
	call	strncmp
	test	eax, eax
	jne	.L10
	.loc 1 64 0
	mov	eax, 4
	jmp	.L6
.L10:
	.loc 1 71 0
	mov	eax, 0
.L6:
	.loc 1 81 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	parse_client_choice, .-parse_client_choice
	.section	.rodata
.LC4:
	.string	"%s"
	.align 8
.LC5:
	.string	"ERROR: prompt() encountered a read error.\n"
	.text
	.globl	prompt
	.type	prompt, @function
prompt:
.LFB1:
	.loc 1 98 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR [rbp-8], rdi
	mov	QWORD PTR [rbp-16], rsi
	mov	DWORD PTR [rbp-20], edx
	.loc 1 100 0
	mov	rax, QWORD PTR [rbp-8]
	mov	rsi, rax
	mov	edi, OFFSET FLAT:.LC4
	mov	eax, 0
	call	printf
	.loc 1 102 0
	mov	rdx, QWORD PTR stdin[rip]
	mov	ecx, DWORD PTR [rbp-20]
	mov	rax, QWORD PTR [rbp-16]
	mov	esi, ecx
	mov	rdi, rax
	call	fgets
	test	rax, rax
	jne	.L12
	.loc 1 104 0
	mov	rax, QWORD PTR stderr[rip]
	mov	rcx, rax
	mov	edx, 42
	mov	esi, 1
	mov	edi, OFFSET FLAT:.LC5
	call	fwrite
	.loc 1 105 0
	mov	eax, -1
	jmp	.L13
.L12:
	.loc 1 107 0
	mov	eax, 0
.L13:
	.loc 1 112 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	prompt, .-prompt
	.globl	client_main
	.type	client_main, @function
client_main:
.LFB2:
	.loc 1 116 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	DWORD PTR [rbp-4], edi
	mov	QWORD PTR [rbp-16], rsi
	mov	DWORD PTR [rbp-8], edx
	.loc 1 120 0
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	client_main, .-client_main
	.section	.rodata
.LC6:
	.string	"client367: "
.LC7:
	.string	"PARSED INPUT: %d\n"
.LC8:
	.string	"Got: %s\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.loc 1 122 0
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 272
	.loc 1 122 0
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR [rbp-8], rax
	xor	eax, eax
	.loc 1 127 0
	lea	rax, [rbp-272]
	mov	edx, 256
	mov	rsi, rax
	mov	edi, OFFSET FLAT:.LC6
	call	prompt
	.loc 1 129 0
	lea	rax, [rbp-272]
	mov	rdi, rax
	call	parse_client_choice
	mov	esi, eax
	mov	edi, OFFSET FLAT:.LC7
	mov	eax, 0
	call	printf
	.loc 1 131 0
	lea	rax, [rbp-272]
	mov	rsi, rax
	mov	edi, OFFSET FLAT:.LC8
	mov	eax, 0
	call	printf
	.loc 1 132 0
	mov	eax, 0
	.loc 1 133 0
	mov	rcx, QWORD PTR [rbp-8]
	xor	rcx, QWORD PTR fs:40
	je	.L17
	call	__stack_chk_fail
.L17:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/4.8/include/stddef.h"
	.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 4 "/usr/include/libio.h"
	.file 5 "/usr/include/stdio.h"
	.file 6 "<built-in>"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x403
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF63
	.byte	0x1
	.long	.LASF64
	.long	.LASF65
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF7
	.byte	0x2
	.byte	0xd4
	.long	0x38
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.long	.LASF8
	.byte	0x3
	.byte	0x83
	.long	0x69
	.uleb128 0x2
	.long	.LASF9
	.byte	0x3
	.byte	0x84
	.long	0x69
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF10
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0x95
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF11
	.uleb128 0x7
	.long	.LASF41
	.byte	0xd8
	.byte	0x4
	.byte	0xf5
	.long	0x21c
	.uleb128 0x8
	.long	.LASF12
	.byte	0x4
	.byte	0xf6
	.long	0x62
	.byte	0
	.uleb128 0x8
	.long	.LASF13
	.byte	0x4
	.byte	0xfb
	.long	0x8f
	.byte	0x8
	.uleb128 0x8
	.long	.LASF14
	.byte	0x4
	.byte	0xfc
	.long	0x8f
	.byte	0x10
	.uleb128 0x8
	.long	.LASF15
	.byte	0x4
	.byte	0xfd
	.long	0x8f
	.byte	0x18
	.uleb128 0x8
	.long	.LASF16
	.byte	0x4
	.byte	0xfe
	.long	0x8f
	.byte	0x20
	.uleb128 0x8
	.long	.LASF17
	.byte	0x4
	.byte	0xff
	.long	0x8f
	.byte	0x28
	.uleb128 0x9
	.long	.LASF18
	.byte	0x4
	.value	0x100
	.long	0x8f
	.byte	0x30
	.uleb128 0x9
	.long	.LASF19
	.byte	0x4
	.value	0x101
	.long	0x8f
	.byte	0x38
	.uleb128 0x9
	.long	.LASF20
	.byte	0x4
	.value	0x102
	.long	0x8f
	.byte	0x40
	.uleb128 0x9
	.long	.LASF21
	.byte	0x4
	.value	0x104
	.long	0x8f
	.byte	0x48
	.uleb128 0x9
	.long	.LASF22
	.byte	0x4
	.value	0x105
	.long	0x8f
	.byte	0x50
	.uleb128 0x9
	.long	.LASF23
	.byte	0x4
	.value	0x106
	.long	0x8f
	.byte	0x58
	.uleb128 0x9
	.long	.LASF24
	.byte	0x4
	.value	0x108
	.long	0x254
	.byte	0x60
	.uleb128 0x9
	.long	.LASF25
	.byte	0x4
	.value	0x10a
	.long	0x25a
	.byte	0x68
	.uleb128 0x9
	.long	.LASF26
	.byte	0x4
	.value	0x10c
	.long	0x62
	.byte	0x70
	.uleb128 0x9
	.long	.LASF27
	.byte	0x4
	.value	0x110
	.long	0x62
	.byte	0x74
	.uleb128 0x9
	.long	.LASF28
	.byte	0x4
	.value	0x112
	.long	0x70
	.byte	0x78
	.uleb128 0x9
	.long	.LASF29
	.byte	0x4
	.value	0x116
	.long	0x46
	.byte	0x80
	.uleb128 0x9
	.long	.LASF30
	.byte	0x4
	.value	0x117
	.long	0x54
	.byte	0x82
	.uleb128 0x9
	.long	.LASF31
	.byte	0x4
	.value	0x118
	.long	0x260
	.byte	0x83
	.uleb128 0x9
	.long	.LASF32
	.byte	0x4
	.value	0x11c
	.long	0x270
	.byte	0x88
	.uleb128 0x9
	.long	.LASF33
	.byte	0x4
	.value	0x125
	.long	0x7b
	.byte	0x90
	.uleb128 0x9
	.long	.LASF34
	.byte	0x4
	.value	0x12e
	.long	0x8d
	.byte	0x98
	.uleb128 0x9
	.long	.LASF35
	.byte	0x4
	.value	0x12f
	.long	0x8d
	.byte	0xa0
	.uleb128 0x9
	.long	.LASF36
	.byte	0x4
	.value	0x130
	.long	0x8d
	.byte	0xa8
	.uleb128 0x9
	.long	.LASF37
	.byte	0x4
	.value	0x131
	.long	0x8d
	.byte	0xb0
	.uleb128 0x9
	.long	.LASF38
	.byte	0x4
	.value	0x132
	.long	0x2d
	.byte	0xb8
	.uleb128 0x9
	.long	.LASF39
	.byte	0x4
	.value	0x134
	.long	0x62
	.byte	0xc0
	.uleb128 0x9
	.long	.LASF40
	.byte	0x4
	.value	0x136
	.long	0x276
	.byte	0xc4
	.byte	0
	.uleb128 0xa
	.long	.LASF66
	.byte	0x4
	.byte	0x9a
	.uleb128 0x7
	.long	.LASF42
	.byte	0x18
	.byte	0x4
	.byte	0xa0
	.long	0x254
	.uleb128 0x8
	.long	.LASF43
	.byte	0x4
	.byte	0xa1
	.long	0x254
	.byte	0
	.uleb128 0x8
	.long	.LASF44
	.byte	0x4
	.byte	0xa2
	.long	0x25a
	.byte	0x8
	.uleb128 0x8
	.long	.LASF45
	.byte	0x4
	.byte	0xa6
	.long	0x62
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x223
	.uleb128 0x6
	.byte	0x8
	.long	0x9c
	.uleb128 0xb
	.long	0x95
	.long	0x270
	.uleb128 0xc
	.long	0x86
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x21c
	.uleb128 0xb
	.long	0x95
	.long	0x286
	.uleb128 0xc
	.long	0x86
	.byte	0x13
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x28c
	.uleb128 0xd
	.long	0x95
	.uleb128 0xe
	.byte	0x4
	.byte	0x1
	.byte	0xa
	.long	0x2c4
	.uleb128 0xf
	.long	.LASF46
	.sleb128 0
	.uleb128 0xf
	.long	.LASF47
	.sleb128 1
	.uleb128 0xf
	.long	.LASF48
	.sleb128 2
	.uleb128 0xf
	.long	.LASF49
	.sleb128 3
	.uleb128 0xf
	.long	.LASF50
	.sleb128 4
	.uleb128 0xf
	.long	.LASF51
	.sleb128 5
	.uleb128 0xf
	.long	.LASF52
	.sleb128 6
	.byte	0
	.uleb128 0x2
	.long	.LASF53
	.byte	0x1
	.byte	0x12
	.long	0x291
	.uleb128 0x10
	.long	.LASF54
	.byte	0x1
	.byte	0x1e
	.long	0x2c4
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0x30c
	.uleb128 0x11
	.string	"str"
	.byte	0x1
	.byte	0x1e
	.long	0x8f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x12
	.long	.LASF67
	.byte	0x6
	.byte	0
	.long	0x62
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.long	.LASF55
	.byte	0x1
	.byte	0x62
	.long	0x62
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x358
	.uleb128 0x11
	.string	"str"
	.byte	0x1
	.byte	0x62
	.long	0x286
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x14
	.long	.LASF56
	.byte	0x1
	.byte	0x62
	.long	0x8f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x14
	.long	.LASF57
	.byte	0x1
	.byte	0x62
	.long	0x62
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
	.uleb128 0x15
	.long	.LASF58
	.byte	0x1
	.byte	0x74
	.long	0x62
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x3a4
	.uleb128 0x14
	.long	.LASF59
	.byte	0x1
	.byte	0x74
	.long	0x62
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x14
	.long	.LASF56
	.byte	0x1
	.byte	0x74
	.long	0x3a4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x14
	.long	.LASF60
	.byte	0x1
	.byte	0x74
	.long	0x62
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xd
	.long	0x3a9
	.uleb128 0x6
	.byte	0x8
	.long	0x8f
	.uleb128 0x16
	.long	.LASF68
	.byte	0x1
	.byte	0x7a
	.long	0x62
	.quad	.LFB3
	.quad	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x3e0
	.uleb128 0x17
	.string	"buf"
	.byte	0x1
	.byte	0x7b
	.long	0x3e0
	.uleb128 0x3
	.byte	0x91
	.sleb128 -288
	.byte	0
	.uleb128 0xb
	.long	0x95
	.long	0x3f0
	.uleb128 0xc
	.long	0x86
	.byte	0xff
	.byte	0
	.uleb128 0x18
	.long	.LASF61
	.byte	0x5
	.byte	0xa8
	.long	0x25a
	.uleb128 0x18
	.long	.LASF62
	.byte	0x5
	.byte	0xaa
	.long	0x25a
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF20:
	.string	"_IO_buf_end"
.LASF50:
	.string	"CLIENT_CHOICE_DOWNLOAD"
.LASF28:
	.string	"_old_offset"
.LASF55:
	.string	"prompt"
.LASF47:
	.string	"CLIENT_CHOICE_LIST"
.LASF23:
	.string	"_IO_save_end"
.LASF5:
	.string	"short int"
.LASF7:
	.string	"size_t"
.LASF46:
	.string	"CLIENT_CHOICE_INVALID"
.LASF10:
	.string	"sizetype"
.LASF33:
	.string	"_offset"
.LASF60:
	.string	"buffer_maxsize"
.LASF17:
	.string	"_IO_write_ptr"
.LASF12:
	.string	"_flags"
.LASF19:
	.string	"_IO_buf_base"
.LASF57:
	.string	"maxsize"
.LASF24:
	.string	"_markers"
.LASF14:
	.string	"_IO_read_end"
.LASF49:
	.string	"CLIENT_CHOICE_DISPLAY"
.LASF54:
	.string	"parse_client_choice"
.LASF51:
	.string	"CLIENT_CHOICE_QUIT"
.LASF62:
	.string	"stderr"
.LASF32:
	.string	"_lock"
.LASF59:
	.string	"sockfd"
.LASF6:
	.string	"long int"
.LASF67:
	.string	"isalpha"
.LASF29:
	.string	"_cur_column"
.LASF45:
	.string	"_pos"
.LASF65:
	.string	"/home/austin/prog/ee367/lab2/part2"
.LASF44:
	.string	"_sbuf"
.LASF41:
	.string	"_IO_FILE"
.LASF1:
	.string	"unsigned char"
.LASF53:
	.string	"CLIENT_CHOICE"
.LASF4:
	.string	"signed char"
.LASF48:
	.string	"CLIENT_CHOICE_CHECK"
.LASF63:
	.string	"GNU C 4.8.4 -masm=intel -mtune=generic -march=x86-64 -g -fstack-protector"
.LASF3:
	.string	"unsigned int"
.LASF42:
	.string	"_IO_marker"
.LASF31:
	.string	"_shortbuf"
.LASF16:
	.string	"_IO_write_base"
.LASF40:
	.string	"_unused2"
.LASF13:
	.string	"_IO_read_ptr"
.LASF2:
	.string	"short unsigned int"
.LASF58:
	.string	"client_main"
.LASF11:
	.string	"char"
.LASF68:
	.string	"main"
.LASF52:
	.string	"CLIENT_CHOICE_HELP"
.LASF43:
	.string	"_next"
.LASF34:
	.string	"__pad1"
.LASF35:
	.string	"__pad2"
.LASF36:
	.string	"__pad3"
.LASF37:
	.string	"__pad4"
.LASF38:
	.string	"__pad5"
.LASF56:
	.string	"buffer"
.LASF0:
	.string	"long unsigned int"
.LASF18:
	.string	"_IO_write_end"
.LASF9:
	.string	"__off64_t"
.LASF8:
	.string	"__off_t"
.LASF25:
	.string	"_chain"
.LASF22:
	.string	"_IO_backup_base"
.LASF61:
	.string	"stdin"
.LASF27:
	.string	"_flags2"
.LASF39:
	.string	"_mode"
.LASF15:
	.string	"_IO_read_base"
.LASF30:
	.string	"_vtable_offset"
.LASF21:
	.string	"_IO_save_base"
.LASF26:
	.string	"_fileno"
.LASF64:
	.string	"client_main.c"
.LASF66:
	.string	"_IO_lock_t"
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
