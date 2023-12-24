; ModuleID = '<stdin>'
source_filename = "simple.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
  br label %1

1:                                                ; preds = %13, %0
  %.02 = phi i32 [ 0, %0 ], [ %14, %13 ]
  %.01 = phi i32 [ 0, %0 ], [ %.2, %13 ]
  %2 = icmp eq i32 %.02, 0
  br i1 %2, label %3, label %15

3:                                                ; preds = %1, %5
  %.03 = phi i32 [ %7, %5 ], [ 0, %1 ]
  %.1 = phi i32 [ %6, %5 ], [ %.01, %1 ]
  %4 = icmp ult i32 %.03, 5
  br i1 %4, label %5, label %8

5:                                                ; preds = %3
  %6 = add nsw i32 %.1, 1
  %7 = add nuw nsw i32 %.03, 1
  br label %3, !llvm.loop !6

8:                                                ; preds = %3, %10
  %.04 = phi i32 [ %12, %10 ], [ 0, %3 ]
  %.2 = phi i32 [ %11, %10 ], [ %.1, %3 ]
  %9 = icmp ult i32 %.04, 5
  br i1 %9, label %10, label %13

10:                                               ; preds = %8
  %11 = add nsw i32 %.2, 1
  %12 = add nuw nsw i32 %.04, 1
  br label %8, !llvm.loop !8

13:                                               ; preds = %8
  %14 = add nuw nsw i32 %.02, 1
  br label %1, !llvm.loop !9

15:                                               ; preds = %1, %54
  %.05 = phi i32 [ %55, %54 ], [ 0, %1 ]
  %.3 = phi i32 [ %.8, %54 ], [ %.01, %1 ]
  %16 = icmp ult i32 %.05, 5
  br i1 %16, label %17, label %56

17:                                               ; preds = %15, %19
  %.06 = phi i32 [ %21, %19 ], [ 0, %15 ]
  %.4 = phi i32 [ %20, %19 ], [ %.3, %15 ]
  %18 = icmp ult i32 %.06, 3
  br i1 %18, label %19, label %22

19:                                               ; preds = %17
  %20 = add nsw i32 %.4, 1
  %21 = add nuw nsw i32 %.06, 1
  br label %17, !llvm.loop !10

22:                                               ; preds = %17, %38
  %.07 = phi i32 [ %39, %38 ], [ 0, %17 ]
  %.5 = phi i32 [ %.7, %38 ], [ %.4, %17 ]
  %23 = icmp ult i32 %.07, 3
  br i1 %23, label %24, label %40

24:                                               ; preds = %22, %26
  %.08 = phi i32 [ %28, %26 ], [ 0, %22 ]
  %.6 = phi i32 [ %27, %26 ], [ %.5, %22 ]
  %25 = icmp ult i32 %.08, 10
  br i1 %25, label %26, label %29

26:                                               ; preds = %24
  %27 = add nsw i32 %.6, 1
  %28 = add nuw nsw i32 %.08, 1
  br label %24, !llvm.loop !11

29:                                               ; preds = %24, %36
  %.09 = phi i32 [ %37, %36 ], [ 0, %24 ]
  %.7 = phi i32 [ %32, %36 ], [ %.6, %24 ]
  %30 = icmp ult i32 %.09, 10
  br i1 %30, label %31, label %38

31:                                               ; preds = %29
  %32 = add nsw i32 %.7, 1
  br label %33

33:                                               ; preds = %33, %31
  %.010 = phi i32 [ 0, %31 ], [ %34, %33 ]
  %34 = add nuw nsw i32 %.010, 1
  %35 = icmp ult i32 %.010, 19
  br i1 %35, label %33, label %36, !llvm.loop !12

36:                                               ; preds = %33
  %37 = add nuw nsw i32 %.09, 1
  br label %29, !llvm.loop !13

38:                                               ; preds = %29
  %39 = add nuw nsw i32 %.07, 1
  br label %22, !llvm.loop !14

40:                                               ; preds = %22, %52
  %.011 = phi i32 [ %53, %52 ], [ 0, %22 ]
  %.8 = phi i32 [ %.10, %52 ], [ %.5, %22 ]
  %41 = icmp ult i32 %.011, 3
  br i1 %41, label %42, label %54

42:                                               ; preds = %40, %44
  %.012 = phi i32 [ %46, %44 ], [ 0, %40 ]
  %.9 = phi i32 [ %45, %44 ], [ %.8, %40 ]
  %43 = icmp ult i32 %.012, 10
  br i1 %43, label %44, label %47

44:                                               ; preds = %42
  %45 = add nsw i32 %.9, 1
  %46 = add nuw nsw i32 %.012, 1
  br label %42, !llvm.loop !15

47:                                               ; preds = %42, %49
  %.013 = phi i32 [ %51, %49 ], [ 0, %42 ]
  %.10 = phi i32 [ %50, %49 ], [ %.9, %42 ]
  %48 = icmp ult i32 %.013, 10
  br i1 %48, label %49, label %52

49:                                               ; preds = %47
  %50 = add nsw i32 %.10, 1
  %51 = add nuw nsw i32 %.013, 1
  br label %47, !llvm.loop !16

52:                                               ; preds = %47
  %53 = add nuw nsw i32 %.011, 1
  br label %40, !llvm.loop !17

54:                                               ; preds = %40
  %55 = add nuw nsw i32 %.05, 1
  br label %15, !llvm.loop !18

56:                                               ; preds = %15, %58
  %.11 = phi i32 [ %59, %58 ], [ %.3, %15 ]
  %57 = phi i1 [ false, %58 ], [ true, %15 ]
  br i1 %57, label %58, label %60

58:                                               ; preds = %56
  %59 = add nsw i32 %.11, 1
  br label %56, !llvm.loop !19

60:                                               ; preds = %56
  ret i32 %.11
}

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 15.0.7"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
!12 = distinct !{!12, !7}
!13 = distinct !{!13, !7}
!14 = distinct !{!14, !7}
!15 = distinct !{!15, !7}
!16 = distinct !{!16, !7}
!17 = distinct !{!17, !7}
!18 = distinct !{!18, !7}
!19 = distinct !{!19, !7}
