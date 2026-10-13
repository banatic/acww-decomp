/* func_ov003_0221d594 @ 0x0221d594, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221d64c(void *);
extern int func_ov003_0221d5cc(void *);
extern int func_ov003_022203dc(int);
extern void func_02064328(char *, char *, int, int, int);
extern char data_ov003_0223c948[];
extern char data_ov003_022390a0[];

char *func_ov003_0221d594(void *param)
{
    int a = func_ov003_0221d64c(param);
    int b = func_ov003_0221d5cc(param);
    int c = func_ov003_022203dc(b);
    func_02064328(data_ov003_0223c948, data_ov003_022390a0, a >> 2, b, c);
    return data_ov003_0223c948;
}
