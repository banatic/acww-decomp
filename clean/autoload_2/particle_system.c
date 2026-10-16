/* The particle system's manager: its lists, its creation from the particle file, its emitters
 * and the frame's update and draw (particle.h). */
#include "particle.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"

static_assert(sizeof(ParticleHeader) == 0x54, "a resource's header");
static_assert(offsetof(ParticleHeader, emitter_life) == 0x38, "ParticleHeader.emitter_life");
static_assert(offsetof(ParticleHeader, misc) == 0x44, "ParticleHeader.misc");
static_assert(offsetof(ParticleHeader, draw_flags) == 0x50, "ParticleHeader.draw_flags");
static_assert(sizeof(ParticleChild) == 0x14, "a resource's child part");
static_assert(sizeof(ParticleResource) == 0x20, "a resource");
static_assert(sizeof(ParticleTexture) == 0x14, "a texture");
static_assert(sizeof(ParticleFile) == 0x20, "the file's header");
static_assert(sizeof(Particle) == 0x44, "a particle");
static_assert(offsetof(Particle, visibility) == 0x2e, "Particle.visibility");
static_assert(offsetof(Particle, emitter_pos) == 0x38, "Particle.emitter_pos");
static_assert(sizeof(ParticleEmitter) == 0x84, "an emitter");
static_assert(offsetof(ParticleEmitter, misc) == 0x68, "ParticleEmitter.misc");
static_assert(offsetof(ParticleEmitter, callback) == 0x78, "ParticleEmitter.callback");
static_assert(sizeof(ParticleSystem) == 0x3c, "the manager");

/* The frame's parity (0 or 1), for the emitters updated every other frame. */
extern u16 data_021fd274;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void GX_BeginLoadTex(void);
extern void GX_LoadTex(const void *src, u32 dest, u32 size);
extern void GX_EndLoadTex(void);
extern void GX_BeginLoadTexPltt(void);
extern void GX_LoadTexPltt(const void *src, u32 dest, u32 size);
extern void GX_EndLoadTexPltt(void);
/* NitroSystem's default VRAM allocators: a key whose low 16 bits are the address over 8. */
extern u32 (*NNS_GfdDefaultFuncAllocTexVram)(u32 size, int compressed, int unused);
extern u32 (*NNS_GfdDefaultFuncAllocPlttVram)(u32 size, int four_colors, int unused);
/* The game's own functions, for the pointers the manager hands on or keeps. */
extern int func_020fab6c(int size, int four_colors);
extern int func_020faba4(int size, int compressed);
extern void func_020ff808(const void *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);
extern void func_020ff740(const void *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);
extern void func_020ff6bc(const void *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);
extern void func_020ff5e4(const void *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);
extern void func_020ff4c8(const void *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);
extern void func_020ff434(const void *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);

#define REG_DISP3DCNT (*(volatile u16 *) 0x04000060)
#define DISP3DCNT_ALPHA_BLEND 0x0008
/* The two bits a write of 1 acknowledges (the line buffer's underflow, the RAM's overflow). */
#define DISP3DCNT_ACKNOWLEDGE 0x3000

/* --- The lists --- */

/* func_020ff83c: `node` taken out of `list`, and given back. Its own links are left as they
 * were. */
ParticleLink *ParticleList_Remove(ParticleList *list, ParticleLink *node)
{
    if (node->next == NULL) {
        if (list->first == node) {
            list->first = NULL;
        } else {
            node->prev->next = NULL;
        }
    } else if (list->first == node) {
        list->first = node->next;
        list->first->prev = NULL;
    } else {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }
    list->count--;
    return node;
}
CLEAN_AS(func_020ff83c, ParticleList_Remove)

/* func_020ff8a8: the list's first member taken out; NULL when it is empty. */
ParticleLink *ParticleList_Pop(ParticleList *list)
{
    ParticleLink *node = list->first;

    if (node == NULL) {
        return NULL;
    }
    list->first = node->next;
    if (list->first != NULL) {
        node->next->prev = NULL;
    }
    list->count--;
    return node;
}
CLEAN_AS(func_020ff8a8, ParticleList_Pop)

/* func_020ff8ec: `node` put first in the list.
 * REQUIRES: the members are word-aligned, as the manager's arrays of them are (the ARM9
 * stores to a misaligned one at the word below). */
void ParticleList_Push(ParticleList *list, ParticleLink *node)
{
    if (list->first == NULL) {
        list->first = node;
        node->next = NULL;
        node->prev = NULL;
    } else {
        node->next = list->first;
        node->prev = NULL;
        list->first->prev = node;
        list->first = node;
    }
    list->count++;
}
CLEAN_AS(func_020ff8ec, ParticleList_Push)

/* --- Emitters --- */

/* func_020fa090: `emitter` moved to `offset` from its resource's base position, and made to
 * give off its particles at once. */
