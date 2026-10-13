/* func_ov050_02263e78 @ 0x02263e78, 0x110 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern int func_0201c0e0(void *);
extern int func_0201c040(void *, int *, int *);
extern void func_0201c054(void *, int, unsigned int, unsigned int);
extern int func_0201c2a4(void *, int);
extern int func_02016108(void *, int);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern int func_020a7278(void);
extern int func_ov050_02260510(void *);
extern void func_ov050_02263640(void *, int);
extern void func_ov050_02264834(void *, int);
extern void func_ov050_02260718(void *);
}

struct UnkStruct_02263e78 {
    char pad_00[0x64];
    unsigned int unk_64;
};
extern struct UnkStruct_02263e78 *data_020ccf94;

class ClassAt658 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

extern "C" int func_ov050_02263e78(void *obj)
{
    unsigned short local_short;
    int a;
    int b;
    int flag;
    int a_val;

    if (func_0201c0e0(obj)) {
        a = 4;
        b = 4;
        if (func_0201c040(obj, &a, &b) && ((a_val = a), a_val == (int) data_020ccf94->unk_64) && a_val == b) {
            unsigned int field = data_020ccf94->unk_64;
            func_0201c054(obj, 1, field, field);
            ((ClassAt658 *) ((char *) obj + 0x658))->f2();
            int ret = func_0201c2a4(obj, 4);
            func_02016108((char *) obj + 0x658, ret);
            if (func_0204bcdc((char *) obj + 0x732)) {
                local_short = 0xfff1;
                flag = (func_0204bc64((char *) obj + 0x732) == func_0204bc64(&local_short)) ? 1 : 0;
            } else {
                flag = (*(unsigned short *) ((char *) obj + 0x732) == 0xfff1) ? 1 : 0;
            }
            if (flag) {
                if (func_ov050_02260510(obj)) {
                    func_ov050_02263640((char *) obj + 0x658, 5);
                } else {
                    func_ov050_02263640((char *) obj + 0x658, 0x13);
                }
            }
            func_ov050_02264834(obj, 4);
        } else {
            if (func_020a7278() && b == 4) {
                func_0201c054(obj, 1, data_020ccf94->unk_64, 4);
                func_ov050_02264834(obj, 0xd);
            }
        }
    } else {
        func_ov050_02260718(obj);
    }
    return 1;
}
