/* func_ov068_0226ada8 @ 0x0226ada8, 0x58 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226ada8 {
    int pad_00;
};
extern char data_021e5a2c[];
extern int func_0207cc94(struct UnkStruct_0226ada8 *, int *, int);
extern int func_0208150c(unsigned int value);
extern char *func_02137550(int *, int);
extern void func_ov068_0226ae48(void *, int, int, void *);

void func_ov068_0226ada8(void *self, int unused, void *arg)
{
    struct UnkStruct_0226ada8 *g;
    int key;
    int status;
    int t;

    g = (struct UnkStruct_0226ada8 *) data_021e5a2c;
    if (g != 0) {
        if ((status = func_0207cc94(g, 0, 0)) != 0) {
            key = func_0208150c(status);
            func_02137550(&t, 4);
            t = key;
            if ((status = func_0207cc94(g, &t, 1)) != 0) {
                func_ov068_0226ae48(self, key, func_0208150c(status), arg);
            }
        }
    }
}
