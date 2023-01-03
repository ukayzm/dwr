set(srcs "lcd1602_i2c.c"
         "lcd1602_lib.c"
)
set(include_dirs "."
)

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${include_dirs}"
                       REQUIRES driver
                       REQUIRES esp_timer
)
