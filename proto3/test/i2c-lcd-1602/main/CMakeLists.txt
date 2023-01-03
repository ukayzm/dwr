set(srcs "i2c-lcd.c"
         "main.c"
)
set(include_dirs "."
)

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${include_dirs}"
                       REQUIRES driver
                       REQUIRES esp_timer
)
