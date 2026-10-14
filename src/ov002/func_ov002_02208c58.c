/* func_ov002_02208c58 @ 0x02208c58, 0x74 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022089ec(void *a, void *b, unsigned char c);
extern void func_ov002_02208a0c(void *a, int b);
extern void func_ov002_02208a04(void *a, int b);
extern void func_ov002_022092e0(void *a);

void func_ov002_02208c58(void *a, const unsigned char *b, int c)
{
    int count = 0;
    int i = count;
    int offset;
    for (; i < 5; i++) {
        unsigned char byte = b[i];
        if (byte == 0xFF) {
            i = 5;
            continue;
        }
        if ((1 << i) & b[10]) {
            count++;
            continue;
        }
        offset = count;
        offset *= 0x74;
        func_ov002_022089ec(a, (char *) a + 0x28 + offset, byte);
        count++;
    }
    if (c) {
        func_ov002_02208a0c(a, 0x20);
    } else {
        func_ov002_02208a04(a, 0x20);
    }
    ((unsigned char *) a)[0x1c] = count;
    func_ov002_022092e0(a);
}
