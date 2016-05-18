// RUN: %clang_cc1 %s -triple=x86_64-apple-darwin -target-feature +sse2 -emit-llvm -o - -Werror | FileCheck %s
// RUN: %clang_cc1 %s -triple=x86_64-apple-darwin -target-feature +sse2 -fno-signed-char -emit-llvm -o - -Werror | FileCheck %s

// Don't include mm_malloc.h, it's system specific.
#define __MM_MALLOC_H

#include <x86intrin.h>

// NOTE: This should match the tests in llvm/test/CodeGen/X86/sse2-intrinsics-fast-isel.ll

__m128i test_mm_add_epi8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_add_epi8
  // CHECK: add <16 x i8>
  return _mm_add_epi8(A, B);
}

__m128i test_mm_add_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_add_epi16
  // CHECK: add <8 x i16>
  return _mm_add_epi16(A, B);
}

__m128i test_mm_add_epi32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_add_epi32
  // CHECK: add <4 x i32>
  return _mm_add_epi32(A, B);
}

__m128i test_mm_add_epi64(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_add_epi64
  // CHECK: add <2 x i64>
  return _mm_add_epi64(A, B);
}

__m128d test_mm_add_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_add_pd
  // CHECK: fadd <2 x double>
  return _mm_add_pd(A, B);
}

__m128d test_mm_add_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_add_sd
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: fadd double
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 0
  return _mm_add_sd(A, B);
}

__m128i test_mm_adds_epi8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_adds_epi8
  // CHECK: call <16 x i8> @llvm.x86.sse2.padds.b(<16 x i8> %{{.*}}, <16 x i8> %{{.*}})
  return _mm_adds_epi8(A, B);
}

__m128i test_mm_adds_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_adds_epi16
  // CHECK: call <8 x i16> @llvm.x86.sse2.padds.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_adds_epi16(A, B);
}

__m128i test_mm_adds_epu8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_adds_epu8
  // CHECK: call <16 x i8> @llvm.x86.sse2.paddus.b(<16 x i8> %{{.*}}, <16 x i8> %{{.*}})
  return _mm_adds_epu8(A, B);
}

__m128i test_mm_adds_epu16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_adds_epu16
  // CHECK: call <8 x i16> @llvm.x86.sse2.paddus.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_adds_epu16(A, B);
}

__m128d test_mm_and_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_and_pd
  // CHECK: and <4 x i32>
  return _mm_and_pd(A, B);
}

__m128i test_mm_and_si128(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_and_si128
  // CHECK: and <2 x i64>
  return _mm_and_si128(A, B);
}

__m128d test_mm_andnot_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_andnot_pd
  // CHECK: xor <4 x i32> %{{.*}}, <i32 -1, i32 -1, i32 -1, i32 -1>
  // CHECK: and <4 x i32>
  return _mm_andnot_pd(A, B);
}

__m128i test_mm_andnot_si128(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_andnot_si128
  // CHECK: xor <2 x i64> %{{.*}}, <i64 -1, i64 -1>
  // CHECK: and <2 x i64>
  return _mm_andnot_si128(A, B);
}

__m128i test_mm_avg_epu8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_avg_epu8
  // CHECK: call <16 x i8> @llvm.x86.sse2.pavg.b(<16 x i8> %{{.*}}, <16 x i8> %{{.*}})
  return _mm_avg_epu8(A, B);
}

__m128i test_mm_avg_epu16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_avg_epu16
  // CHECK: call <8 x i16> @llvm.x86.sse2.pavg.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_avg_epu16(A, B);
}

__m128i test_mm_bslli_si128(__m128i A) {
  // CHECK-LABEL: test_mm_bslli_si128
  // CHECK: shufflevector <16 x i8> %{{.*}}, <16 x i8> %{{.*}}, <16 x i32> <i32 11, i32 12, i32 13, i32 14, i32 15, i32 16, i32 17, i32 18, i32 19, i32 20, i32 21, i32 22, i32 23, i32 24, i32 25, i32 26>
  return _mm_bslli_si128(A, 5);
}

__m128i test_mm_bsrli_si128(__m128i A) {
  // CHECK-LABEL: test_mm_bsrli_si128
  // CHECK: shufflevector <16 x i8> %{{.*}}, <16 x i8> %{{.*}}, <16 x i32> <i32 5, i32 6, i32 7, i32 8, i32 9, i32 10, i32 11, i32 12, i32 13, i32 14, i32 15, i32 16, i32 17, i32 18, i32 19, i32 20>
  return _mm_bsrli_si128(A, 5);
}

void test_mm_clflush(void* A) {
  // CHECK-LABEL: test_mm_clflush
  // CHECK: call void @llvm.x86.sse2.clflush(i8* %{{.*}})
  _mm_clflush(A);
}

__m128i test_mm_cmpeq_epi8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_cmpeq_epi8
  // CHECK: icmp eq <16 x i8>
  return _mm_cmpeq_epi8(A, B);
}

__m128i test_mm_cmpeq_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_cmpeq_epi16
  // CHECK: icmp eq <8 x i16>
  return _mm_cmpeq_epi16(A, B);
}

__m128i test_mm_cmpeq_epi32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_cmpeq_epi32
  // CHECK: icmp eq <4 x i32>
  return _mm_cmpeq_epi32(A, B);
}

__m128d test_mm_cmpeq_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpeq_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 0)
  return _mm_cmpeq_pd(A, B);
}

__m128d test_mm_cmpeq_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpeq_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 0)
  return _mm_cmpeq_sd(A, B);
}

__m128d test_mm_cmpge_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpge_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 2)
  return _mm_cmpge_pd(A, B);
}