void ParticleSys_EmitAt(ParticleSystem *sys, ParticleEmitter *emitter, const Vec3 *offset)
{
    emitter->position.x = particle_add(offset->x, emitter->resource->header->base_pos.x);
    emitter->position.y = particle_add(offset->y, emitter->resource->header->base_pos.y);
    emitter->position.z = particle_add(offset->z, emitter->resource->header->base_pos.z);
    ParticleSys_EmitFrom(emitter, &sys->free_particles);
}
CLEAN_AS(func_020fa090, ParticleSys_EmitAt)

/* A free emitter made from resource `resource` at `pos`, handed to `init` when there is one,
 * and put in the manager's list. NULL without a free emitter, and for a self-maintaining
 * resource (whose emitter ends by itself, so the caller must not keep it). */
static ParticleEmitter *create_emitter(ParticleSystem *sys, int resource, const Vec3 *pos,
                                       void (*init)(ParticleEmitter *emitter))
{
    ParticleEmitter *emitter;

    if (sys->free_emitters.first == NULL) {
        return NULL;
    }
    emitter = (ParticleEmitter *) ParticleList_Pop(&sys->free_emitters);
    ParticleEmitter_Init(emitter, &sys->resources[resource], pos);
    if (init != NULL) {
        init(emitter);
    }
    ParticleList_Push(&sys->emitters, &emitter->link);
    if (emitter->resource->header->flags & PARTICLE_SELF_MAINTAINING) {
        return NULL;
    }
    return emitter;
}

/* func_020fa0fc: an emitter of resource `resource` at the origin, given to `init` (a function
 * of the game's) before it starts. */
ParticleEmitter *ParticleSys_CreateEmitterWith(ParticleSystem *sys, int resource, void (*init)(ParticleEmitter *emitter))
{
    Vec3 origin = {0, 0, 0};

    return create_emitter(sys, resource, &origin, init);
}
CLEAN_AS(func_020fa0fc, ParticleSys_CreateEmitterWith)

/* func_020fa190: an emitter of resource `resource` at `pos`. */
ParticleEmitter *ParticleSys_CreateEmitterAt(ParticleSystem *sys, int resource, const Vec3 *pos)
{
    return create_emitter(sys, resource, pos, NULL);
}
CLEAN_AS(func_020fa190, ParticleSys_CreateEmitterAt)

/* The emitter's resource's header, read afresh: the emitter's fields are written between the
 * reads, in the ROM's order, so the result is the ROM's even for a header that overlaps them. */
static const ParticleHeader *header_of(const ParticleEmitter *emitter)
{
    return emitter->resource->header;
}

/* A texture coordinate the quad reaches: 1 << repeat textures. */
static s16 tex_extent(u32 repeat)
{
    return (s16) (u16) (0x1000u << repeat);
}

/* `*coord` turned round. */
static void flip(s16 *coord)
{
    *coord = (s16) (u16) (0u - (u16) *coord);
}

/* func_020fb640: `emitter` made afresh from `resource` at `pos` (from the resource's base
 * position), with the resource's values; its own collision height none, its colour white;
 * its texture coordinates 1 << repeat, negative when flipped. */
void ParticleEmitter_Init(ParticleEmitter *emitter, const ParticleResource *resource, const Vec3 *pos)
{
    emitter->resource = resource;
    emitter->state = 0;
    emitter->position.x = particle_add(pos->x, header_of(emitter)->base_pos.x);
    emitter->position.y = particle_add(pos->y, header_of(emitter)->base_pos.y);
    emitter->position.z = particle_add(pos->z, header_of(emitter)->base_pos.z);
    emitter->velocity.z = 0;
    emitter->velocity.y = 0;
    emitter->velocity.x = 0;
    emitter->age = 0;
    emitter->emission_fraction = 0;
    {
        const ParticleHeader *header = header_of(emitter);
        fx16 x = header->axis.x;
        fx16 y = header->axis.y;
        emitter->axis.x = x;
        emitter->axis.y = y;
        emitter->axis.z = header->axis.z;
    }
    emitter->init_angle = 0;
    emitter->radius = header_of(emitter)->radius;
    emitter->length = header_of(emitter)->length;
    emitter->speed = header_of(emitter)->speed;
    emitter->axis_speed = header_of(emitter)->axis_speed;
    emitter->base_scale = header_of(emitter)->base_scale;
    emitter->particle_life = header_of(emitter)->particle_life;
    emitter->color = 0x7fff;
    emitter->misc = particle_with_bits(emitter->misc, EMITTER_INTERVAL_SHIFT, 8, header_of(emitter)->emission_interval);
    emitter->misc = particle_with_bits(emitter->misc, EMITTER_BASE_ALPHA_SHIFT, 8, header_of(emitter)->base_alpha);
    emitter->misc &= 0xffff; /* no update cycle */
    emitter->collision_y = EMITTER_NO_COLLISION_Y;
    emitter->tex_s = tex_extent(particle_bits(header_of(emitter)->misc, PARTICLE_TEX_S_SHIFT, 2));
    emitter->tex_t = tex_extent(particle_bits(header_of(emitter)->misc, PARTICLE_TEX_T_SHIFT, 2));
    if (header_of(emitter)->tex_flip & 1) {
        flip(&emitter->tex_s);
    }
    if (header_of(emitter)->tex_flip & 2) {
        flip(&emitter->tex_t);
    }
    {
        const ParticleResource *res = emitter->resource;
        if (res->header->flags & PARTICLE_HAS_CHILDREN) {
            emitter->child_tex_s = tex_extent(particle_bits(res->child->tex_flags, 0, 2));
            emitter->child_tex_t = tex_extent(particle_bits(emitter->resource->child->tex_flags, 2, 2));
            if (emitter->resource->child->tex_flags & 0x10) {
                flip(&emitter->child_tex_s);
            }
            if (emitter->resource->child->tex_flags & 0x20) {
                flip(&emitter->child_tex_t);
            }
        }
    }
    emitter->link.prev = NULL;
    emitter->link.next = NULL;
    emitter->children.first = NULL;
    emitter->particles.first = NULL;
    emitter->children.count = 0;
    emitter->particles.count = 0;
    emitter->callback = NULL;
    emitter->user_ptr = NULL;
    emitter->user_data = 0;
}
CLEAN_AS(func_020fb640, ParticleEmitter_Init)

