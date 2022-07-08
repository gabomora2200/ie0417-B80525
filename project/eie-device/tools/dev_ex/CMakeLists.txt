add_executable(dev_ex main.c)

target_link_libraries(dev_ex ${LIB_NAME})

install(
	TARGETS dev_ex
  RUNTIME DESTINATION bin
)
