//
// Created by Cory Smith on 7/25/25.
//
#include "r_internal.h"
#include "../core/core.h"
#include <_stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//
// IMPLEMENTATION
//
struct Render {
    Arena arena;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debug_messenger;
    VkPhysicalDevice physical_device;
    VkDevice device;
    VkQueue graphics_queue;
    VkQueue present_queue;
    VkSurfaceKHR surface;
};

struct QueueFamiliesIndices {
    u32 graphics_family;
    u32 present_family;
};

Render *r;

const char* required_mac[] = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    "VK_KHR_portability_subset",
};

const u32 required_mac_count = 2;

const char* required_extensions[] = {
    //VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
//#ifdef MACOS
    VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
//#endif
};
const u32 required_count = 1;

const char* validation_layers[] = {
    "VK_LAYER_KHRONOS_validation",
};
const u32 validation_layers_count = 1;

#ifdef DEBUG
const bool enabled_validation_layers = true;
#else
const bool enabled_validation_layers = false;
#endif

void r_init(
    GLFWwindow **window
) {
    r_vk_init();
    r_vk_setup_debug();
    _vk_create_surface(window);
    _vk_pick_physical_device();
    _vk_create_logical_device();
}
void r_vk_init(
) {
    r = (Render *)malloc(sizeof(Render));
    c_arena_init(&r->arena, GB(1));

    if (enabled_validation_layers && !_check_validation_layers_support()) {
        panic("validation is on and not used");
    }


    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "Vulkan Application";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Vulkan Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    ArrayString *as = _get_required_extensions();

    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    create_info.enabledExtensionCount = as->len;
    create_info.ppEnabledExtensionNames = as->data;

    u32 available_extension_count = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &available_extension_count, NULL);
    VkExtensionProperties *available_props = c_arena_alloc(&r->arena, available_extension_count * sizeof(VkExtensionProperties));
    vkEnumerateInstanceExtensionProperties(NULL, &available_extension_count, available_props);
    printf("\nAvailable extensions\n");
    for (i32 i = 0; i < (i32)available_extension_count; i++) {
        LOG(info, "%s", available_props[i].extensionName);
    }

    VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
    if (enabled_validation_layers) {
        create_info.enabledLayerCount = validation_layers_count;
        create_info.ppEnabledLayerNames = validation_layers;

        populate_debug_info(&debug_create_info);
        create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debug_create_info;
    } else {
        create_info.enabledLayerCount = 0;
    }


    // Create instance
    VkResult res = vkCreateInstance(&create_info, NULL, &r->instance) ;
    LOG(debug, "Instance Result: %d", res);
    if (res != VK_SUCCESS) {
        panic("Instance Creation");
        exit(1);
    }


}

void r_vk_deinit(
) {
    vkDestroySurfaceKHR(r->instance, r->surface, NULL);
    vkDestroyDevice(r->device, NULL);

    if (enabled_validation_layers) {
        destroy_debug_util(r->instance, NULL, &r->debug_messenger);
    }
    vkDestroyInstance(r->instance, NULL);
}

// SURFACE

static void _vk_create_surface(
    GLFWwindow **w
) {
    VkResult res = glfwCreateWindowSurface(r->instance, *w, NULL, &r->surface);
    LOG(debug, "result: %d", res);
    if (res != VK_SUCCESS) {
        panic("cant make a surface");
    }
}


// DEVICE

bool _vk_queue_family_complete(
    QueueFamiliesIndices fam
) {
    return (fam.graphics_family != UINT32_MAX && fam.present_family != UINT32_MAX);
}

static QueueFamiliesIndices _vk_find_queue_families(
    VkPhysicalDevice device
) {
    QueueFamiliesIndices indices = {
        .graphics_family = UINT32_MAX,
        .present_family = UINT32_MAX,
    };

    u32 queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, NULL);
    assert(queue_family_count > 0);

    VkQueueFamilyProperties *queue_family_properties = c_arena_alloc(&r->arena, queue_family_count * sizeof(VkQueueFamilyProperties));
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_family_properties);


    LOG(debug, "This queue family %d", queue_family_count);
    for (u32 i = 0; i < queue_family_count; i++) {
        LOG(debug, "%d", queue_family_properties[i].queueCount);
        if (queue_family_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphics_family = i;
        }
        VkBool32 present_supported = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(r->physical_device, i, r->surface, &present_supported);

        if ( present_supported ) {
            indices.present_family = i;
        }

        if (_vk_queue_family_complete(indices)) {
            break;
        }
    }

    return indices;
}


bool _vk_is_device_suitable(
    VkPhysicalDevice device
) {
    VkPhysicalDeviceProperties props;
    VkPhysicalDeviceFeatures feats;
    vkGetPhysicalDeviceProperties(device, &props);
    vkGetPhysicalDeviceFeatures(device, &feats);

    return true;
}

static bool _vk_pick_physical_device() {
    u32 device_count = 0;
    vkEnumeratePhysicalDevices(r->instance, &device_count, NULL);

    if (device_count == 0) {
        panic("Cannot find device that supports vulkan");
    }

    VkPhysicalDevice *devices = (VkPhysicalDevice*) c_arena_alloc(&r->arena, device_count * sizeof(VkPhysicalDevice));
    vkEnumeratePhysicalDevices(r->instance, &device_count, devices);

    for (usize i = 0; i < device_count; i++) {
        if (_vk_is_device_suitable(devices[i])) {
            r->physical_device = devices[i];
            break;
        }
    }

    if (r->physical_device == VK_NULL_HANDLE) {
        panic("Failed to find a suitable GPU");
    }
}

