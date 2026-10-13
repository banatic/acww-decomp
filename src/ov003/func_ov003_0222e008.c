/* func_ov003_0222e008 @ 0x0222e008, 0xa4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x25c];
} Actor;
extern Actor data_ov003_022617bc[];
extern Actor data_ov003_02260994[];
extern Actor data_ov003_02260e4c[];
extern void func_ov003_0222fe18(void *a, void *b, int c);
extern void func_020e9898(void *a);
extern void func_0209d138(void *a);
extern void func_02044528(void);

int func_ov003_0222e008(char *self)
{
    Actor *a = data_ov003_022617bc;
    Actor *b = data_ov003_02260994;
    Actor *c = data_ov003_02260e4c;
    int i;
    int j;
    for (i = 0; i < 8; i++) {
        func_ov003_0222fe18(self, a++, 1);
    }
    for (i = 0; i < 2; i++) {
        void **p;
        func_ov003_0222fe18(self, b++, 2);
        p = (void **) (self + i * 4);
        func_020e9898(p[0x26]);
        p[0x26] = 0;
    }
    for (j = 0; j < 4; j++) {
        func_ov003_0222fe18(self, c++, 3);
    }
    func_0209d138(self + 0x50);
    func_0209d138(self + 0x68);
    func_0209d138(self + 0x80);
    func_02044528();
    return 1;
}
