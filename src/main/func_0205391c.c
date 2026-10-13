/* func_0205391c @ 0x0205391c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e8(void *);
extern void *func_0206e7bc(void *, int);
extern int data_021c8c48;

int func_0205391c(int id)
{
    void *obj;
    unsigned char flags;

    if (id >= 0x6e9) {
        id = 0x6e8;
    }
    obj = func_0206e7bc(func_0206e6e8(&data_021c8c48), id);
    if (obj == 0) {
        goto fail;
    }
    flags = *((unsigned char *) obj + 1);
    if ((flags & 1) != 0) {
        return 1;
    }
    return 0;
fail:
    return 0;
}
