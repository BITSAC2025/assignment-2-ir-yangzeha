; ModuleID = 'demo.c'
source_filename = "demo.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@tgetstr.initstr = internal global [25 x i8] c"select* From City ..\00\00\00\00\00", align 16

; Function Attrs: noinline nounwind optnone uwtable
define dso_local ptr @tgetstr() #0 {
  ret ptr @tgetstr.initstr
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca [5 x i32], align 16
  %8 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  %9 = call ptr @tgetstr()
  store ptr %9, ptr %2, align 8
  %10 = load ptr, ptr %2, align 8
  store ptr %10, ptr %3, align 8
  %11 = load ptr, ptr %3, align 8
  store ptr %11, ptr %4, align 8
  %12 = load ptr, ptr %4, align 8
  call void @broadcast(ptr noundef %12)
  store i32 1, ptr %6, align 4
  store ptr %6, ptr %5, align 8
  %13 = load ptr, ptr %5, align 8
  store i32 3, ptr %13, align 4
  %14 = load i32, ptr %6, align 4
  %15 = icmp eq i32 %14, 3
  call void @svf_assert(i1 noundef zeroext %15)
  store i32 0, ptr %8, align 4
  br label %16

16:                                               ; preds = %19, %0
  %17 = load i32, ptr %8, align 4
  %18 = icmp slt i32 %17, 5
  br i1 %18, label %19, label %24

19:                                               ; preds = %16
  %20 = load i32, ptr %8, align 4
  %21 = add nsw i32 %20, 1
  store i32 %21, ptr %8, align 4
  %22 = sext i32 %21 to i64
  %23 = getelementptr inbounds [5 x i32], ptr %7, i64 0, i64 %22
  store i32 10, ptr %23, align 4
  br label %16, !llvm.loop !6

24:                                               ; preds = %16
  ret i32 0
}

declare void @broadcast(ptr noundef) #1

declare void @svf_assert(i1 noundef zeroext) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
