#pragma once

#include <GLFW/glfw3.h>

#include <map>

#include "../Window/Window.h"

#include "../Logging/Log.h"

typedef int VLK_KEY_CODE;
typedef int VLK_MOUSE_BUTTON_CODE;

typedef int VLK_EVENT;

#define VLK_UNKNOWN_ACTION        -1

#define VLK_RELEASE                0

#define VLK_PRESS                  1

#define VLK_HAT_CENTERED           0
#define VLK_HAT_UP                 1
#define VLK_HAT_RIGHT              2
#define VLK_HAT_DOWN               4
#define VLK_HAT_LEFT               8
#define VLK_HAT_RIGHT_UP           (VLK_HAT_RIGHT | VLK_HAT_UP)
#define VLK_HAT_RIGHT_DOWN         (VLK_HAT_RIGHT | VLK_HAT_DOWN)
#define VLK_HAT_LEFT_UP            (VLK_HAT_LEFT  | VLK_HAT_UP)
#define VLK_HAT_LEFT_DOWN          (VLK_HAT_LEFT  | VLK_HAT_DOWN)

#define VLK_KEY_UNKNOWN            -1

#define VLK_KEY_SPACE              32
#define VLK_KEY_APOSTROPHE         39
#define VLK_KEY_COMMA              44
#define VLK_KEY_MINUS              45
#define VLK_KEY_PERIOD             46
#define VLK_KEY_SLASH              47
#define VLK_KEY_0                  48
#define VLK_KEY_1                  49
#define VLK_KEY_2                  50
#define VLK_KEY_3                  51
#define VLK_KEY_4                  52
#define VLK_KEY_5                  53
#define VLK_KEY_6                  54
#define VLK_KEY_7                  55
#define VLK_KEY_8                  56
#define VLK_KEY_9                  57
#define VLK_KEY_SEMICOLON          59
#define VLK_KEY_EQUAL              61
#define VLK_KEY_A                  65
#define VLK_KEY_B                  66
#define VLK_KEY_C                  67
#define VLK_KEY_D                  68
#define VLK_KEY_E                  69
#define VLK_KEY_F                  70
#define VLK_KEY_G                  71
#define VLK_KEY_H                  72
#define VLK_KEY_I                  73
#define VLK_KEY_J                  74
#define VLK_KEY_K                  75
#define VLK_KEY_L                  76
#define VLK_KEY_M                  77
#define VLK_KEY_N                  78
#define VLK_KEY_O                  79
#define VLK_KEY_P                  80
#define VLK_KEY_Q                  81
#define VLK_KEY_R                  82
#define VLK_KEY_S                  83
#define VLK_KEY_T                  84
#define VLK_KEY_U                  85
#define VLK_KEY_V                  86
#define VLK_KEY_W                  87
#define VLK_KEY_X                  88
#define VLK_KEY_Y                  89
#define VLK_KEY_Z                  90
#define VLK_KEY_LEFT_BRACKET       91
#define VLK_KEY_BACKSLASH          92
#define VLK_KEY_RIGHT_BRACKET      93
#define VLK_KEY_GRAVE_ACCENT       96
#define VLK_KEY_WORLD_1            161
#define VLK_KEY_WORLD_2            162

