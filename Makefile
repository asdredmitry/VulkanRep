VULKAN_SDK_PATH = /home/dmitry/1.1.101.0/x86_64

CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan

09_shader_modules : 15_hello_triangle.cpp
	g++ $(CFLAGS) -o 15_hello_triangle.o 15_hello_triangle.cpp $(LDFLAGS)

test: VulkanTest
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib 
	VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/explicit_layer.d
	./VulkanTest

clean:
	rm -f VulkanTest
