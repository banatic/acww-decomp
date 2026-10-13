/* func_0205556c @ 0x0205556c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x38];
    int unk_98;
} UnkStruct_0205556c;

extern int func_020562cc(int arg);
extern void func_02055f6c(UnkStruct_0205556c *ptr);
extern int func_02055698(UnkStruct_0205556c *ptr, int arg2, int arg3, int arg4);

int func_0205556c(UnkStruct_0205556c *ptr, int arg2, int arg3)
{
    ptr->unk_5C = func_020562cc(arg2);
    if (ptr->unk_5C != 0) {
        func_02055f6c(ptr);
        return 1;
    } else {
        ptr->unk_98 = arg2;
        return func_02055698(ptr, arg3, 0, arg2);
    }
}
