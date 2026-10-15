/* func_020b0164 @ 0x020b0164, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02063ccc(void *buf, int a, int b);
extern int func_020638b0(void *a, unsigned int b, void *c, int d, void *e, int f, int g, int h);
extern void func_02063cc8(void *buf);
extern void func_02061b1c(void *out, void *src, int n);
extern char data_021f4a80[];

void func_020b0164(char *base, int *index_ptr, int p2, int p3, unsigned int count, int p5, unsigned char flag)
{
    if (count == 0) {
        return;
    }
    {
        int off;
        unsigned short buffer2;
        unsigned int buffer[3];
        unsigned int i;

        func_02063ccc(buffer, p2, p3);
        func_020638b0(base + 2 * (*index_ptr), count, buffer, 0, &data_021f4a80, 0, 1, 0);
        func_02063cc8(buffer);
        if (flag != 0) {
            for (i = 0; i < count; i++) {
                off = (i + *index_ptr) * 2;
                func_02061b1c(&buffer2, base + off, 1);
                *(unsigned short *) (base + off) = buffer2;
            }
        }
        *index_ptr += count;
    }
}
