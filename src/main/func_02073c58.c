/* func_02073c58 @ 0x02073c58, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int);

void func_02073c58(int *r0, int r1)
{
    int *r4;
    int r0_val;
    int r1_val;

    r4 = r0;
    r0_val = r1;
    r0_val = func_02077b58(r0_val);
    r4 = (int *) ((char *) r4 + 0x18);
    r1_val = r0_val << 2;
    r0_val = *(int *) ((char *) r4 + r1_val);
    r0_val = r0_val + 1;
    *(int *) ((char *) r4 + r1_val) = r0_val;
}
