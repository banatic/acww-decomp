/* func_ov126_022a0a50 @ 0x022a0a50, 0x40 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov126_0229ffdc(void *);
extern void func_ov126_022a0ae0(void *, int);
extern void func_ov126_022a0110(void *);

struct UnkStruct_022a0a50 {
    char pad_00[0xad];
    unsigned char unk_AD;
};

int func_ov126_022a0a50(struct UnkStruct_022a0a50 *s)
{
    switch (s->unk_AD) {
        case 0:
            func_ov126_0229ffdc(s);
            func_ov126_022a0ae0(s, 1);
            return 1;
        case 1:
            func_ov126_0229ffdc(s);
            func_ov126_022a0ae0(s, 0);
            return 1;
        default:
            func_ov126_022a0110(s);
            return 0;
    }
}
