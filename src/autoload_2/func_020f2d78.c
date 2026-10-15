/* func_020f2d78 @ 0x020f2d78, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f45c4(void *);
extern unsigned int data_0213ed44;

struct obj_020f2d78 {
    unsigned int unk_00;
    char unk_04;
};

struct obj_020f2d78 *func_020f2d78(struct obj_020f2d78 *obj)
{
    func_020f45c4(obj);
    obj->unk_00 = (unsigned int) &data_0213ed44;
    obj->unk_04 = 0x2b;
    return obj;
}
