/* func_0207a51c @ 0x0207a51c, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short b[15];
} UnkStruct_0207a51c;

typedef struct {
    unsigned short unk_00;
    unsigned char m[12];
    unsigned char pad_0E;
    unsigned char unk_0F;
} Rec;

extern char data_021dc7bc[];

extern void *func_02065f7c(void *p);
extern int func_0209527c(UnkStruct_0207a51c *it, void *x);
extern int func_020951bc(UnkStruct_0207a51c *it);
extern void *func_02098868(char *g, UnkStruct_0207a51c *it);
extern void *func_02065f64(void *p);
extern void *func_02099640(void *p);
extern int func_0209a9a8(void *a, void *b);
extern void *func_02003760(Rec *r, void *v);
extern int func_02003704(Rec *r);
extern void *func_0207ce98(void *self, Rec *r);
extern void func_02081144(void *a, void *b, void *c);
extern int func_02081418(void *a, void *b);
extern int func_02003750(Rec *r);
extern int func_0209526c(UnkStruct_0207a51c *it);

int func_0207a51c(void *self, void *p1)
{
    UnkStruct_0207a51c it;
    Rec rec;
    void *x;
    void *obj;
    void *y;
    int ret;

    if (p1 == 0) {
        goto fail;
    }
    x = func_02065f7c(p1);
    if (x == 0) {
        goto fail;
    }
    func_0209527c(&it, x);
    if (func_020951bc(&it) == 0) {
        goto cleanup_it;
    }
    obj = func_02098868(data_021dc7bc, &it);
    y = func_02065f64(p1);
    if (obj != 0) {
        func_0209a9a8(func_02099640(obj), p1);
    }
    if (y == 0) {
        goto cleanup_it;
    }
    func_02003760(&rec, y);
    if (func_02003704(&rec) == 0) {
        goto cleanup_rec;
    }
    y = func_0207ce98(self, &rec);
    if (y == 0) {
        goto cleanup_rec;
    }
    func_02081144(y, obj, p1);
    ret = func_02081418(y, p1);
    func_02003750(&rec);
    func_0209526c(&it);
    return ret;
cleanup_rec:
    func_02003750(&rec);
cleanup_it:
    func_0209526c(&it);
fail:
    return 0;
}