/* func_020fabdc: the emitter gives off its particles, taken from `free_particles`. */
void ParticleSys_EmitFrom(ParticleEmitter *emitter, ParticleList *free_particles)
{
    Particle_Emit(emitter, free_particles);
}
CLEAN_AS(func_020fabdc, ParticleSys_EmitFrom)

/* --- The frame's update --- */

/* The particle's polygon ID: the manager's fixed one, or the next in turn from min to max. */
static void give_polygon_id(ParticleSystem *sys, Particle *ptcl, int fixed)
{
    u32 id;

    if (fixed) {
        id = particle_bits(sys->polygon_ids, PARTICLE_ID_FIXED_SHIFT, 6);
    } else {
        u32 next;

        id = particle_bits(sys->polygon_ids, PARTICLE_ID_NEXT_SHIFT, 6);
        next = (id + 1) & 0x3f;
        if (next > particle_bits(sys->polygon_ids, PARTICLE_ID_MAX_SHIFT, 6)) {
            next = particle_bits(sys->polygon_ids, PARTICLE_ID_MIN_SHIFT, 6);
        }
        sys->polygon_ids = particle_with_bits(sys->polygon_ids, PARTICLE_ID_NEXT_SHIFT, 6, next);
    }
    ptcl->visibility = (u16) particle_with_bits(ptcl->visibility, PARTICLE_POLYGON_ID_SHIFT, 6, id);
}

/* The particle turned, slowed by the air, pushed by `acc` and moved by its velocity and the
 * emitter's. */
static void move_particle(Particle *ptcl, const ParticleEmitter *emitter, const Vec3 *acc, s32 air)
{
    ptcl->rotation = (u16) (ptcl->rotation + ptcl->angular_velocity);

    ptcl->velocity.x = particle_asr(particle_mul(ptcl->velocity.x, air), 9);
    ptcl->velocity.y = particle_asr(particle_mul(ptcl->velocity.y, air), 9);
    ptcl->velocity.z = particle_asr(particle_mul(ptcl->velocity.z, air), 9);

    ptcl->velocity.x = particle_add(ptcl->velocity.x, acc->x);
    ptcl->velocity.y = particle_add(ptcl->velocity.y, acc->y);
    ptcl->velocity.z = particle_add(ptcl->velocity.z, acc->z);

    ptcl->position.x = particle_add(ptcl->position.x, particle_add(ptcl->velocity.x, emitter->velocity.x));
    ptcl->position.y = particle_add(ptcl->position.y, particle_add(ptcl->velocity.y, emitter->velocity.y));
    ptcl->position.z = particle_add(ptcl->position.z, particle_add(ptcl->velocity.z, emitter->velocity.z));
}

/* The resource's behaviours, each given the particle and the acceleration to add to. */
static void run_behaviors(const ParticleResource *res, int count, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter)
{
    for (int i = 0; i < count; i++) {
        res->behaviors[i].fn(res->behaviors[i].data, ptcl, acc, emitter);
    }
}

/* The particle one frame older; given back to the free list once older than its life. */
static void age_particle(ParticleSystem *sys, ParticleList *list, Particle *ptcl)
{
    ptcl->age++;
    if (ptcl->age > ptcl->life) {
        ParticleList_Push(&sys->free_particles, ParticleList_Remove(list, &ptcl->link));
    }
}

typedef void (*ParticleAnimFn)(Particle *ptcl, const ParticleResource *res, int rate);

