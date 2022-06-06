add_executable(cmd_mgr main.c)

target_link_libraries(cmd_mgr ${LIB_NAME})

install(
	TARGETS cmd_mgr
  RUNTIME DESTINATION bin
)
