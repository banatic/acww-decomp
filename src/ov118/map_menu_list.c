/* map_menu_list: 6 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229a474 @ 0x0229a474, 0x44 bytes, Thumb
 * func_ov118_0229a460 @ 0x0229a460, 0x12 bytes, Thumb
 * func_ov118_0229a450 @ 0x0229a450, 0xe bytes, Thumb
 * func_ov118_0229a440 @ 0x0229a440, 0xe bytes, Thumb
 * func_ov118_0229a43c @ 0x0229a43c, 0x2 bytes, Thumb
 * func_ov118_0229a438 @ 0x0229a438, 0x2 bytes, Thumb
 */

typedef struct {
    unsigned char bytes[3];
} Triple;

typedef struct {
    unsigned char pad_00[0xa9];
    unsigned char type;
    unsigned char pad_AA[0x47ad - 0xaa];
    Triple arr[256];
} UnkStruct_0229a474;

struct UnkStruct_0229a460 {
    char pad_00[0x9c];
    unsigned short unk_9C;
};

typedef struct {
    char pad_00[0x9c];
    unsigned short unk_9C;
} UnkStruct_0229a450;

struct UnkStruct_0229a440 {
    unsigned char pad_00[0x9c];
    unsigned short unk_9C;
};

extern void func_02004668(int, int);

void func_ov118_0229a474(UnkStruct_0229a474 *p, int a1)
{
    int val;
    if (p->type == 14) {
        return;
    }
    val = (p->arr[p->type].bytes[0] - 0x18) * 2 - 0x7f;
    if (val < -127) {
        val = -127;
    } else if (val > 128) {
        val = 128;
    }
    func_02004668(a1, val);
}

int func_ov118_0229a460(struct UnkStruct_0229a460 *s, unsigned short mask)
{
    int t = s->unk_9C & mask;
    if (t == 0) {
        return 0;
    } else {
        return 1;
    }
}

void func_ov118_0229a450(UnkStruct_0229a450 *obj, unsigned short mask)
{
    obj->unk_9C |= mask;
}

void func_ov118_0229a440(struct UnkStruct_0229a440 *self, unsigned int mask)
{
    self->unk_9C &= ~mask;
}

void func_ov118_0229a43c(void *object) {}

void func_ov118_0229a438(void *element) {}
