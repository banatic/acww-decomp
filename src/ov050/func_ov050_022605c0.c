/* func_ov050_022605c0 @ 0x022605c0, 0xf4 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;

struct UnkStruct_022605c0 {
    int a;
    int b;
    int c;
};

extern struct UnkStruct_022605c0 *func_02095794(int n);
extern int func_ov050_02263638(void *p);
extern int func_ov050_022604bc(void *obj);
extern int func_ov050_022609f0(void *obj);
extern int func_02030818(struct UnkStruct_022605c0 *v);
extern int func_0201c2c8(void *obj, int n);
extern void func_0201aff4(void *p, int n);
extern int func_02073d90(void *);
extern short *func_0209d358(int a, int b);
extern void *func_020984e8(void);
extern int func_02099640(int argument0);
extern int func_02099020(void *p, int n);
extern void func_ov050_02263640(void *p, int n);
extern int func_0203e0a8(void *obj, int n);
extern void func_ov050_02264834(void *obj, int n);

int func_ov050_022605c0(void *obj)
{
    struct UnkStruct_022605c0 v;
    struct UnkStruct_022605c0 *s;
    void *h;

    s = func_02095794(4);
    v.a = s->a;
    v.b = s->b;
    v.c = s->c;
    if (func_ov050_02263638((char *) obj + 0x658) != 1 && func_ov050_02263638((char *) obj + 0x658) != 0x12) {
        if (func_ov050_022604bc(obj) != 0 && func_ov050_022609f0(obj) == 0) {
            if (func_02030818(&v) != 0) {
                func_0201aff4((char *) obj + 0x350, func_0201c2c8(obj, 4));
            }
            return 0;
        }
        if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
            return 0;
        }
        h = func_020984e8();
        func_02099640((int) h);
        if (func_02099020(h, 1) != 0) {
            return 0;
        }
    }
    if (func_02030818(&v) != 0) {
        if (func_ov050_022604bc(obj) != 0) {
            func_ov050_02263640((char *) obj + 0x658, 0x12);
        } else {
            func_ov050_02263640((char *) obj + 0x658, 1);
        }
        func_0203e0a8(obj, 0);
        func_ov050_02264834(obj, 0x12);
        return 1;
    }
    return 0;
}
