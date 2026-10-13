/* func_ov004_0221fe84 @ 0x0221fe84, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202e1a0(void *);
extern void func_020e9898(int);

int func_ov004_0221fe84(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_0202e1a0(self) == 0x0) {
        return 0x0;
    } else {
        if (*(int *) (self + 0xa58) != 0x0) {
            func_020e9898(*(int *) (self + 0xa58));
            *(void **) (self + 0xa58) = 0x0;
            *(void **) (self + 0xa5c) = 0x0;
        }
        return 0x1;
    }
}
