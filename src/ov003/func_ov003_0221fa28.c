/* func_ov003_0221fa28 @ 0x0221fa28, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221f144(void *);
extern void func_ov003_0221f444(void *);
extern void func_ov003_0221f244(void *);
extern void func_02057538(void *);
extern void func_ov003_0221f6dc(void *);
extern int data_021d3124;

int func_ov003_0221fa28(void *arg0)
{
    int i, j;
    char *ptr;
    func_ov003_0221f144((char *) arg0 + 0x150);
    func_ov003_0221f444((char *) arg0 + 0x54);
    ptr = *(char **) ((char *) arg0 + 0x50);
    for (i = 0; i < *(int *) ((char *) arg0 + 0x14c); i++) {
        for (j = 0; j < *(int *) ((char *) arg0 + 0x148); j++) {
            func_ov003_0221f244(ptr);
            ptr += 0xEC;
        }
    }
    func_02057538((char *) arg0 + 0x1f0);
    func_02057538((char *) arg0 + 0x280);
    func_ov003_0221f6dc(arg0);
    data_021d3124 = 0;
    return 1;
}
