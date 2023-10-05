declare i32 @strcmp(i8*, i8*)
declare i32 @printf(i8*, ...)
declare void @abort()
declare i8* @malloc(i32)
define i32 @Main.main() {

entry:
	%vtpm.0 = alloca i32
	%vtpm.1 = alloca i32
	%vtpm.2 = alloca i32
	br i1 true, label %true.0, label %false.0

true.0:
	br i1 false, label %true.1, label %false.1

true.1:
	store i32 2, i32* %vtpm.0
	br label %end.1

false.1:
	store i32 3, i32* %vtpm.0
	br label %end.1

end.1:
	%vtpm.3 = load i32, i32* %vtpm.0
	store i32 %vtpm.3, i32* %vtpm.2
	br label %end.0

false.0:
	br i1 true, label %true.2, label %false.2

true.2:
	store i32 7, i32* %vtpm.1
	br label %end.2

false.2:
	store i32 9, i32* %vtpm.1
	br label %end.2

end.2:
	%vtpm.4 = load i32, i32* %vtpm.1
	store i32 %vtpm.4, i32* %vtpm.2
	br label %end.0

end.0:
	%vtpm.5 = load i32, i32* %vtpm.2
	ret i32 %vtpm.5

abort:
	call void @abort(  )
	unreachable
}

@main.printout.str = internal constant [25 x i8] c"Main.main() returned %d\0A\00"
define i32 @main() {

entry:
	%vtpm.7 = call i32 @Main.main(  )
	%tpm = getelementptr [25 x i8], [25 x i8]* @main.printout.str, i32 0, i32 0
	%vtpm.8 = call i32(i8*, ... ) @printf( i8* %tpm, i32 %vtpm.7 )
	ret i32 0
}

