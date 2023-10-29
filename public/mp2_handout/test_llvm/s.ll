; ModuleID = 'module'
source_filename = "module"

@main.printout.str = private unnamed_addr constant [25 x i8] c"Main.main() returned %d\0A\00", align 1

declare i32 @strcmp(ptr, ptr)

declare i32 @printf(ptr, ...)

declare void @abort()

declare ptr @malloc(i32)

define i32 @Main.main() {
entry:
  %0 = alloca i32, align 4
  %1 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 10, ptr %1, align 4
  store i32 0, ptr %0, align 4
  %2 = load i32, ptr %1, align 4
  %3 = load i32, ptr %1, align 4
  %4 = mul i32 %2, %3
  %5 = load i32, ptr %1, align 4
  %6 = icmp eq i32 0, %5
  br i1 %6, label %abort, label %ok.0

abort:                                            ; preds = %ok.0, %entry
  call void @abort()
  unreachable

ok.0:                                             ; preds = %entry
  %7 = sdiv i32 %4, %5
  store i32 %7, ptr %0, align 4
  %8 = load i32, ptr %0, align 4
  %9 = load i32, ptr %0, align 4
  %10 = load i32, ptr %1, align 4
  %11 = sub i32 %9, %10
  %12 = icmp eq i32 0, %11
  br i1 %12, label %abort, label %ok.1

ok.1:                                             ; preds = %ok.0
  %13 = sdiv i32 %8, %11
  ret i32 %13
}

define i32 @main() {
entry:
  %0 = call i32 @Main.main()
  %1 = call i32 (ptr, ...) @printf(ptr @main.printout.str, i32 %0)
  ret i32 0
}
