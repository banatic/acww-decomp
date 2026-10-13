/* func_020fad1c @ 0x020fad1c, 0xdc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct VecFx32 {
    int x, y, z;
} VecFx32;
typedef int (*SPLDrawCallback)(VecFx32 *, VecFx32);
typedef struct SPLManager SPLManager;
typedef struct SPLEmitter SPLEmitter;
typedef struct SPLResource SPLResource;
typedef struct SPLHeader SPLHeader;
typedef struct SPLTexture SPLTexture;
typedef struct SPLParticle SPLParticle;

typedef void (*ParticleDraw)(SPLManager *self, SPLParticle *node, SPLDrawCallback arg2);
typedef void (*TextureBind)(SPLTexture *elem);

struct SPLParticle {
    SPLParticle *next;
    unsigned char pad0[0x28];
    unsigned char byte;
};

struct SPLHeader {
    unsigned int low : 4;
    unsigned int mode : 2;
    unsigned int mid : 5;
    unsigned int flag : 1;
    unsigned int high : 20;
    unsigned char pad0[0x3f];
    unsigned char byte;
};

struct SPLResource {
    SPLHeader *r;
};

struct SPLEmitter {
    unsigned char pad0[0x8];
    SPLParticle *list;
    unsigned char pad1[0xc];
    SPLResource *c;
};

struct SPLTexture {
    unsigned char data[0x14];
};

struct SPLManager {
    unsigned char pad0[0x20];
    SPLTexture *base;
    unsigned char pad1[0x10];
    SPLEmitter *b;
};

extern void func_020fb8e8(SPLTexture *elem);
extern void func_020fb8e4(SPLTexture *elem);
extern void func_020fd4e0(SPLManager *self, SPLParticle *node, SPLDrawCallback arg2);
extern void func_020fc8c4(SPLManager *self, SPLParticle *node, SPLDrawCallback arg2);
extern void func_020fbda4(SPLManager *self, SPLParticle *node, SPLDrawCallback arg2);

void func_020fad1c(SPLManager *self, SPLDrawCallback arg2)
{
    SPLEmitter *b;
    SPLHeader *r;
    SPLParticle *node;
    int idx;
    TextureBind emit;
    ParticleDraw cb = 0;

    b = self->b;
    r = b->c->r;
    idx = r->byte;
    func_020fb8e8(&self->base[idx]);
    switch (r->mode) {
        case 0:
            cb = func_020fd4e0;
            break;
        case 1:
            cb = func_020fc8c4;
            break;
        case 2:
            cb = func_020fbda4;
            break;
        default:
            break;
    }
    emit = r->flag ? func_020fb8e8 : func_020fb8e4;
    node = b->list;
    if (node != 0) {
        do {
            emit(&self->base[node->byte]);
            cb(self, node, arg2);
            node = node->next;
        } while (node != 0);
    }
}
