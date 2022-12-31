set(srcs "main.cpp"
         "example.cpp"
)
set(include_dirs "."
	"../components/I2Cdev"
	"../components/MPU6050"
)

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${include_dirs}"
                       REQUIRES driver
		       REQUIRES esp_timer
)
