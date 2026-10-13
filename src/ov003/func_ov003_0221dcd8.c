/* func_ov003_0221dcd8 @ 0x0221dcd8, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221dd0c(void);
extern int func_ov003_022203dc(int x);
extern void func_02064328(char *a, char *b, signed char c, int d);
extern char data_ov003_0223c998[];
extern char data_ov003_02239390[];
extern signed char data_ov003_02236654[];

void *func_ov003_0221dcd8(void)
{
    int x = func_ov003_0221dd0c();
    int y = func_ov003_022203dc(x);
    func_02064328(data_ov003_0223c998, data_ov003_02239390, data_ov003_02236654[x & 0xF], y);
    return data_ov003_0223c998;
}
