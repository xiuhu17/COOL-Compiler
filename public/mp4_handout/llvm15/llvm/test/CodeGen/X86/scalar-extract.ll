; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=i686-- -mattr=+mmx | FileCheck %s

; Check that widening doesn't introduce a mmx register in this case when
; a simple load/store would suffice.

define void @foo(ptr %A, ptr %B) {
; CHECK-LABEL: foo:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl {{[0-9]+}}(%esp), %eax
; CHECK-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; CHECK-NEXT:    movl (%ecx), %ecx
; CHECK-NEXT:    movl %ecx, (%eax)
; CHECK-NEXT:    retl
entry:
	%tmp1 = load <2 x i16>, ptr %A		; <<2 x i16>> [#uses=1]
	store <2 x i16> %tmp1, ptr %B
	ret void
}
