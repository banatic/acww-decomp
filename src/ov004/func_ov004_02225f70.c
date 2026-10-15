/* func_ov004_02225f70 @ 0x02225f70, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073770(void *a, unsigned int b, unsigned int c);
extern void func_020737f0(void *argument0, int argument1, int argument2);
extern void func_02073820(void *argument0);
extern int func_02073d90(void *argument0);
extern void func_0209645c(unsigned char *out, unsigned int a, unsigned int b);
extern void *data_020ccf94;

void func_ov004_02225f70(char *self, unsigned int a1, unsigned int a2)
{
    // DECLS
    int v2;
    int v4;
    unsigned char frame[0x4];
    // ENDDECLS
    v2 = func_02073d90((void *) ((void *) (*(int *) ((char *) &data_020ccf94))));
    if (v2 != 0x0) {
        func_0209645c(frame, a1, a2);
        v4 = *(int *) ((char *) &data_020ccf94);
        func_02073820((void *) (v4));
        func_020737f0((void *) (v4), (int) (frame), (int) (0x1));
        func_02073770((void *) (v4), (unsigned int) (0x2c), (unsigned int) (0x4));
    }
}
