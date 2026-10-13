/* func_ov107_0229d190 @ 0x0229d190, 0x94 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d128(void *self, void *p);
extern int func_ov107_0229d0bc(void *self, void *p);
extern unsigned int func_ov107_0229d0f0(void *self, void *p);
extern int func_ov107_0229c2b4(void *self, int a);

int func_ov107_0229d190(void *self, void *p)
{
    unsigned int id;

    if (func_ov107_0229d128(self, p) != 0) {
        return 0;
    }
    if (func_ov107_0229d0bc(self, p) != 0) {
        return 1;
    }

    id = func_ov107_0229d0f0(self, p);

    if ((id >= 0x137c && id <= 0x137c) || (id >= 0x1408 && id <= 0x1428) || (id >= 0x1471 && id <= 0x1491)) {
        return 1;
    }
    if (id >= 0x12e8 && id <= 0x131f) {
        if (func_ov107_0229c2b4(self, 0x40) == 0) {
            return 1;
        }
    }
    return 0;
}
