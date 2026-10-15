/* func_020af898 @ 0x020af898, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020af028(void *);
extern unsigned int func_020af8e0(void *, unsigned int);
extern int func_020af648(void);
extern int data_021f395c;

int func_020af898(void *param)
{
    unsigned int x = func_020af028(param);
    if (x == 3) {
        return x;
    }
    {
        unsigned int y = func_020af8e0(param, x);
        if (*(unsigned int *) param < y) {
            goto label;
        }
        {
            int z;
            asm { ldr r0, =data_021f395c }
            z = func_020af648();
            if (x == 2) {
                if (z == 0) {
                    goto label;
                }
                return x + 1;
            } else {
                return x + 1;
            }
        }
    }
label:
    return func_020af028(param);
}
