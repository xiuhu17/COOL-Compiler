define i32 @max(i32 %a, i32 %b) {
entry:
    %i = icmp sge i32 %a, %b
    br i1 %i, label %then, label %else

then:
    br label %end

else:
    br label %end

end:
    %c = phi i32 [%a, %then], [%b, %else]
    ret i32 %c
}

define i32 @main() {
    %c = call i32 @max(i32 15, i32 24)
    ret i32 %c
}
