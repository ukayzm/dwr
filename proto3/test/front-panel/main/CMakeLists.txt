set(srcs "main.c" "gpio.c" "ir_receive.c"
)

set(include_dirs "."
)

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${include_dirs}"
                       REQUIRES driver
                       REQUIRES esp_timer
)