/* An animation of the frame, run on the particle's life rate or its loop's. */
typedef struct AnimStep {
    ParticleAnimFn fn;
    int on_loop;
} AnimStep;

/* func_020fadf8: the frame's update of an emitter. The emitter's callback is told before (0)
 * and after (1). Once started and within its life it gives off particles every `interval`
 * frames; then each particle runs its animations, follows the emitter if the resource says so,
 * runs the behaviours, moves, gives off its children when due, takes a polygon ID and ages;
 * then each child the same, with the child part's two animations. The emitter ages last.
 * QUIRK: an interval of 0 counts as 1 (the ROM's remainder by 0 is 0). */
void ParticleSys_UpdateEmitter(ParticleSystem *sys, ParticleEmitter *emitter)
{
    const ParticleResource *res = emitter->resource;
    const ParticleChild *child = res->child;
    const ParticleHeader *header = res->header;
    u32 flags = header->flags;
    s32 air = header->air_resistance + 0x180;
    int behaviors = res->behavior_count;
    AnimStep steps[4];
    int step_count = 0;
    Particle *ptcl;
    Particle *next;

    if (emitter->callback != NULL) {
        emitter->callback(emitter, 0);
    }

    if (header->emitter_life == 0 || emitter->age < header->emitter_life) {
        if (particle_mod(emitter->age, (u8) particle_bits(emitter->misc, EMITTER_INTERVAL_SHIFT, 8)) == 0 &&
            !(emitter->state & EMITTER_ENDING) && !(emitter->state & EMITTER_NO_EMISSION) &&
            (emitter->state & EMITTER_STARTED)) {
            Particle_Emit(emitter, &sys->free_particles);
        }
    }

    if (flags & PARTICLE_HAS_SCALE_ANIM) {
        steps[step_count].fn = ParticleAnim_Scale;
        steps[step_count++].on_loop = res->scale_anim->flags & 1;
    }
    if ((flags & PARTICLE_HAS_COLOR_ANIM) && !(res->color_anim->flags & 1)) {
        steps[step_count].fn = ParticleAnim_Color;
        steps[step_count++].on_loop = (res->color_anim->flags >> 1) & 1;
    }
    if (flags & PARTICLE_HAS_ALPHA_ANIM) {
        steps[step_count].fn = ParticleAnim_Alpha;
        steps[step_count++].on_loop = res->alpha_anim->flags & 1;
    }
    if ((flags & PARTICLE_HAS_TEX_ANIM) && !(res->tex_anim->flags & 1)) {
        steps[step_count].fn = ParticleAnim_Texture;
        steps[step_count++].on_loop = (res->tex_anim->flags >> 1) & 1;
    }

    for (ptcl = (Particle *) emitter->particles.first; ptcl != NULL; ptcl = next) {
        u8 rate[2];
        Vec3 acc = {0, 0, 0};

        next = (Particle *) ptcl->link.next;
        /* QUIRK: the rates are kept to a byte: 0 to 255 over the life, and over the loop. */
        rate[0] = (u8) (((u32) ptcl->life_factor * ptcl->age) >> 8);
        rate[1] = (u8) (ptcl->loop_offset + (((u32) ptcl->loop_factor * ptcl->age) >> 8));
        for (int i = 0; i < step_count; i++) {
            steps[i].fn(ptcl, res, rate[steps[i].on_loop]);
        }

        if (flags & PARTICLE_FOLLOW_EMITTER) {
            ptcl->emitter_pos = emitter->position;
        }
        run_behaviors(res, behaviors, ptcl, &acc, emitter);
        move_particle(ptcl, emitter, &acc, air);

        if (flags & PARTICLE_HAS_CHILDREN) {
            /* The first children come `delay` / 256 into the parent's life, then every
             * `interval` frames. */
            fx32 delay = particle_asr(particle_fx_mul(ptcl->life << 12, child->delay << 12), 8);
            fx32 since = particle_sub(ptcl->age << 12, delay);
            if (since >= 0 && particle_mod(since >> 12, child->interval) == 0) {
                Particle_EmitChildren(ptcl, emitter, &sys->free_particles);
            }
        }

        give_polygon_id(sys, ptcl, (emitter->resource->header->flags & PARTICLE_FIXED_POLYGON_ID) != 0);
        age_particle(sys, &emitter->particles, ptcl);
    }

    if (flags & PARTICLE_HAS_CHILDREN) {
        step_count = 0;
        if (child->flags & PARTICLE_CHILD_SCALE_ANIM) {
            steps[step_count].fn = ParticleAnim_ChildScale;
            steps[step_count++].on_loop = 0;
        }
        if (child->flags & PARTICLE_CHILD_ALPHA_ANIM) {
            steps[step_count].fn = ParticleAnim_ChildAlpha;
            steps[step_count++].on_loop = 0;
        }
        if (!(child->flags & PARTICLE_CHILD_BEHAVIORS)) {
            behaviors = 0;
        }

        for (ptcl = (Particle *) emitter->children.first; ptcl != NULL; ptcl = next) {
            /* QUIRK: with a life of 0 the ROM's division gives back age << 8, so 0. */
            u8 rate = (u8) particle_div(ptcl->age << 8, ptcl->life);
            Vec3 acc = {0, 0, 0};

            next = (Particle *) ptcl->link.next;
            for (int i = 0; i < step_count; i++) {
                steps[i].fn(ptcl, res, rate);
            }

            if (child->flags & PARTICLE_CHILD_FOLLOW_EMITTER) {
                ptcl->emitter_pos = emitter->position;
            }
            run_behaviors(res, behaviors, ptcl, &acc, emitter);
            move_particle(ptcl, emitter, &acc, air);

            give_polygon_id(sys, ptcl, (emitter->resource->header->flags & PARTICLE_CHILD_FIXED_POLYGON_ID) != 0);
            age_particle(sys, &emitter->children, ptcl);
        }
    }

    emitter->age++;

    if (emitter->callback != NULL) {
        emitter->callback(emitter, 1);
    }
}
CLEAN_AS(func_020fadf8, ParticleSys_UpdateEmitter)

