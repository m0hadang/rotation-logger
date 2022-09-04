execute_process(
	COMMAND cmake --build _build/)
execute_process(
	COMMAND _build/test/test --gmock_verbose=info)