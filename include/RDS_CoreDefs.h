/// @file RDS_CoreDefs.h

#ifndef RDS_COREDEFS_H
#define RDS_COREDEFS_H

// clang-format off

/// @brief 메인 네임스페이스(\p rds) 구간 시작 매크로
#define RDS_BEGIN namespace rds {

/// @brief 메인 네임스페이스(\p rds) 구간 종료 매크로
#define RDS_END };

#define RDS_TAG_ tag::


RDS_BEGIN

// clang-format on
// 32 bit
using PointerDifference_t = int;
// 64 bit

RDS_END

#define RDS_ZERO 0

#define RDS_INT8_MIN (-127 - 1)
#define RDS_INT8_MAX (127)

#define RDS_UINT8_MIN (RDS_ZERO)
#define RDS_UINT8_MAX 0xFF

#define RDS_SCHAR_MIN RDS_INT8_MIN
#define RDS_SCHAR_MAX RDS_INT8_MAX

#define RDS_UCHAR_MIN RDS_UINT8_MIN
#define RDS_UCHAR_MAX RDS_UINT8_MAX

#define RDS_INT16_MIN (-32'767 - 1)
#define RDS_INT16_MAX (32'767)

#define RDS_UINT16_MIN (RDS_ZERO)
#define RDS_UINT16_MAX 0xFFFF

#define RDS_INT32_MIN (-2'147'483'647 - 1)
#define RDS_INT32_MAX (2'147'483'647)

#define RDS_UINT32_MIN RDS_ZERO
#define RDS_UINT32_MAX 0xFFFF'FFFF

#define RDS_INT64_MIN (-9'223'372'036'854'775'807 - 1)
#define RDS_INT64_MAX (9'223'372'036'854'775'807)

#ifdef _WIN64
#define RDS_INTPTR_MIN  RDS_INT64_MIN
#define RDS_INTPTR_MAX  RDS_INT64_MAX
#define RDS_UINTPTR_MAX RDS_UINT64_MAX
#else
#define RDS_INTPTR_MIN  RDS_INT32_MIN
#define RDS_INTPTR_MAX  RDS_INT32_MAX
#define RDS_UINTPTR_MAX RDS_UINT32_MAX
#endif

#define RDS_PTRDIFF_MIN RDS_INTPTR_MIN
#define RDS_PTRDIFF_MAX RDS_INTPTR_MAX

#endif // RDS_COREDEFS_H