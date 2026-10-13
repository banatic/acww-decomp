/* func_ov068_02267468 @ 0x02267468, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_02019c90(void *, int, int, unsigned short);
extern unsigned short data_020c80f8;

typedef struct {
    int a;
} UnkStruct_02267468;
typedef struct {
    char pad_00[0x564];
    UnkStruct_02267468 sub;
} Src;
typedef struct {
    char pad_00[0x1c];
    unsigned char flag;
    char pad_1D[3];
    int value;
} UnkStruct_02267468_2;

void func_ov068_02267468(UnkStruct_02267468_2 *out, Src *src)
{
    if (func_02019e00(&src->sub) != 3) {
        return;
    }
    if (func_02019de8(&src->sub) == 0) {
        return;
    }
    func_02019c90(&src->sub, 1, 0x1a, data_020c80f8);
    out->value = 0x14;
    out->flag = 1;
}
