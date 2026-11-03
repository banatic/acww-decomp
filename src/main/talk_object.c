/* talk_object: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02067344 @ 0x02067344, 0x9c bytes, Thumb
 * func_02067308 @ 0x02067308, 0x3c bytes, Thumb
 * func_020672cc @ 0x020672cc, 0x3c bytes, Thumb
 * func_0206726c @ 0x0206726c, 0x60 bytes, Thumb
 * func_02067218 @ 0x02067218, 0x54 bytes, Thumb
 * func_020671fc @ 0x020671fc, 0x1a bytes, Thumb
 */

struct UnkStruct_02067218_2 {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
};

struct UnkStruct_02067218 {
    unsigned char pad_00[0x14a8];
    struct UnkStruct_02067218_2 *ptr;
    unsigned char pad_14AC[0x9cb];
    unsigned char unk_1E77;
    signed char unk_1E78;
};

extern int strlen(const char *s);
extern int func_02064328(const char *fmt, ...);
extern char data_021cdb74[];
extern char data_020df094[];
extern char data_020df0a8[];
extern char data_020df0bc[];
extern int strncmp(char *str, void *ptr, int offset);
extern char *data_020ccec4[];
extern const char *data_020ccee8[];
extern void func_0206d63c(void *ptr);
extern int func_020a9a08(void *ptr, int ret);
extern int func_020a9938(void *ptr, int val);
extern int func_020a9530(void *ptr);
extern void func_020a82bc(void *ptr, int ret);
extern void func_020a99d8(void *ptr);
extern char data_021f43f8;
extern void func_020a8164(void *p, signed char *q);
extern void func_0206844c(void *s, void *g, int i);
extern void func_0206741c(void *s);
extern void func_02067c20(void *s);

char *func_02067308(void *unused, char *str);
const char *func_020672cc(void *a, const char *s);

void *func_02067344(void *self, char *s, int flag)
{
    void *r7;
    void *r4;
    if (flag == 0) {
        void *obj = *(void **) ((char *) self + 0x14a8);
        void *vtable = *(void **) obj;
        flag = (*(int (**)(void *))((char *) vtable + 0xc))(obj);
    }
    if (s == 0) {
        void *obj = *(void **) ((char *) self + 0x14a8);
        s = (char *) obj + 4;
    }
    r7 = (void *) func_02067308(self, s);
    if (r7 != 0) {
        int len1 = strlen((char *) r7) + 1;
        char *s2 = s + len1;
        r4 = (void *) func_020672cc(self, (const char *) s2);
        if (r4 != 0) {
            char *p = s2 + (strlen((char *) r4) + 1);
            func_02064328(data_021cdb74, data_020df094, flag, r7, r4, p);
        } else {
            func_02064328(data_021cdb74, data_020df0a8, flag, r7, s2);
        }
    } else {
        func_02064328(data_021cdb74, data_020df0bc, flag, s);
    }
    return data_021cdb74;
}

char *func_02067308(void *unused, char *str)
{
    char **cur = data_020ccec4;
    char *elem;
    while ((elem = *cur) != 0) {
        int offset = strlen((const char *) elem);
        if (strncmp(str, elem, offset) == 0 && str[offset] == '_') {
            break;
        }
        cur++;
    }
    return elem;
}

const char *func_020672cc(void *a, const char *s)
{
    const char **ptr;
    const char *p;
    int n;

    ptr = data_020ccee8;
    while ((p = *ptr) != 0) {
        n = (__arm int) strlen(p);
        if ((__arm int) strncmp((char *) s, (void *) p, n) == 0 && s[n] == '_') {
            break;
        }
        ptr++;
    }
    return p;
}

void func_0206726c(void *p)
{
    int ret;
    func_0206d63c((char *) p + 0xb14);
    ret = (int) func_02067344(p, 0, 0);
    if (func_020a9a08((char *) p + 0xb14, ret)) {
        func_020a9938((char *) p + 0xb14, *(int *) ((char *) p + 0x14a8) + 0x1e);
    }
    ret = func_020a9530((char *) p + 0xb14);
    func_020a82bc((char *) p + 0x14ac, ret);
    func_020a99d8((char *) p + 0xb14);
}

void func_02067218(struct UnkStruct_02067218 *s)
{
    signed char v;
    s->ptr->unk_1E = s->unk_1E77;
    v = s->unk_1E78;
    if (v != 0) {
        func_020a8164(s->ptr, &s->unk_1E78);
    }
    func_0206844c(s, &data_021f43f8, 0);
    func_0206726c(s);
    func_0206741c(s);
    func_02067c20(s);
}

void func_020671fc(void *arg)
{
    func_0206726c(arg);
    func_0206741c(arg);
    func_02067c20(arg);
}
