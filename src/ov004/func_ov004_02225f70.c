/* func_ov004_02225f70 @ 0x02225f70, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073770();
extern void func_020737f0();
extern void func_02073820();
extern int func_02073d90();
extern void func_0209645c();
extern void *data_020ccf94;

int func_ov004_02225f70(char *self, int a1, int a2)
{
    // DECLS
    int v2;
    int v4;
    char frame[0x4];
    // ENDDECLS
    v2 = func_02073d90(*(int *) ((char *) &data_020ccf94), a1, a2);
    if (v2 != 0x0) {
        func_0209645c(frame, a1, a2);
        v4 = *(int *) ((char *) &data_020ccf94);
        func_02073820(v4);
        func_020737f0(v4, frame, 0x1);
        return func_02073770(v4, 0x2c, 0x4);
    }
    return v2;
}
