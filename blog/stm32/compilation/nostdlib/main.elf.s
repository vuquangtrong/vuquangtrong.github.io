
main.elf:     file format elf32-littlearm


Disassembly of section .text:

08000198 <main>:
 8000198:	b580      	push	{r7, lr}
 800019a:	af00      	add	r7, sp, #0
 800019c:	4b14      	ldr	r3, [pc, #80]	; (80001f0 <main+0x58>)
 800019e:	681b      	ldr	r3, [r3, #0]
 80001a0:	4a13      	ldr	r2, [pc, #76]	; (80001f0 <main+0x58>)
 80001a2:	f043 0301 	orr.w	r3, r3, #1
 80001a6:	6013      	str	r3, [r2, #0]
 80001a8:	4b12      	ldr	r3, [pc, #72]	; (80001f4 <main+0x5c>)
 80001aa:	681b      	ldr	r3, [r3, #0]
 80001ac:	4a11      	ldr	r2, [pc, #68]	; (80001f4 <main+0x5c>)
 80001ae:	f423 6300 	bic.w	r3, r3, #2048	; 0x800
 80001b2:	6013      	str	r3, [r2, #0]
 80001b4:	4b0f      	ldr	r3, [pc, #60]	; (80001f4 <main+0x5c>)
 80001b6:	681b      	ldr	r3, [r3, #0]
 80001b8:	4a0e      	ldr	r2, [pc, #56]	; (80001f4 <main+0x5c>)
 80001ba:	f443 6380 	orr.w	r3, r3, #1024	; 0x400
 80001be:	6013      	str	r3, [r2, #0]
 80001c0:	e00f      	b.n	80001e2 <main+0x4a>
 80001c2:	4b0d      	ldr	r3, [pc, #52]	; (80001f8 <main+0x60>)
 80001c4:	681b      	ldr	r3, [r3, #0]
 80001c6:	4a0c      	ldr	r2, [pc, #48]	; (80001f8 <main+0x60>)
 80001c8:	f043 0320 	orr.w	r3, r3, #32
 80001cc:	6013      	str	r3, [r2, #0]
 80001ce:	f000 f817 	bl	8000200 <delay>
 80001d2:	4b09      	ldr	r3, [pc, #36]	; (80001f8 <main+0x60>)
 80001d4:	681b      	ldr	r3, [r3, #0]
 80001d6:	4a08      	ldr	r2, [pc, #32]	; (80001f8 <main+0x60>)
 80001d8:	f443 1300 	orr.w	r3, r3, #2097152	; 0x200000
 80001dc:	6013      	str	r3, [r2, #0]
 80001de:	f000 f80f 	bl	8000200 <delay>
 80001e2:	4b06      	ldr	r3, [pc, #24]	; (80001fc <main+0x64>)
 80001e4:	681b      	ldr	r3, [r3, #0]
 80001e6:	2b00      	cmp	r3, #0
 80001e8:	d1eb      	bne.n	80001c2 <main+0x2a>
 80001ea:	2300      	movs	r3, #0
 80001ec:	4618      	mov	r0, r3
 80001ee:	bd80      	pop	{r7, pc}
 80001f0:	40023830 	.word	0x40023830
 80001f4:	40020000 	.word	0x40020000
 80001f8:	40020018 	.word	0x40020018
 80001fc:	20000000 	.word	0x20000000

08000200 <delay>:
 8000200:	b480      	push	{r7}
 8000202:	af00      	add	r7, sp, #0
 8000204:	f64b 62ef 	movw	r2, #48879	; 0xbeef
 8000208:	4b07      	ldr	r3, [pc, #28]	; (8000228 <delay+0x28>)
 800020a:	601a      	str	r2, [r3, #0]
 800020c:	bf00      	nop
 800020e:	4b06      	ldr	r3, [pc, #24]	; (8000228 <delay+0x28>)
 8000210:	681b      	ldr	r3, [r3, #0]
 8000212:	1e5a      	subs	r2, r3, #1
 8000214:	4904      	ldr	r1, [pc, #16]	; (8000228 <delay+0x28>)
 8000216:	600a      	str	r2, [r1, #0]
 8000218:	2b00      	cmp	r3, #0
 800021a:	d1f8      	bne.n	800020e <delay+0xe>
 800021c:	bf00      	nop
 800021e:	bf00      	nop
 8000220:	46bd      	mov	sp, r7
 8000222:	bc80      	pop	{r7}
 8000224:	4770      	bx	lr
 8000226:	bf00      	nop
 8000228:	20000004 	.word	0x20000004

0800022c <Default_Handler>:
 800022c:	b480      	push	{r7}
 800022e:	af00      	add	r7, sp, #0
 8000230:	e7fe      	b.n	8000230 <Default_Handler+0x4>
	...

08000234 <Reset_Handler>:
 8000234:	b580      	push	{r7, lr}
 8000236:	b086      	sub	sp, #24
 8000238:	af00      	add	r7, sp, #0
 800023a:	4a1a      	ldr	r2, [pc, #104]	; (80002a4 <Reset_Handler+0x70>)
 800023c:	4b1a      	ldr	r3, [pc, #104]	; (80002a8 <Reset_Handler+0x74>)
 800023e:	1ad3      	subs	r3, r2, r3
 8000240:	60fb      	str	r3, [r7, #12]
 8000242:	4b19      	ldr	r3, [pc, #100]	; (80002a8 <Reset_Handler+0x74>)
 8000244:	60bb      	str	r3, [r7, #8]
 8000246:	4b19      	ldr	r3, [pc, #100]	; (80002ac <Reset_Handler+0x78>)
 8000248:	607b      	str	r3, [r7, #4]
 800024a:	2300      	movs	r3, #0
 800024c:	617b      	str	r3, [r7, #20]
 800024e:	e00a      	b.n	8000266 <Reset_Handler+0x32>
 8000250:	697b      	ldr	r3, [r7, #20]
 8000252:	687a      	ldr	r2, [r7, #4]
 8000254:	441a      	add	r2, r3
 8000256:	697b      	ldr	r3, [r7, #20]
 8000258:	68b9      	ldr	r1, [r7, #8]
 800025a:	440b      	add	r3, r1
 800025c:	7812      	ldrb	r2, [r2, #0]
 800025e:	701a      	strb	r2, [r3, #0]
 8000260:	697b      	ldr	r3, [r7, #20]
 8000262:	3301      	adds	r3, #1
 8000264:	617b      	str	r3, [r7, #20]
 8000266:	697b      	ldr	r3, [r7, #20]
 8000268:	68fa      	ldr	r2, [r7, #12]
 800026a:	429a      	cmp	r2, r3
 800026c:	d8f0      	bhi.n	8000250 <Reset_Handler+0x1c>
 800026e:	4a10      	ldr	r2, [pc, #64]	; (80002b0 <Reset_Handler+0x7c>)
 8000270:	4b10      	ldr	r3, [pc, #64]	; (80002b4 <Reset_Handler+0x80>)
 8000272:	1ad3      	subs	r3, r2, r3
 8000274:	60fb      	str	r3, [r7, #12]
 8000276:	4b0f      	ldr	r3, [pc, #60]	; (80002b4 <Reset_Handler+0x80>)
 8000278:	60bb      	str	r3, [r7, #8]
 800027a:	2300      	movs	r3, #0
 800027c:	613b      	str	r3, [r7, #16]
 800027e:	e007      	b.n	8000290 <Reset_Handler+0x5c>
 8000280:	693b      	ldr	r3, [r7, #16]
 8000282:	68ba      	ldr	r2, [r7, #8]
 8000284:	4413      	add	r3, r2
 8000286:	2200      	movs	r2, #0
 8000288:	701a      	strb	r2, [r3, #0]
 800028a:	693b      	ldr	r3, [r7, #16]
 800028c:	3301      	adds	r3, #1
 800028e:	613b      	str	r3, [r7, #16]
 8000290:	693b      	ldr	r3, [r7, #16]
 8000292:	68fa      	ldr	r2, [r7, #12]
 8000294:	429a      	cmp	r2, r3
 8000296:	d8f3      	bhi.n	8000280 <Reset_Handler+0x4c>
 8000298:	f7ff ff7e 	bl	8000198 <main>
 800029c:	bf00      	nop
 800029e:	3718      	adds	r7, #24
 80002a0:	46bd      	mov	sp, r7
 80002a2:	bd80      	pop	{r7, pc}
 80002a4:	20000004 	.word	0x20000004
 80002a8:	20000000 	.word	0x20000000
 80002ac:	080002bc 	.word	0x080002bc
 80002b0:	20000008 	.word	0x20000008
 80002b4:	20000004 	.word	0x20000004
