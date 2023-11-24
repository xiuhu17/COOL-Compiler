define i32 @fib(i32 %n) {
entry:
    %base = icmp sle i32 %n, 2
    br i1 %base, label %then, label %else

then:
    ret i32 1

else:
    %n.1 = sub i32 %n, 1
    %n.2 = sub i32 %n, 2
    %f.1 = call i32 @fib(i32 %n.1)
    %f.2 = call i32 @fib(i32 %n.2)
    %f = add i32 %f.1, %f.2
    ret i32 %f
}

define i32 @main() {
    %c = call i32 @fib(i32 12)
    ret i32 %c
}
