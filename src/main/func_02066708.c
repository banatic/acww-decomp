/* func_02066708 @ 0x02066708, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct _Info {
    unsigned char data[0x1e];
    unsigned char type;
};

void *func_02066708(struct _Info *obj)
{
    if (obj->type == 1 || obj->type == 2 || obj->type == 6) {
        return obj;
    } else {
        return 0;
    }
}