__m128d test_mm_cmpge_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpge_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 2)
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: insertelement <2 x double> undef, double %{{.*}}, i32 0
  // CHECK: extractelement <2 x double> %{{.*}}, i32 1
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 1
  return _mm_cmpge_sd(A, B);
}

__m128i test_mm_cmpgt_epi8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_cmpgt_epi8
  // CHECK: icmp sgt <16 x i8>
  return _mm_cmpgt_epi8(A, B);
}

__m128i test_mm_cmpgt_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_cmpgt_epi16
  // CHECK: icmp sgt <8 x i16>
  return _mm_cmpgt_epi16(A, B);
}

__m128i test_mm_cmpgt_epi32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_cmpgt_epi32
  // CHECK: icmp sgt <4 x i32>
  return _mm_cmpgt_epi32(A, B);
}

__m128d test_mm_cmpgt_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpgt_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 1)
  return _mm_cmpgt_pd(A, B);
}

__m128d test_mm_cmpgt_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpgt_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 1)
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: insertelement <2 x double> undef, double %{{.*}}, i32 0
  // CHECK: extractelement <2 x double> %{{.*}}, i32 1
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 1
  return _mm_cmpgt_sd(A, B);
}

__m128d test_mm_cmple_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmple_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 2)
  return _mm_cmple_pd(A, B);
}

__m128d test_mm_cmple_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmple_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 2)
  return _mm_cmple_sd(A, B);
}

__m128i test_mm_cmplt_epi8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_cmplt_epi8
  // CHECK: icmp sgt <16 x i8>
  return _mm_cmplt_epi8(A, B);
}

__m128i test_mm_cmplt_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_cmplt_epi16
  // CHECK: icmp sgt <8 x i16>
  return _mm_cmplt_epi16(A, B);
}

__m128i test_mm_cmplt_epi32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_cmplt_epi32
  // CHECK: icmp sgt <4 x i32>
  return _mm_cmplt_epi32(A, B);
}

__m128d test_mm_cmplt_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmplt_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 1)
  return _mm_cmplt_pd(A, B);
}

__m128d test_mm_cmplt_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmplt_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 1)
  return _mm_cmplt_sd(A, B);
}

__m128d test_mm_cmpneq_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpneq_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 4)
  return _mm_cmpneq_pd(A, B);
}

__m128d test_mm_cmpneq_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpneq_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 4)
  return _mm_cmpneq_sd(A, B);
}

__m128d test_mm_cmpnge_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpnge_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 6)
  return _mm_cmpnge_pd(A, B);
}

__m128d test_mm_cmpnge_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpnge_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 6)
  return _mm_cmpnge_sd(A, B);
}

__m128d test_mm_cmpngt_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpngt_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 5)
  return _mm_cmpngt_pd(A, B);
}

__m128d test_mm_cmpngt_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpngt_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 5)
  return _mm_cmpngt_sd(A, B);
}

__m128d test_mm_cmpnle_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpnle_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 6)
  return _mm_cmpnle_pd(A, B);
}

__m128d test_mm_cmpnle_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpnle_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 6)
  return _mm_cmpnle_sd(A, B);
}

__m128d test_mm_cmpnlt_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpnlt_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 5)
  return _mm_cmpnlt_pd(A, B);
}

__m128d test_mm_cmpnlt_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpnlt_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 5)
  return _mm_cmpnlt_sd(A, B);
}

__m128d test_mm_cmpord_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpord_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 7)
  return _mm_cmpord_pd(A, B);
}

__m128d test_mm_cmpord_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpord_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 7)
  return _mm_cmpord_sd(A, B);
}

__m128d test_mm_cmpunord_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpunord_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 3)
  return _mm_cmpunord_pd(A, B);
}

__m128d test_mm_cmpunord_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_cmpunord_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.cmp.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}}, i8 3)
  return _mm_cmpunord_sd(A, B);
}

int test_mm_comieq_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_comieq_sd
  // CHECK: call i32 @llvm.x86.sse2.comieq.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_comieq_sd(A, B);
}

int test_mm_comige_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_comige_sd
  // CHECK: call i32 @llvm.x86.sse2.comige.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_comige_sd(A, B);
}

int test_mm_comigt_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_comigt_sd
  // CHECK: call i32 @llvm.x86.sse2.comigt.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_comigt_sd(A, B);
}

int test_mm_comile_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_comile_sd
  // CHECK: call i32 @llvm.x86.sse2.comile.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_comile_sd(A, B);
}

int test_mm_comilt_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_comilt_sd
  // CHECK: call i32 @llvm.x86.sse2.comilt.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_comilt_sd(A, B);
}

int test_mm_comineq_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_comineq_sd
  // CHECK: call i32 @llvm.x86.sse2.comineq.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_comineq_sd(A, B);
}

__m128d test_mm_cvtepi32_pd(__m128i A) {
  // CHECK-LABEL: test_mm_cvtepi32_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cvtdq2pd(<4 x i32> %{{.*}})
  return _mm_cvtepi32_pd(A);
}

__m128 test_mm_cvtepi32_ps(__m128i A) {
  // CHECK-LABEL: test_mm_cvtepi32_ps
  // CHECK: call <4 x float> @llvm.x86.sse2.cvtdq2ps(<4 x i32> %{{.*}})
  return _mm_cvtepi32_ps(A);
}

__m128i test_mm_cvtpd_epi32(__m128d A) {
  // CHECK-LABEL: test_mm_cvtpd_epi32
  // CHECK: call <4 x i32> @llvm.x86.sse2.cvtpd2dq(<2 x double> %{{.*}})
  return _mm_cvtpd_epi32(A);
}

