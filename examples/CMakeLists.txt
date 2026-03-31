include_directories(${INCLUDE_DIR})

set (HEADERS
	${INCLUDE_DIR}/aabb.h
	${INCLUDE_DIR}/euler6.h
	${INCLUDE_DIR}/hxMath.h
	${INCLUDE_DIR}/mat.h
	${INCLUDE_DIR}/ray.h
	${INCLUDE_DIR}/vec.h
	${INCLUDE_DIR}/rotor.h
	${INCLUDE_DIR}/onb.h
	${INCLUDE_DIR}/vecUtils.h
	)

set (MATH_SOURCES
	${INCLUDE_DIR}/aabb.cpp
	${INCLUDE_DIR}/mat.cpp
	${INCLUDE_DIR}/vec.cpp
	${INCLUDE_DIR}/rotor.cpp
	)

add_executable (examples ${HEADERS} ${MATH_SOURCES} main.cpp main.h)
