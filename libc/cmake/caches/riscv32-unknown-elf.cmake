set(CMAKE_SYSTEM_PROCESSOR RISCV CACHE STRING "")
set(RUNTIMES_TARGET_TRIPLE "riscv32-unknown-elf" CACHE STRING "")

foreach(lang C;CXX;ASM)
    set(CMAKE_${lang}_FLAGS "-Wno-atomic-alignment" CACHE STRING "")
endforeach()

include(${CMAKE_CURRENT_LIST_DIR}/baremetal_common.cmake)