__m128 test_mm_cvtpd_ps(__m128d A) {
  // CHECK-LABEL: test_mm_cvtpd_ps
  // CHECK: call <4 x float> @llvm.x86.sse2.cvtpd2ps(<2 x double> %{{.*}})
  return _mm_cvtpd_ps(A);
}

__m128i test_mm_cvtps_epi32(__m128 A) {
  // CHECK-LABEL: test_mm_cvtps_epi32
  // CHECK: call <4 x i32> @llvm.x86.sse2.cvtps2dq(<4 x float> %{{.*}})
  return _mm_cvtps_epi32(A);
}

__m128d test_mm_cvtps_pd(__m128 A) {
  // CHECK-LABEL: test_mm_cvtps_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.cvtps2pd(<4 x float> %{{.*}})
  return _mm_cvtps_pd(A);
}

double test_mm_cvtsd_f64(__m128d A) {
  // CHECK-LABEL: test_mm_cvtsd_f64
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  return _mm_cvtsd_f64(A);
}

int test_mm_cvtsd_si32(__m128d A) {
  // CHECK-LABEL: test_mm_cvtsd_si32
  // CHECK: call i32 @llvm.x86.sse2.cvtsd2si(<2 x double> %{{.*}})
  return _mm_cvtsd_si32(A);
}

long long test_mm_cvtsd_si64(__m128d A) {
  // CHECK-LABEL: test_mm_cvtsd_si64
  // CHECK: call i64 @llvm.x86.sse2.cvtsd2si64(<2 x double> %{{.*}})
  return _mm_cvtsd_si64(A);
}

__m128 test_mm_cvtsd_ss(__m128 A, __m128d B) {
  // CHECK-LABEL: test_mm_cvtsd_ss
  // CHECK: fptrunc double %{{.*}} to float
  return _mm_cvtsd_ss(A, B);
}

int test_mm_cvtsi128_si32(__m128i A) {
  // CHECK-LABEL: test_mm_cvtsi128_si32
  // CHECK: extractelement <4 x i32> %{{.*}}, i32 0
  return _mm_cvtsi128_si32(A);
}

long long test_mm_cvtsi128_si64(__m128i A) {
  // CHECK-LABEL: test_mm_cvtsi128_si64
  // CHECK: extractelement <2 x i64> %{{.*}}, i32 0
  return _mm_cvtsi128_si64(A);
}

__m128d test_mm_cvtsi32_sd(__m128d A, int B) {
  // CHECK-LABEL: test_mm_cvtsi32_sd
  // CHECK: sitofp i32 %{{.*}} to double
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 0
  return _mm_cvtsi32_sd(A, B);
}

__m128i test_mm_cvtsi32_si128(int A) {
  // CHECK-LABEL: test_mm_cvtsi32_si128
  // CHECK: insertelement <4 x i32> undef, i32 %{{.*}}, i32 0
  // CHECK: insertelement <4 x i32> %{{.*}}, i32 0, i32 1
  // CHECK: insertelement <4 x i32> %{{.*}}, i32 0, i32 2
  // CHECK: insertelement <4 x i32> %{{.*}}, i32 0, i32 3
  return _mm_cvtsi32_si128(A);
}

__m128d test_mm_cvtsi64_sd(__m128d A, long long B) {
  // CHECK-LABEL: test_mm_cvtsi64_sd
  // CHECK: sitofp i64 %{{.*}} to double
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 0
  return _mm_cvtsi64_sd(A, B);
}

__m128i test_mm_cvtsi64_si128(long long A) {
  // CHECK-LABEL: test_mm_cvtsi64_si128
  // CHECK: insertelement <2 x i64> undef, i64 %{{.*}}, i32 0
  // CHECK: insertelement <2 x i64> %{{.*}}, i64 0, i32 1
  return _mm_cvtsi64_si128(A);
}

__m128d test_mm_cvtss_sd(__m128d A, __m128 B) {
  // CHECK-LABEL: test_mm_cvtss_sd
  // CHECK: extractelement <4 x float> %{{.*}}, i32 0
  // CHECK: fpext float %{{.*}} to double
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 0
  return _mm_cvtss_sd(A, B);
}

__m128i test_mm_cvttpd_epi32(__m128d A) {
  // CHECK-LABEL: test_mm_cvttpd_epi32
  // CHECK: call <4 x i32> @llvm.x86.sse2.cvttpd2dq(<2 x double> %{{.*}})
  return _mm_cvttpd_epi32(A);
}

__m128i test_mm_cvttps_epi32(__m128 A) {
  // CHECK-LABEL: test_mm_cvttps_epi32
  // CHECK: call <4 x i32> @llvm.x86.sse2.cvttps2dq(<4 x float> %{{.*}})
  return _mm_cvttps_epi32(A);
}

int test_mm_cvttsd_si32(__m128d A) {
  // CHECK-LABEL: test_mm_cvttsd_si32
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: fptosi double %{{.*}} to i32
  return _mm_cvttsd_si32(A);
}

long long test_mm_cvttsd_si64(__m128d A) {
  // CHECK-LABEL: test_mm_cvttsd_si64
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: fptosi double %{{.*}} to i64
  return _mm_cvttsd_si64(A);
}

__m128d test_mm_div_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_div_pd
  // CHECK: fdiv <2 x double>
  return _mm_div_pd(A, B);
}

__m128d test_mm_div_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_div_sd
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: fdiv double
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 0
  return _mm_div_sd(A, B);
}

