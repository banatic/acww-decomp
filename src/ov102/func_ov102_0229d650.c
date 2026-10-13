/* func_ov102_0229d650 @ 0x0229d650, 0x64 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *ptr, int val);
extern void func_ov002_02208098(void *ptr, int val);
extern void func_ov094_022999c0(void);
extern void func_ov102_0229cc90(void *ptr, unsigned char val);
extern void func_ov102_0229cd80(void *ptr);

struct UnkStruct_0229d650 {
    unsigned char data[0x25ab];
};

void func_ov102_0229d650(struct UnkStruct_0229d650 *obj, unsigned char val)
{
    obj->data[0x25a2] = val;
    obj->data[0x25a4] = val;
    obj->data[0x25a3] = obj->data[0x25aa];
    func_ov002_02207d24(&obj->data[0x218c], 1);
    func_ov102_0229cc90(obj, val);
    if (obj->data[0x259f] == 1) {
        func_ov002_02208098(obj, 2);
    }
    func_ov102_0229cd80(obj);
    func_ov094_022999c0();
}
