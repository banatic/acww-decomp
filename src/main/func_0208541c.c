/* func_0208541c @ 0x0208541c, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_0208541c;
typedef struct {
    unsigned char pad_00[4];
} UnkStruct_0208541c_2;

extern int func_020b6660(void);
extern void func_020795f4(void);
extern UnkStruct_0208541c *data_020ccf94;
extern int func_02073dd4(UnkStruct_0208541c *g, int v);
extern void func_0207c6a4(UnkStruct_0208541c_2 *o);
extern UnkStruct_0208541c_2 data_021e5a2c;
extern void *func_0207cec0(UnkStruct_0208541c_2 *o, int i);
extern int func_0208150c(void *x);
extern int func_02003704(int v);
extern void *func_0207f270(void *x);
extern int func_020825d8(unsigned short *w);
extern int func_020794c4(void *y);
extern void func_02079494(void *y);
extern int func_020794a0(void *y);
extern void func_020794c0(void *y, int z);
extern int func_0207944c(void *y);
extern void func_02079410(int a, int b);

int func_0208541c(void)
{
    UnkStruct_0208541c_2 *o = &data_021e5a2c;
    unsigned short w;
    void *x;
    void *y;
    int i;

    if (func_020b6660() != 0) {
        func_020795f4();
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0 && o != 0) {
            func_0207c6a4(o);
        }
    }
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0 && o != 0) {
        w = 0xfff1;
        for (i = 0; i < 8; i++) {
            x = func_0207cec0(o, i);
            if (x != 0) {
                if (func_02003704(func_0208150c(x)) != 0) {
                    y = func_0207f270(x);
                    if (y != 0) {
                        w = (unsigned short) ((i & 0xfff) | 0xe000);
                        if (func_020825d8(&w) == 0) {
                            if (func_020794c4(y) != 0) {
                                func_02079494(y);
                                if (func_020794a0(y) == 0) {
                                    func_020794c0(y, 0);
                                }
                                func_02079410(func_0207944c(y), 0);
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}
