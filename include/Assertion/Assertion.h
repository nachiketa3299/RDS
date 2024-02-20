/// @file RDS_Assertion.h

#ifndef RDS_ASSERTION_H
#define RDS_ASSERTION_H

#include "RDS_CoreDefs.h"

RDS_BEGIN

#ifdef _DEBUG // _DEBUG가 정의되어 있을 때만 디버그 모드로 동작

/// @brief RDS 라이브러리에서 사용하는 메인 Assertion 매크로
/// @param[in] Expression bool 로 평가되는 표현식
/// @see \ref rds_assert(bool, const char*, const char*, long int*)
#define RDS_Assert(Expression) rds_assert(Expression, #Expression, __FILE__, __LINE__)
#define RDS_Error(Message) rds_error(Message, __FILE__, __LINE__)

#else // _DEBUG가 정의되어 있지 않을 때는 아무것도 하지 않음 (과연?)

#define RDS_Assert(Expression) ((void)0)
#define RDS_Error(Message) ((void)0)

#endif

/// @brief Assertion 매크로 내부 함수 (직접 호출하지 말 것!)
/// @warning 직접 호출하지 말고 #RDS_Assert 매크로를 통해 호출할 것
/// @param[in] exp bool로 평가되는 표현식
/// @param[in] exp_str 표현식의 문자열
/// @param[in] file_str 이 Assertion이 호출된 파일의 이름 (`__FILE__`)
/// @param[in] line 이 Assertion이 호출된 줄 번호 (`__LINE__`)
void rds_assert(bool exp, const char* exp_str, const char* file_str, long int line);

/// @brief Error 매크로 내부 함수 (직접 호출하지 말 것!)
/// @param message 에러 메시지
/// @param file_str 에러가 발생한 파일 이름 (`__FILE__`)
/// @param line  에러가 발생한 줄 번호 (`__LINE__`)
void rds_error(const char* message, const char* file_str, long int line);

RDS_END

#endif // RDS_ASSERTION_H