// Lowering to pextrw requires optimization.
int test_mm_extract_epi16(__m128i A) {
  // CHECK-LABEL: test_mm_extract_epi16
  // CHECK: [[x:%.*]] = and i32 %{{.*}}, 7
  // CHECK: extractelement <8 x i16> %{{.*}}, i32 [[x]]
  // CHECK: zext i16 %{{.*}} to i32
  return _mm_extract_epi16(A, 9);
}

__m128i test_mm_insert_epi16(__m128i A, short B) {
  // CHECK-LABEL: test_mm_insert_epi16
  // CHECK: [[x:%.*]] = and i32 %{{.*}}, 7
  // CHECK: insertelement <8 x i16> %{{.*}}, i32 [[x]]
  return _mm_insert_epi16(A, B, 8);
}

void test_mm_lfence() {
  // CHECK-LABEL: test_mm_lfence
  // CHECK: call void @llvm.x86.sse2.lfence()
  _mm_lfence();
}

__m128d test_mm_load_pd(double const* A) {
  // CHECK-LABEL: test_mm_load_pd
  // CHECK: load <2 x double>, <2 x double>* %{{.*}}, align 16
  return _mm_load_pd(A);
}

__m128d test_mm_load_sd(double const* A) {
  // CHECK-LABEL: test_mm_load_sd
  // CHECK: load double, double* %{{.*}}, align 1
  return _mm_load_sd(A);
}

__m128i test_mm_load_si128(__m128i const* A) {
  // CHECK-LABEL: test_mm_load_si128
  // CHECK: load <2 x i64>, <2 x i64>* %{{.*}}, align 16
  return _mm_load_si128(A);
}

__m128d test_mm_load1_pd(double const* A) {
  // CHECK-LABEL: test_mm_load1_pd
  // CHECK: load double, double* %{{.*}}, align 8
  // CHECK: insertelement <2 x double> undef, double %{{.*}}, i32 0
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 1
  return _mm_load1_pd(A);
}

__m128d test_mm_loadh_pd(__m128d x, void* y) {
  // CHECK-LABEL: test_mm_loadh_pd
  // CHECK: load double, double* %{{.*}}, align 1{{$}}
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 1
  return _mm_loadh_pd(x, y);
}

__m128i test_mm_loadl_epi64(__m128i* y) {
  // CHECK: test_mm_loadl_epi64
  // CHECK: load i64, i64* {{.*}}, align 1{{$}}
  // CHECK: insertelement <2 x i64> undef, i64 {{.*}}, i32 0
  // CHECK: insertelement <2 x i64> {{.*}}, i64 0, i32 1
  return _mm_loadl_epi64(y);
}

__m128d test_mm_loadl_pd(__m128d x, void* y) {
  // CHECK-LABEL: test_mm_loadl_pd
  // CHECK: load double, double* %{{.*}}, align 1{{$}}
  // CHECK: insertelement <2 x double> undef, double %{{.*}}, i32 0
  // CHECK: extractelement <2 x double> %{{.*}}, i32 1
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 1
  return _mm_loadl_pd(x, y);
}

__m128d test_mm_loadr_pd(double const* A) {
  // CHECK-LABEL: test_mm_loadr_pd
  // CHECK: load <2 x double>, <2 x double>* %{{.*}}, align 16
  // CHECK: shufflevector <2 x double> %{{.*}}, <2 x double> %{{.*}}, <2 x i32> <i32 1, i32 0>
  return _mm_loadr_pd(A);
}

__m128d test_mm_loadu_pd(double const* A) {
  // CHECK-LABEL: test_mm_loadu_pd
  // CHECK: load <2 x double>, <2 x double>* %{{.*}}, align 1
  return _mm_loadu_pd(A);
}

__m128i test_mm_loadu_si128(__m128i const* A) {
  // CHECK-LABEL: test_mm_loadu_si128
  // CHECK: load <2 x i64>, <2 x i64>* %{{.*}}, align 1
  return _mm_loadu_si128(A);
}

__m128i test_mm_madd_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_madd_epi16
  // CHECK: call <4 x i32> @llvm.x86.sse2.pmadd.wd(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_madd_epi16(A, B);
}

void test_mm_maskmoveu_si128(__m128i A, __m128i B, char* C) {
  // CHECK-LABEL: test_mm_maskmoveu_si128
  // CHECK: call void @llvm.x86.sse2.maskmov.dqu(<16 x i8> %{{.*}}, <16 x i8> %{{.*}}, i8* %{{.*}})
  _mm_maskmoveu_si128(A, B, C);
}

__m128i test_mm_max_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_max_epi16
  // CHECK: call <8 x i16> @llvm.x86.sse2.pmaxs.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_max_epi16(A, B);
}

__m128i test_mm_max_epu8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_max_epu8
  // CHECK: call <16 x i8> @llvm.x86.sse2.pmaxu.b(<16 x i8> %{{.*}}, <16 x i8> %{{.*}})
  return _mm_max_epu8(A, B);
}

__m128d test_mm_max_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_max_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.max.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_max_pd(A, B);
}

__m128d test_mm_max_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_max_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.max.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_max_sd(A, B);
}

void test_mm_mfence() {
  // CHECK-LABEL: test_mm_mfence
  // CHECK: call void @llvm.x86.sse2.mfence()
  _mm_mfence();
}

__m128i test_mm_min_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_min_epi16
  // CHECK: call <8 x i16> @llvm.x86.sse2.pmins.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_min_epi16(A, B);
}

__m128i test_mm_min_epu8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_min_epu8
  // CHECK: call <16 x i8> @llvm.x86.sse2.pminu.b(<16 x i8> %{{.*}}, <16 x i8> %{{.*}})
  return _mm_min_epu8(A, B);
}

__m128d test_mm_min_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_min_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.min.pd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_min_pd(A, B);
}

