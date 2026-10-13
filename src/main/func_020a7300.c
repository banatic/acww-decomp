/* func_020a7300 @ 0x020a7300, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct triple {
    unsigned char a, b, c;
};

extern struct triple data_021f4320[];

void func_020a7738(struct triple *p, unsigned char *a, unsigned char *b, unsigned char *c);

unsigned char func_020a7300(int n)
{
    if (n < 4) {
        unsigned char local[3];
        func_020a7738(&data_021f4320[n], &local[0], &local[1], &local[2]);
        return local[1];
    }
    return 1;
}
