/* func_02016d6c @ 0x02016d6c, 0x1c4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct UnkStruct_02016d6c {
    u32 state;
    u8 pad_04[0x98 - 4];
    u8 flag;
} UnkStruct_02016d6c;

typedef struct Other {
    u8 pad_00[0x5c];
    s32 unk_5C;
    u8 pad_60[4];
    s32 unk_64;
    u8 pad_68[0x8e - 0x68];
    s16 unk_8E;
    u8 pad_90[0x350 - 0x90];
    u8 sub;
} Other;

extern u16 data_020c80f8;
extern u8 data_021fbee8[];

extern void func_0201b188(void *p, void *q);
extern int func_0201bee0(void *p, int *arr, s16 *s);
extern void func_0201b1a4(void *p, void *a, int b, int c, int d);
extern void func_0201aff4(void *p, int v);
extern void func_0201b044(void *p, void *q);
extern void func_0201afd4(void *p, void *q);
extern int func_0201b1a0(void *p);
extern int func_0201c3dc(int v);
extern int func_020e8ed8(int x, int y);
extern int FX_MulFunc(int x, int y);

void func_02016d6c(UnkStruct_02016d6c *self, Other *other)
{
    s16 s;
    s32 arr[3];
    int diff0, diff1, result;

    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;

    s = other->unk_8E;
    func_0201b188(&other->sub, other);
    if (func_0201bee0((void *) other, arr, &s) != 0) {
        diff0 = arr[0] - other->unk_5C;
        diff1 = arr[2] - other->unk_64;
        if (FX_MulFunc(diff0, diff0) + FX_MulFunc(diff1, diff1) < 41) {
            if (s != other->unk_8E) {
                func_0201b1a4(&other->sub, (void *) other, 3, 0, data_020c80f8);
                func_0201aff4(&other->sub, s);
                self->flag = 2;
            } else {
                func_0201b1a4(&other->sub, (void *) other, 0, 0, data_020c80f8);
                func_0201aff4(&other->sub, s);
                func_0201b044(&other->sub, data_021fbee8);
                func_0201afd4(&other->sub, data_021fbee8);
                self->flag = 0;
            }
        } else {
            result = func_020e8ed8(diff0, diff1) - s;
            if (func_0201c3dc((s16) result) == 0) {
                func_0201b1a4(&other->sub, (void *) other, 3, 0, data_020c80f8);
                func_0201aff4(&other->sub, s);
                self->flag = 2;
            } else {
                if (func_0201b1a0(&other->sub) == 1) {
                    if (self->state == 2) {
                        func_0201b1a4(&other->sub, (void *) other, 2, 0, data_020c80f8);
                    }
                } else {
                    if (func_0201b1a0(&other->sub) == 2) {
                        if (self->state == 1) {
                            func_0201b1a4(&other->sub, (void *) other, 1, 0, data_020c80f8);
                        }
                    }
                }
                func_0201b044(&other->sub, arr);
                func_0201afd4(&other->sub, arr);
            }
        }
    } else {
        func_0201b1a4(&other->sub, (void *) other, 0, 0, data_020c80f8);
        func_0201aff4(&other->sub, s);
        func_0201b044(&other->sub, data_021fbee8);
        func_0201afd4(&other->sub, data_021fbee8);
        self->flag = 0;
    }
}