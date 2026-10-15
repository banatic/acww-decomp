/* func_ov003_0221d6dc @ 0x0221d6dc, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_022203b8(void);
extern int func_ov003_0221fe9c(void *argument0);
extern void func_0205510c(char *p, int v);

int func_ov003_0221d6dc(void *self)
{

    if (func_ov003_0221fe9c((void *) func_ov003_022203b8())) {
        func_0205510c((char *) self + 0x2b4, 0);
    }
    return 1;
}
