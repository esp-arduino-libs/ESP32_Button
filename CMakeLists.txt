if("${IDF_VERSION_MAJOR}.${IDF_VERSION_MINOR}" VERSION_GREATER_EQUAL "5.0")
    list(APPEND PRIVREQ esp_adc)
else()
    list(APPEND PRIVREQ esp_adc_cal)
endif()

idf_component_register(SRCS "src/original/button_adc.c"
                            "src/original/button_gpio.c"
                            "src/original/button_matrix.c"
                            "src/original/iot_button.c"
                            # "src/original/adc_oneshot.c"
                            "src/Button.cpp"
                        INCLUDE_DIRS "src"
                        REQUIRES driver ${PRIVREQ}
                        PRIV_REQUIRES esp_timer)


# set(PRIVREQ esp_timer)

# if("${IDF_VERSION_MAJOR}.${IDF_VERSION_MINOR}" VERSION_GREATER_EQUAL "5.0")
#     list(APPEND REQ esp_adc)
# else()
#     list(APPEND REQ esp_adc_cal)
# endif()

# idf_component_register(SRCS "src/original/button_adc.c"
#                             "src/original/button_gpio.c"
#                             "src/original/button_matrix.c"
#                             "src/original/iot_button.c"
#                             "src/Button.cpp"
#                         INCLUDE_DIRS "src"
#                         REQUIRES driver ${REQ}
#                         PRIV_REQUIRES ${PRIVREQ})
#                         # REQUIRES driver
#                         # PRIV_REQUIRES esp_timer)

# # include(package_manager)
# # cu_pkg_define_version(${CMAKE_CURRENT_LIST_DIR})