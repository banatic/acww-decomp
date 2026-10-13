/* func_020753a8 @ 0x020753a8, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a7880(unsigned char *);
extern void MI_CpuCopy8(unsigned char *, unsigned char *, int);
extern void func_020a7830(unsigned char *, unsigned char *, unsigned char *, unsigned char *, unsigned int *);
extern void func_020a7394(unsigned int, unsigned char, unsigned char, unsigned char, unsigned int);
extern void func_020a7870(unsigned char *);

void func_020753a8(unsigned char *p)
{
    unsigned int i;
    unsigned char buf[8];
    unsigned int word;

    i = 0;
    do {
        func_020a7880(&buf[3]);
        MI_CpuCopy8(p, &buf[3], 2);
        func_020a7830(&buf[3], &buf[0], &buf[1], &buf[2], &word);
        func_020a7394(i, buf[0], buf[1], buf[2], word);
        p += 2;
        func_020a7870(&buf[3]);
        i++;
    } while (i < 4);
}
