; ModuleID = 'sim.o'
source_filename = "sim.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"b greater\00", align 1

; Function Attrs: nofree nounwind uwtable
define dso_local i32 @main() local_unnamed_addr #0 !dbg !9 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = bitcast i32* %1 to i8*, !dbg !17
  call void @llvm.lifetime.start.p0i8(i64 4, i8* nonnull %3), !dbg !17
  call void @llvm.dbg.declare(metadata i32* %1, metadata !14, metadata !DIExpression()), !dbg !18
  %4 = bitcast i32* %2 to i8*, !dbg !17
  call void @llvm.lifetime.start.p0i8(i64 4, i8* nonnull %4), !dbg !17
  call void @llvm.dbg.declare(metadata i32* %2, metadata !16, metadata !DIExpression()), !dbg !19
  store volatile i32 10, i32* %1, align 4, !dbg !20, !tbaa !21
  store volatile i32 20, i32* %2, align 4, !dbg !25, !tbaa !21
  %5 = load volatile i32, i32* %1, align 4, !dbg !26, !tbaa !21
  %6 = load volatile i32, i32* %2, align 4, !dbg !28, !tbaa !21
  %7 = icmp slt i32 %5, %6, !dbg !29
  br i1 %7, label %8, label %10, !dbg !30

8:                                                ; preds = %0
  %9 = tail call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0)), !dbg !31
  br label %10, !dbg !33

10:                                               ; preds = %8, %0
  call void @llvm.lifetime.end.p0i8(i64 4, i8* nonnull %4), !dbg !34
  call void @llvm.lifetime.end.p0i8(i64 4, i8* nonnull %3), !dbg !34
  ret i32 0, !dbg !35
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #2

; Function Attrs: nofree nounwind
declare noundef i32 @printf(i8* nocapture noundef readonly, ...) local_unnamed_addr #3

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #1

attributes #0 = { nofree nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { argmemonly nofree nosync nounwind willreturn }
attributes #2 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #3 = { nofree nounwind "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6, !7}
!llvm.ident = !{!8}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "Ubuntu clang version 14.0.6-++20220622053131+f28c006a5895-1~exp1~20220622173215.157", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "sim.c", directory: "/home/raihan/tutllvm", checksumkind: CSK_MD5, checksum: "5fc2d3344608d62469660288b32a7324")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{!"Ubuntu clang version 14.0.6-++20220622053131+f28c006a5895-1~exp1~20220622173215.157"}
!9 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 3, type: !10, scopeLine: 4, flags: DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !13)
!10 = !DISubroutineType(types: !11)
!11 = !{!12}
!12 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!13 = !{!14, !16}
!14 = !DILocalVariable(name: "a", scope: !9, file: !1, line: 5, type: !15)
!15 = !DIDerivedType(tag: DW_TAG_volatile_type, baseType: !12)
!16 = !DILocalVariable(name: "b", scope: !9, file: !1, line: 5, type: !15)
!17 = !DILocation(line: 5, column: 2, scope: !9)
!18 = !DILocation(line: 5, column: 15, scope: !9)
!19 = !DILocation(line: 5, column: 17, scope: !9)
!20 = !DILocation(line: 6, column: 3, scope: !9)
!21 = !{!22, !22, i64 0}
!22 = !{!"int", !23, i64 0}
!23 = !{!"omnipotent char", !24, i64 0}
!24 = !{!"Simple C/C++ TBAA"}
!25 = !DILocation(line: 7, column: 3, scope: !9)
!26 = !DILocation(line: 8, column: 5, scope: !27)
!27 = distinct !DILexicalBlock(scope: !9, file: !1, line: 8, column: 5)
!28 = !DILocation(line: 8, column: 9, scope: !27)
!29 = !DILocation(line: 8, column: 7, scope: !27)
!30 = !DILocation(line: 8, column: 5, scope: !9)
!31 = !DILocation(line: 9, column: 3, scope: !32)
!32 = distinct !DILexicalBlock(scope: !27, file: !1, line: 8, column: 11)
!33 = !DILocation(line: 10, column: 2, scope: !32)
!34 = !DILocation(line: 12, column: 1, scope: !9)
!35 = !DILocation(line: 11, column: 2, scope: !9)
