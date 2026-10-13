/* func_0208fa1c @ 0x0208fa1c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208aef0(void *p);
extern int func_0208aeec(void *p);
extern void *func_0208a1d0(void *p);
extern void func_02088df8(int a, void *b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);

typedef struct {
    unsigned char pad_00[0x38];
    unsigned char unk_38;
    unsigned char unk_39;
} UnkStruct_0208fa1c;

void func_0208fa1c(UnkStruct_0208fa1c *param)
{
    if (param->unk_38 != 0 && param->unk_39 == 0) {
        int ret1;
        int ret2;
        char *p;
        void *ret3;

        ret1 = func_0208aef0(param);
        ret2 = func_0208aeec(param);
        p = (char *) param + 0xc;
        ret3 = func_0208a1d0(p);

        func_02088df8(0, ret3, ret1, ret2, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        func_02088df8(0, ret3, ret1, ret2, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
    }
}
