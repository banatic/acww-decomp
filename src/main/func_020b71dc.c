/* func_020b71dc @ 0x020b71dc, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e54b4;
extern int data_020e54bc;
extern void func_0204f934(int);

struct s_020b71dc {
    char pad_00[0x10];
    int unk_10;
    int unk_14;
};

void func_020b71dc(struct s_020b71dc *p)
{
    int x = p->unk_10;
    data_020e54b4 = x;
    data_020e54bc = p->unk_14;
    if (x != -1) {
        func_0204f934(x);
    }
    if (data_020e54bc != -1) {
        func_0204f934(data_020e54bc);
    }
}
