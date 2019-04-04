#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
#include <string.h>
const int WIDTH = 600;
const int HEIGHT = 800;

const std::vector<const char*> validationLayers = {
"VK_LAYER_LUNARG_standard_validation"
};

#ifdef NDEBUG
    const bool enabelValidationLayers = false;
#else   
    const bool enableValidationLayers = true;
#endif
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    //auto func (PFN_vkDestroyDebugUtilsMessnengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if(func != nullptr)
    {
        func(instance, callback, pAllocator);
    }
}
class HelloTriangleApplication
{
    private:
        GLFWwindow * window;
        VkInstance instance;
        VkDebugUtilsMessengerEXT callback;
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
            setupDebugCallback();
            pickPhysicalDevice();

        }
        void pickPhysicalDevice()
        {
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

            if(deviceCount == 0)
            {
                throw std::runtime_error("failed to find gpu with vulkan support");
            }
            std::vector<VkPhysicalDevice> devices(deviceCount);
            vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

            for(const auto& device : devices)
            {
                if(isDeviceSuitable(device))
                {
                    physicalDevice = device;
                    break;
                }
            }
            if(physicalDevice == VK_NULL_HANDLE)
            {
                throw std::runtime_error("failed to find a suitable gpu!");
            }
        }
        bool isDeviceSuitable(VkPhysicalDevice device)
        {
            VkPhysicalDeviceProperties deviceProperties;
            vkGetPhysicalDeviceProperties(device, &deviceProperties);
            VkPhysicalDeviceFeatures deviceFeatures;
            vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
            
            return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU &&  deviceFeatures.geometryShader;
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
            if(enableValidationLayers)
                DestroyDebugUtilsMessengerEXT(instance, callback, nullptr);

            vkDestroyInstance(instance, nullptr);
            
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
            if(enableValidationLayers && !checkValidationLayerSupport())
            {
                throw std::runtime_error("validation layers requested but not available!");
            }
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

            auto extensions = getRequiredExtensions();
            createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
            createInfo.ppEnabledExtensionNames = extensions.data();

            if(enableValidationLayers)
            {
                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();
            }
            else
            {
                createInfo.enabledLayerCount = 0;
            }

            if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to create instance!");
            }
        }
        bool checkValidationLayerSupport()
        {   
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

            std :: cout << "layer Names : " << std :: endl;
            for(const auto& layerProperties : availableLayers)
            {
                std :: cout << layerProperties.layerName << std :: endl;
            }
            for(const char* layerName : validationLayers)
            {
                bool layerFound = false;
            
                for(const auto& layerProperties :availableLayers)
                {
                    if(strcmp(layerName, layerProperties.layerName) == 0)
                    {
                        layerFound = true;
                        break;
                    }
                }
                if(!layerFound)
                    return false;
            }
            return true;
        }
        
        std::vector<const char*> getRequiredExtensions()
        {
            uint32_t glfwExtensionCount = 0;
            const char ** glfwExtensions;
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

            if(enableValidationLayers)
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            
            return extensions;
        }
         static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }
        void setupDebugCallback()
        {
            if(!enableValidationLayers)
                return ;
            VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            createInfo.messageSeverity = 
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT|
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            createInfo.messageType = 
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT|
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | 
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            createInfo.pfnUserCallback = debugCallback;
            createInfo.pUserData = nullptr;
            if(CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &callback) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to set up debug callback!");
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