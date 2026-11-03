/* collision_query: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02031060 @ 0x02031060, 0x16 bytes, Thumb
 * func_0203104c @ 0x0203104c, 0x14 bytes, Thumb
 */

extern int func_02031078(int, int, int *, int *, int *);

int func_02031060(int param1, int param2)
{
    int a, b, c;
    return func_02031078(param1, param2, &a, &b, &c);
}

int func_0203104c(int *arg0)
{
    int r0;
    int r1;
    int *ptr;

    ptr = arg0;
    r0 = *ptr >> 13;
    r1 = *(ptr + 2) >> 13;
    return func_02031060(r0, r1);
}
