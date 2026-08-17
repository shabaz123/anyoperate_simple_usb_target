cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

set(projname "simple_usb_target")
project(${projname} C CXX ASM)

pico_sdk_init()

add_executable(${projname}
    main.cpp
)

target_link_libraries(${projname}
    pico_stdlib
)

if (PICO_CYW43_SUPPORTED)
    target_compile_definitions(${projname} PRIVATE HAS_WLAN_MODULE=1)
    target_link_libraries(${projname} pico_cyw43_arch_none)
else()
    target_compile_definitions(${projname} PRIVATE HAS_WLAN_MODULE=0)
endif()

pico_enable_stdio_usb(${projname} 1)
pico_enable_stdio_uart(${projname} 0)

pico_add_extra_outputs(${projname})
