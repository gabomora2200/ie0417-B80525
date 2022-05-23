add_executable(eie_dev main.c)

target_link_libraries(eie_dev ${LIB_NAME})

install(
	TARGETS eie_dev
  RUNTIME DESTINATION bin
)
