#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
#include <string.h>
const int WIDTH = 200;
const int HEIGHT = 200;

class HelloTriangleApplication
{
    private:
        GLFWwindow * window;
        VkInstance instance;
    public:
        void run()
        {
            initWindow();
            initVulkan();
            mainLoop();
            cleanup();
        }
    private:
        void initVulkan()
        {
            createInstance();

        }
        
        void mainLoop()
        {
            while(!glfwWindowShouldClose(window))
            {
                glfwPollEvents();
            }
        }

        void cleanup()
        {
            glfwDestroyWindow(window);

            glfwTerminate();
        }
        void initWindow()
        {
            glfwInit();

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
        }
        int checkExtensions(const char ** glfwExtensions, int glfwExtensionCount, std :: vector<VkExtensionProperties> & glfwExtensionSupported)
        {
            for(int i = 0; i < glfwExtensionCount; i++)
            {
                int tmp = 0;
                for(int j = 0; j < glfwExtensionSupported.size(); j++)
                {
                    tmp += (strcmp(glfwExtensionSupported[j].extensionName, glfwExtensions[i]) != 0) ? 0 : 1;
                }
                if(tmp == 0)
                    return 0;
            }
            return 1;
        }
        void createInstance()
        {
            VkApplicationInfo appInfo = {};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "Hello Triangle";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "No Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;

            uint32_t extensionCount = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

            std :: vector<VkExtensionProperties> extensions(extensionCount);
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

            std :: cout << "avaliable extensions " << std :: endl;

            for(const auto& extension : extensions)
            {
                std :: cout << " \t "<< extension.extensionName << std :: endl;
            }

            uint32_t glfwExtensionCount = 0;
            const char ** glfwExtensions;

            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            std :: cout << std :: endl;
            for(int i = 0; i < glfwExtensionCount; i++)
            {
                std :: cout << glfwExtensions[i] << std :: endl;
            }
            std :: cout << std :: endl;
            if(checkExtensions(glfwExtensions, glfwExtensionCount, extensions))
            {
                std :: cout <<"It is ok" << std :: endl;
            }
            else 
            {
                std :: cout << "fuck" << std :: endl;
            }

            createInfo.enabledExtensionCount = glfwExtensionCount;
            createInfo.ppEnabledExtensionNames = glfwExtensions;
            createInfo.enabledLayerCount = 0;
            
            VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

            if(result != VK_SUCCESS)
            {
                throw std :: runtime_error("failed to create instance!");
            }
        }
};
int main()
{
    HelloTriangleApplication app;
    try
    {
        app.run();
    } catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}