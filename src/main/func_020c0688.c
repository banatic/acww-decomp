/* func_020c0688 @ 0x020c0688, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
    unsigned int unk_44;
    unsigned int unk_48;
    unsigned int unk_4C;
    unsigned int unk_50;
} UnkStruct_020c0688;

extern void *func_020bdc50(unsigned int, int, int, int, int);
extern unsigned int FX_MulFunc(unsigned int, unsigned int);

extern unsigned char data_021f8b48[];

void func_020c0688(int a, int b, int c)
{
    volatile long long unused;
    UnkStruct_020c0688 *obj;

    (void) &unused;
    obj = (UnkStruct_020c0688 *) func_020bdc50((unsigned int) data_021f8b48, 2, 0x3c, a, 0);
    if (obj) {
        obj->unk_4C = b;
        obj->unk_50 = b;
        obj->unk_40 = FX_MulFunc(c, 0x800);
        obj->unk_44 = 0;
        obj->unk_48 = 0;
    }
}
