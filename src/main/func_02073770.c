/* func_02073770 @ 0x02073770, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64; // at 0x64
    unsigned char pad_68[0xc8 - 0x68];
    int c8; // 0xc8
    int cc; // 0xcc
    int d0; // 0xd0
    int d4; // 0xd4
} UnkStruct_02073770;

extern int func_02073d90(void *);
extern int func_020b65c4(void);
extern int func_020a6c98(int);
extern void func_02077880(void *dst, unsigned short value);
extern void func_02077a54(void *dst, int value, unsigned char byte);
extern void MI_CpuCopy8(void *dst, int value, int count);

void func_02073770(UnkStruct_02073770 *p, unsigned int param1, unsigned int param2)
{
    unsigned char arr1[4];
    unsigned char arr2[8];
    int diff;

    if (func_02073d90(p)) {
        if ((param2 - 6) <= 1) {
            func_020a6c98((int) func_020b65c4());
        }

        diff = p->d4 - p->d0;

        func_02077880(arr1, (unsigned short) (diff - 5));
        arr1[2] = (unsigned char) param1;
        arr1[3] = (unsigned char) param2;

        func_02077a54(arr2, func_020b65c4(), p->unk_64);

        MI_CpuCopy8(arr1, p->d0, 5);

        p->c8 = p->c8 + diff;
        p->cc = p->d4;
    }
}