/* func_020fa270: the frame's update of every emitter. One starts once older than its start
 * delay (its age then counts from 0); one not paused is updated every frame, or every other
 * frame when it has an update cycle (1 on even frames, 2 on odd ones); one that is ending, or
 * self-maintaining and older than its life, goes back to the free list once its particles and
 * children are all gone. */
void ParticleSys_Update(ParticleSystem *sys)
{
    ParticleLink *node = sys->emitters.first;

    while (node != NULL) {
        ParticleEmitter *emitter = (ParticleEmitter *) node;
        const ParticleHeader *header = emitter->resource->header;
        ParticleLink *next = node->next;

        if (!(emitter->state & EMITTER_STARTED) && emitter->age >= header->start_delay) {
            emitter->state |= EMITTER_STARTED;
            emitter->age = 0;
        }

        if (!(emitter->state & EMITTER_NO_UPDATE)) {
            u32 cycle = particle_bits(emitter->misc, EMITTER_UPDATE_CYCLE_SHIFT, 3);
            if (cycle == 0 || data_021fd274 == cycle - 1) {
                ParticleSys_UpdateEmitter(sys, emitter);
            }
        }

        if (((header->flags & PARTICLE_SELF_MAINTAINING) && header->emitter_life != 0 && (emitter->state & EMITTER_STARTED) &&
             emitter->age > header->emitter_life) ||
            (emitter->state & EMITTER_ENDING)) {
            if (emitter->particles.count == 0 && emitter->children.count == 0) {
                ParticleList_Push(&sys->free_emitters, ParticleList_Remove(&sys->emitters, node));
            }
        }
        node = next;
    }

    data_021fd274 = (u16) (data_021fd274 + 1);
    if (data_021fd274 > 1) {
        data_021fd274 = 0;
    }
}
CLEAN_AS(func_020fa270, ParticleSys_Update)

/* --- The frame's draw --- */

/* func_020fa204: every emitter not hidden drawn with the camera's `view` matrix; `callback`
 * (the game's) is asked about each particle's place.
 * HW: alpha blending is turned on in DISP3DCNT first; the acknowledge bits are written 0, so
 * left as they are. */
void ParticleSys_Draw(ParticleSystem *sys, const Mtx43 *view, ParticleDrawCallback callback)
{
    REG_DISP3DCNT = (u16) ((REG_DISP3DCNT & ~DISP3DCNT_ACKNOWLEDGE) | DISP3DCNT_ALPHA_BLEND);
    sys->view = view;
    for (ParticleLink *node = sys->emitters.first; node != NULL; node = node->next) {
        sys->emitter = (ParticleEmitter *) node;
        if (!(sys->emitter->state & EMITTER_HIDDEN)) {
            ParticleSys_DrawEmitter(sys, callback);
        }
    }
}
CLEAN_AS(func_020fa204, ParticleSys_Draw)

/* func_020fabe8: the emitter being drawn: its particles and its children, the children first
 * when the resource says so; the particles not when it hides them. */
void ParticleSys_DrawEmitter(ParticleSystem *sys, ParticleDrawCallback callback)
{
    const ParticleHeader *header = sys->emitter->resource->header;

    if (header->flags & PARTICLE_CHILDREN_FIRST) {
        ParticleSys_DrawChildren(sys, callback);
        if (!(header->flags & PARTICLE_HIDE_PARENTS)) {
            ParticleSys_DrawParents(sys, callback);
        }
    } else {
        if (!(header->flags & PARTICLE_HIDE_PARENTS)) {
            ParticleSys_DrawParents(sys, callback);
        }
        ParticleSys_DrawChildren(sys, callback);
    }
}
CLEAN_AS(func_020fabe8, ParticleSys_DrawEmitter)

