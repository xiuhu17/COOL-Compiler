; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -S -loop-vectorize -mtriple=x86_64-- -mattr=+sse2   | FileCheck %s --check-prefix=SSE2
; RUN: opt < %s -S -loop-vectorize -mtriple=x86_64-- -mattr=+sse4.1 | FileCheck %s --check-prefix=SSE41
; RUN: opt < %s -S -loop-vectorize -mtriple=x86_64-- -mattr=+avx    | FileCheck %s --check-prefix=AVX1
; RUN: opt < %s -S -loop-vectorize -mtriple=x86_64-- -mattr=+avx2   | FileCheck %s --check-prefix=AVX2
; RUN: opt < %s -S -loop-vectorize -mtriple=x86_64-- -mcpu=slm      | FileCheck %s --check-prefix=SSE2

define void @test_muladd(i32* noalias nocapture %d1, i16* noalias nocapture readonly %s1, i16* noalias nocapture readonly %s2, i32 %n) {
; SSE2-LABEL: @test_muladd(
; SSE2-NEXT:  entry:
; SSE2-NEXT:    [[CMP30:%.*]] = icmp sgt i32 [[N:%.*]], 0
; SSE2-NEXT:    br i1 [[CMP30]], label [[FOR_BODY_PREHEADER:%.*]], label [[FOR_END:%.*]]
; SSE2:       for.body.preheader:
; SSE2-NEXT:    [[WIDE_TRIP_COUNT:%.*]] = zext i32 [[N]] to i64
; SSE2-NEXT:    [[MIN_ITERS_CHECK:%.*]] = icmp ult i64 [[WIDE_TRIP_COUNT]], 4
; SSE2-NEXT:    br i1 [[MIN_ITERS_CHECK]], label [[SCALAR_PH:%.*]], label [[VECTOR_PH:%.*]]
; SSE2:       vector.ph:
; SSE2-NEXT:    [[N_MOD_VF:%.*]] = urem i64 [[WIDE_TRIP_COUNT]], 4
; SSE2-NEXT:    [[N_VEC:%.*]] = sub i64 [[WIDE_TRIP_COUNT]], [[N_MOD_VF]]
; SSE2-NEXT:    br label [[VECTOR_BODY:%.*]]
; SSE2:       vector.body:
; SSE2-NEXT:    [[INDEX:%.*]] = phi i64 [ 0, [[VECTOR_PH]] ], [ [[INDEX_NEXT:%.*]], [[VECTOR_BODY]] ]
; SSE2-NEXT:    [[TMP0:%.*]] = add i64 [[INDEX]], 0
; SSE2-NEXT:    [[TMP1:%.*]] = shl nuw nsw i64 [[TMP0]], 1
; SSE2-NEXT:    [[TMP2:%.*]] = getelementptr inbounds i16, i16* [[S1:%.*]], i64 [[TMP1]]
; SSE2-NEXT:    [[TMP3:%.*]] = getelementptr inbounds i16, i16* [[TMP2]], i32 0
; SSE2-NEXT:    [[TMP4:%.*]] = bitcast i16* [[TMP3]] to <8 x i16>*
; SSE2-NEXT:    [[WIDE_VEC:%.*]] = load <8 x i16>, <8 x i16>* [[TMP4]], align 2
; SSE2-NEXT:    [[STRIDED_VEC:%.*]] = shufflevector <8 x i16> [[WIDE_VEC]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; SSE2-NEXT:    [[STRIDED_VEC1:%.*]] = shufflevector <8 x i16> [[WIDE_VEC]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; SSE2-NEXT:    [[TMP5:%.*]] = sext <4 x i16> [[STRIDED_VEC]] to <4 x i32>
; SSE2-NEXT:    [[TMP6:%.*]] = getelementptr inbounds i16, i16* [[S2:%.*]], i64 [[TMP1]]
; SSE2-NEXT:    [[TMP7:%.*]] = getelementptr inbounds i16, i16* [[TMP6]], i32 0
; SSE2-NEXT:    [[TMP8:%.*]] = bitcast i16* [[TMP7]] to <8 x i16>*
; SSE2-NEXT:    [[WIDE_VEC2:%.*]] = load <8 x i16>, <8 x i16>* [[TMP8]], align 2
; SSE2-NEXT:    [[STRIDED_VEC3:%.*]] = shufflevector <8 x i16> [[WIDE_VEC2]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; SSE2-NEXT:    [[STRIDED_VEC4:%.*]] = shufflevector <8 x i16> [[WIDE_VEC2]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; SSE2-NEXT:    [[TMP9:%.*]] = sext <4 x i16> [[STRIDED_VEC3]] to <4 x i32>
; SSE2-NEXT:    [[TMP10:%.*]] = mul nsw <4 x i32> [[TMP9]], [[TMP5]]
; SSE2-NEXT:    [[TMP13:%.*]] = sext <4 x i16> [[STRIDED_VEC1]] to <4 x i32>
; SSE2-NEXT:    [[TMP15:%.*]] = sext <4 x i16> [[STRIDED_VEC4]] to <4 x i32>
; SSE2-NEXT:    [[TMP16:%.*]] = mul nsw <4 x i32> [[TMP15]], [[TMP13]]
; SSE2-NEXT:    [[TMP17:%.*]] = add nsw <4 x i32> [[TMP16]], [[TMP10]]
; SSE2-NEXT:    [[TMP18:%.*]] = getelementptr inbounds i32, i32* [[D1:%.*]], i64 [[TMP0]]
; SSE2-NEXT:    [[TMP19:%.*]] = getelementptr inbounds i32, i32* [[TMP18]], i32 0
; SSE2-NEXT:    [[TMP20:%.*]] = bitcast i32* [[TMP19]] to <4 x i32>*
; SSE2-NEXT:    store <4 x i32> [[TMP17]], <4 x i32>* [[TMP20]], align 4
; SSE2-NEXT:    [[INDEX_NEXT]] = add nuw i64 [[INDEX]], 4
; SSE2-NEXT:    [[TMP21:%.*]] = icmp eq i64 [[INDEX_NEXT]], [[N_VEC]]
; SSE2-NEXT:    br i1 [[TMP21]], label [[MIDDLE_BLOCK:%.*]], label [[VECTOR_BODY]], !llvm.loop [[LOOP0:![0-9]+]]
; SSE2:       middle.block:
; SSE2-NEXT:    [[CMP_N:%.*]] = icmp eq i64 [[WIDE_TRIP_COUNT]], [[N_VEC]]
; SSE2-NEXT:    br i1 [[CMP_N]], label [[FOR_END_LOOPEXIT:%.*]], label [[SCALAR_PH]]
; SSE2:       scalar.ph:
; SSE2-NEXT:    [[BC_RESUME_VAL:%.*]] = phi i64 [ [[N_VEC]], [[MIDDLE_BLOCK]] ], [ 0, [[FOR_BODY_PREHEADER]] ]
; SSE2-NEXT:    br label [[FOR_BODY:%.*]]
; SSE2:       for.body:
; SSE2-NEXT:    [[INDVARS_IV:%.*]] = phi i64 [ [[BC_RESUME_VAL]], [[SCALAR_PH]] ], [ [[INDVARS_IV_NEXT:%.*]], [[FOR_BODY]] ]
; SSE2-NEXT:    [[TMP22:%.*]] = shl nuw nsw i64 [[INDVARS_IV]], 1
; SSE2-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP22]]
; SSE2-NEXT:    [[TMP23:%.*]] = load i16, i16* [[ARRAYIDX]], align 2
; SSE2-NEXT:    [[CONV:%.*]] = sext i16 [[TMP23]] to i32
; SSE2-NEXT:    [[ARRAYIDX4:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP22]]
; SSE2-NEXT:    [[TMP24:%.*]] = load i16, i16* [[ARRAYIDX4]], align 2
; SSE2-NEXT:    [[CONV5:%.*]] = sext i16 [[TMP24]] to i32
; SSE2-NEXT:    [[MUL6:%.*]] = mul nsw i32 [[CONV5]], [[CONV]]
; SSE2-NEXT:    [[TMP25:%.*]] = or i64 [[TMP22]], 1
; SSE2-NEXT:    [[ARRAYIDX10:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP25]]
; SSE2-NEXT:    [[TMP26:%.*]] = load i16, i16* [[ARRAYIDX10]], align 2
; SSE2-NEXT:    [[CONV11:%.*]] = sext i16 [[TMP26]] to i32
; SSE2-NEXT:    [[ARRAYIDX15:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP25]]
; SSE2-NEXT:    [[TMP27:%.*]] = load i16, i16* [[ARRAYIDX15]], align 2
; SSE2-NEXT:    [[CONV16:%.*]] = sext i16 [[TMP27]] to i32
; SSE2-NEXT:    [[MUL17:%.*]] = mul nsw i32 [[CONV16]], [[CONV11]]
; SSE2-NEXT:    [[ADD18:%.*]] = add nsw i32 [[MUL17]], [[MUL6]]
; SSE2-NEXT:    [[ARRAYIDX20:%.*]] = getelementptr inbounds i32, i32* [[D1]], i64 [[INDVARS_IV]]
; SSE2-NEXT:    store i32 [[ADD18]], i32* [[ARRAYIDX20]], align 4
; SSE2-NEXT:    [[INDVARS_IV_NEXT]] = add nuw nsw i64 [[INDVARS_IV]], 1
; SSE2-NEXT:    [[EXITCOND_NOT:%.*]] = icmp eq i64 [[INDVARS_IV_NEXT]], [[WIDE_TRIP_COUNT]]
; SSE2-NEXT:    br i1 [[EXITCOND_NOT]], label [[FOR_END_LOOPEXIT]], label [[FOR_BODY]], !llvm.loop [[LOOP2:![0-9]+]]
; SSE2:       for.end.loopexit:
; SSE2-NEXT:    br label [[FOR_END]]
; SSE2:       for.end:
; SSE2-NEXT:    ret void
;
; SSE41-LABEL: @test_muladd(
; SSE41-NEXT:  entry:
; SSE41-NEXT:    [[CMP30:%.*]] = icmp sgt i32 [[N:%.*]], 0
; SSE41-NEXT:    br i1 [[CMP30]], label [[FOR_BODY_PREHEADER:%.*]], label [[FOR_END:%.*]]
; SSE41:       for.body.preheader:
; SSE41-NEXT:    [[WIDE_TRIP_COUNT:%.*]] = zext i32 [[N]] to i64
; SSE41-NEXT:    [[MIN_ITERS_CHECK:%.*]] = icmp ult i64 [[WIDE_TRIP_COUNT]], 8
; SSE41-NEXT:    br i1 [[MIN_ITERS_CHECK]], label [[SCALAR_PH:%.*]], label [[VECTOR_PH:%.*]]
; SSE41:       vector.ph:
; SSE41-NEXT:    [[N_MOD_VF:%.*]] = urem i64 [[WIDE_TRIP_COUNT]], 8
; SSE41-NEXT:    [[N_VEC:%.*]] = sub i64 [[WIDE_TRIP_COUNT]], [[N_MOD_VF]]
; SSE41-NEXT:    br label [[VECTOR_BODY:%.*]]
; SSE41:       vector.body:
; SSE41-NEXT:    [[INDEX:%.*]] = phi i64 [ 0, [[VECTOR_PH]] ], [ [[INDEX_NEXT:%.*]], [[VECTOR_BODY]] ]
; SSE41-NEXT:    [[TMP0:%.*]] = add i64 [[INDEX]], 0
; SSE41-NEXT:    [[TMP1:%.*]] = add i64 [[INDEX]], 4
; SSE41-NEXT:    [[TMP2:%.*]] = shl nuw nsw i64 [[TMP0]], 1
; SSE41-NEXT:    [[TMP3:%.*]] = shl nuw nsw i64 [[TMP1]], 1
; SSE41-NEXT:    [[TMP4:%.*]] = getelementptr inbounds i16, i16* [[S1:%.*]], i64 [[TMP2]]
; SSE41-NEXT:    [[TMP5:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP3]]
; SSE41-NEXT:    [[TMP6:%.*]] = getelementptr inbounds i16, i16* [[TMP4]], i32 0
; SSE41-NEXT:    [[TMP7:%.*]] = bitcast i16* [[TMP6]] to <8 x i16>*
; SSE41-NEXT:    [[TMP8:%.*]] = getelementptr inbounds i16, i16* [[TMP5]], i32 0
; SSE41-NEXT:    [[TMP9:%.*]] = bitcast i16* [[TMP8]] to <8 x i16>*
; SSE41-NEXT:    [[WIDE_VEC:%.*]] = load <8 x i16>, <8 x i16>* [[TMP7]], align 2
; SSE41-NEXT:    [[WIDE_VEC1:%.*]] = load <8 x i16>, <8 x i16>* [[TMP9]], align 2
; SSE41-NEXT:    [[STRIDED_VEC:%.*]] = shufflevector <8 x i16> [[WIDE_VEC]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; SSE41-NEXT:    [[STRIDED_VEC2:%.*]] = shufflevector <8 x i16> [[WIDE_VEC1]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; SSE41-NEXT:    [[STRIDED_VEC3:%.*]] = shufflevector <8 x i16> [[WIDE_VEC]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; SSE41-NEXT:    [[STRIDED_VEC4:%.*]] = shufflevector <8 x i16> [[WIDE_VEC1]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; SSE41-NEXT:    [[TMP10:%.*]] = sext <4 x i16> [[STRIDED_VEC]] to <4 x i32>
; SSE41-NEXT:    [[TMP11:%.*]] = sext <4 x i16> [[STRIDED_VEC2]] to <4 x i32>
; SSE41-NEXT:    [[TMP12:%.*]] = getelementptr inbounds i16, i16* [[S2:%.*]], i64 [[TMP2]]
; SSE41-NEXT:    [[TMP13:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP3]]
; SSE41-NEXT:    [[TMP14:%.*]] = getelementptr inbounds i16, i16* [[TMP12]], i32 0
; SSE41-NEXT:    [[TMP15:%.*]] = bitcast i16* [[TMP14]] to <8 x i16>*
; SSE41-NEXT:    [[TMP16:%.*]] = getelementptr inbounds i16, i16* [[TMP13]], i32 0
; SSE41-NEXT:    [[TMP17:%.*]] = bitcast i16* [[TMP16]] to <8 x i16>*
; SSE41-NEXT:    [[WIDE_VEC5:%.*]] = load <8 x i16>, <8 x i16>* [[TMP15]], align 2
; SSE41-NEXT:    [[WIDE_VEC6:%.*]] = load <8 x i16>, <8 x i16>* [[TMP17]], align 2
; SSE41-NEXT:    [[STRIDED_VEC7:%.*]] = shufflevector <8 x i16> [[WIDE_VEC5]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; SSE41-NEXT:    [[STRIDED_VEC8:%.*]] = shufflevector <8 x i16> [[WIDE_VEC6]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; SSE41-NEXT:    [[STRIDED_VEC9:%.*]] = shufflevector <8 x i16> [[WIDE_VEC5]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; SSE41-NEXT:    [[STRIDED_VEC10:%.*]] = shufflevector <8 x i16> [[WIDE_VEC6]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; SSE41-NEXT:    [[TMP18:%.*]] = sext <4 x i16> [[STRIDED_VEC7]] to <4 x i32>
; SSE41-NEXT:    [[TMP19:%.*]] = sext <4 x i16> [[STRIDED_VEC8]] to <4 x i32>
; SSE41-NEXT:    [[TMP20:%.*]] = mul nsw <4 x i32> [[TMP18]], [[TMP10]]
; SSE41-NEXT:    [[TMP21:%.*]] = mul nsw <4 x i32> [[TMP19]], [[TMP11]]
; SSE41-NEXT:    [[TMP26:%.*]] = sext <4 x i16> [[STRIDED_VEC3]] to <4 x i32>
; SSE41-NEXT:    [[TMP27:%.*]] = sext <4 x i16> [[STRIDED_VEC4]] to <4 x i32>
; SSE41-NEXT:    [[TMP30:%.*]] = sext <4 x i16> [[STRIDED_VEC9]] to <4 x i32>
; SSE41-NEXT:    [[TMP31:%.*]] = sext <4 x i16> [[STRIDED_VEC10]] to <4 x i32>
; SSE41-NEXT:    [[TMP32:%.*]] = mul nsw <4 x i32> [[TMP30]], [[TMP26]]
; SSE41-NEXT:    [[TMP33:%.*]] = mul nsw <4 x i32> [[TMP31]], [[TMP27]]
; SSE41-NEXT:    [[TMP34:%.*]] = add nsw <4 x i32> [[TMP32]], [[TMP20]]
; SSE41-NEXT:    [[TMP35:%.*]] = add nsw <4 x i32> [[TMP33]], [[TMP21]]
; SSE41-NEXT:    [[TMP36:%.*]] = getelementptr inbounds i32, i32* [[D1:%.*]], i64 [[TMP0]]
; SSE41-NEXT:    [[TMP37:%.*]] = getelementptr inbounds i32, i32* [[D1]], i64 [[TMP1]]
; SSE41-NEXT:    [[TMP38:%.*]] = getelementptr inbounds i32, i32* [[TMP36]], i32 0
; SSE41-NEXT:    [[TMP39:%.*]] = bitcast i32* [[TMP38]] to <4 x i32>*
; SSE41-NEXT:    store <4 x i32> [[TMP34]], <4 x i32>* [[TMP39]], align 4
; SSE41-NEXT:    [[TMP40:%.*]] = getelementptr inbounds i32, i32* [[TMP36]], i32 4
; SSE41-NEXT:    [[TMP41:%.*]] = bitcast i32* [[TMP40]] to <4 x i32>*
; SSE41-NEXT:    store <4 x i32> [[TMP35]], <4 x i32>* [[TMP41]], align 4
; SSE41-NEXT:    [[INDEX_NEXT]] = add nuw i64 [[INDEX]], 8
; SSE41-NEXT:    [[TMP42:%.*]] = icmp eq i64 [[INDEX_NEXT]], [[N_VEC]]
; SSE41-NEXT:    br i1 [[TMP42]], label [[MIDDLE_BLOCK:%.*]], label [[VECTOR_BODY]], !llvm.loop [[LOOP0:![0-9]+]]
; SSE41:       middle.block:
; SSE41-NEXT:    [[CMP_N:%.*]] = icmp eq i64 [[WIDE_TRIP_COUNT]], [[N_VEC]]
; SSE41-NEXT:    br i1 [[CMP_N]], label [[FOR_END_LOOPEXIT:%.*]], label [[SCALAR_PH]]
; SSE41:       scalar.ph:
; SSE41-NEXT:    [[BC_RESUME_VAL:%.*]] = phi i64 [ [[N_VEC]], [[MIDDLE_BLOCK]] ], [ 0, [[FOR_BODY_PREHEADER]] ]
; SSE41-NEXT:    br label [[FOR_BODY:%.*]]
; SSE41:       for.body:
; SSE41-NEXT:    [[INDVARS_IV:%.*]] = phi i64 [ [[BC_RESUME_VAL]], [[SCALAR_PH]] ], [ [[INDVARS_IV_NEXT:%.*]], [[FOR_BODY]] ]
; SSE41-NEXT:    [[TMP43:%.*]] = shl nuw nsw i64 [[INDVARS_IV]], 1
; SSE41-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP43]]
; SSE41-NEXT:    [[TMP44:%.*]] = load i16, i16* [[ARRAYIDX]], align 2
; SSE41-NEXT:    [[CONV:%.*]] = sext i16 [[TMP44]] to i32
; SSE41-NEXT:    [[ARRAYIDX4:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP43]]
; SSE41-NEXT:    [[TMP45:%.*]] = load i16, i16* [[ARRAYIDX4]], align 2
; SSE41-NEXT:    [[CONV5:%.*]] = sext i16 [[TMP45]] to i32
; SSE41-NEXT:    [[MUL6:%.*]] = mul nsw i32 [[CONV5]], [[CONV]]
; SSE41-NEXT:    [[TMP46:%.*]] = or i64 [[TMP43]], 1
; SSE41-NEXT:    [[ARRAYIDX10:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP46]]
; SSE41-NEXT:    [[TMP47:%.*]] = load i16, i16* [[ARRAYIDX10]], align 2
; SSE41-NEXT:    [[CONV11:%.*]] = sext i16 [[TMP47]] to i32
; SSE41-NEXT:    [[ARRAYIDX15:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP46]]
; SSE41-NEXT:    [[TMP48:%.*]] = load i16, i16* [[ARRAYIDX15]], align 2
; SSE41-NEXT:    [[CONV16:%.*]] = sext i16 [[TMP48]] to i32
; SSE41-NEXT:    [[MUL17:%.*]] = mul nsw i32 [[CONV16]], [[CONV11]]
; SSE41-NEXT:    [[ADD18:%.*]] = add nsw i32 [[MUL17]], [[MUL6]]
; SSE41-NEXT:    [[ARRAYIDX20:%.*]] = getelementptr inbounds i32, i32* [[D1]], i64 [[INDVARS_IV]]
; SSE41-NEXT:    store i32 [[ADD18]], i32* [[ARRAYIDX20]], align 4
; SSE41-NEXT:    [[INDVARS_IV_NEXT]] = add nuw nsw i64 [[INDVARS_IV]], 1
; SSE41-NEXT:    [[EXITCOND_NOT:%.*]] = icmp eq i64 [[INDVARS_IV_NEXT]], [[WIDE_TRIP_COUNT]]
; SSE41-NEXT:    br i1 [[EXITCOND_NOT]], label [[FOR_END_LOOPEXIT]], label [[FOR_BODY]], !llvm.loop [[LOOP2:![0-9]+]]
; SSE41:       for.end.loopexit:
; SSE41-NEXT:    br label [[FOR_END]]
; SSE41:       for.end:
; SSE41-NEXT:    ret void
;
; AVX1-LABEL: @test_muladd(
; AVX1-NEXT:  entry:
; AVX1-NEXT:    [[CMP30:%.*]] = icmp sgt i32 [[N:%.*]], 0
; AVX1-NEXT:    br i1 [[CMP30]], label [[FOR_BODY_PREHEADER:%.*]], label [[FOR_END:%.*]]
; AVX1:       for.body.preheader:
; AVX1-NEXT:    [[WIDE_TRIP_COUNT:%.*]] = zext i32 [[N]] to i64
; AVX1-NEXT:    [[MIN_ITERS_CHECK:%.*]] = icmp ult i64 [[WIDE_TRIP_COUNT]], 16
; AVX1-NEXT:    br i1 [[MIN_ITERS_CHECK]], label [[SCALAR_PH:%.*]], label [[VECTOR_PH:%.*]]
; AVX1:       vector.ph:
; AVX1-NEXT:    [[N_MOD_VF:%.*]] = urem i64 [[WIDE_TRIP_COUNT]], 16
; AVX1-NEXT:    [[N_VEC:%.*]] = sub i64 [[WIDE_TRIP_COUNT]], [[N_MOD_VF]]
; AVX1-NEXT:    br label [[VECTOR_BODY:%.*]]
; AVX1:       vector.body:
; AVX1-NEXT:    [[INDEX:%.*]] = phi i64 [ 0, [[VECTOR_PH]] ], [ [[INDEX_NEXT:%.*]], [[VECTOR_BODY]] ]
; AVX1-NEXT:    [[TMP0:%.*]] = add i64 [[INDEX]], 0
; AVX1-NEXT:    [[TMP1:%.*]] = add i64 [[INDEX]], 4
; AVX1-NEXT:    [[TMP2:%.*]] = add i64 [[INDEX]], 8
; AVX1-NEXT:    [[TMP3:%.*]] = add i64 [[INDEX]], 12
; AVX1-NEXT:    [[TMP4:%.*]] = shl nuw nsw i64 [[TMP0]], 1
; AVX1-NEXT:    [[TMP5:%.*]] = shl nuw nsw i64 [[TMP1]], 1
; AVX1-NEXT:    [[TMP6:%.*]] = shl nuw nsw i64 [[TMP2]], 1
; AVX1-NEXT:    [[TMP7:%.*]] = shl nuw nsw i64 [[TMP3]], 1
; AVX1-NEXT:    [[TMP8:%.*]] = getelementptr inbounds i16, i16* [[S1:%.*]], i64 [[TMP4]]
; AVX1-NEXT:    [[TMP9:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP5]]
; AVX1-NEXT:    [[TMP10:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP6]]
; AVX1-NEXT:    [[TMP11:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP7]]
; AVX1-NEXT:    [[TMP12:%.*]] = getelementptr inbounds i16, i16* [[TMP8]], i32 0
; AVX1-NEXT:    [[TMP13:%.*]] = bitcast i16* [[TMP12]] to <8 x i16>*
; AVX1-NEXT:    [[TMP14:%.*]] = getelementptr inbounds i16, i16* [[TMP9]], i32 0
; AVX1-NEXT:    [[TMP15:%.*]] = bitcast i16* [[TMP14]] to <8 x i16>*
; AVX1-NEXT:    [[TMP16:%.*]] = getelementptr inbounds i16, i16* [[TMP10]], i32 0
; AVX1-NEXT:    [[TMP17:%.*]] = bitcast i16* [[TMP16]] to <8 x i16>*
; AVX1-NEXT:    [[TMP18:%.*]] = getelementptr inbounds i16, i16* [[TMP11]], i32 0
; AVX1-NEXT:    [[TMP19:%.*]] = bitcast i16* [[TMP18]] to <8 x i16>*
; AVX1-NEXT:    [[WIDE_VEC:%.*]] = load <8 x i16>, <8 x i16>* [[TMP13]], align 2
; AVX1-NEXT:    [[WIDE_VEC1:%.*]] = load <8 x i16>, <8 x i16>* [[TMP15]], align 2
; AVX1-NEXT:    [[WIDE_VEC2:%.*]] = load <8 x i16>, <8 x i16>* [[TMP17]], align 2
; AVX1-NEXT:    [[WIDE_VEC3:%.*]] = load <8 x i16>, <8 x i16>* [[TMP19]], align 2
; AVX1-NEXT:    [[STRIDED_VEC:%.*]] = shufflevector <8 x i16> [[WIDE_VEC]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; AVX1-NEXT:    [[STRIDED_VEC4:%.*]] = shufflevector <8 x i16> [[WIDE_VEC1]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; AVX1-NEXT:    [[STRIDED_VEC5:%.*]] = shufflevector <8 x i16> [[WIDE_VEC2]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; AVX1-NEXT:    [[STRIDED_VEC6:%.*]] = shufflevector <8 x i16> [[WIDE_VEC3]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; AVX1-NEXT:    [[STRIDED_VEC7:%.*]] = shufflevector <8 x i16> [[WIDE_VEC]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; AVX1-NEXT:    [[STRIDED_VEC8:%.*]] = shufflevector <8 x i16> [[WIDE_VEC1]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; AVX1-NEXT:    [[STRIDED_VEC9:%.*]] = shufflevector <8 x i16> [[WIDE_VEC2]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; AVX1-NEXT:    [[STRIDED_VEC10:%.*]] = shufflevector <8 x i16> [[WIDE_VEC3]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; AVX1-NEXT:    [[TMP20:%.*]] = sext <4 x i16> [[STRIDED_VEC]] to <4 x i32>
; AVX1-NEXT:    [[TMP21:%.*]] = sext <4 x i16> [[STRIDED_VEC4]] to <4 x i32>
; AVX1-NEXT:    [[TMP22:%.*]] = sext <4 x i16> [[STRIDED_VEC5]] to <4 x i32>
; AVX1-NEXT:    [[TMP23:%.*]] = sext <4 x i16> [[STRIDED_VEC6]] to <4 x i32>
; AVX1-NEXT:    [[TMP24:%.*]] = getelementptr inbounds i16, i16* [[S2:%.*]], i64 [[TMP4]]
; AVX1-NEXT:    [[TMP25:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP5]]
; AVX1-NEXT:    [[TMP26:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP6]]
; AVX1-NEXT:    [[TMP27:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP7]]
; AVX1-NEXT:    [[TMP28:%.*]] = getelementptr inbounds i16, i16* [[TMP24]], i32 0
; AVX1-NEXT:    [[TMP29:%.*]] = bitcast i16* [[TMP28]] to <8 x i16>*
; AVX1-NEXT:    [[TMP30:%.*]] = getelementptr inbounds i16, i16* [[TMP25]], i32 0
; AVX1-NEXT:    [[TMP31:%.*]] = bitcast i16* [[TMP30]] to <8 x i16>*
; AVX1-NEXT:    [[TMP32:%.*]] = getelementptr inbounds i16, i16* [[TMP26]], i32 0
; AVX1-NEXT:    [[TMP33:%.*]] = bitcast i16* [[TMP32]] to <8 x i16>*
; AVX1-NEXT:    [[TMP34:%.*]] = getelementptr inbounds i16, i16* [[TMP27]], i32 0
; AVX1-NEXT:    [[TMP35:%.*]] = bitcast i16* [[TMP34]] to <8 x i16>*
; AVX1-NEXT:    [[WIDE_VEC11:%.*]] = load <8 x i16>, <8 x i16>* [[TMP29]], align 2
; AVX1-NEXT:    [[WIDE_VEC12:%.*]] = load <8 x i16>, <8 x i16>* [[TMP31]], align 2
; AVX1-NEXT:    [[WIDE_VEC13:%.*]] = load <8 x i16>, <8 x i16>* [[TMP33]], align 2
; AVX1-NEXT:    [[WIDE_VEC14:%.*]] = load <8 x i16>, <8 x i16>* [[TMP35]], align 2
; AVX1-NEXT:    [[STRIDED_VEC15:%.*]] = shufflevector <8 x i16> [[WIDE_VEC11]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; AVX1-NEXT:    [[STRIDED_VEC16:%.*]] = shufflevector <8 x i16> [[WIDE_VEC12]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; AVX1-NEXT:    [[STRIDED_VEC17:%.*]] = shufflevector <8 x i16> [[WIDE_VEC13]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; AVX1-NEXT:    [[STRIDED_VEC18:%.*]] = shufflevector <8 x i16> [[WIDE_VEC14]], <8 x i16> poison, <4 x i32> <i32 0, i32 2, i32 4, i32 6>
; AVX1-NEXT:    [[STRIDED_VEC19:%.*]] = shufflevector <8 x i16> [[WIDE_VEC11]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; AVX1-NEXT:    [[STRIDED_VEC20:%.*]] = shufflevector <8 x i16> [[WIDE_VEC12]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; AVX1-NEXT:    [[STRIDED_VEC21:%.*]] = shufflevector <8 x i16> [[WIDE_VEC13]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; AVX1-NEXT:    [[STRIDED_VEC22:%.*]] = shufflevector <8 x i16> [[WIDE_VEC14]], <8 x i16> poison, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
; AVX1-NEXT:    [[TMP36:%.*]] = sext <4 x i16> [[STRIDED_VEC15]] to <4 x i32>
; AVX1-NEXT:    [[TMP37:%.*]] = sext <4 x i16> [[STRIDED_VEC16]] to <4 x i32>
; AVX1-NEXT:    [[TMP38:%.*]] = sext <4 x i16> [[STRIDED_VEC17]] to <4 x i32>
; AVX1-NEXT:    [[TMP39:%.*]] = sext <4 x i16> [[STRIDED_VEC18]] to <4 x i32>
; AVX1-NEXT:    [[TMP40:%.*]] = mul nsw <4 x i32> [[TMP36]], [[TMP20]]
; AVX1-NEXT:    [[TMP41:%.*]] = mul nsw <4 x i32> [[TMP37]], [[TMP21]]
; AVX1-NEXT:    [[TMP42:%.*]] = mul nsw <4 x i32> [[TMP38]], [[TMP22]]
; AVX1-NEXT:    [[TMP43:%.*]] = mul nsw <4 x i32> [[TMP39]], [[TMP23]]
; AVX1-NEXT:    [[TMP52:%.*]] = sext <4 x i16> [[STRIDED_VEC7]] to <4 x i32>
; AVX1-NEXT:    [[TMP53:%.*]] = sext <4 x i16> [[STRIDED_VEC8]] to <4 x i32>
; AVX1-NEXT:    [[TMP54:%.*]] = sext <4 x i16> [[STRIDED_VEC9]] to <4 x i32>
; AVX1-NEXT:    [[TMP55:%.*]] = sext <4 x i16> [[STRIDED_VEC10]] to <4 x i32>
; AVX1-NEXT:    [[TMP60:%.*]] = sext <4 x i16> [[STRIDED_VEC19]] to <4 x i32>
; AVX1-NEXT:    [[TMP61:%.*]] = sext <4 x i16> [[STRIDED_VEC20]] to <4 x i32>
; AVX1-NEXT:    [[TMP62:%.*]] = sext <4 x i16> [[STRIDED_VEC21]] to <4 x i32>
; AVX1-NEXT:    [[TMP63:%.*]] = sext <4 x i16> [[STRIDED_VEC22]] to <4 x i32>
; AVX1-NEXT:    [[TMP64:%.*]] = mul nsw <4 x i32> [[TMP60]], [[TMP52]]
; AVX1-NEXT:    [[TMP65:%.*]] = mul nsw <4 x i32> [[TMP61]], [[TMP53]]
; AVX1-NEXT:    [[TMP66:%.*]] = mul nsw <4 x i32> [[TMP62]], [[TMP54]]
; AVX1-NEXT:    [[TMP67:%.*]] = mul nsw <4 x i32> [[TMP63]], [[TMP55]]
; AVX1-NEXT:    [[TMP68:%.*]] = add nsw <4 x i32> [[TMP64]], [[TMP40]]
; AVX1-NEXT:    [[TMP69:%.*]] = add nsw <4 x i32> [[TMP65]], [[TMP41]]
; AVX1-NEXT:    [[TMP70:%.*]] = add nsw <4 x i32> [[TMP66]], [[TMP42]]
; AVX1-NEXT:    [[TMP71:%.*]] = add nsw <4 x i32> [[TMP67]], [[TMP43]]
; AVX1-NEXT:    [[TMP72:%.*]] = getelementptr inbounds i32, i32* [[D1:%.*]], i64 [[TMP0]]
; AVX1-NEXT:    [[TMP73:%.*]] = getelementptr inbounds i32, i32* [[D1]], i64 [[TMP1]]
; AVX1-NEXT:    [[TMP74:%.*]] = getelementptr inbounds i32, i32* [[D1]], i64 [[TMP2]]
; AVX1-NEXT:    [[TMP75:%.*]] = getelementptr inbounds i32, i32* [[D1]], i64 [[TMP3]]
; AVX1-NEXT:    [[TMP76:%.*]] = getelementptr inbounds i32, i32* [[TMP72]], i32 0
; AVX1-NEXT:    [[TMP77:%.*]] = bitcast i32* [[TMP76]] to <4 x i32>*
; AVX1-NEXT:    store <4 x i32> [[TMP68]], <4 x i32>* [[TMP77]], align 4
; AVX1-NEXT:    [[TMP78:%.*]] = getelementptr inbounds i32, i32* [[TMP72]], i32 4
; AVX1-NEXT:    [[TMP79:%.*]] = bitcast i32* [[TMP78]] to <4 x i32>*
; AVX1-NEXT:    store <4 x i32> [[TMP69]], <4 x i32>* [[TMP79]], align 4
; AVX1-NEXT:    [[TMP80:%.*]] = getelementptr inbounds i32, i32* [[TMP72]], i32 8
; AVX1-NEXT:    [[TMP81:%.*]] = bitcast i32* [[TMP80]] to <4 x i32>*
; AVX1-NEXT:    store <4 x i32> [[TMP70]], <4 x i32>* [[TMP81]], align 4
; AVX1-NEXT:    [[TMP82:%.*]] = getelementptr inbounds i32, i32* [[TMP72]], i32 12
; AVX1-NEXT:    [[TMP83:%.*]] = bitcast i32* [[TMP82]] to <4 x i32>*
; AVX1-NEXT:    store <4 x i32> [[TMP71]], <4 x i32>* [[TMP83]], align 4
; AVX1-NEXT:    [[INDEX_NEXT]] = add nuw i64 [[INDEX]], 16
; AVX1-NEXT:    [[TMP84:%.*]] = icmp eq i64 [[INDEX_NEXT]], [[N_VEC]]
; AVX1-NEXT:    br i1 [[TMP84]], label [[MIDDLE_BLOCK:%.*]], label [[VECTOR_BODY]], !llvm.loop [[LOOP0:![0-9]+]]
; AVX1:       middle.block:
; AVX1-NEXT:    [[CMP_N:%.*]] = icmp eq i64 [[WIDE_TRIP_COUNT]], [[N_VEC]]
; AVX1-NEXT:    br i1 [[CMP_N]], label [[FOR_END_LOOPEXIT:%.*]], label [[SCALAR_PH]]
; AVX1:       scalar.ph:
; AVX1-NEXT:    [[BC_RESUME_VAL:%.*]] = phi i64 [ [[N_VEC]], [[MIDDLE_BLOCK]] ], [ 0, [[FOR_BODY_PREHEADER]] ]
; AVX1-NEXT:    br label [[FOR_BODY:%.*]]
; AVX1:       for.body:
; AVX1-NEXT:    [[INDVARS_IV:%.*]] = phi i64 [ [[BC_RESUME_VAL]], [[SCALAR_PH]] ], [ [[INDVARS_IV_NEXT:%.*]], [[FOR_BODY]] ]
; AVX1-NEXT:    [[TMP85:%.*]] = shl nuw nsw i64 [[INDVARS_IV]], 1
; AVX1-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP85]]
; AVX1-NEXT:    [[TMP86:%.*]] = load i16, i16* [[ARRAYIDX]], align 2
; AVX1-NEXT:    [[CONV:%.*]] = sext i16 [[TMP86]] to i32
; AVX1-NEXT:    [[ARRAYIDX4:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP85]]
; AVX1-NEXT:    [[TMP87:%.*]] = load i16, i16* [[ARRAYIDX4]], align 2
; AVX1-NEXT:    [[CONV5:%.*]] = sext i16 [[TMP87]] to i32
; AVX1-NEXT:    [[MUL6:%.*]] = mul nsw i32 [[CONV5]], [[CONV]]
; AVX1-NEXT:    [[TMP88:%.*]] = or i64 [[TMP85]], 1
; AVX1-NEXT:    [[ARRAYIDX10:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP88]]
; AVX1-NEXT:    [[TMP89:%.*]] = load i16, i16* [[ARRAYIDX10]], align 2
; AVX1-NEXT:    [[CONV11:%.*]] = sext i16 [[TMP89]] to i32
; AVX1-NEXT:    [[ARRAYIDX15:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP88]]
; AVX1-NEXT:    [[TMP90:%.*]] = load i16, i16* [[ARRAYIDX15]], align 2
; AVX1-NEXT:    [[CONV16:%.*]] = sext i16 [[TMP90]] to i32
; AVX1-NEXT:    [[MUL17:%.*]] = mul nsw i32 [[CONV16]], [[CONV11]]
; AVX1-NEXT:    [[ADD18:%.*]] = add nsw i32 [[MUL17]], [[MUL6]]
; AVX1-NEXT:    [[ARRAYIDX20:%.*]] = getelementptr inbounds i32, i32* [[D1]], i64 [[INDVARS_IV]]
; AVX1-NEXT:    store i32 [[ADD18]], i32* [[ARRAYIDX20]], align 4
; AVX1-NEXT:    [[INDVARS_IV_NEXT]] = add nuw nsw i64 [[INDVARS_IV]], 1
; AVX1-NEXT:    [[EXITCOND_NOT:%.*]] = icmp eq i64 [[INDVARS_IV_NEXT]], [[WIDE_TRIP_COUNT]]
; AVX1-NEXT:    br i1 [[EXITCOND_NOT]], label [[FOR_END_LOOPEXIT]], label [[FOR_BODY]], !llvm.loop [[LOOP2:![0-9]+]]
; AVX1:       for.end.loopexit:
; AVX1-NEXT:    br label [[FOR_END]]
; AVX1:       for.end:
; AVX1-NEXT:    ret void
;
; AVX2-LABEL: @test_muladd(
; AVX2-NEXT:  entry:
; AVX2-NEXT:    [[CMP30:%.*]] = icmp sgt i32 [[N:%.*]], 0
; AVX2-NEXT:    br i1 [[CMP30]], label [[FOR_BODY_PREHEADER:%.*]], label [[FOR_END:%.*]]
; AVX2:       for.body.preheader:
; AVX2-NEXT:    [[WIDE_TRIP_COUNT:%.*]] = zext i32 [[N]] to i64
; AVX2-NEXT:    [[MIN_ITERS_CHECK:%.*]] = icmp ult i64 [[WIDE_TRIP_COUNT]], 8
; AVX2-NEXT:    br i1 [[MIN_ITERS_CHECK]], label [[SCALAR_PH:%.*]], label [[VECTOR_PH:%.*]]
; AVX2:       vector.ph:
; AVX2-NEXT:    [[N_MOD_VF:%.*]] = urem i64 [[WIDE_TRIP_COUNT]], 8
; AVX2-NEXT:    [[N_VEC:%.*]] = sub i64 [[WIDE_TRIP_COUNT]], [[N_MOD_VF]]
; AVX2-NEXT:    br label [[VECTOR_BODY:%.*]]
; AVX2:       vector.body:
; AVX2-NEXT:    [[INDEX:%.*]] = phi i64 [ 0, [[VECTOR_PH]] ], [ [[INDEX_NEXT:%.*]], [[VECTOR_BODY]] ]
; AVX2-NEXT:    [[TMP0:%.*]] = add i64 [[INDEX]], 0
; AVX2-NEXT:    [[TMP1:%.*]] = shl nuw nsw i64 [[TMP0]], 1
; AVX2-NEXT:    [[TMP2:%.*]] = getelementptr inbounds i16, i16* [[S1:%.*]], i64 [[TMP1]]
; AVX2-NEXT:    [[TMP3:%.*]] = getelementptr inbounds i16, i16* [[TMP2]], i32 0
; AVX2-NEXT:    [[TMP4:%.*]] = bitcast i16* [[TMP3]] to <16 x i16>*
; AVX2-NEXT:    [[WIDE_VEC:%.*]] = load <16 x i16>, <16 x i16>* [[TMP4]], align 2
; AVX2-NEXT:    [[STRIDED_VEC:%.*]] = shufflevector <16 x i16> [[WIDE_VEC]], <16 x i16> poison, <8 x i32> <i32 0, i32 2, i32 4, i32 6, i32 8, i32 10, i32 12, i32 14>
; AVX2-NEXT:    [[STRIDED_VEC1:%.*]] = shufflevector <16 x i16> [[WIDE_VEC]], <16 x i16> poison, <8 x i32> <i32 1, i32 3, i32 5, i32 7, i32 9, i32 11, i32 13, i32 15>
; AVX2-NEXT:    [[TMP5:%.*]] = sext <8 x i16> [[STRIDED_VEC]] to <8 x i32>
; AVX2-NEXT:    [[TMP6:%.*]] = getelementptr inbounds i16, i16* [[S2:%.*]], i64 [[TMP1]]
; AVX2-NEXT:    [[TMP7:%.*]] = getelementptr inbounds i16, i16* [[TMP6]], i32 0
; AVX2-NEXT:    [[TMP8:%.*]] = bitcast i16* [[TMP7]] to <16 x i16>*
; AVX2-NEXT:    [[WIDE_VEC2:%.*]] = load <16 x i16>, <16 x i16>* [[TMP8]], align 2
; AVX2-NEXT:    [[STRIDED_VEC3:%.*]] = shufflevector <16 x i16> [[WIDE_VEC2]], <16 x i16> poison, <8 x i32> <i32 0, i32 2, i32 4, i32 6, i32 8, i32 10, i32 12, i32 14>
; AVX2-NEXT:    [[STRIDED_VEC4:%.*]] = shufflevector <16 x i16> [[WIDE_VEC2]], <16 x i16> poison, <8 x i32> <i32 1, i32 3, i32 5, i32 7, i32 9, i32 11, i32 13, i32 15>
; AVX2-NEXT:    [[TMP9:%.*]] = sext <8 x i16> [[STRIDED_VEC3]] to <8 x i32>
; AVX2-NEXT:    [[TMP10:%.*]] = mul nsw <8 x i32> [[TMP9]], [[TMP5]]
; AVX2-NEXT:    [[TMP13:%.*]] = sext <8 x i16> [[STRIDED_VEC1]] to <8 x i32>
; AVX2-NEXT:    [[TMP15:%.*]] = sext <8 x i16> [[STRIDED_VEC4]] to <8 x i32>
; AVX2-NEXT:    [[TMP16:%.*]] = mul nsw <8 x i32> [[TMP15]], [[TMP13]]
; AVX2-NEXT:    [[TMP17:%.*]] = add nsw <8 x i32> [[TMP16]], [[TMP10]]
; AVX2-NEXT:    [[TMP18:%.*]] = getelementptr inbounds i32, i32* [[D1:%.*]], i64 [[TMP0]]
; AVX2-NEXT:    [[TMP19:%.*]] = getelementptr inbounds i32, i32* [[TMP18]], i32 0
; AVX2-NEXT:    [[TMP20:%.*]] = bitcast i32* [[TMP19]] to <8 x i32>*
; AVX2-NEXT:    store <8 x i32> [[TMP17]], <8 x i32>* [[TMP20]], align 4
; AVX2-NEXT:    [[INDEX_NEXT]] = add nuw i64 [[INDEX]], 8
; AVX2-NEXT:    [[TMP21:%.*]] = icmp eq i64 [[INDEX_NEXT]], [[N_VEC]]
; AVX2-NEXT:    br i1 [[TMP21]], label [[MIDDLE_BLOCK:%.*]], label [[VECTOR_BODY]], !llvm.loop [[LOOP0:![0-9]+]]
; AVX2:       middle.block:
; AVX2-NEXT:    [[CMP_N:%.*]] = icmp eq i64 [[WIDE_TRIP_COUNT]], [[N_VEC]]
; AVX2-NEXT:    br i1 [[CMP_N]], label [[FOR_END_LOOPEXIT:%.*]], label [[SCALAR_PH]]
; AVX2:       scalar.ph:
; AVX2-NEXT:    [[BC_RESUME_VAL:%.*]] = phi i64 [ [[N_VEC]], [[MIDDLE_BLOCK]] ], [ 0, [[FOR_BODY_PREHEADER]] ]
; AVX2-NEXT:    br label [[FOR_BODY:%.*]]
; AVX2:       for.body:
; AVX2-NEXT:    [[INDVARS_IV:%.*]] = phi i64 [ [[BC_RESUME_VAL]], [[SCALAR_PH]] ], [ [[INDVARS_IV_NEXT:%.*]], [[FOR_BODY]] ]
; AVX2-NEXT:    [[TMP22:%.*]] = shl nuw nsw i64 [[INDVARS_IV]], 1
; AVX2-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP22]]
; AVX2-NEXT:    [[TMP23:%.*]] = load i16, i16* [[ARRAYIDX]], align 2
; AVX2-NEXT:    [[CONV:%.*]] = sext i16 [[TMP23]] to i32
; AVX2-NEXT:    [[ARRAYIDX4:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP22]]
; AVX2-NEXT:    [[TMP24:%.*]] = load i16, i16* [[ARRAYIDX4]], align 2
; AVX2-NEXT:    [[CONV5:%.*]] = sext i16 [[TMP24]] to i32
; AVX2-NEXT:    [[MUL6:%.*]] = mul nsw i32 [[CONV5]], [[CONV]]
; AVX2-NEXT:    [[TMP25:%.*]] = or i64 [[TMP22]], 1
; AVX2-NEXT:    [[ARRAYIDX10:%.*]] = getelementptr inbounds i16, i16* [[S1]], i64 [[TMP25]]
; AVX2-NEXT:    [[TMP26:%.*]] = load i16, i16* [[ARRAYIDX10]], align 2
; AVX2-NEXT:    [[CONV11:%.*]] = sext i16 [[TMP26]] to i32
; AVX2-NEXT:    [[ARRAYIDX15:%.*]] = getelementptr inbounds i16, i16* [[S2]], i64 [[TMP25]]
; AVX2-NEXT:    [[TMP27:%.*]] = load i16, i16* [[ARRAYIDX15]], align 2
; AVX2-NEXT:    [[CONV16:%.*]] = sext i16 [[TMP27]] to i32
; AVX2-NEXT:    [[MUL17:%.*]] = mul nsw i32 [[CONV16]], [[CONV11]]
; AVX2-NEXT:    [[ADD18:%.*]] = add nsw i32 [[MUL17]], [[MUL6]]
; AVX2-NEXT:    [[ARRAYIDX20:%.*]] = getelementptr inbounds i32, i32* [[D1]], i64 [[INDVARS_IV]]
; AVX2-NEXT:    store i32 [[ADD18]], i32* [[ARRAYIDX20]], align 4
; AVX2-NEXT:    [[INDVARS_IV_NEXT]] = add nuw nsw i64 [[INDVARS_IV]], 1
; AVX2-NEXT:    [[EXITCOND_NOT:%.*]] = icmp eq i64 [[INDVARS_IV_NEXT]], [[WIDE_TRIP_COUNT]]
; AVX2-NEXT:    br i1 [[EXITCOND_NOT]], label [[FOR_END_LOOPEXIT]], label [[FOR_BODY]], !llvm.loop [[LOOP2:![0-9]+]]
; AVX2:       for.end.loopexit:
; AVX2-NEXT:    br label [[FOR_END]]
; AVX2:       for.end:
; AVX2-NEXT:    ret void
;
entry:
  %cmp30 = icmp sgt i32 %n, 0
  br i1 %cmp30, label %for.body.preheader, label %for.end

for.body.preheader:
  %wide.trip.count = zext i32 %n to i64
  br label %for.body

for.body:
  %indvars.iv = phi i64 [ 0, %for.body.preheader ], [ %indvars.iv.next, %for.body ]
  %0 = shl nuw nsw i64 %indvars.iv, 1
  %arrayidx = getelementptr inbounds i16, i16* %s1, i64 %0
  %1 = load i16, i16* %arrayidx, align 2
  %conv = sext i16 %1 to i32
  %arrayidx4 = getelementptr inbounds i16, i16* %s2, i64 %0
  %2 = load i16, i16* %arrayidx4, align 2
  %conv5 = sext i16 %2 to i32
  %mul6 = mul nsw i32 %conv5, %conv
  %3 = or i64 %0, 1
  %arrayidx10 = getelementptr inbounds i16, i16* %s1, i64 %3
  %4 = load i16, i16* %arrayidx10, align 2
  %conv11 = sext i16 %4 to i32
  %arrayidx15 = getelementptr inbounds i16, i16* %s2, i64 %3
  %5 = load i16, i16* %arrayidx15, align 2
  %conv16 = sext i16 %5 to i32
  %mul17 = mul nsw i32 %conv16, %conv11
  %add18 = add nsw i32 %mul17, %mul6
  %arrayidx20 = getelementptr inbounds i32, i32* %d1, i64 %indvars.iv
  store i32 %add18, i32* %arrayidx20, align 4
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  %exitcond.not = icmp eq i64 %indvars.iv.next, %wide.trip.count
  br i1 %exitcond.not, label %for.end.loopexit, label %for.body

for.end.loopexit:
  br label %for.end

for.end:
  ret void
}