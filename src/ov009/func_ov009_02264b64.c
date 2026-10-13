/* func_ov009_02264b64 @ 0x02264b64, 0x7c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bbd4(int);
extern int func_ov003_022203dc(void);
extern int func_02064328(void *, void *, int, int, int);
extern char data_ov009_02265b94[];
extern char data_ov009_02265ab4[];

void *func_ov009_02264b64(char *self)
{
    volatile unsigned short t;
    int h;

    t = (unsigned short) func_0204bbd4(*(int *) (self + 0x138));
    switch (t) {
        case 0x500a:
        case 0x5011:
        case 0x501c:
        case 0x501d:
            return 0;
    }
    h = *(int *) (self + 0x138);
    func_02064328(data_ov009_02265b94, data_ov009_02265ab4, h, h, func_ov003_022203dc());
    return data_ov009_02265b94;
}
