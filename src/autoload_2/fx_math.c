/* fx_math: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e930c @ 0x020e930c, 0x8 bytes, ARM
 * func_020e92e8 @ 0x020e92e8, 0x24 bytes, ARM
 * func_020e92d0 @ 0x020e92d0, 0x18 bytes, ARM
 */

typedef struct {
    unsigned long unk_00;
} UnkStruct_020e930c;

void func_020e930c(UnkStruct_020e930c *p, unsigned long v)
{
    p->unk_00 = v;
}

unsigned int func_020e92e8(unsigned int *r0)
{
    unsigned int r3;
    unsigned int r1;
    unsigned int r2;
    unsigned int result;

    r3 = *r0;
    r1 = 0x0019660d;
    r2 = 0x3c6ef35f;
    r1 = r3 * r1 + r2;
    *r0 = r1;
    result = *r0;
    return result;
}

unsigned int func_020e92d0(unsigned int a, unsigned int b)
{
    unsigned int r;
    r = func_020e92e8((unsigned int *) a);
    return (unsigned int) ((unsigned long long) b * r >> 32);
}
