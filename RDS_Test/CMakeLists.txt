# @date 2024-04-22
# Project Settings

CMAKE_MINIMUM_REQUIRED(VERSION 3.27)
PROJECT(RDS_Test VERSION 0.1.0)
SET(PROJECT_DESCRIPTION "RDS 정적 라이브러리 자체 테스트 프로젝트")

SET(rdt_log_prefix ">> [RDS_Test]")

INCLUDE(RDS_Test-macros.cmake) # add_test_target 정의

add_test_target(SimpleTest)
add_test_target(array)
add_test_target(vector)