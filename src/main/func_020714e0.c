/* func_020714e0 @ 0x020714e0, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x2c4];
} UnkStruct_020714e0;
typedef struct {
    char data[0x38];
} UnkStruct_020714e0_2;
extern int data_021d04e4[];
extern UnkStruct_020714e0 *data_021d0470;
extern UnkStruct_020714e0_2 *data_021d0480;
extern int func_02072a48(void *p, unsigned int a);
extern int func_0203cff8(UnkStruct_020714e0 *p, int val);
extern int func_0203cfc8(UnkStruct_020714e0 *p);
extern int func_020577c8(UnkStruct_020714e0_2 *p, int a1, int a2, int a3, int a4, int a5, int a6);
extern unsigned char data_021ed278[];

int func_020714e0(unsigned int a)
{
    int i = (unsigned char) (a & 7);
    int value = data_021d04e4[i];
    if (value == 0) {
        goto fail;
    }
    if (data_021d0470 == 0) {
        goto fail;
    }
    if (data_021d0480 == 0) {
        goto fail;
    }
    func_0203cff8(&data_021d0470[i], func_02072a48((void *) data_021ed278, a));
    func_020577c8(&data_021d0480[i], value, 0, 0, func_0203cfc8(&data_021d0470[i]), 0, 0);
    return 1;
fail:
    return 0;
}
