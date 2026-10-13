/* func_020b00fc @ 0x020b00fc, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020637d0(unsigned short *, unsigned int, int, int, int, int, int, int, int);
extern void func_02061b1c(unsigned short *, unsigned short *, int);

extern unsigned char data_021f4a80[];

void func_020b00fc(unsigned short *p0, int *index_ptr, int param2, int param3, unsigned int count, unsigned int unused,
                   unsigned char flag)
{
    if (count == 0) {
        return;
    }

    func_020637d0(p0 + *index_ptr, count, param2, param3, 0, 0, 10, (unsigned int) data_021f4a80, 0);

    if (flag != 0) {
        unsigned int off;
        unsigned int i;
        unsigned short tmp;

        for (i = 0; i < count; i++) {
            off = (i + *index_ptr) * 2;
            func_02061b1c(&tmp, (unsigned short *) ((char *) p0 + off), 1);
            *(unsigned short *) ((char *) p0 + off) = tmp;
        }
    }

    *index_ptr += count;
}
