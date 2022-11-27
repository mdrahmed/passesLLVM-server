; ModuleID = 'example.c'
source_filename = "example.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%i\00", align 1, !dbg !0
@.str.1 = private unnamed_addr constant [4 x i8] c"%i\0A\00", align 1, !dbg !7
@.str.2 = private unnamed_addr constant [20 x i8] c"Num is less than 10\00", align 1, !dbg !12

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %argc, ptr noundef %argv) #0 !dbg !27 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca ptr, align 8
  %no = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  store i32 %argc, ptr %argc.addr, align 4
  call void @llvm.dbg.declare(metadata ptr %argc.addr, metadata !35, metadata !DIExpression()), !dbg !36
  store ptr %argv, ptr %argv.addr, align 8
  call void @llvm.dbg.declare(metadata ptr %argv.addr, metadata !37, metadata !DIExpression()), !dbg !38
  call void @llvm.dbg.declare(metadata ptr %no, metadata !39, metadata !DIExpression()), !dbg !40
  %call = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str, ptr noundef %no), !dbg !41
  %0 = load i32, ptr %no, align 4, !dbg !42
  %cmp = icmp sgt i32 %0, 10, !dbg !44
  br i1 %cmp, label %if.then, label %if.else, !dbg !45

if.then:                                          ; preds = %entry
  %1 = load i32, ptr %no, align 4, !dbg !46
  %add = add nsw i32 %1, 2, !dbg !48
  %call1 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %add), !dbg !49
  br label %if.end, !dbg !50

if.else:                                          ; preds = %entry
  %call2 = call i32 (ptr, ...) @printf(ptr noundef @.str.2), !dbg !51
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret i32 0, !dbg !53
}

 26   br i1 %cmp, label %if.then, label %if.else, !dbg !45
; Function Attrs: nocallback nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__isoc99_scanf(ptr noundef, ...) #2

declare i32 @printf(ptr noundef, ...) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind readnone speculatable willreturn }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!17}
!llvm.module.flags = !{!19, !20, !21, !22, !23, !24, !25}
!llvm.ident = !{!26}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 4, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "example.c", directory: "/home/raihan/test", checksumkind: CSK_MD5, checksum: "6235b1ea45fbf32b5643a5526ee8bd2c")
!3 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 24, elements: !5)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !{!6}
!6 = !DISubrange(count: 3)
!7 = !DIGlobalVariableExpression(var: !8, expr: !DIExpression())
!8 = distinct !DIGlobalVariable(scope: null, file: !2, line: 6, type: !9, isLocal: true, isDefinition: true)
!9 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 32, elements: !10)
!10 = !{!11}
!11 = !DISubrange(count: 4)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(scope: null, file: !2, line: 9, type: !14, isLocal: true, isDefinition: true)
!13 = distinct !DIGlobalVariable(scope: null, file: !2, line: 9, type: !14, isLocal: true, isDefinition: true)
!14 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 160, elements: !15)
!15 = !{!16}
!16 = !DISubrange(count: 20)
!17 = distinct !DICompileUnit(language: DW_LANG_C99, file: !2, producer: "clang version 15.0.0 (https://github.com/llvm/llvm-project.git df6afee9859f982fa927dc90398e82d689f19db6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, globals: !18, splitDebugInlining: false, nameTableKind: None)
!18 = !{!0, !7, !12}
!19 = !{i32 7, !"Dwarf Version", i32 5}
!20 = !{i32 2, !"Debug Info Version", i32 3}
!21 = !{i32 1, !"wchar_size", i32 4}
!22 = !{i32 7, !"PIC Level", i32 2}
!23 = !{i32 7, !"PIE Level", i32 2}
!24 = !{i32 7, !"uwtable", i32 2}
!25 = !{i32 7, !"frame-pointer", i32 2}
!26 = !{!"clang version 15.0.0 (https://github.com/llvm/llvm-project.git df6afee9859f982fa927dc90398e82d689f19db6)"}
!27 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 2, type: !28, scopeLine: 2, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !17, retainedNodes: !34)
!28 = !DISubroutineType(types: !29)
!29 = !{!30, !30, !31}
!30 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64)
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64)
!33 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!34 = !{}
!35 = !DILocalVariable(name: "argc", arg: 1, scope: !27, file: !2, line: 2, type: !30)
!36 = !DILocation(line: 2, column: 14, scope: !27)
!37 = !DILocalVariable(name: "argv", arg: 2, scope: !27, file: !2, line: 2, type: !31)
!38 = !DILocation(line: 2, column: 33, scope: !27)
!39 = !DILocalVariable(name: "no", scope: !27, file: !2, line: 3, type: !30)
!40 = !DILocation(line: 3, column: 9, scope: !27)
!41 = !DILocation(line: 4, column: 5, scope: !27)
!42 = !DILocation(line: 5, column: 8, scope: !43)
!43 = distinct !DILexicalBlock(scope: !27, file: !2, line: 5, column: 8)
!44 = !DILocation(line: 5, column: 10, scope: !43)
!45 = !DILocation(line: 5, column: 8, scope: !27)
!46 = !DILocation(line: 6, column: 21, scope: !47)
!47 = distinct !DILexicalBlock(scope: !43, file: !2, line: 5, column: 15)
!48 = !DILocation(line: 6, column: 24, scope: !47)
!49 = !DILocation(line: 6, column: 6, scope: !47)
!50 = !DILocation(line: 7, column: 5, scope: !47)
!51 = !DILocation(line: 9, column: 6, scope: !52)
!52 = distinct !DILexicalBlock(scope: !43, file: !2, line: 8, column: 9)
