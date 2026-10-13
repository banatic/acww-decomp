/* func_02083c84 @ 0x02083c84, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e1b70;
extern void func_020edb3c(void *obj, void *ptr);

struct UnkStruct_02083c84 {
    char *unk_00;
};

void *func_02083c84(struct UnkStruct_02083c84 *obj)
{
    obj->unk_00 = &data_020e1b70;
    func_020edb3c(obj, &data_020e1b70);
    return obj;
}
