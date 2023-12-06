; Rotate bits in a 8-byte integer n right for k bits
define i8 @rotate(i8 %n, i8 %k) {
entry:
    %k.1 = urem i8 %k, 8
    %n.lo = lshr i8 %n, %k.1

    %m = sub i8 8, %k.1
    %n.hi = shl i8 %n, %m
    
    %n.1 = or i8 %n.hi, %n.lo

    ret i8 %n.1
}

define i8 @main() {
    %c = call i8 @rotate(i8 251, i8 3)
    ret i8 %c
}