typedef void (*ParticleDrawFn)(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback);

/* func_020fac60: the children of the emitter being drawn, with the child part's texture and
 * way of drawing. REQUIRES: a draw type of 0 to 2 (for 3 the ROM calls address 0 for each
 * child). */
void ParticleSys_DrawChildren(ParticleSystem *sys, ParticleDrawCallback callback)
{
    ParticleEmitter *emitter = sys->emitter;
    const ParticleResource *res = emitter->resource;
    ParticleDrawFn draw;

    if (!(res->header->flags & PARTICLE_HAS_CHILDREN)) {
        return;
    }
    ParticleDraw_BindTexture(&sys->textures[res->child->texture]);
    switch (particle_bits(res->child->flags, PARTICLE_CHILD_DRAW_SHIFT, 2)) {
        case 0:
            draw = ParticleDraw_ChildBillboard;
            break;
        case 1:
            draw = ParticleDraw_ChildStretched;
            break;
        case 2:
            draw = ParticleDraw_ChildPolygon;
            break;
        default:
            return;
    }
    for (ParticleLink *node = emitter->children.first; node != NULL; node = node->next) {
        draw(sys, (Particle *) node, callback);
    }
}
CLEAN_AS(func_020fac60, ParticleSys_DrawChildren)

/* func_020fad1c: the particles of the emitter being drawn, with the resource's texture, or
 * each its own when the resource animates them, and its way of drawing. REQUIRES: a draw type
 * of 0 to 2, as above. */
void ParticleSys_DrawParents(ParticleSystem *sys, ParticleDrawCallback callback)
{
    ParticleEmitter *emitter = sys->emitter;
    const ParticleHeader *header = emitter->resource->header;
    ParticleDrawFn draw;
    int own_textures;

    ParticleDraw_BindTexture(&sys->textures[header->texture]);
    switch (particle_bits(header->flags, PARTICLE_DRAW_SHIFT, 2)) {
        case 0:
            draw = ParticleDraw_Billboard;
            break;
        case 1:
            draw = ParticleDraw_Stretched;
            break;
        case 2:
            draw = ParticleDraw_Polygon;
            break;
        default:
            draw = NULL;
            break;
    }
    own_textures = (header->flags & PARTICLE_HAS_TEX_ANIM) != 0;
    for (ParticleLink *node = emitter->particles.first; node != NULL; node = node->next) {
        Particle *ptcl = (Particle *) node;

        if (own_textures) {
            ParticleDraw_BindTexture(&sys->textures[ptcl->texture]);
        } else {
            ParticleDraw_NoTexture(&sys->textures[ptcl->texture]);
        }
        if (draw == NULL) {
            return;
        }
        draw(sys, ptcl, callback);
    }
}
CLEAN_AS(func_020fad1c, ParticleSys_DrawParents)

/* --- Creation and the file --- */

/* func_020fab6c: `size` bytes of palette VRAM from NitroSystem's default allocator; the
 * address. */
int ParticleSys_AllocPaletteVram(int size, int four_colors)
{
    return (int) ((NNS_GfdDefaultFuncAllocPlttVram((u32) size, four_colors, 0) & 0xffff) << 3);
}
CLEAN_AS(func_020fab6c, ParticleSys_AllocPaletteVram)

/* func_020faba4: `size` bytes of texture VRAM, the same way. */
int ParticleSys_AllocTextureVram(int size, int compressed)
{
    return (int) ((NNS_GfdDefaultFuncAllocTexVram((u32) size, compressed, 0) & 0xffff) << 3);
}
CLEAN_AS(func_020faba4, ParticleSys_AllocTextureVram)

/* func_020fa3e4: each texture's palette loaded into palette VRAM where `alloc` (the game's)
 * puts it; a texture without a palette has address 0. 1. */
int ParticleSys_UploadPalettesWith(ParticleSystem *sys, u32 (*alloc)(u32 size, int four_colors))
{
    GX_BeginLoadTexPltt();
    for (int i = 0; i < sys->texture_count; i++) {
        ParticleTexture *texture = &sys->textures[i];
        const ParticleTexFile *file = texture->file;
        u32 addr = 0;

        if (file->palette_size != 0) {
            addr = alloc(file->palette_size, (file->param & PARTICLE_TEX_FORMAT_MASK) == PARTICLE_TEX_FORMAT_PLTT4);
            GX_LoadTexPltt((const u8 *) texture->file + file->palette, addr, file->palette_size);
        }
        texture->palette_addr = addr;
    }
    GX_EndLoadTexPltt();
    return 1;
}
CLEAN_AS(func_020fa3e4, ParticleSys_UploadPalettesWith)

/* func_020fa498: each texture's image loaded into texture VRAM where `alloc` (the game's)
 * puts it; a shared texture takes the address of the one it shares (loaded before it). 1. */
