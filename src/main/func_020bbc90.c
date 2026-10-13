/* func_020bbc90 @ 0x020bbc90, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642a8(void *, void *);
extern void func_0209e474(void *);
extern void func_020e930c(int *, int);
extern int func_020e92d0(int *, int);

extern unsigned char data_021dc7aa[];

void func_020bbc90(void *out)
{
    struct UnkStruct_020bbc90 {
        unsigned char pad[3];
        unsigned char b0;
        unsigned char b1;
        unsigned char b2;
        unsigned char pad2;
        unsigned char pad3;
        int c;
        unsigned short d;
        unsigned char filler[14];
    } local;
    unsigned int r4;
    int val;

    *(unsigned int *) &local = 0;
    *((unsigned int *) ((char *) &local + 4)) = 0;

    func_020642a8((void *) data_021dc7aa, &local.d);

    func_0209e474(&local);

    r4 = local.b0 | (local.b1 << 5 | (((unsigned int) local.d << 16) | ((local.b2 & 0x1f) << 9)));

    func_020e930c(&local.c, 1);
    func_020e930c(&local.c, (int) r4);

    val = func_020e92d0(&local.c, 0x2aaa);
    val -= 0x1555;
    *(unsigned short *) ((char *) out + 0x1538) = (unsigned short) val;
}
