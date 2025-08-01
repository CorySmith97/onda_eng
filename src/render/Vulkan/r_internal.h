#pragma once

#include "../core/core.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <_stdio.h>
#include <stdint.h>
#include <vulkan/vulkan.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
Forward Declarations
*/
typedef struct Render Render;
typedef struct QueueFamiliesIndices QueueFamiliesIndices;


static void r_vk_init();
static void r_vk_setup_debug();

//
// DEVICE
//
static bool _vk_select_device();
static bool _vk_pick_physical_device();
static QueueFamiliesIndices _vk_find_queue_families(VkPhysicalDevice);
static void _vk_create_logical_device();

//
// DEBUG
//
static bool _check_validation_layers_support();
static ArrayString* _get_required_extensions();
static VKAPI_ATTR VkBool32 VKAPI_CALL _debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
    void* p_user_data);

static VkResult create_debug_util_messenger( VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *p_create_info,
    const VkAllocationCallbacks *p_allocator,
    VkDebugUtilsMessengerEXT *p_messenger);

static void destroy_debug_util( VkInstance instance,
    const VkAllocationCallbacks *p_allocator,
    VkDebugUtilsMessengerEXT *p_messenger);

static void populate_debug_info(VkDebugUtilsMessengerCreateInfoEXT*);

//
// SURFACE
//
static void _vk_create_surface(GLFWwindow **);