void _vk_create_logical_device() {
    QueueFamiliesIndices indices = _vk_find_queue_families(r->physical_device);
    assert(indices.graphics_family != UINT32_MAX);
    assert(indices.present_family != UINT32_MAX);

    u32 unique_indices_count = indices.present_family == indices.graphics_family ? 1 : 2;
    LOG(debug, "count: %d", unique_indices_count);
    u32 *queues = c_arena_alloc(&r->arena, unique_indices_count * sizeof(u32));
    if (unique_indices_count == 1) {
        queues[0] = indices.graphics_family;
    } else {
        queues[0] = indices.graphics_family;
        queues[1] = indices.present_family;
    }
    VkDeviceQueueCreateInfo *queue_infos = c_arena_alloc(&r->arena, unique_indices_count * sizeof(VkDeviceQueueCreateInfo));

    f32 queue_prio = 1.0;
    for (u32 i = 0; i < unique_indices_count; i++) {
        LOG(debug, "count through loop:");
        VkDeviceQueueCreateInfo queue_create_info = {0};
        queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.queueFamilyIndex = queues[i];
        queue_create_info.queueCount = 1;
        queue_create_info.pQueuePriorities = &queue_prio;
        queue_infos[i] = queue_create_info;
    }


    VkPhysicalDeviceFeatures device_features = {0};

    VkDeviceCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.pQueueCreateInfos = queue_infos;
    create_info.queueCreateInfoCount = unique_indices_count;
    create_info.pEnabledFeatures = &device_features;
    create_info.enabledExtensionCount = required_mac_count;
    create_info.ppEnabledExtensionNames = required_mac;

    assert(r->physical_device != NULL);
    VkResult res = vkCreateDevice(r->physical_device, &create_info, NULL, &r->device);
    if (res != VK_SUCCESS) {
        LOG(error, "Error Code: %d", res);
        panic("failed to create device");
    }

    vkGetDeviceQueue(r->device, indices.graphics_family, 0, &r->graphics_queue);
}


// DEBUG

// ============================================================================
static bool _check_validation_layers_support() {
    u32 layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, NULL);

    VkLayerProperties *layer_props = c_arena_alloc(&r->arena, layer_count * sizeof(VkLayerProperties));
    vkEnumerateInstanceLayerProperties(&layer_count, layer_props);
    LOG(debug, "layer count: %d", layer_count);

    for (u32 i = 0; i < validation_layers_count; i++) {
        const char* layer_name = validation_layers[i];
        bool layer_found = false;

        for (u32 j = 0; i < layer_count; j++) {
            VkLayerProperties layer = layer_props[j];
            LOG(warn, "%s\n%s", layer.layerName, layer_name);
            if (strcmp(layer_name, layer.layerName) == 0) {
                layer_found = true;
                break;
            }
        }
        if (!layer_found) return false;
    }

    return true;
}

static ArrayString* _get_required_extensions() {
    ArrayString *as = c_array_string_create(&r->arena, 8);

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    for (uint32_t i = 0; i < glfwExtensionCount; i++) {
        c_array_string_push(&r->arena, as, glfwExtensions[i]);
    }

    for (uint32_t i = 0; i < required_count; i++) {
        c_array_string_push(&r->arena, as, required_extensions[i]);
    }

    if (enabled_validation_layers) {
        c_array_string_push(&r->arena, as, VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    for (uint32_t i = 0; i < as->len; i++) {
        LOG(debug, "%s", as->data[i]);
        //printf("%s\n", totalExtensions[i]);
    }

    return as;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL _debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
    void* p_user_data
) {

    if (message_severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        LOG(error, "%s", p_callback_data->pMessage);
    }
    if (message_severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        LOG(warn, "%s", p_callback_data->pMessage);
    }
    if (message_severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
        //LOG(info, "%s", p_callback_data->pMessage);
    }
    if (p_user_data && message_type) {}

    return VK_FALSE;
}


static void r_vk_setup_debug() {
    LOG(info, "%d", enabled_validation_layers);
    if (!enabled_validation_layers) return;

    VkDebugUtilsMessengerCreateInfoEXT create_info;
    populate_debug_info(&create_info);

    VkResult res = create_debug_util_messenger(r->instance, &create_info, NULL, &r->debug_messenger);
    LOG(debug, "%d", res);

    if (create_debug_util_messenger(r->instance, &create_info, NULL, &r->debug_messenger) != VK_SUCCESS) {
        panic("Failed to setup debug");
    }
}

static VkResult create_debug_util_messenger(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *p_create_info,
    const VkAllocationCallbacks *p_allocator,
    VkDebugUtilsMessengerEXT *p_messenger
) {
    PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    if (func != NULL) {
        return func(instance, p_create_info, p_allocator, p_messenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

static void populate_debug_info(
    VkDebugUtilsMessengerCreateInfoEXT* create_info
) {
    *create_info = (VkDebugUtilsMessengerCreateInfoEXT){};
    create_info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    create_info->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;

    create_info->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    create_info->pfnUserCallback = _debug_callback;
    create_info->pUserData = NULL;

}
static void destroy_debug_util( VkInstance instance,
    const VkAllocationCallbacks *p_allocator,
    VkDebugUtilsMessengerEXT *p_messenger
) {
    PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    if (func != NULL) {
        return func(instance, *p_messenger, p_allocator);
    }

}
