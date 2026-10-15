/* func_020fa564 @ 0x020fa564, 0x2bc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct SPLResHeader {
    struct {
        u32 pad0 : 8;
        u32 hasA : 1; // bit 8
        u32 hasB : 1; // bit 9
        u32 hasC : 1; // bit 10
        u32 hasD : 1; // bit 11
        u32 pad1 : 4;
        u32 hasE : 1; // bit 16
        u32 pad2 : 7;
        u32 beh0 : 1; // bit 24
        u32 beh1 : 1;
        u32 beh2 : 1;
        u32 beh3 : 1;
        u32 beh4 : 1;
        u32 beh5 : 1; // bit 29
        u32 pad3 : 2;
    } flags;
} SPLResHeader;

typedef void (*SPLBehaviorFn)(void *, void *, void *, void *);

typedef struct SPLBehavior {
    SPLBehaviorFn fn;
    void *data;
} SPLBehavior;

typedef struct SPLResource {
    SPLResHeader *header;   // 0x00
    void *a;                // 0x04
    void *b;                // 0x08
    void *c;                // 0x0c
    void *d;                // 0x10
    void *e;                // 0x14
    SPLBehavior *behaviors; // 0x18
    u16 behaviorCount;      // 0x1c
    u16 pad_1E;
} SPLResource;

typedef struct SPLManager {
    void *(*alloc)(u32 size); // 0x00
    u8 pad_04[0x1c - 4];
    SPLResource *resources; // 0x1c
    u8 pad_20[0x24 - 0x20];
    u16 resourceCount; // 0x24
} SPLManager;

extern void MI_CpuFill8(void *dst, u8 data, u32 size);

extern void func_020ff808(void *behavior, void *particle, void *acceleration, void *emitter);
extern void func_020ff740(void *behavior, void *particle, void *acceleration, void *emitter);
extern void func_020ff6bc(void *behavior, void *particle, void *acceleration, void *emitter);
extern void func_020ff5e4(void *behavior, void *particle, void *acceleration, void *emitter);
extern void func_020ff4c8(void *behavior, void *particle, void *acceleration, void *emitter);
extern void func_020ff434(void *behavior, void *particle, void *acceleration, void *emitter);

void func_020fa564(SPLManager *mgr, u8 *base)
{
    int i;
    u32 off;
    SPLResource *res;
    SPLResHeader h;
    SPLBehavior *p;

    off = 0;
    mgr->resources = mgr->alloc(mgr->resourceCount * sizeof(SPLResource));
    MI_CpuFill8(mgr->resources, 0, mgr->resourceCount * sizeof(SPLResource));

    for (i = 0; i < mgr->resourceCount; i++) {
        res = &mgr->resources[i];
        res->header = (SPLResHeader *) (base + off);
        h = *res->header;
        off += 0x54;

        if (h.flags.hasA) {
            res->a = base + off;
            off += 0xc;
        } else {
            res->a = 0;
        }
        if (h.flags.hasB) {
            res->b = base + off;
            off += 0xc;
        } else {
            res->b = 0;
        }
        if (h.flags.hasC) {
            res->c = base + off;
            off += 8;
        } else {
            res->c = 0;
        }
        if (h.flags.hasD) {
            res->d = base + off;
            off += 0xc;
        } else {
            res->d = 0;
        }
        if (h.flags.hasE) {
            res->e = base + off;
            off += 0x14;
        } else {
            res->e = 0;
        }

        res->behaviorCount = (u16) (h.flags.beh0 + h.flags.beh1 + h.flags.beh2 + h.flags.beh3 + h.flags.beh4 + h.flags.beh5);

        if (res->behaviorCount != 0) {
            res->behaviors = mgr->alloc(res->behaviorCount * sizeof(SPLBehavior));
            p = res->behaviors;
            if (h.flags.beh0) {
                p->data = base + off;
                p->fn = func_020ff808;
                off += 8;
                p++;
            }
            if (h.flags.beh1) {
                p->data = base + off;
                p->fn = func_020ff740;
                off += 8;
                p++;
            }
            if (h.flags.beh2) {
                p->data = base + off;
                p->fn = func_020ff6bc;
                off += 0x10;
                p++;
            }
            if (h.flags.beh3) {
                p->data = base + off;
                p->fn = func_020ff5e4;
                off += 4;
                p++;
            }
            if (h.flags.beh4) {
                p->data = base + off;
                p->fn = func_020ff4c8;
                off += 8;
                p++;
            }
            if (h.flags.beh5) {
                p->data = base + off;
                p->fn = func_020ff434;
                off += 0x10;
            }
        } else {
            res->behaviors = 0;
        }
    }
}
