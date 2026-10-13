/* func_020b7130 @ 0x020b7130, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f6944;
extern unsigned char data_020e5538[];
extern unsigned int data_020e54f4[];
extern unsigned int data_020e54b8;
extern unsigned char data_020e54a8;
extern int data_020e5688[];
extern int data_020e54c0;
extern void func_0204f934(int);

void func_020b7130(void)
{
    unsigned char c;
    unsigned int w;

    c = data_020e5538[data_021f6944];
    w = data_020e54f4[c];
    func_0204f934(w);
    data_020e54b8 = w;
    data_020e54a8 = c;

    if (data_020e5688[data_021f6944] != -1) {
        func_0204f934(data_020e5688[data_021f6944]);
        data_020e54c0 = data_020e5688[data_021f6944];
    }
}
