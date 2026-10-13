/* func_02076e58 @ 0x02076e58, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern void *data_020ccf94;
extern void func_020736bc(void *obj, void *data, int a);
extern void func_02073820(void *obj);
extern void func_020737f0(void *obj, void *data, int flag);
extern void func_02073770(void *obj, int a, int b);
extern unsigned char func_ov003_0222d7d0(unsigned char);

void func_02076e58(int a, int b, int c, int d)
{
    unsigned char data[2];
    void *obj;
    unsigned int cond;

    data[1] = 1;
    obj = data_020ccf94;
    func_020736bc(obj, data, a);

    cond = (data_020e54a8 == 0) ? 1 : 0;
    if (cond > 0) {
        data[1] = func_ov003_0222d7d0(data[0]);
    }

    func_02073820(obj);

    if (data[1] == 0) {
        data[0] &= 0xF;
        data[0] |= (d << 4);
        data[0] += 0x10;
        obj = data_020ccf94;
        func_020737f0(obj, data, 1);
        func_02073770(obj, 0x29, 7);
    } else {
        obj = data_020ccf94;
        func_020737f0(obj, data + 1, 1);
        func_02073770(obj, 0x29, d);
    }
}
