/* func_0207417c @ 0x0207417c, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0207417c {
    unsigned char pad_00[0x64];
    int unk_64;
};
extern struct UnkStruct_0207417c *data_020ccf94;

extern int func_02073dd4(void *a, int b);
extern void func_020a6f74(int a, int b);
extern void *func_02073d28(void *a, int b);
extern void func_02077b3c(void *a, int b, int c);
extern int func_02073e30(void *a, void *b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_02073918(void *a, int b);
extern void func_02073820(void *a);
extern void func_020737f0(void *a, void *b, int c);
extern void func_02073770(void *a, int b, int c);

int func_0207417c(int param)
{
    char byte;
    struct UnkStruct_0207417c *self;
    int field;
    struct UnkStruct_0207417c *g2;
    void *p1;
    void *p2;
    struct UnkStruct_0207417c *g3;

    self = data_020ccf94;
    field = self->unk_64;

    if (func_02073dd4(self, field) == 0) {
        func_020a6f74(3, 4);
        g2 = data_020ccf94;
        p1 = func_02073d28(g2, 4);
        func_02077b3c(p1, 0, 5);
        ((char *) p1)[1] = 0;
        p2 = func_02073d28(g2, 4);
        return func_02073e30(g2, p2, 2, 1, 0, 0, 0, 0, 0, 0);
    } else {
        if (func_02073918(self, 0) != 0) {
            func_020a6f74(field, param);
        } else {
            func_020a6f74(field, 4);
            byte = (char) param;
            g3 = data_020ccf94;
            func_02073820(g3);
            func_020737f0(g3, &byte, 1);
            func_02073770(g3, 0, 0);
        }
    }
    return 1;
}
