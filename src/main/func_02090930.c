/* func_02090930 @ 0x02090930, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02090930 {
    int id;
    int unk_04;
    unsigned char flag;
    unsigned char pad_09[0xf];
} UnkStruct_02090930;

UnkStruct_02090930 *func_02090930(void *self, int id)
{
    UnkStruct_02090930 *res;
    UnkStruct_02090930 *e;
    int i;
    unsigned int t;

    e = (UnkStruct_02090930 *) ((char *) self + 4);
    res = 0;
    for (i = 0; i < 0x20; i++) {
        if (id == e->id) {
            if (e->flag == 1) {
                t = 1;
            } else {
                t = 0;
            }
            if (t > 0) {
                goto next;
            }
            res = e;
            goto done;
        }
    next:
        e = (UnkStruct_02090930 *) ((char *) e + 0x18);
    }
done:
    return res;
}
