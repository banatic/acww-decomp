/* collision_post_source: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02031ec0 @ 0x02031ec0, 0xc bytes, Thumb
 * func_02031eb4 @ 0x02031eb4, 0xc bytes, Thumb
 * func_02031ea8 @ 0x02031ea8, 0xc bytes, Thumb
 * func_02031e90 @ 0x02031e90, 0x18 bytes, Thumb
 * func_02031e84 @ 0x02031e84, 0xc bytes, Thumb
 * func_02031e80 @ 0x02031e80, 0x4 bytes, Thumb
 */

extern void func_020edb3c(void *ptr);
extern unsigned char data_020da1fc[];

void func_02031ec0(void **out)
{
    *out = ((int *) data_020da1fc);
}

void func_02031eb4(void *ptr)
{
    *(int **) ptr = ((int *) data_020da1fc);
}

void func_02031ea8(int *p)
{
    *p = (int) ((int *) data_020da1fc);
}

void *func_02031e90(void *ptr)
{
    *(void **) ptr = (void *) data_020da1fc;
    func_020edb3c(ptr);
    return ptr;
}

void func_02031e84(int **ptr)
{
    *ptr = ((int *) data_020da1fc);
}

int func_02031e80(void)
{
    return 0;
}
