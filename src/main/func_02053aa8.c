/* func_02053aa8 @ 0x02053aa8, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *table);
extern unsigned char *func_0206e7bc(void *t, int idx);

extern unsigned char data_021c8c48[];

int func_02053aa8(int id)
{
    unsigned char *p;
    int f1, f2;
    int idx;

    if (id >= 0x6e9) {
        idx = 0x6e8;
    } else {
        idx = id;
    }
    p = func_0206e7bc(func_0206e6ec((void *) data_021c8c48), idx);
    if (p != 0) {
        if ((p[7] & 1) != 0) {
            f1 = 1;
        } else {
            f1 = 0;
        }
    } else {
        f1 = 0;
    }

    if (id >= 0x6e9) {
        id = 0x6e8;
    }
    p = func_0206e7bc(func_0206e6ec((void *) data_021c8c48), id);
    if (f1 != 0) {
        return 1;
    }
    if (p != 0) {
        if (((p[7] >> 1) & 1) != 0) {
            f2 = 1;
        } else {
            f2 = 0;
        }
    } else {
        f2 = 0;
    }
    if (f2 != 0) {
        return 2;
    }
    return 0;
}
