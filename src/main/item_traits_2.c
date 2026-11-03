/* item_traits_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204c308 @ 0x0204c308, 0x28 bytes, Thumb
 * func_0204c2b4 @ 0x0204c2b4, 0x54 bytes, Thumb
 * func_0204c260 @ 0x0204c260, 0x54 bytes, Thumb
 * func_0204c228 @ 0x0204c228, 0x38 bytes, Thumb
 */

extern int func_0204c358(int param);
extern int func_0204c330(int param);
extern int func_02061624(unsigned char param);
extern void func_02061e2c(int *buf, int arg);
extern int func_0204bcf8(int *buf);
extern int func_02062408(int *buf);
extern int func_0204bcdc(int *buf);
extern int func_02053728(int *buf);
extern int func_0206233c(void *);
extern int func_020536c8(void *);
extern void func_020051b0(void *);
extern void *func_0204b2c8(void *arg);
extern int func_0204b42c(void *arg);
extern void func_0204b3cc(void *object, unsigned int value);
extern void *func_020622c4(void *ptr);

unsigned short func_0204c308(int param)
{
    if (func_0204c358(param) != 0) {
        return (unsigned short) func_02061624((unsigned char) func_0204c330(param));
    } else {
        return 0;
    }
}

int func_0204c2b4(int arg)
{
    int buf[2];
    func_02061e2c(buf, arg);
    if (func_0204bcf8(buf) == 1) {
        int r4 = func_02062408(buf);
        func_020051b0((void *) buf);
        return r4;
    } else {
        if (func_0204bcdc(buf) != 0) {
            int r4 = func_02053728(buf);
            func_020051b0((void *) buf);
            return r4;
        } else {
            func_020051b0((void *) buf);
            return 0;
        }
    }
}

int func_0204c260(void *param)
{
    char local[8];
    func_02061e2c((int *) local, (int) param);
    if (func_0204bcf8((int *) local) == 1) {
        int ret = func_0206233c(local);
        func_020051b0(local);
        return ret;
    } else if (func_0204bcdc((int *) local) != 0) {
        int ret = func_020536c8(local);
        func_020051b0(local);
        return ret;
    } else {
        func_020051b0(local);
        return 1;
    }
}

void *func_0204c228(void *arg)
{
    void *result;
    unsigned int size;
    unsigned int local[2];

    if (func_0204b2c8(arg) != 0) {
        size = func_0204b42c(arg);
        func_0204b3cc(local, size);
        result = func_020622c4(local);
        func_020051b0(local);
        return result;
    }
    return 0;
}
