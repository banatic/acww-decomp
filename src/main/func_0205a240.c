/* func_0205a240 @ 0x0205a240, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
} UnkStruct_0205a240;

extern char data_021e5a2c[];
extern char data_021c9704[];

extern int func_0207ce98(char *g, void *d);
extern void func_0200366c(void *d, char *g, int n, void *a);
extern int func_020036e8(void *d);
extern int func_0209765c(int v);
extern void func_02066694(void *o);
extern void func_020662bc(void *o, UnkStruct_0205a240 *s, char *g, unsigned char *p, void *d, void *c, int one);
extern void func_02065ed0(void *o, unsigned short v, int k);
extern int func_02097a54(void *o);
extern void func_02066688(void *o);
extern int func_020979f0(void *o, int k);

int func_0205a240(void *a0, int a1, void *a2, void *a3, unsigned short *a4, int a5)
{
    UnkStruct_0205a240 s;
    int obj[0x40];

    if (func_0207ce98(data_021e5a2c, a3) != 0) {
        func_0200366c(a3, data_021c9704, 0x28, a0);
        s.unk_00 = (unsigned char) a1;
        s.unk_01 = (unsigned char) func_0209765c(func_020036e8(a3));
        if (a5 != -1) {
            s.unk_01 = (unsigned char) a5;
        }
        func_02066694(obj);
        func_020662bc(obj, &s, data_021c9704, &s.unk_01, a3, a2, 1);
        if (a4 != 0) {
            func_02065ed0(obj, *a4, 1);
        }
        if (func_02097a54(obj) != 0) {
            func_02066688(obj);
            return 1;
        }
        if (func_020979f0(obj, 0) != 0) {
            func_02066688(obj);
            return 1;
        }
        func_02066688(obj);
    }
    return 0;
}
