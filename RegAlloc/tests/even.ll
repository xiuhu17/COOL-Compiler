define i1 @even(i32 %n) {
entry:
    %z = icmp eq i32 %n, 0
    br i1 %z, label %true, label %nonzero

nonzero:
    %p = icmp sgt i32 %n, 0
    br i1 %p, label %positive, label %negative

positive:
    %n.1 = sub i32 %n, 1
    %even.1 = call i1 @even(i32 %n.1)
    br i1 %even.1, label %false, label %true

negative:
    %n.2 = add i32 %n, 1
    %even.2 = call i1 @even(i32 %n.2)
    br i1 %even.2, label %false, label %true

true:
    ret i1 1

false:
    ret i1 0
}

define i1 @main() {
    %c = call i1 @even(i32 -11)
    ret i1 %c
}
