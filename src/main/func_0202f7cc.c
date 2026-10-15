/* func_0202f7cc @ 0x0202f7cc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ea6e0(void *, int);

void func_0202f7cc(unsigned int *param, int a)
{
    unsigned int local[3];
    unsigned int *r4 = param;
    unsigned int tmp0, tmp2;

    tmp0 = r4[0];
    tmp2 = r4[1];
    local[0] = tmp0;
    local[1] = 0;
    local[2] = tmp2;
    func_020ea6e0(local, a);
    r4[0] = local[0];
    r4[1] = local[2];
}