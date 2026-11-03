/* bromide_2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02213650 @ 0x02213650, 0x4 bytes, Thumb
 * func_ov004_0221362c @ 0x0221362c, 0x22 bytes, Thumb
 */

extern int func_ov004_02213590(void *self, int k);

int func_ov004_02213650(void)
{
    return 1;
}

void func_ov004_0221362c(void *self, int k)
{
    switch (k) {
        case 1:
            func_ov004_02213590(self, 1);
            break;
        case 8:
            func_ov004_02213590(self, 0);
            break;
    }
}