__m128d test_mm_min_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_min_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.min.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_min_sd(A, B);
}

int test_mm_movemask_epi8(__m128i A) {
  // CHECK-LABEL: test_mm_movemask_epi8
  // CHECK: call i32 @llvm.x86.sse2.pmovmskb.128(<16 x i8> %{{.*}})
  return _mm_movemask_epi8(A);
}

int test_mm_movemask_pd(__m128d A) {
  // CHECK-LABEL: test_mm_movemask_pd
  // CHECK: call i32 @llvm.x86.sse2.movmsk.pd(<2 x double> %{{.*}})
  return _mm_movemask_pd(A);
}

__m128i test_mm_mul_epu32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_mul_epu32
  // CHECK: call <2 x i64> @llvm.x86.sse2.pmulu.dq(<4 x i32> %{{.*}}, <4 x i32> %{{.*}})
  return _mm_mul_epu32(A, B);
}

__m128d test_mm_mul_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_mul_pd
  // CHECK: fmul <2 x double> %{{.*}}, %{{.*}}
  return _mm_mul_pd(A, B);
}

__m128d test_mm_mul_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_mul_sd
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: fmul double
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 0
  return _mm_mul_sd(A, B);
}

__m128i test_mm_mulhi_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_mulhi_epi16
  // CHECK: call <8 x i16> @llvm.x86.sse2.pmulh.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_mulhi_epi16(A, B);
}

__m128i test_mm_mulhi_epu16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_mulhi_epu16
  // CHECK: call <8 x i16> @llvm.x86.sse2.pmulhu.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_mulhi_epu16(A, B);
}

__m128i test_mm_mullo_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_mullo_epi16
  // CHECK: mul <8 x i16> %{{.*}}, %{{.*}}
  return _mm_mullo_epi16(A, B);
}

__m128d test_mm_or_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_or_pd
  // CHECK: or <4 x i32> %{{.*}}, %{{.*}}
  return _mm_or_pd(A, B);
}

__m128i test_mm_or_si128(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_or_si128
  // CHECK: or <2 x i64> %{{.*}}, %{{.*}}
  return _mm_or_si128(A, B);
}

__m128i test_mm_packs_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_packs_epi16
  // CHECK: call <16 x i8> @llvm.x86.sse2.packsswb.128(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_packs_epi16(A, B);
}

__m128i test_mm_packs_epi32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_packs_epi32
  // CHECK: call <8 x i16> @llvm.x86.sse2.packssdw.128(<4 x i32> %{{.*}}, <4 x i32> %{{.*}})
  return _mm_packs_epi32(A, B);
}

__m128i test_mm_packus_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_packus_epi16
  // CHECK: call <16 x i8> @llvm.x86.sse2.packuswb.128(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_packus_epi16(A, B);
}

void test_mm_pause() {
  // CHECK-LABEL: test_mm_pause
  // CHECK: call void @llvm.x86.sse2.pause()
  return _mm_pause();
}

__m128i test_mm_sad_epu8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_sad_epu8
  // CHECK: call <2 x i64> @llvm.x86.sse2.psad.bw(<16 x i8> %{{.*}}, <16 x i8> %{{.*}})
  return _mm_sad_epu8(A, B);
}

__m128d test_mm_setzero_pd() {
  // CHECK-LABEL: test_mm_setzero_pd
  // CHECK: store <2 x double> zeroinitializer
  return _mm_setzero_pd();
}

__m128i test_mm_setzero_si128() {
  // CHECK-LABEL: test_mm_setzero_si128
  // CHECK: store <2 x i64> zeroinitializer
  return _mm_setzero_si128();
}

__m128i test_mm_shuffle_epi32(__m128i A) {
  // CHECK-LABEL: test_mm_shuffle_epi32
  // CHECK: shufflevector <4 x i32> %{{.*}}, <4 x i32> %{{.*}}, <4 x i32> zeroinitializer
  return _mm_shuffle_epi32(A, 0);
}

__m128d test_mm_shuffle_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_shuffle_pd
  // CHECK: shufflevector <2 x double> %{{.*}}, <2 x double> %{{.*}}, <2 x i32> <i32 1, i32 2>
  return _mm_shuffle_pd(A, B, 1);
}

__m128i test_mm_shufflehi_epi16(__m128i A) {
  // CHECK-LABEL: test_mm_shufflehi_epi16
  // CHECK: shufflevector <8 x i16> %{{.*}}, <8 x i16> %{{.*}}, <8 x i32> <i32 0, i32 1, i32 2, i32 3, i32 4, i32 4, i32 4, i32 4>
  return _mm_shufflehi_epi16(A, 0);
}

__m128i test_mm_shufflelo_epi16(__m128i A) {
  // CHECK-LABEL: test_mm_shufflelo_epi16
  // CHECK: shufflevector <8 x i16> %{{.*}}, <8 x i16> %{{.*}}, <8 x i32> <i32 0, i32 0, i32 0, i32 0, i32 4, i32 5, i32 6, i32 7>
  return _mm_shufflelo_epi16(A, 0);
}

__m128i test_mm_sll_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_sll_epi16
  // CHECK: call <8 x i16> @llvm.x86.sse2.psll.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_sll_epi16(A, B);
}

__m128i test_mm_sll_epi32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_sll_epi32
  // CHECK: call <4 x i32> @llvm.x86.sse2.psll.d(<4 x i32> %{{.*}}, <4 x i32> %{{.*}})
  return _mm_sll_epi32(A, B);
}

__m128i test_mm_sll_epi64(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_sll_epi64
  // CHECK: call <2 x i64> @llvm.x86.sse2.psll.q(<2 x i64> %{{.*}}, <2 x i64> %{{.*}})
  return _mm_sll_epi64(A, B);
}

