# Add sources from the current directory to the project target.
# We pass the target that needs the sources as the first argument,
# then a visibility parameter for the sources (which should normally be PRIVATE).
# Finally, we supply a list of source files that will be built into the target.

target_sources("${PROJECT_NAME}"
    PRIVATE
        ClipperChannel.h
        ClipperChannel.cpp
        DspChannel.h
        DspChannel.cpp
        ToneChannel.h
        ToneChannel.cpp)

# Add subdirectories with source files
# add_subdirectory(...)