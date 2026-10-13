/* func_020261b0 @ 0x020261b0, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207f1c8(int);
extern int func_0209b5e8(int);

typedef void (*func_type)(unsigned short *, int, int);
extern func_type data_020c8f24[5];

void func_020261b0(unsigned short *out, void *src, unsigned int c)
{
    if (c < 5) {
        func_type fp = data_020c8f24[c];
        if (fp != 0) {
            void *p = *(void **) ((char *) src + 0x100);
            int x = *(int *) ((char *) p + 0x830);
            int z = func_0209b5e8(func_0207f1c8(x));
            fp(out, z, x);
            return;
        }
    }
    *out = 0xfff1;
}
