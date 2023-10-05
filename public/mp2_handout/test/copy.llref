declare i32 @strcmp(i8*, i8*)
declare i32 @printf(i8*, ...)
declare void @abort()
declare i8* @malloc(i32)
define i32 @Main.main() {

entry:
	%tmp.0 = alloca i32
	%tmp.1 = icmp slt i32 2, 1
	br i1 %tmp.1, label %true.0, label %false.0

true.0:
	store i32 11, i32* %tmp.0
	br label %end.0

false.0:
	store i32 14, i32* %tmp.0
	br label %end.0

end.0:
	%tmp.2 = load i32, i32* %tmp.0
	ret i32 %tmp.2

abort:
	call void @abort(  )
	unreachable
}

@main.printout.str = internal constant [25 x i8] c"Main.main() returned %d\0A\00"
define i32 @main() {

entry:
	%vtpm.0 = call i32 @Main.main(  )
	%tpm = getelementptr [25 x i8], [25 x i8]* @main.printout.str, i32 0, i32 0
	%vtpm.1 = call i32(i8*, ... ) @printf( i8* %tpm, i32 %vtpm.0 )
	ret i32 0
}

