
#define Assert(x) if(!(x)) __debugbreak()

typedef struct PermanentState{
} PermanentState, State;

typedef struct TransientState{
} TransientState;

typedef struct Arena{
    void* base;
    size_t size;
    size_t used;
} Arena;

static void render_something(RenderBuffer* render_buffer){
    u8* row = (u8*)render_buffer->base;
    for(i32 y=0; y < render_buffer->height; ++y){
        u32* pixel = (u32*)row;
        for(i32 x=0; x < render_buffer->width; ++x){
            *pixel++ = (100 << 16|100);
        }
        row += render_buffer->stride;
    }
}

static void update_game(Memory* memory, RenderBuffer* render_buffer, Controller* controller, Clock* clock){

    Assert(sizeof(PermanentState) < memory->permanent_size);
    Assert(sizeof(TransientState) < memory->permanent_size);
    PermanentState* permanent_state = (PermanentState*)memory->permanent_base;
    TransientState* transient_state = (TransientState*)memory->transient_base;

    if(memory->initialized){
        memory->initialized = true;
    }

    render_something(render_buffer);
}
