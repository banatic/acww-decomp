/* nook_store_5: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020afd9c @ 0x020afd9c, 0x2c bytes, Thumb
 * func_020afd58 @ 0x020afd58, 0x44 bytes, Thumb
 * func_020afd24 @ 0x020afd24, 0x34 bytes, Thumb
 * func_020afcf4 @ 0x020afcf4, 0x30 bytes, Thumb
 * func_020afcd4 @ 0x020afcd4, 0x20 bytes, Thumb
 * func_020afc84 @ 0x020afc84, 0x50 bytes, Thumb
 */

struct UnkStruct_020afc84 {
    unsigned char a, b, c, d, e, unk_05;
    unsigned short g;
};

extern int func_0203d7b0(int, void *);
extern int func_0203d79c(int, void *);
extern void *func_020644cc(int);
extern void *func_02077f14(void *, const void *);
extern char data_020e41c4[];
extern void *func_020b5630(char *p);
extern int func_020b45d0(char *p, void *arg, int n, int a, int b, int c);
extern int func_0203d7c4(int a, char *p);
extern void *func_020b5618(char *p);
extern void *func_02062f90(void *dst, unsigned int value);
extern void *func_02062f4c(void *dst);
extern void *func_020af028(void *);
extern unsigned char data_020e41b8[];
extern unsigned char data_021f395c[];
extern unsigned char *func_020afad4(unsigned char *p);

void func_020afd9c(void *arg0, void *arg1)
{
    func_0203d7b0(0, arg0);
    func_0203d79c(1, arg1);
    func_02077f14(func_020644cc(2), data_020e41c4);
}

void func_020afd58(void *arg)
{
    char st[0x40];
    func_020b5630(st);
    func_020b45d0(st, arg, 10, 0, 0, 0);
    func_0203d7c4(2, st);
    func_02077f14((void *) ((int) func_020644cc(2) + 2), (const void *) (((int *) data_020e41c4)));
    func_020b5618(st);
}

void func_020afd24(unsigned int param)
{
    unsigned char buffer[0x2c];
    func_02062f90(buffer, param);
    func_0203d7c4(3, (char *) buffer);
    func_02077f14((void *) ((unsigned int) func_020644cc(2) + 4), (const void *) (((unsigned char *) data_020e41c4)));
    func_02062f4c(buffer);
}

int func_020afcf4(int a, int b)
{
    func_0203d7b0(2, (void *) a);
    func_0203d79c(3, (void *) b);
    return (int) func_02077f14(func_020af028(((int *) data_021f395c)), (const void *) (((int *) data_020e41b8)));
}

void func_020afcd4(void)
{
    func_02077f14((void *) ((int) func_020af028((void *) data_021f395c) + 3), (const void *) ((void *) data_020e41b8));
}

int func_020afc84(struct UnkStruct_020afc84 *out)
{
    unsigned char *base = ((unsigned char *) data_021f395c);
    if (func_020afad4(base)[3] != 0) {
        out->unk_05 = func_020afad4(base)[2];
        out->e = func_020afad4(base)[1];
        out->d = func_020afad4(base)[0];
        out->c = 6;
        out->b = 0;
        out->a = 0;
        out->g = 0;
        return 1;
    } else {
        return 0;
    }
}
