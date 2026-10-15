/* func_02067344 @ 0x02067344, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02067308(void *self, char *s);
extern void *func_020672cc(void *self, char *s);
extern int strlen(const char *s);
extern int func_02064328(const char *fmt, ...);
extern char data_021cdb74[];
extern char data_020df094[];
extern char data_020df0a8[];
extern char data_020df0bc[];

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
    r7 = func_02067308(self, s);
    if (r7 != 0) {
        int len1 = strlen((char *) r7) + 1;
        char *s2 = s + len1;
        r4 = func_020672cc(self, s2);
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
