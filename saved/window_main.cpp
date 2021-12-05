
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

global bool global_running;


LRESULT win_message_handler_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param){
    LRESULT result = 0;
    switch(message){
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
            while(global_running){

                MSG message;
                while(PeekMessageA(&message, window, 0, 0, PM_REMOVE)){
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
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

