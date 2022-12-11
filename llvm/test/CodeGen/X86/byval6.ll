; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mcpu=generic -mtriple=i686-- | FileCheck %s

	%struct.W = type { x86_fp80, x86_fp80 }
@B = global %struct.W { x86_fp80 0xK4001A000000000000000, x86_fp80 0xK4001C000000000000000 }, align 32
@.cpx = internal constant %struct.W { x86_fp80 0xK4001E000000000000000, x86_fp80 0xK40028000000000000000 }

define i32 @main() nounwind  {
; CHECK-LABEL: main:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushl %ebx
; CHECK-NEXT:    pushl %edi
; CHECK-NEXT:    pushl %esi
; CHECK-NEXT:    movl .cpx+20, %eax
; CHECK-NEXT:    movl .cpx+16, %ecx
; CHECK-NEXT:    movl .cpx+12, %edx
; CHECK-NEXT:    movl .cpx+8, %esi
; CHECK-NEXT:    movl .cpx+4, %edi
; CHECK-NEXT:    movl .cpx, %ebx
; CHECK-NEXT:    pushl %eax
; CHECK-NEXT:    pushl %ecx
; CHECK-NEXT:    pushl %edx
; CHECK-NEXT:    pushl %esi
; CHECK-NEXT:    pushl %edi
; CHECK-NEXT:    pushl %ebx
; CHECK-NEXT:    pushl $3
; CHECK-NEXT:    calll bar
; CHECK-NEXT:    addl $28, %esp
; CHECK-NEXT:    movl B+20, %eax
; CHECK-NEXT:    movl B+16, %ecx
; CHECK-NEXT:    movl B+12, %edx
; CHECK-NEXT:    movl B+8, %esi
; CHECK-NEXT:    movl B+4, %edi
; CHECK-NEXT:    movl B, %ebx
; CHECK-NEXT:    pushl %eax
; CHECK-NEXT:    pushl %ecx
; CHECK-NEXT:    pushl %edx
; CHECK-NEXT:    pushl %esi
; CHECK-NEXT:    pushl %edi
; CHECK-NEXT:    pushl %ebx
; CHECK-NEXT:    pushl $3
; CHECK-NEXT:    calll baz
; CHECK-NEXT:    addl $28, %esp
; CHECK-NEXT:    popl %esi
; CHECK-NEXT:    popl %edi
; CHECK-NEXT:    popl %ebx
; CHECK-NEXT:    retl
entry:
	tail call void (i32, ...) @bar( i32 3, %struct.W* byval(%struct.W) @.cpx ) nounwind
	tail call void (i32, ...) @baz( i32 3, %struct.W* byval(%struct.W)  @B ) nounwind
	ret i32 undef
}

declare void @bar(i32, ...)

declare void @baz(i32, ...)