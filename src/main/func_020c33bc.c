/* func_020c33bc @ 0x020c33bc, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019de8(void *ptr);
extern int func_02019e00(void *ptr);
extern void func_02019d0c(void *ptr, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern unsigned short data_020c80f8;

typedef struct UnkStruct_020c33bc {
    char pad_00[0x564];
    int member;
} UnkStruct_020c33bc;

int func_020c33bc(UnkStruct_020c33bc *param)
{
    if (func_02019de8(&param->member) != 0 && func_02019e00(&param->member) == 1) {
        func_02019d0c(&param->member, 0, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    }
    return 1;
}
