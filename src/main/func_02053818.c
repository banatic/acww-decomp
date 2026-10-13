/* func_02053818 @ 0x02053818, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e8(void *table);
extern unsigned char *func_0206e7bc(void *t, int idx);

extern unsigned char data_021c8c48[];

int func_02053818(int id)
{
    unsigned char *p;
    int flag;
    int idx;

    if (id >= 0x6e9) {
        idx = 0x6e8;
    } else {
        idx = id;
    }
    p = func_0206e7bc(func_0206e6e8((void *) data_021c8c48), idx);
    if (p != 0) {
        if (((p[1] >> 4) & 1) != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }
    if (flag != 0) {
        return 1;
    }

    if (id >= 0x6e9) {
        id = 0x6e8;
    }
    p = func_0206e7bc(func_0206e6e8((void *) data_021c8c48), id);
    if (p != 0) {
        if (((p[1] >> 5) & 1) != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }
    if (flag != 0) {
        return 2;
    }
    return 0;
}
