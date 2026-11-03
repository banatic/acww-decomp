/* object_claim: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203f2c4 @ 0x0203f2c4, 0x5c bytes, Thumb
 * func_0203f278 @ 0x0203f278, 0x4c bytes, Thumb
 * func_0203f26c @ 0x0203f26c, 0xc bytes, Thumb
 * func_0203f260 @ 0x0203f260, 0xc bytes, Thumb
 */

extern unsigned char data_020dab94;
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, unsigned char *, int);
extern void func_02073770(void *, int, int);
extern int func_0203f454(unsigned char, int);
extern void func_0203f490(int, int);
extern unsigned int OSiHeapInfo[];
extern int func_0203f444(unsigned char);

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

void func_0203f278(unsigned char *ptr, int param)
{
    unsigned int combined;

    combined = ((unsigned int) ptr[4] << 24) |
               (((unsigned int) ptr[3] << 16) | ((unsigned int) ptr[1] | ((unsigned int) ptr[2] << 8)));
    if (func_0203f454((unsigned char) param, combined)) {
        OSiHeapInfo[param] = combined;
        func_0203f490(1, param);
    } else {
        func_0203f490(2, param);
    }
}

void func_0203f26c(unsigned char *src)
{
    unsigned char val;
    val = *src;
    data_020dab94 = val;
}

void func_0203f260(int arg0, int arg1)
{
    func_0203f444(arg1);
}
