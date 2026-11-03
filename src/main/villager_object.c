/* villager_object: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209b6b8 @ 0x0209b6b8, 0x6 bytes, Thumb
 * func_0209b69c @ 0x0209b69c, 0x1a bytes, Thumb
 * func_0209b64c @ 0x0209b64c, 0x50 bytes, Thumb
 * func_0209b634 @ 0x0209b634, 0x18 bytes, Thumb
 * func_0209b61c @ 0x0209b61c, 0x18 bytes, Thumb
 * func_0209b604 @ 0x0209b604, 0x16 bytes, Thumb
 * func_0209b5f0 @ 0x0209b5f0, 0x14 bytes, Thumb
 * func_0209b5ec @ 0x0209b5ec, 0x2 bytes, Thumb
 * func_0209b5e8 @ 0x0209b5e8, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[46];
    unsigned char unk_2E;
} UnkStruct_0209b6b8;

extern int func_0209b91c(void *);
extern int func_0209bd44(int);
extern int func_0209bc40(int);
extern int func_0209b914(int);
extern unsigned char data_020d1a30[];
extern void *func_0209c3e4(void *p);
extern void *func_0209bb48(void *p);
extern void *func_0209bb30(void *ptr);
extern char *func_0209c3c8(void *ptr);
extern void func_0209c398(void *ptr);
extern void func_0209baf4(void *ptr);
extern void func_0209c334(void *arg, int, int);
extern int func_0209c330(void *arg);

unsigned char func_0209b6b8(UnkStruct_0209b6b8 *p)
{
    return p->unk_2E;
}

unsigned char func_0209b69c(unsigned char *p, int n)
{
    int v = p[0x2e] + n;
    if (v > 14) {
        v = 14;
    }
    p[0x2e] = v;
    return p[0x2e];
}

int func_0209b64c(int arg0)
{
    int a, i;

    a = func_0209b91c((void *) arg0);
    if (func_0209bd44(a) != 0 && func_0209bc40(a) == 4 && (i = func_0209b914(arg0)) < 6) {
        if ((unsigned int) func_0209b6b8((UnkStruct_0209b6b8 *) arg0) >= data_020d1a30[i]) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

void *func_0209b634(void *p)
{
    func_0209c3e4(p);
    func_0209bb48((char *) p + 0x24);
    return p;
}

void *func_0209b61c(void *ptr)
{
    func_0209bb30((char *) ptr + 0x24);
    func_0209c3c8(ptr);
    return ptr;
}

void func_0209b604(void *arg)
{
    void *ptr;
    void *ptr2;

    ptr = arg;
    func_0209c398(ptr);
    ptr2 = (char *) ptr + 0x24;
    func_0209baf4(ptr2);
}

void func_0209b5f0(void *arg, int argument1, int argument2)
{
    func_0209c334(arg, (int) argument1, (int) argument2);
    func_0209c330(arg);
}

void *func_0209b5ec(void *object)
{
    return object;
}

int func_0209b5e8(int p0)
{
    return ((int) (p0) + (36));
}