__m128i test_mm_slli_epi16(__m128i A) {
  // CHECK-LABEL: test_mm_slli_epi16
  // CHECK: call <8 x i16> @llvm.x86.sse2.pslli.w(<8 x i16> %{{.*}}, i32 %{{.*}})
  return _mm_slli_epi16(A, 1);
}

__m128i test_mm_slli_epi32(__m128i A) {
  // CHECK-LABEL: test_mm_slli_epi32
  // CHECK: call <4 x i32> @llvm.x86.sse2.pslli.d(<4 x i32> %{{.*}}, i32 %{{.*}})
  return _mm_slli_epi32(A, 1);
}

__m128i test_mm_slli_epi64(__m128i A) {
  // CHECK-LABEL: test_mm_slli_epi64
  // CHECK: call <2 x i64> @llvm.x86.sse2.pslli.q(<2 x i64> %{{.*}}, i32 %{{.*}})
  return _mm_slli_epi64(A, 1);
}

__m128i test_mm_slli_si128(__m128i A) {
  // CHECK-LABEL: test_mm_slli_si128
  // CHECK: shufflevector <16 x i8> %{{.*}}, <16 x i8> %{{.*}}, <16 x i32> <i32 11, i32 12, i32 13, i32 14, i32 15, i32 16, i32 17, i32 18, i32 19, i32 20, i32 21, i32 22, i32 23, i32 24, i32 25, i32 26>
  return _mm_slli_si128(A, 5);
}

__m128d test_mm_sqrt_pd(__m128d A) {
  // CHECK-LABEL: test_mm_sqrt_pd
  // CHECK: call <2 x double> @llvm.x86.sse2.sqrt.pd(<2 x double> %{{.*}})
  return _mm_sqrt_pd(A);
}

__m128d test_mm_sqrt_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_sqrt_sd
  // CHECK: call <2 x double> @llvm.x86.sse2.sqrt.sd(<2 x double> %{{.*}})
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: insertelement <2 x double> undef, double %{{.*}}, i32 0
  // CHECK: extractelement <2 x double> %{{.*}}, i32 1
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 0
  return _mm_sqrt_sd(A, B);
}

__m128i test_mm_sra_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_sra_epi16
  // CHECK: call <8 x i16> @llvm.x86.sse2.psra.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_sra_epi16(A, B);
}

__m128i test_mm_sra_epi32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_sra_epi32
  // CHECK: call <4 x i32> @llvm.x86.sse2.psra.d(<4 x i32> %{{.*}}, <4 x i32> %{{.*}})
  return _mm_sra_epi32(A, B);
}

__m128i test_mm_srai_epi16(__m128i A) {
  // CHECK-LABEL: test_mm_srai_epi16
  // CHECK: call <8 x i16> @llvm.x86.sse2.psrai.w(<8 x i16> %{{.*}}, i32 %{{.*}})
  return _mm_srai_epi16(A, 1);
}

__m128i test_mm_srai_epi32(__m128i A) {
  // CHECK-LABEL: test_mm_srai_epi32
  // CHECK: call <4 x i32> @llvm.x86.sse2.psrai.d(<4 x i32> %{{.*}}, i32 %{{.*}})
  return _mm_srai_epi32(A, 1);
}

__m128i test_mm_srl_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_srl_epi16
  // CHECK: call <8 x i16> @llvm.x86.sse2.psrl.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_srl_epi16(A, B);
}

__m128i test_mm_srl_epi32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_srl_epi32
  // CHECK: call <4 x i32> @llvm.x86.sse2.psrl.d(<4 x i32> %{{.*}}, <4 x i32> %{{.*}})
  return _mm_srl_epi32(A, B);
}

__m128i test_mm_srl_epi64(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_srl_epi64
  // CHECK: call <2 x i64> @llvm.x86.sse2.psrl.q(<2 x i64> %{{.*}}, <2 x i64> %{{.*}})
  return _mm_srl_epi64(A, B);
}

__m128i test_mm_srli_epi16(__m128i A) {
  // CHECK-LABEL: test_mm_srli_epi16
  // CHECK: call <8 x i16> @llvm.x86.sse2.psrli.w(<8 x i16> %{{.*}}, i32 %{{.*}})
  return _mm_srli_epi16(A, 1);
}

__m128i test_mm_srli_epi32(__m128i A) {
  // CHECK-LABEL: test_mm_srli_epi32
  // CHECK: call <4 x i32> @llvm.x86.sse2.psrli.d(<4 x i32> %{{.*}}, i32 %{{.*}})
  return _mm_srli_epi32(A, 1);
}

__m128i test_mm_srli_epi64(__m128i A) {
  // CHECK-LABEL: test_mm_srli_epi64
  // CHECK: call <2 x i64> @llvm.x86.sse2.psrli.q(<2 x i64> %{{.*}}, i32 %{{.*}})
  return _mm_srli_epi64(A, 1);
}

__m128i test_mm_srli_si128(__m128i A) {
  // CHECK-LABEL: test_mm_srli_si128
  // CHECK: shufflevector <16 x i8> %{{.*}}, <16 x i8> %{{.*}}, <16 x i32> <i32 5, i32 6, i32 7, i32 8, i32 9, i32 10, i32 11, i32 12, i32 13, i32 14, i32 15, i32 16, i32 17, i32 18, i32 19, i32 20>
  return _mm_srli_si128(A, 5);
}

void test_mm_store_pd(double* A, __m128d B) {
  // CHECK-LABEL: test_mm_store_pd
  // CHECK: store <2 x double> %{{.*}}, <2 x double>* %{{.*}}, align 16
  _mm_store_pd(A, B);
}

