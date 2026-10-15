/* func_020bde98 @ 0x020bde98, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066688(void *object);

extern void *func_02098844(void *addr, int idx);
extern int func_02099020(void *arg, int val);
extern void func_02066694(void *obj);
extern unsigned char func_020644cc(int val);
extern int func_02099870(void *arg);
extern void func_02066024(void *obj, void *sub, void *a, void *b, void *c, int d);
extern void func_02063ccc(void *buf, int a, int b);
extern void func_020638d4(void *p, void *q, int a, int b, int c, int d, int e);
extern void func_02063cc8(void *buf);
extern unsigned short func_02065ed0(void *obj, unsigned short s, int flag);
extern int func_02097a54(void *obj);
extern void func_02098fd0(void *arg, int val);

extern unsigned char data_020e596c[];
extern unsigned char data_020e5970[];
extern unsigned char data_020e7ad0[];
extern unsigned char data_021dc7bc[];

void func_020bde98(void)
{
    int zero = 0;
    int idx = 0;
    int i;
    struct UnkStruct_020bde98 {
        unsigned char c;
        unsigned short s;
    } sub;
    struct Buf {
        unsigned int a, b;
    } buf14, buf1c;
    unsigned char obj[0x100];

    for (i = 0; i < 4; i++) {
        void *p = func_02098844((void *) data_021dc7bc, i);
        if (p == 0) {
            continue;
        }
        if (func_02099020(p, 0x32) == 0) {
            continue;
        }

        func_02066694(obj);
        sub.c = func_020644cc(3);
        {
            int r = func_02099870(p);
            func_02066024(obj, &sub, (void *) data_020e7ad0, (void *) data_020e5970, (void *) data_020e596c, r);
        }
        func_02063ccc(&buf14, idx, 4);
        buf1c.a = buf14.a;
        buf1c.b = buf14.b;
        func_020638d4(&sub.s, &buf1c, zero, zero, 1, 1, zero);
        func_02063cc8(&buf1c);
        func_02065ed0(obj, sub.s, 1);
        if (func_02097a54(obj) != 0) {
            func_02098fd0(p, 0x32);
        }
        func_02063cc8(&buf14);
        func_02066688(obj);
    }
}
