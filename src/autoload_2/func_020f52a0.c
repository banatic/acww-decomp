/* func_020f52a0 @ 0x020f52a0, 0xc0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fd1bc[];
extern void *data_021fd234;
extern void func_020f5178(void *out);
extern void func_020f4eec(void *ptr, void *out);
extern void func_020f4c70(void *ptr, unsigned short val, int *data);
extern void func_020f50e4(void *out);

struct UnkStruct_020f52a0 {
    int pad_00;
    int pad_04;
    int pad_08;
    int a;
    int b;
    int c;
    unsigned short v;
    unsigned char flag1;
    unsigned char flag2;
};

void func_020f52a0(struct UnkStruct_020f52a0 *out, int value, int *src)
{
    if (data_021fd1bc[0x4d] != 0) {
        return;
    }
    out->a = src[0];
    out->b = src[1];
    out->c = src[2];
    if (value > 0x3e9 && value < 0x430) {
        out->v = value;
        out->flag1 = 1;
        out->flag2 = 1;
        func_020f4eec(data_021fd234, out);
        return;
    } else {
        func_020f5178(out);
        func_020f4c70(data_021fd234, (unsigned short) value, &out->a);
        func_020f50e4(out);
        return;
    }
}
