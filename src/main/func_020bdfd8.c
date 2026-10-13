/* func_020bdfd8 @ 0x020bdfd8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209f100(void *param1, int param2);
extern void func_020be000(void *param1);
extern void func_020bde98(void *param1);

extern unsigned char data_021dc7a8[];

void func_020bdfd8(void *param1, int param2)
{
    void *r4 = param1;
    if (param2 != 0) {
        func_0209f100((void *) data_021dc7a8, 9);
        func_020be000(r4);
        func_020bde98(r4);
    }
}
