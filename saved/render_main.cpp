
#include <windows.h>
#include <stdint.h>
#include <stdbool.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define global static

typedef struct RenderBuffer{
    void* base;
    size_t size;

    i32 width;
    i32 height;
    i32 bytes_per_pixel;
    i32 stride;

    BITMAPINFO bitmap_info;
} RenderBuffer;

global bool global_running;
global RenderBuffer render_buffer;

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
        case WM_KEYUP:
        case WM_SYSKEYUP:{
            if(w_param == VK_ESCAPE){
                OutputDebugStringA("quiting\n");
                global_running = false;
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

                u8* row = (u8*)render_buffer.base;
                for(i32 y=0; y < render_buffer.height; ++y){
                    u32* pixel = (u32*)row;
                    for(i32 x=0; x < render_buffer.width; ++x){
                        *pixel++ = (100 << 16|100);
                    }
                    row += render_buffer.stride;
                }

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

