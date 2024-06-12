#ifndef RDS_ASSERTION_H
#define RDS_ASSERTION_H

#include "RDS_CoreDefs.h"

#ifdef _DEBUG // _DEBUG가 정의되어 있을 때만 디버그 모드로 동작

/** @brief `Expression`이 `false`로 평가되면 프로그램을 비정상 종료하고, 에러
 *  로그를 출력한다.
 *  @param[in] Expression bool로 평가되는 표현식
 *
 *  @see \ref rds::__assert
 */
#define RDS_Assert(Expression)                                                 \
    rds::__assert(Expression, #Expression, __FILE__, __LINE__)

/** @brief 에러 메시지를 출력하고 프로그램을 비정상 종료한다.
 *  @param[in] Message 에러 메시지
 *
 *  @see \ref rds::__error
 */
#define RDS_Error(Message) rds::__error(Message, __FILE__, __LINE__)

#else // _DEBUG가 정의되어 있지 않을 때는 아무것도 하지 않음

// TODO 과연 이것들이 _DEBUG 모드가 아닐 때에 아무것도 하지 않는지 확인할 것
#define RDS_Assert(Expression) ((void)0)
#define RDS_Error(Message)     ((void)0)

#endif

namespace rds
{

/** @brief #RDS_Assert 매크로 내부 함수
 *
 *  @param[in] exp bool로 평가되는 표현식
 *  @param[in] exp_str 표현식의 문자열
 *  @param[in] file_str 이 Assertion이 호출된 파일의 이름 (`__FILE__`)
 *  @param[in] line 이 Assertion이 호출된 줄 번호 (`__LINE__`)
 *
 *  @warning 직접 호출하지 말 것
 */
auto __assert(bool exp, const char* exp_str, const char* file_str,
              long int line) -> void;

/** @brief #RDS_Error 매크로 내부 함수
 *  @param[in] message 에러 메시지
 *  @param[in] file_str 에러가 발생한 파일 이름 (`__FILE__`)
 *  @param[in] line 에러가 발생한 줄 번호 (`__LINE__`)
 *
 *  @warning 직접 호출하지 말 것
 */
auto __error(const char* message, const char* file_str, long int line) -> void;

} // namespace rds

#endif // RDS_ASSERTION_H
