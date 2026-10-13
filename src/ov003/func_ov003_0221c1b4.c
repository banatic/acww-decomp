/* func_ov003_0221c1b4 @ 0x0221c1b4, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(int *p);

int func_ov003_0221c1b4(unsigned char *param)
{
    int local[2];

    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    param[0x2bb] = ((unsigned char *) local)[2];
    return 1;
}
