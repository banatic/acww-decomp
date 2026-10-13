/* func_02069a94 @ 0x02069a94, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02069a94 UnkStruct_02069a94;
typedef int (*Method)(UnkStruct_02069a94 *, int, int);
typedef struct {
    Method m[14];
} Vtbl;
struct UnkStruct_02069a94 {
    Vtbl *vtbl;
};

extern int func_020a8718(void *addr, unsigned char *b1, unsigned char *b2);
extern int func_020984e8(int val);
extern int func_02099870(int val);
extern int func_020950c0(int val);
extern void func_0206b964(void *self, unsigned char *buf);

void func_02069a94(void *self)
{
    unsigned char buf[3];
    void *p;
    UnkStruct_02069a94 *obj;
    int flag;

    p = *(void **) ((char *) self + 0x24);
    obj = *(UnkStruct_02069a94 **) ((char *) p + 0x14a8);
    obj->vtbl->m[13](obj, 3, 2);

    flag = (func_020950c0(func_02099870(func_020984e8(func_020a8718((char *) self + 0x38, &buf[1], &buf[2])))) != 0);
    buf[0] = (&buf[1])[flag];

    func_0206b964(self, buf);
}
