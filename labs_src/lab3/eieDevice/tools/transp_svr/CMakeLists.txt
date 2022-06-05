add_executable(transp_svr main.c)

target_link_libraries(transp_svr ${LIB_NAME})

install(
	TARGETS transp_svr
  RUNTIME DESTINATION bin
)
