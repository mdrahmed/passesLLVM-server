; ModuleID = 'basic_block.c'
source_filename = "basic_block.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  %e = alloca i32, align 4
  %f = alloca i32, align 4
  %g = alloca i32, align 4
  %h = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %k = alloca i32, align 4
  %l = alloca i32, align 4
  %m = alloca i32, align 4
  %n = alloca i32, align 4
  %o = alloca i32, align 4
  %p = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  %0 = load i32, ptr %m, align 4
  %1 = load i32, ptr %n, align 4
  %cmp = icmp sgt i32 %0, %1
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %2 = load i32, ptr %a, align 4
  store i32 %2, ptr %g, align 4
  %3 = load i32, ptr %b, align 4
  store i32 %3, ptr %h, align 4
  %4 = load i32, ptr %a, align 4
  %5 = load i32, ptr %b, align 4
  %add = add nsw i32 %4, %5
  store i32 %add, ptr %c, align 4
  %6 = load i32, ptr %c, align 4
  %7 = load i32, ptr %h, align 4
  %add1 = add nsw i32 %6, %7
  store i32 %add1, ptr %e, align 4
  br label %if.end

if.else:                                          ; preds = %entry
  %8 = load i32, ptr %a, align 4
  store i32 %8, ptr %g, align 4
  %9 = load i32, ptr %b, align 4
  store i32 %9, ptr %h, align 4
  %10 = load i32, ptr %a, align 4
  %11 = load i32, ptr %b, align 4
  %add2 = add nsw i32 %10, %11
  store i32 %add2, ptr %c, align 4
  %12 = load i32, ptr %c, align 4
  %13 = load i32, ptr %h, align 4
  %add3 = add nsw i32 %12, %13
  store i32 %add3, ptr %e, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %14 = load i32, ptr %g, align 4
  %15 = load i32, ptr %h, align 4
  %add4 = add nsw i32 %14, %15
  store i32 %add4, ptr %o, align 4
  %16 = load i32, ptr %c, align 4
  %17 = load i32, ptr %e, align 4
  %add5 = add nsw i32 %16, %17
  store i32 %add5, ptr %p, align 4
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 15.0.0 (https://github.com/llvm/llvm-project.git df6afee9859f982fa927dc90398e82d689f19db6)"}