#define VLK_KEY_ESCAPE             256
#define VLK_KEY_ENTER              257
#define VLK_KEY_TAB                258
#define VLK_KEY_BACKSPACE          259
#define VLK_KEY_INSERT             260
#define VLK_KEY_DELETE             261
#define VLK_KEY_RIGHT              262
#define VLK_KEY_LEFT               263
#define VLK_KEY_DOWN               264
#define VLK_KEY_UP                 265
#define VLK_KEY_PAGE_UP            266
#define VLK_KEY_PAGE_DOWN          267
#define VLK_KEY_HOME               268
#define VLK_KEY_END                269
#define VLK_KEY_CAPS_LOCK          280
#define VLK_KEY_SCROLL_LOCK        281
#define VLK_KEY_NUM_LOCK           282
#define VLK_KEY_PRINT_SCREEN       283
#define VLK_KEY_PAUSE              284
#define VLK_KEY_F1                 290
#define VLK_KEY_F2                 291
#define VLK_KEY_F3                 292
#define VLK_KEY_F4                 293
#define VLK_KEY_F5                 294
#define VLK_KEY_F6                 295
#define VLK_KEY_F7                 296
#define VLK_KEY_F8                 297
#define VLK_KEY_F9                 298
#define VLK_KEY_F10                299
#define VLK_KEY_F11                300
#define VLK_KEY_F12                301
#define VLK_KEY_F13                302
#define VLK_KEY_F14                303
#define VLK_KEY_F15                304
#define VLK_KEY_F16                305
#define VLK_KEY_F17                306
#define VLK_KEY_F18                307
#define VLK_KEY_F19                308
#define VLK_KEY_F20                309
#define VLK_KEY_F21                310
#define VLK_KEY_F22                311
#define VLK_KEY_F23                312
#define VLK_KEY_F24                313
#define VLK_KEY_F25                314
#define VLK_KEY_KP_0               320
#define VLK_KEY_KP_1               321
#define VLK_KEY_KP_2               322
#define VLK_KEY_KP_3               323
#define VLK_KEY_KP_4               324
#define VLK_KEY_KP_5               325
#define VLK_KEY_KP_6               326
#define VLK_KEY_KP_7               327
#define VLK_KEY_KP_8               328
#define VLK_KEY_KP_9               329
#define VLK_KEY_KP_DECIMAL         330
#define VLK_KEY_KP_DIVIDE          331
#define VLK_KEY_KP_MULTIPLY        332
#define VLK_KEY_KP_SUBTRACT        333
#define VLK_KEY_KP_ADD             334
#define VLK_KEY_KP_ENTER           335
#define VLK_KEY_KP_EQUAL           336
#define VLK_KEY_LEFT_SHIFT         340
#define VLK_KEY_LEFT_CONTROL       341
#define VLK_KEY_LEFT_ALT           342
#define VLK_KEY_LEFT_SUPER         343
#define VLK_KEY_RIGHT_SHIFT        344
#define VLK_KEY_RIGHT_CONTROL      345
#define VLK_KEY_RIGHT_ALT          346
#define VLK_KEY_RIGHT_SUPER        347
#define VLK_KEY_MENU               348

#define VLK_KEY_LAST               VLK_KEY_MENU

#define VLK_MOUSE_BUTTON_UNKNOWN  -1

#define VLK_MOUSE_BUTTON_1         0
#define VLK_MOUSE_BUTTON_2         1
#define VLK_MOUSE_BUTTON_3         2
#define VLK_MOUSE_BUTTON_4         3
#define VLK_MOUSE_BUTTON_5         4
#define VLK_MOUSE_BUTTON_6         5
#define VLK_MOUSE_BUTTON_7         6
#define VLK_MOUSE_BUTTON_8         7
#define VLK_MOUSE_BUTTON_LAST      VLK_MOUSE_BUTTON_8
#define VLK_MOUSE_BUTTON_LEFT      VLK_MOUSE_BUTTON_1
#define VLK_MOUSE_BUTTON_RIGHT     VLK_MOUSE_BUTTON_2
#define VLK_MOUSE_BUTTON_MIDDLE    VLK_MOUSE_BUTTON_3

namespace Velkro
{
	class Event
	{
	public:
		using EventCallback = std::function<void(Event& event)>;

		VELKRO_API		static void SetEventCallback(EventCallback eventCallback);

		VELKRO_API		static void Update(Window& window);

		VELKRO_API		VLK_EVENT GetKeyEvent(VLK_KEY_CODE key);
		VELKRO_API		VLK_EVENT GetMouseButtonEvent(VLK_MOUSE_BUTTON_CODE mouseButton);

	private:
		VELKRO_API		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		VELKRO_API		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		static inline EventCallback m_EventCallback;

		static inline std::map<VLK_KEY_CODE, VLK_EVENT> m_KeyEvents;
		static inline std::map<VLK_MOUSE_BUTTON_CODE, VLK_EVENT> m_MouseButtonEvents;
	};
}