/* func_ov068_0226dd7c @ 0x0226dd7c, 0x70 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226dd7c {
    int a;
    int b;
    int c;
};

extern struct UnkStruct_0226dd7c data_021fbee8;

extern void *func_02095794(int);
extern void func_0203bc50(int, void *);
extern void func_0203be6c(int);
extern void func_01ffcbb0(void *, int);
extern int func_0203c57c(int);
extern int func_0203c568(int);
extern int func_0203c548(int);
extern void func_0203bd84(int, void *, int, int, int);

void func_ov068_0226dd7c(int obj)
{
    int a;
    int b;
    int c;
    struct UnkStruct_0226dd7c s;
    int buf[4];
    struct UnkStruct_0226dd7c *p;

    s.a = data_021fbee8.a;
    s.b = data_021fbee8.b;
    s.c = data_021fbee8.c;
    p = func_02095794(4);
    if (p != 0) {
        s.a = p->a;
        s.b = p->b;
        s.c = p->c;
    }
    func_0203bc50(obj, &s);
    func_0203be6c(obj);
    func_01ffcbb0(buf, obj);
    a = func_0203c57c(obj);
    b = func_0203c568(obj);
    c = func_0203c548(obj);
    func_0203bd84(obj, buf, a, b, c);
}
