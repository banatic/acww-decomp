/* func_020bc514 @ 0x020bc514, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020be0d4(void *p, int a);
extern void *func_020bdc50(void *p, int a, int b, int c, int d);

typedef struct UnkStruct_020bc514 {
    unsigned char data[0x60];
    int unk_60;
    unsigned char pad_64[0x10];
} UnkStruct_020bc514;

void func_020bc514(UnkStruct_020bc514 *param)
{
    int index;
    UnkStruct_020bc514 *r4;
    index = func_020be0d4(param, 3);
    r4 = param + index;
    if (r4 != 0) {
        func_020bdc50(param, 2, 0x3c, 0, 1);
        r4->unk_60 = 1;
    }
}
