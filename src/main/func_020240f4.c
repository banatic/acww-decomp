/* func_020240f4 @ 0x020240f4, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    unsigned char b;
} Cfg;

extern const Cfg data_020d9128;
extern const int data_020d9d38[];
extern const Cfg data_020d9120;

extern int func_0202d9c4(void *self);
extern int func_0209bcc4(int h, int *out);
extern unsigned int func_0208150c(int v);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern void func_0202db48(void *self, Cfg c);

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_020240f4;

void func_020240f4(void *self, UnkStruct_020240f4 *out)
{
    Cfg cfg;
    int idx;

    cfg = data_020d9128;
    idx = 0;
    func_0209bcc4(func_0202d9c4(self), &idx);
    if (idx < 5) {
        cfg.a = data_020d9d38[idx];
    }
    if (cfg.a != 0) {
        func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e,
                      func_020036e8((unsigned char *) func_0208150c(*(int *) (*(char **) ((char *) self + 0x100) + 0x830))),
                      cfg.a, cfg.b, 0, 0);
        out->p = (char *) self + 0x104;
        out->b = *((unsigned char *) self + 0x122);
    }
    func_0202db48(self, data_020d9120);
}
