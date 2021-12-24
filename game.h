typedef struct Arena{
    void* base;
    size_t size;
    size_t used;
} Arena;

typedef struct PermanentState{
    Arena arena;
} PermanentState, State;

typedef struct TransientState{
    Arena arena;
} TransientState;

static void
init_arena(Arena* arena, void* base, size_t size){
    arena->base = base;
    arena->size = size;
    arena->used = 0;
}

#define allocate_array(arena, count, type) allocate_size_(arena, count * sizeof(type));
#define allocate_struct(arena, type) allocate_size_(arena, sizeof(type));
#define allocate_size(arena, size) allocate_size_(arena, size);
static void*
allocate_size_(Arena* arena, size_t size){
    Assert((arena->used + size) < arena->size);
    void* result = (u8*)arena->base + arena->used;
    arena->used += size;
    return(result);
}

static void
update_game(Memory* memory, RenderBuffer* render_buffer, Controller* controller, Clock* clock){

    Assert(sizeof(PermanentState) <= memory->permanent_size);
    Assert(sizeof(TransientState) <= memory->transient_size);
    PermanentState* permanent_state = (PermanentState*)memory->permanent_base;
    TransientState* transient_state = (TransientState*)memory->transient_base;

    if(!memory->initialized){
        init_arena(&permanent_state->arena, (u8*)memory->permanent_base + sizeof(PermanentState), memory->permanent_size - sizeof(PermanentState));
        init_arena(&transient_state->arena, (u8*)memory->transient_base + sizeof(TransientState), memory->transient_size - sizeof(TransientState));
    }
}
