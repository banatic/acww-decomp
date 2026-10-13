/* func_ov003_0221d1b8 @ 0x0221d1b8, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);

int func_ov003_0221d1b8(unsigned char *param0)
{
    unsigned int local[2];
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    param0[0x2b4] = ((unsigned char *) local)[2];
    return 1;
}
