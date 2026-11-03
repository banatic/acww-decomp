/* talk_pick_scan: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020691f4 @ 0x020691f4, 0x28 bytes, Thumb
 * func_020691cc @ 0x020691cc, 0x28 bytes, Thumb
 * func_020691a4 @ 0x020691a4, 0x28 bytes, Thumb
 * func_02069194 @ 0x02069194, 0x10 bytes, Thumb
 * func_02069168 @ 0x02069168, 0x2c bytes, Thumb
 */

typedef struct Vtbl {
    char pad_00[0x64];
    void (*func)(void *, unsigned char);
} Vtbl;

typedef struct UnkStruct_02069168 {
    Vtbl *vtbl;
} UnkStruct_02069168;

extern void *func_020a941c(void *obj);
extern void func_020edb3c(void *obj);
extern unsigned char data_020defc0[];
extern unsigned char data_020e3e68[];
extern void func_020a9354(void *param1, void *param2);
extern int func_020a92d8(void *param1, int param2);
extern void func_020a8764(void *, int);
extern void func_020a8754(void *ptr);
extern void func_020a873c(void *, void *);

void func_02069194(void *ptr);
void func_02069168(void *self);

void *func_020691f4(void *obj)
{
    ((volatile unsigned int *) obj)[0] = (unsigned int) data_020defc0;
    ((volatile unsigned int *) obj)[0] = (unsigned int) data_020e3e68;
    func_020a941c(obj);
    func_020edb3c(obj);
    return obj;
}

void func_020691cc(void *param1, void *param2)
{
    void *r5 = param1;
    void *r4 = param2;

    func_02069194(param1);
    *(int *) ((char *) r5 + 0x28) = 0;
    func_020a9354(r5, r4);
    func_020a92d8(r5, 0);
}

/* FAKEMATCH: the empty if keeps both pair words loaded before the first compare; the plain condition compares a before loading b */
void func_020691a4(void *self, int a)
{
    int b;
    func_020a8764((char *) self + 0x2c, a);
    if (*(unsigned int *) ((char *) self + 0x28) == 0) {
        a = *(int *) ((char *) self + 0x2c);
        if ((self && self) && self) {
        }
        b = *(int *) ((char *) self + 0x30);
        if ((a == 0xa) && (b == 0)) {
            func_02069168(self);
        }
    }
}

void func_02069194(void *ptr)
{
    *(unsigned int *) ((char *) ptr + 0x28) = 0;
    func_020a8754((char *) ptr + 0x2c);
}

void func_02069168(void *self)
{
    unsigned char local[8];
    unsigned char ch;
    void *ptr1;
    UnkStruct_02069168 *obj;
    Vtbl *vtbl;

    func_020a873c((char *) self + 0x2c, local);
    ptr1 = *(void **) ((char *) self + 0x24);
    obj = *(UnkStruct_02069168 **) ((char *) ptr1 + 0x14a8);
    ch = local[0];
    vtbl = obj->vtbl;
    vtbl->func(obj, ch);
}
