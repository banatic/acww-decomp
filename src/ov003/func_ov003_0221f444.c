/* func_ov003_0221f444 @ 0x0221f444, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221f5ac(void *arg);
extern void func_02056ffc(void *ptr);

struct UnkStruct_0221f444 {
    char pad_00[8];
    int value;
    char pad_0C[12];
    int *ptr;
    char pad_1C[4];
};

int func_ov003_0221f444(void *arg)
{
    if (func_ov003_0221f5ac(arg)) {
        struct UnkStruct_0221f444 *p = (struct UnkStruct_0221f444 *) ((unsigned char *) arg + 0xb4);
        struct UnkStruct_0221f444 *end = (struct UnkStruct_0221f444 *) ((unsigned char *) arg + 0xf4);
        while (p < end) {
            func_02056ffc(p);
            *p->ptr = p->value;
            p++;
        }
        return 1;
    }
    return 0;
}
