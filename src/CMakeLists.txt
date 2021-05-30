# search .h files at current catalog
# save the name of .h files into DIR_LIB_SRCS
aux_source_directory(. DIR_LIB_SRCS)

# generate target lib
add_library (zhanglib SHARED ${DIR_LIB_SRCS})