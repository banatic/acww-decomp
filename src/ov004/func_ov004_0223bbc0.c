/* func_ov004_0223bbc0 @ 0x0223bbc0, 0x3a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020961a8(int argument0);
extern int func_ov004_0223bbfc(int *argument0, int *argument1, void *argument2, int argument3, void *argument4,
                               void *argument5);

int func_ov004_0223bbc0(char *self, int a1, int a2, int a3)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_020961a8((int) ((int) (0x4)));
    if (v1 != 0x0) {
        return func_ov004_0223bbfc((int *) (self), (int *) (a1), (void *) ((char *) v1 + 0x5c),
                                   (int) (*(short *) ((char *) v1 + 0x8e)), (void *) (a2), (void *) (a3));
    }
    return -0x1;
}
