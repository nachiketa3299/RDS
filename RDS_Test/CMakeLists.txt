# @date 2024-04-22
# Project Settings

CMAKE_MINIMUM_REQUIRED(VERSION 3.27)
PROJECT(RDS_Test VERSION 0.1.0)
SET(PROJECT_DESCRIPTION "Simple test project for RDS Library")

SET(rdt_log_prefix ">> [RDS_Test]")
INCLUDE(RDS_Test.cmake)

rdt_add_test_target(SimpleTest)