void test_mm_store_sd(double* A, __m128d B) {
  // CHECK-LABEL: test_mm_store_sd
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: store double %{{.*}}, double* %{{.*}}, align 1{{$}}
  _mm_store_sd(A, B);
}

void test_mm_store_si128(__m128i* A, __m128i B) {
  // CHECK-LABEL: test_mm_store_si128
  // CHECK: store <2 x i64> %{{.*}}, <2 x i64>* %{{.*}}, align 16
  _mm_store_si128(A, B);
}

void test_mm_store1_pd(double* x, __m128d y) {
  // CHECK-LABEL: test_mm_store1_pd
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: store {{.*}} double* {{.*}}, align 1{{$}}
  // CHECK: store {{.*}} double* {{.*}}, align 1{{$}}
  _mm_store1_pd(x, y);
}

void test_mm_storeh_pd(double* A, __m128d B) {
  // CHECK-LABEL: test_mm_storeh_pd
  // CHECK: extractelement <2 x double> %{{.*}}, i32 1
  // CHECK: store double %{{.*}}, double* %{{.*}}, align 1
  _mm_storeh_pd(A, B);
}

void test_mm_storel_epi64(__m128i x, void* y) {
  // CHECK-LABEL: test_mm_storel_epi64
  // CHECK: extractelement <2 x i64> %{{.*}}, i32 0
  // CHECK: store {{.*}} i64* {{.*}}, align 1{{$}}
  _mm_storel_epi64(y, x);
}

void test_mm_storel_pd(double* A, __m128d B) {
  // CHECK-LABEL: test_mm_storel_pd
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: store double %{{.*}}, double* %{{.*}}, align 1
  _mm_storel_pd(A, B);
}

void test_mm_storer_pd(__m128d A, double* B) {
  // CHECK-LABEL: test_mm_storer_pd
  // CHECK: shufflevector <2 x double> {{.*}}, <2 x double> {{.*}}, <2 x i32> <i32 1, i32 0>
  // CHECK: store {{.*}} <2 x double>* {{.*}}, align 16{{$}}
  _mm_storer_pd(B, A);
}

void test_mm_storeu_pd(double* A, __m128d B) {
  // CHECK-LABEL: test_mm_storeu_pd
  // CHECK: store <2 x double> %{{.*}}, <2 x double>* %{{.*}}, align 1
  _mm_storeu_pd(A, B);
}

void test_mm_storeu_si128(__m128i* A, __m128i B) {
  // CHECK-LABEL: test_mm_storeu_si128
  // CHECK: store <2 x i64> %{{.*}}, <2 x i64>* %{{.*}}, align 1
  _mm_storeu_si128(A, B);
}

void test_mm_stream_pd(double *A, __m128d B) {
  // CHECK-LABEL: test_mm_stream_pd
  // CHECK: store <2 x double> %{{.*}}, <2 x double>* %{{.*}}, align 16, !nontemporal
  _mm_stream_pd(A, B);
}

void test_mm_stream_si32(int *A, int B) {
  // CHECK-LABEL: test_mm_stream_si32
  // CHECK: store i32 %{{.*}}, i32* %{{.*}}, align 1, !nontemporal
  _mm_stream_si32(A, B);
}

void test_mm_stream_si64(long long *A, long long B) {
  // CHECK-LABEL: test_mm_stream_si64
  // CHECK: store i64 %{{.*}}, i64* %{{.*}}, align 1, !nontemporal
  _mm_stream_si64(A, B);
}

void test_mm_stream_si128(__m128i *A, __m128i B) {
  // CHECK-LABEL: test_mm_stream_si128
  // CHECK: store <2 x i64> %{{.*}}, <2 x i64>* %{{.*}}, align 16, !nontemporal
  _mm_stream_si128(A, B);
}

__m128i test_mm_sub_epi8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_sub_epi8
  // CHECK: sub <16 x i8>
  return _mm_sub_epi8(A, B);
}

__m128i test_mm_sub_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_sub_epi16
  // CHECK: sub <8 x i16>
  return _mm_sub_epi16(A, B);
}

__m128i test_mm_sub_epi32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_sub_epi32
  // CHECK: sub <4 x i32>
  return _mm_sub_epi32(A, B);
}

__m128i test_mm_sub_epi64(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_sub_epi64
  // CHECK: sub <2 x i64>
  return _mm_sub_epi64(A, B);
}

__m128d test_mm_sub_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_sub_pd
  // CHECK: fsub <2 x double>
  return _mm_sub_pd(A, B);
}

__m128d test_mm_sub_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_sub_sd
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: extractelement <2 x double> %{{.*}}, i32 0
  // CHECK: fsub double
  // CHECK: insertelement <2 x double> %{{.*}}, double %{{.*}}, i32 0
  return _mm_sub_sd(A, B);
}

__m128i test_mm_subs_epi8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_subs_epi8
  // CHECK: call <16 x i8> @llvm.x86.sse2.psubs.b(<16 x i8> %{{.*}}, <16 x i8> %{{.*}})
  return _mm_subs_epi8(A, B);
}

__m128i test_mm_subs_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_subs_epi16
  // CHECK: call <8 x i16> @llvm.x86.sse2.psubs.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_subs_epi16(A, B);
}

__m128i test_mm_subs_epu8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_subs_epu8
  // CHECK: call <16 x i8> @llvm.x86.sse2.psubus.b(<16 x i8> %{{.*}}, <16 x i8> %{{.*}})
  return _mm_subs_epu8(A, B);
}

