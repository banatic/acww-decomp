/* func_0203fdc4 @ 0x0203fdc4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_0203fda0(int, unsigned int *);
extern void func_0209e474(void *);
extern int func_0209e380(void *, void *);
extern unsigned int data_021c74d4;

int func_0203fdc4(int arg)
{
    unsigned int local[4];
    unsigned char *p;
    unsigned char *q;
    int result = -1;

    p = func_0203fda0(arg, &data_021c74d4);
    if (p != 0) {
        local[0] = 0;
        local[1] = 0;
        local[2] = 0;
        local[3] = 0;
        func_0209e474(local);

        ((unsigned char *) local)[2] = 0;
        ((unsigned char *) local)[1] = 0;
        ((unsigned char *) local)[0] = 0;

        q = p + 4;
        local[2] = 0;
        local[3] = 0;

        ((unsigned char *) local)[13] = ((unsigned char *) local)[5];
        ((unsigned char *) local)[12] = q[3];
        ((unsigned char *) local)[11] = q[2];

        result = func_0209e380(&local[2], local);
    }
    return result;
}