int ParticleSys_UploadTexturesWith(ParticleSystem *sys, u32 (*alloc)(u32 size, int compressed))
{
    GX_BeginLoadTex();
    for (int i = 0; i < sys->texture_count; i++) {
        ParticleTexture *texture = &sys->textures[i];
        const ParticleTexFile *file = texture->file;

        if (file->param & PARTICLE_TEX_SHARED) {
            texture->image_addr = sys->textures[particle_bits(file->param, PARTICLE_TEX_SHARED_ID_SHIFT, 8)].image_addr;
        } else {
            u32 addr = alloc(file->image_size, (file->param & PARTICLE_TEX_FORMAT_MASK) == PARTICLE_TEX_FORMAT_COMP4X4);
            GX_LoadTex((const u8 *) texture->file + sizeof(ParticleTexFile), addr, file->image_size);
            texture->image_addr = addr;
        }
    }
    GX_EndLoadTex();
    return 1;
}
CLEAN_AS(func_020fa498, ParticleSys_UploadTexturesWith)

/* func_020fa3bc: the palettes loaded with the default allocator. */
int ParticleSys_UploadPalettes(ParticleSystem *sys)
{
    return ParticleSys_UploadPalettesWith(sys, (u32 (*)(u32, int)) func_020fab6c);
}
CLEAN_AS(func_020fa3bc, ParticleSys_UploadPalettes)

/* func_020fa3d0: the textures loaded with the default allocator. */
int ParticleSys_UploadTextures(ParticleSystem *sys)
{
    return ParticleSys_UploadTexturesWith(sys, (u32 (*)(u32, int)) func_020faba4);
}
CLEAN_AS(func_020fa3d0, ParticleSys_UploadTextures)

/* `size` bytes of the file at `*offset`, which moves past them. */
static const u8 *take(const u8 *file, u32 *offset, u32 size)
{
    const u8 *part = file + *offset;
    *offset += size;
    return part;
}

/* The parts that follow a resource's header, in their order, with their sizes. */
#define SCALE_ANIM_SIZE 0xc
#define COLOR_ANIM_SIZE 0xc
#define ALPHA_ANIM_SIZE 8
#define TEX_ANIM_SIZE 0xc
#define CHILD_SIZE 0x14

/* The behaviours, in their order in the file: flag, function and size. */
static const struct {
    u32 flag;
    ParticleBehaviorFn fn;
    u32 size;
} behavior_kinds[] = {
    {PARTICLE_GRAVITY, (ParticleBehaviorFn) func_020ff808, 8},   {PARTICLE_RANDOM, (ParticleBehaviorFn) func_020ff740, 8},
    {PARTICLE_MAGNET, (ParticleBehaviorFn) func_020ff6bc, 0x10}, {PARTICLE_SPIN, (ParticleBehaviorFn) func_020ff5e4, 4},
    {PARTICLE_COLLISION, (ParticleBehaviorFn) func_020ff4c8, 8}, {PARTICLE_CONVERGE, (ParticleBehaviorFn) func_020ff434, 0x10},
};

/* func_020fa564: the resources read from the start of the particle file's resources: each a
 * header and the parts its flags announce, its behaviours in a table allocated for them (the
 * game's six functions, each with its part of the file). */
void ParticleSys_LoadResources(ParticleSystem *sys, const u8 *file)
{
    u32 offset = 0;

    sys->resources = sys->alloc(sys->resource_count * sizeof(ParticleResource));
    MI_CpuFill8(sys->resources, 0, sys->resource_count * sizeof(ParticleResource));

    for (int i = 0; i < sys->resource_count; i++) {
        ParticleResource *res = &sys->resources[i];
        u32 flags;
        u16 count = 0;

        res->header = (const ParticleHeader *) take(file, &offset, sizeof(ParticleHeader));
        flags = res->header->flags;
        res->scale_anim = flags & PARTICLE_HAS_SCALE_ANIM ? (const void *) take(file, &offset, SCALE_ANIM_SIZE) : NULL;
        res->color_anim = flags & PARTICLE_HAS_COLOR_ANIM ? (const void *) take(file, &offset, COLOR_ANIM_SIZE) : NULL;
        res->alpha_anim = flags & PARTICLE_HAS_ALPHA_ANIM ? (const void *) take(file, &offset, ALPHA_ANIM_SIZE) : NULL;
        res->tex_anim = flags & PARTICLE_HAS_TEX_ANIM ? (const void *) take(file, &offset, TEX_ANIM_SIZE) : NULL;
        res->child = flags & PARTICLE_HAS_CHILDREN ? (const void *) take(file, &offset, CHILD_SIZE) : NULL;

        for (size_t k = 0; k < sizeof(behavior_kinds) / sizeof(behavior_kinds[0]); k++) {
            if (flags & behavior_kinds[k].flag) {
                count++;
            }
        }
        res->behavior_count = count;
        if (count == 0) {
            res->behaviors = NULL;
            continue;
        }
        res->behaviors = sys->alloc(res->behavior_count * sizeof(ParticleBehavior));
        ParticleBehavior *behavior = res->behaviors;
        for (size_t k = 0; k < sizeof(behavior_kinds) / sizeof(behavior_kinds[0]); k++) {
            if (flags & behavior_kinds[k].flag) {
                behavior->data = take(file, &offset, behavior_kinds[k].size);
                behavior->fn = behavior_kinds[k].fn;
                behavior++;
            }
        }
    }
}
CLEAN_AS(func_020fa564, ParticleSys_LoadResources)