__m128i test_mm_subs_epu16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_subs_epu16
  // CHECK: call <8 x i16> @llvm.x86.sse2.psubus.w(<8 x i16> %{{.*}}, <8 x i16> %{{.*}})
  return _mm_subs_epu16(A, B);
}

int test_mm_ucomieq_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_ucomieq_sd
  // CHECK: call i32 @llvm.x86.sse2.ucomieq.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_ucomieq_sd(A, B);
}

int test_mm_ucomige_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_ucomige_sd
  // CHECK: call i32 @llvm.x86.sse2.ucomige.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_ucomige_sd(A, B);
}

int test_mm_ucomigt_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_ucomigt_sd
  // CHECK: call i32 @llvm.x86.sse2.ucomigt.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_ucomigt_sd(A, B);
}

int test_mm_ucomile_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_ucomile_sd
  // CHECK: call i32 @llvm.x86.sse2.ucomile.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_ucomile_sd(A, B);
}

int test_mm_ucomilt_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_ucomilt_sd
  // CHECK: call i32 @llvm.x86.sse2.ucomilt.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_ucomilt_sd(A, B);
}

int test_mm_ucomineq_sd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_ucomineq_sd
  // CHECK: call i32 @llvm.x86.sse2.ucomineq.sd(<2 x double> %{{.*}}, <2 x double> %{{.*}})
  return _mm_ucomineq_sd(A, B);
}

__m128d test_mm_undefined_pd() {
  // CHECK-LABEL: @test_mm_undefined_pd
  // CHECK: ret <2 x double> undef
  return _mm_undefined_pd();
}

__m128i test_mm_undefined_si128() {
  // CHECK-LABEL: @test_mm_undefined_si128
  // CHECK: ret <2 x i64> undef
  return _mm_undefined_si128();
}

__m128i test_mm_unpackhi_epi8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_unpackhi_epi8
  // CHECK: shufflevector <16 x i8> %{{.*}}, <16 x i8> %{{.*}}, <16 x i32> <i32 8, i32 24, i32 9, i32 25, i32 10, i32 26, i32 11, i32 27, i32 12, i32 28, i32 13, i32 29, i32 14, i32 30, i32 15, i32 31>
  return _mm_unpackhi_epi8(A, B);
}

__m128i test_mm_unpackhi_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_unpackhi_epi16
  // CHECK: shufflevector <8 x i16> %{{.*}}, <8 x i16> %{{.*}}, <8 x i32> <i32 4, i32 12, i32 5, i32 13, i32 6, i32 14, i32 7, i32 15>
  return _mm_unpackhi_epi16(A, B);
}

__m128i test_mm_unpackhi_epi32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_unpackhi_epi32
  // CHECK: shufflevector <4 x i32> %{{.*}}, <4 x i32> %{{.*}}, <4 x i32> <i32 2, i32 6, i32 3, i32 7>
  return _mm_unpackhi_epi32(A, B);
}

__m128i test_mm_unpackhi_epi64(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_unpackhi_epi64
  // CHECK: shufflevector <2 x i64> %{{.*}}, <2 x i64> %{{.*}}, <2 x i32> <i32 1, i32 3>
  return _mm_unpackhi_epi64(A, B);
}

__m128d test_mm_unpackhi_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_unpackhi_pd
  // CHECK: shufflevector <2 x double> %{{.*}}, <2 x double> %{{.*}}, <2 x i32> <i32 1, i32 3>
  return _mm_unpackhi_pd(A, B);
}

__m128i test_mm_unpacklo_epi8(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_unpacklo_epi8
  // CHECK: shufflevector <16 x i8> %{{.*}}, <16 x i8> %{{.*}}, <16 x i32> <i32 0, i32 16, i32 1, i32 17, i32 2, i32 18, i32 3, i32 19, i32 4, i32 20, i32 5, i32 21, i32 6, i32 22, i32 7, i32 23>
  return _mm_unpacklo_epi8(A, B);
}

__m128i test_mm_unpacklo_epi16(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_unpacklo_epi16
  // CHECK: shufflevector <8 x i16> %{{.*}}, <8 x i16> %{{.*}}, <8 x i32> <i32 0, i32 8, i32 1, i32 9, i32 2, i32 10, i32 3, i32 11>
  return _mm_unpacklo_epi16(A, B);
}

__m128i test_mm_unpacklo_epi32(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_unpacklo_epi32
  // CHECK: shufflevector <4 x i32> %{{.*}}, <4 x i32> %{{.*}}, <4 x i32> <i32 0, i32 4, i32 1, i32 5>
  return _mm_unpacklo_epi32(A, B);
}

__m128i test_mm_unpacklo_epi64(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_unpacklo_epi64
  // CHECK: shufflevector <2 x i64> %{{.*}}, <2 x i64> %{{.*}}, <2 x i32> <i32 0, i32 2>
  return _mm_unpacklo_epi64(A, B);
}

__m128d test_mm_unpacklo_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_unpacklo_pd
  // CHECK: shufflevector <2 x double> %{{.*}}, <2 x double> %{{.*}}, <2 x i32> <i32 0, i32 2>
  return _mm_unpacklo_pd(A, B);
}

__m128d test_mm_xor_pd(__m128d A, __m128d B) {
  // CHECK-LABEL: test_mm_xor_pd
  // CHECK: xor <4 x i32> %{{.*}}, %{{.*}}
  return _mm_xor_pd(A, B);
}

__m128i test_mm_xor_si128(__m128i A, __m128i B) {
  // CHECK-LABEL: test_mm_xor_si128
  // CHECK: xor <2 x i64> %{{.*}}, %{{.*}}
  return _mm_xor_si128(A, B);
}
