#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef float f32;
typedef double f64;

#define global static
#define Kilobytes(x) (x * 1024LL)
#define Megabytes(x) (Kilobytes(x) * 1024LL)
#define Gigabytes(x) (Megabytes(x) * 1024LL)
#define Terabytes(x) (Gigaybtes(x) * 1024LL)

#define GET_TICKS(name) i64 name(void)
typedef GET_TICKS(GetTicks);
#define GET_SECONDS_ELAPSED(name) f64 name(i64 start, i64 end)
typedef GET_SECONDS_ELAPSED(GetSecondsElapsed);
#define GET_MS_ELAPSED(name) f64 name(i64 start, i64 end)
typedef GET_MS_ELAPSED(GetMsElapsed);

typedef struct Clock{
    i32 dt;
    i64 frequency;
    GetTicks* get_ticks; 
    GetSecondsElapsed* get_seconds_elapsed; 
    GetMsElapsed* get_ms_elapsed; 
} Clock;

typedef struct Button{
    bool pressed;
} Button;

typedef struct Controller{
    Button up;
    Button down;
    Button left;
    Button right;
} Controller;

typedef struct RenderBuffer{
    void* base;
    size_t size;

    i32 width;
    i32 height;
    i32 bytes_per_pixel;
    i32 stride;

    BITMAPINFO bitmap_info;
} RenderBuffer;

typedef struct Memory{
    void* base;
    size_t size;

    void* permanent_base;
    size_t permanent_size;
    void* transient_base;
    size_t transient_size;

    bool initialized;
} Memory;

global bool global_running;
global RenderBuffer render_buffer;
global Controller controller;
global Memory memory;
global Clock clock;


static void
print(char *format, ...) {
    char buffer[4096] = {0};
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    printf("%s", buffer);
    OutputDebugStringA(buffer);
}

static void
init_render_buffer(RenderBuffer* render_buffer, i32 width, i32 height){
    render_buffer->width = width;
    render_buffer->height = height;

    render_buffer->bitmap_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    render_buffer->bitmap_info.bmiHeader.biWidth = width;
    render_buffer->bitmap_info.bmiHeader.biHeight = -height;
    render_buffer->bitmap_info.bmiHeader.biPlanes = 1;
    render_buffer->bitmap_info.bmiHeader.biBitCount = 32;
    render_buffer->bitmap_info.bmiHeader.biCompression = BI_RGB;

    i32 bytes_per_pixel = 4;
    render_buffer->bytes_per_pixel = bytes_per_pixel;
    render_buffer->stride = width * bytes_per_pixel;
    render_buffer->size = width * height * bytes_per_pixel;
    render_buffer->base = VirtualAlloc(0, render_buffer->size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
}

static void
update_window(HWND window, RenderBuffer render_buffer){
    HDC device_context = GetDC(window);
    if(StretchDIBits(device_context, 
                     0, 0, render_buffer.width, render_buffer.height,
                     0, 0, render_buffer.width, render_buffer.height,
                     render_buffer.base, &render_buffer.bitmap_info, DIB_RGB_COLORS, SRCCOPY))
    {
    }
    else{
        OutputDebugStringA("StrechDIBits failed\n");
    }
}

GET_TICKS(get_ticks){
    LARGE_INTEGER result;
    QueryPerformanceCounter(&result);
    return(result.QuadPart);
}

GET_SECONDS_ELAPSED(get_seconds_elapsed){
    f64 result;
    result = ((f64)(start - end) / ((f64)clock.frequency));
    return(result);
}

GET_MS_ELAPSED(get_ms_elapsed){
    f64 result;
    result = (1000 * ((f64)(start - end) / ((f64)clock.frequency)));
    return(result);
}

#include "game.h"

LRESULT win_message_handler_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param){
    LRESULT result = 0;
    switch(message){
        case WM_PAINT:{
            PAINTSTRUCT paint;
            BeginPaint(window, &paint);
            update_window(window, render_buffer);
            EndPaint(window, &paint);
        } break;
        case WM_CLOSE:
        case WM_QUIT:
        case WM_DESTROY:{
            OutputDebugStringA("quiting\n");
            global_running = false;
        } break;
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP:{
            bool was_down = ((l_param & (1 << 30)) != 0);
            bool is_down = ((l_param & (1 << 31)) == 0);
            if(is_down != was_down){
                switch(w_param){
                    case 'W':{
                        controller.up.pressed = is_down;
                    } break;
                    case 'S':{
                        controller.down.pressed = is_down;
                    } break;
                    case 'A':{
                        controller.left.pressed = is_down;
                    } break;
                    case 'D':{
                        controller.right.pressed = is_down;
                    } break;
                    case VK_ESCAPE:{
                        OutputDebugStringA("quiting\n");
                        global_running = false;
                    } break;
                }
            }
        } break;
        default:{
            result = DefWindowProc(window, message, w_param, l_param);
        } break;
    }
    return(result);
}

i32 WinMain(HINSTANCE instance, HINSTANCE pinstance, LPSTR command_line, i32 window_type){
    WNDCLASS window_class = {0};
    window_class.style = CS_HREDRAW|CS_VREDRAW;
    window_class.lpfnWndProc = win_message_handler_callback;
    window_class.hInstance = instance;
    window_class.lpszClassName = "window class";

    memory.permanent_size = Megabytes(4);
    memory.transient_size = Gigabytes(4);
    memory.size = memory.permanent_size + memory.transient_size;
    memory.base = VirtualAlloc(0, memory.size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    memory.permanent_base = memory.base;
    memory.transient_base = (u8*)memory.base + memory.permanent_size;

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock.frequency = frequency.QuadPart;
    clock.get_ticks = get_ticks;
    clock.get_seconds_elapsed = get_seconds_elapsed;
    clock.get_ms_elapsed = get_ms_elapsed;
    clock.dt = 1/60;

    if(RegisterClassA(&window_class)){
        HWND window = CreateWindowA(window_class.lpszClassName, "Title", WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instance, 0);

        if(window){
            global_running = true;
            init_render_buffer(&render_buffer, 1024, 768);
            while(global_running){

                MSG message;
                while(PeekMessageA(&message, window, 0, 0, PM_REMOVE)){
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }

                update_game(&memory, &render_buffer, &controller, &clock);
                //update_game(&memory, &render_buffer, &sound, &controller, &clock, &threads);
                update_window(window, render_buffer);
            }
        }
        else{
            OutputDebugStringA("CreateWindowA failed\n");
        }
    }
    else{
        OutputDebugStringA("RegisterClassA failed\n");
    }
    return(0);
}