/* func_020fa820: the counts of resources and textures read from the file's header, and the
 * textures, which follow the resources, each with its size from its parameters. */
void ParticleSys_LoadTextures(ParticleSystem *sys, const ParticleFile *file)
{
    const u8 *bytes = (const u8 *) file;
    u32 offset = sizeof(ParticleFile);

    sys->resource_count = file->resource_count;
    sys->texture_count = file->texture_count;

    for (int i = 0; i < sys->resource_count; i++) {
        u32 flags = ((const ParticleHeader *) (bytes + offset))->flags;

        offset += sizeof(ParticleHeader);
        offset += flags & PARTICLE_HAS_SCALE_ANIM ? SCALE_ANIM_SIZE : 0;
        offset += flags & PARTICLE_HAS_COLOR_ANIM ? COLOR_ANIM_SIZE : 0;
        offset += flags & PARTICLE_HAS_ALPHA_ANIM ? ALPHA_ANIM_SIZE : 0;
        offset += flags & PARTICLE_HAS_TEX_ANIM ? TEX_ANIM_SIZE : 0;
        offset += flags & PARTICLE_HAS_CHILDREN ? CHILD_SIZE : 0;
        for (size_t k = 0; k < sizeof(behavior_kinds) / sizeof(behavior_kinds[0]); k++) {
            offset += flags & behavior_kinds[k].flag ? behavior_kinds[k].size : 0;
        }
    }

    sys->textures = sys->alloc(sys->texture_count * sizeof(ParticleTexture));
    MI_CpuFill8(sys->textures, 0, sys->texture_count * sizeof(ParticleTexture));

    for (int i = 0; i < sys->texture_count; i++) {
        ParticleTexture *texture = &sys->textures[i];
        const ParticleTexFile *tex = (const ParticleTexFile *) (bytes + offset);

        texture->file = tex;
        texture->width = (u16) (1 << (particle_bits(tex->param, PARTICLE_TEX_SIZE_S_SHIFT, 4) + 3));
        texture->height = (u16) (1 << (particle_bits(tex->param, PARTICLE_TEX_SIZE_T_SHIFT, 4) + 3));
        texture->param = tex->param;
        offset += tex->size;
    }
}
CLEAN_AS(func_020fa820, ParticleSys_LoadTextures)

/* Room for `count` records of `size` bytes from `alloc`, cleared, each put in `list`. */
static void fill_free_list(void *(*alloc)(u32 size), ParticleList *list, int count, u32 size)
{
    u8 *record = alloc(count * size);

    MI_CpuFill8(record, 0, count * size);
    for (int i = 0; i < count; i++) {
        ParticleList_Push(list, (ParticleLink *) record);
        record += size;
    }
}

/* func_020fa9f4: a manager made with `alloc` (the game's), with room for `max_emitters`
 * emitters and `max_particles` particles in its free lists; particles take polygon IDs from
 * `min_id` to `max_id` in turn, or `fixed_id` for the resources that say so. */
ParticleSystem *ParticleSys_Create(void *(*alloc)(u32 size), int max_emitters, int max_particles, int fixed_id, u16 min_id,
                                   u16 max_id)
{
    ParticleSystem *sys = alloc(sizeof(ParticleSystem));

    MI_CpuFill8(sys, 0, sizeof(ParticleSystem));
    sys->max_emitters = (u16) max_emitters;
    sys->max_particles = (u16) max_particles;
    sys->polygon_ids = (u32) (min_id & 0x3f) << PARTICLE_ID_MIN_SHIFT | (u32) (max_id & 0x3f) << PARTICLE_ID_MAX_SHIFT |
                       (u32) (min_id & 0x3f) << PARTICLE_ID_NEXT_SHIFT | ((u32) fixed_id & 0x3f) << PARTICLE_ID_FIXED_SHIFT;
    sys->alloc = alloc;
    fill_free_list(alloc, &sys->free_emitters, max_emitters, sizeof(ParticleEmitter));
    fill_free_list(alloc, &sys->free_particles, max_particles, sizeof(Particle));
    return sys;
}
CLEAN_AS(func_020fa9f4, ParticleSys_Create)
