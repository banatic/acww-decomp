/* func_020b3ac4 @ 0x020b3ac4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02031e84(void *obj);
extern void func_020edb3c(void *obj);
extern unsigned char data_020e50e8;

struct UnkStruct_020b3ac4 {
    void *unk_00;
};

void *func_020b3ac4(struct UnkStruct_020b3ac4 *obj)
{
    obj->unk_00 = &data_020e50e8;
    func_02031e84(obj);
    func_020edb3c(obj);
    return obj;
}
