/* func_0203f2c4 @ 0x0203f2c4, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020dab94;
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, unsigned char *, int);
extern void func_02073770(void *, int, int);

void func_0203f2c4(unsigned int a, unsigned char b, unsigned char c)
{
    unsigned char buf[6];
    void *obj;

    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }
    data_020dab94 = c;
    buf[0] = c;
    buf[1] = (unsigned char) a;
    buf[2] = (unsigned char) (a >> 8);
    buf[3] = (unsigned char) (a >> 16);
    buf[4] = (unsigned char) (a >> 24);
    buf[5] = b;
    obj = data_020ccf94;
    func_02073820(obj);
    func_020737f0(obj, buf, 6);
    func_02073770(obj, 0x17, 6);
}
