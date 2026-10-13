/* func_ov003_0222e6c4 @ 0x0222e6c4, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222e6c4;

extern UnkStruct_0222e6c4 *data_020ccf94;
extern unsigned char data_ov003_02260e4c[];

extern int func_02073dd4(UnkStruct_0222e6c4 *p, int val);
extern int func_02073918(UnkStruct_0222e6c4 *p, int id);
extern void func_02073820(UnkStruct_0222e6c4 *p);
extern void func_020737f0(UnkStruct_0222e6c4 *p, unsigned char *id, int n);
extern void func_02073770(UnkStruct_0222e6c4 *p, int a, int b);
extern void func_0209129c(int h);

void func_ov003_0222e6c4(unsigned char id, int flag)
{
    unsigned char *p;
    UnkStruct_0222e6c4 *o;

    p = data_ov003_02260e4c + id * 0x25c;
    o = data_020ccf94;
    if (func_02073dd4(o, o->unk_64) != 0 && flag != 0 && func_02073918(o, id) != 0) {
        o = data_020ccf94;
        func_02073820(o);
        func_020737f0(o, &id, 1);
        func_02073770(o, 0x30, 4);
    }
    if (*(int *) (p + 0x22c) != -1) {
        func_0209129c(*(int *) (p + 0x22c));
        *(int *) (p + 0x22c) = -1;
    }
    p[0x251] = 0xa;
}
