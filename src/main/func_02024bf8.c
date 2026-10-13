/* func_02024bf8 @ 0x02024bf8, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202d9c4(void);
extern int func_0209bc40(void);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, void *, int, int, void *, int, int, unsigned char);
extern char data_020c8e50;
extern char data_020c8e5c;
struct Pair {
    unsigned int x;
    unsigned int y;
};
extern struct Pair data_020d9180;

void func_02024bf8(void *p, void *out)
{
    int mode = 2;
    void *data = (void *) &data_020c8e50;
    int res;

    func_0202d9c4();
    if (func_0209bc40() == 4) {
        data = (void *) &data_020c8e5c;
        mode = 3;
    }

    {
        int *field = *(int **) ((char *) p + 0x40);
        if (field) {
            *(int *) ((char *) field + 8) = 1;
        }
    }

    {
        void **ptr = *(void ***) ((char *) p + 0x100);
        int val = *(int *) ((char *) ptr + 0x830);
        res = func_020036e8(func_0208150c(val));
    }

    func_0202da38(p, (char *) p + 0x104, (char *) p + 0x122, 30, res, data, 3, 1, (unsigned char) mode);

    *(void **) out = (char *) p + 0x104;
    *(unsigned char *) ((char *) out + 4) = *(unsigned char *) ((char *) p + 0x122);

    *(struct Pair *) ((char *) p + 0xc8) = data_020d9180;
}
