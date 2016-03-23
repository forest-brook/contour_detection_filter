#! /usr/bin/make -f

project := \
    contour_detection_filter

ifndef "${target}"
    target := release_x64
endif

ifeq "${target}" "release_x64"
    cxx := g++
    cxxflags := -m64 -O3 -DNDEBUG -Wall -MMD
    ldflags := -m64 -s
else ifeq "${target}" "debug_x64"
    cxx := g++
    cxxflags := -m64 -g -DDEBUG -Wall -MMD
    ldflags := -m64
else ifeq "${target}" "release_x32"
    cxx := g++
    cxxflags := -m32 -O3 -DNDEBUG -Wall -MMD
    ldflags := -m32 -s
else ifeq "${target}" "debug_x32"
    cxx := g++
    cxxflags := -m32 -g -DDEBUG -Wall -MMD
    ldflags := -m32
else
    $(error Received the unknown target "${target}".)
endif

include_directories := \
    ../source

source_files := \
    image_filter/image_filter_data.cpp \
    image_filter/image_filter_tool.cpp \
    image_stream/image_stream_data.cpp \
    image_stream/image_stream_tool.cpp \
    main/main.cpp

library_directories := 

library_files := \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc

output_name := \
    ${project}

output_directory := \
    ../binary/${target}

intermediate_directory := \
    ${target}

object_files := \
    $(patsubst %.cpp,${intermediate_directory}/source/%.o,${source_files})

dependency_files := \
    $(patsubst %.o,%.d,${object_files})

include_directories := \
    $(patsubst %,-I%,${include_directories})

library_directories := \
    $(patsubst %,-L%,${library_directories})

.PHONY : \
	all \
	clean
	

all : \
	${output_directory}/${output_name}
	

${output_directory}/${output_name} : \
	${object_files}
	mkdir -p $(dir $@); \
	${cxx} ${ldflags} $^ ${library_directories} ${library_files} -o $@

${intermediate_directory}/source/%.o : \
	../source/%.cpp
	mkdir -p $(dir $@); \
	${cxx} ${cxxflags} ${include_directories} -c $< -o $@

clean :
	rm -r -f ${intermediate_directory}; \
	rm -r -f ${output_directory}; \
	(rmdir --ignore-fail-on-non-empty ../binary 2> /dev/null) || true

-include ${dependency_files}


