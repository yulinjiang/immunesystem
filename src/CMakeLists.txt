PROJECT(ImmuneSystem)

SET( SRC_DIR ./ )
SET( SRC_FILE
	   	${SRC_DIR}/main.cpp
		${SRC_DIR}/printData.cpp
		${SRC_DIR}/fitness.cpp
		${SRC_DIR}/popInit.cpp
		${SRC_DIR}/similar.cpp
		${SRC_DIR}/concentration.cpp
	    ${SRC_DIR}/excellence.cpp
	    ${SRC_DIR}/cross.cpp
		${SRC_DIR}/select.cpp
		${SRC_DIR}/mutation.cpp
		${SRC_DIR}/incorporate.cpp
		${SRC_DIR}/bestSelect.cpp
		)

ADD_EXECUTABLE( ../ImmuneSystem ${SRC_FILE} )
