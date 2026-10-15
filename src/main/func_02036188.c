/* func_02036188 @ 0x02036188, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02095794(int size);
extern int func_02034270(void *dst, const void *src, int a, int b);
extern void func_0203423c(void *obj);
extern void func_02036558(void *self, int a, int b, int c);

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} Header;

typedef struct {
    unsigned char pad_00[0x34];
    unsigned int unk_34;
    unsigned char pad2[0x8];
} UnkStruct_02036188;

typedef struct {
    unsigned int x, y, z;
} Vec3;

typedef struct {
    unsigned char pad_00[0x30];
    unsigned int val;
    unsigned char pad2[0x10];
} UnkStruct_02036188_2;

typedef struct {
    unsigned char pad_00[0xc];
    unsigned int state;
} UnkStruct_02036188_3;

void func_02036188(int unused, UnkStruct_02036188_3 *self)
{
    Header *ptr;
    UnkStruct_02036188 obj1;
    Vec3 vec;
    UnkStruct_02036188_2 obj2;
    unsigned int state;
    unsigned int id;
    unsigned int val;
    unsigned int tx, ty, tz;
    int flag;

    state = self->state;
    flag = 0;
    ptr = (Header *) func_02095794(4);
    if (ptr == 0) {
        goto skip;
    }

    func_02034270(&obj1, ptr, 0, 0);
    id = obj1.unk_34;
    tz = ptr->unk_08 + 0x2000;
    ty = ptr->unk_04;
    tx = ptr->unk_00;
    vec.x = tx;
    vec.y = ty;
    vec.z = tz;
    func_02034270(&obj2, &vec, 0, 0);
    val = obj2.val;
    if (id == 0x13 || id == 0x16 || val == 1) {
        flag = 1;
    }
    func_0203423c(&obj2);
    func_0203423c(&obj1);

skip:
    if (state == 0) {
        if (flag != 0) {
            func_02036558(self, 0x28, 0x3c, 1);
            self->state = 0x10;
        }
    } else if (state == 0x10) {
        if (flag == 0) {
            func_02036558(self, 0x7f, 0x3c, 1);
            self->state = 0;
        }
    }
}
