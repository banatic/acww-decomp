/* func_0205d9ec @ 0x0205d9ec, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020b65c4(void);
extern unsigned int func_020b5e04(void);
extern unsigned int func_020b5df8(void);
extern unsigned int func_02085f08(void);
extern unsigned int func_0205dab8(void);
extern unsigned int func_020e9968(unsigned int, unsigned int, unsigned int);

extern unsigned int data_021c9aec;
extern unsigned char *data_020ccf94;

void func_0205d9ec(unsigned int *out)
{
    unsigned int min_count, i, v, w, limit, j, size;
    unsigned int g;
    unsigned char byte;

    g = data_021c9aec;
    byte = data_020ccf94[0x6c];
    func_020b65c4();
    min_count = func_020b5e04();
    if (byte < min_count) {
        min_count = byte;
    }

    i = 0;
    while (i < min_count) {
        out[i] = func_020e9968(g, func_0205dab8(), 4);
        i++;
    }

    if (min_count == 0) {
        min_count = 1;
    }

    func_020b65c4();
    v = func_020b5df8();
    w = func_02085f08();
    limit = v + w - min_count;

    size = 4;
    j = 4;
    while (j < limit + 4) {
        out[j] = func_020e9968(g, func_0205dab8(), size);
        j++;
    }
}
