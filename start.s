@ Copyright (c) 2026 Michael Randrianantenaina
@ SPDX-License-Identifier: MIT

.section .text
.code 32 
.global _start
.extern mainloop

_start:
	bl mainloop
	