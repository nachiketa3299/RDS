#ifndef RDS_TAGS_H
#define RDS_TAGS_H

#include "RDS_CoreDefs.h"

namespace rds::tag
{

/** @brief 출력 반복자(Output Iterator)를 나타내는 태그
 *  @details
 *  - 컨테이너를 한 번 전방으로 스캔할 수 있다.\n
 *  - 가리키는 값에 쓸 수 있다.\n
 *  - 가리키는 값을 읽을 수 없다.
 */
struct OuputIterator
{};

/** @brief 입력 반복자(Input Iterator)를 나타내는 태그
 *  @details
 *  - 컨테이너를 한 번 전방으로 스캔할 수 있다.\n
 *  - 가리키는 값에 쓸 수 없다.\n
 *  - 가리키는 값을 읽을 수 있다.
 */
struct InputIterator
{};

/** @brief 전방 반복자(Forward Iterator)를 나타내는 태그
 *  @details
 *  - 컨테이너를 여러 번 전방으로 스캔할 수 있다.\n
 *  - 가리키는 값에 쓸 수 있다.\n
 *  - 가리키는 값을 읽을 수 있다.
 */
struct ForwardIterator: InputIterator
{};

/** @brief 양방향 반복자(Bidirectional Iterator)를 나타내는 태그
 *  @details
 *  - 컨테이너를 여러 번 전후방으로 스캔할 수 있다.\n
 *  - 가리키는 값에 쓸 수 있다.\n
 *  - 가리키는 값을 읽을 수 있다.
 */
struct BidirectionalIterator: ForwardIterator
{};

/** @brief 임의 접근 반복자(Random Access Iterator)를 나타내는 태그
 *  @details
 *  - 컨테이너를 여러 번 전후방으로 스캔할 수 있다.\n
 *  - 가리키는 값에 쓸 수 있다.\n
 *  - 가리키는 값을 읽을 수 있다.\n
 *  - 컨테이너의 요소에 비순차적으로 접근할 수 있다.
 */
struct RandomAccessIterator: BidirectionalIterator
{};

/** @brief 연속 반복자(Contiguous Iterator)를 나타내는 태그
 *  @details
 *  - 컨테이너를 여러 번 전후방으로 스캔할 수 있다.\n
 *  - 가리키는 값에 쓸 수 있다.\n
 *  - 가리키는 값을 읽을 수 있다.\n
 *  - 컨테이너의 요소에 비순차적으로 접근할 수 있다.\n
 *  - 컨테이너의 논리적으로 인접한 요소가 물리적으로도 인접해 있다.
 */
struct ContiguosIterator_Tag: RandomAccessIterator
{};

} // namespace rds::tag

#endif // RDS_TAGS_H