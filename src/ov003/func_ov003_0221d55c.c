/* func_ov003_0221d55c @ 0x0221d55c, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223c970[];
extern int data_ov003_02239084[];
extern int func_ov003_0221d64c(int);
extern int func_ov003_0221d5cc(int);
extern int func_ov003_022203dc(void);
extern int func_02064328(int *, int *, int, int, int);

int *func_ov003_0221d55c(int arg)
{
    int ret1 = func_ov003_0221d64c(arg);
    int ret2 = func_ov003_0221d5cc(arg);
    int ret3 = func_ov003_022203dc();
    func_02064328(data_ov003_0223c970, data_ov003_02239084, ret1 >> 2, ret2, ret3);
    return data_ov003_0223c970;
}
