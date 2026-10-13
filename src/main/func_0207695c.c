/* func_0207695c @ 0x0207695c, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern int data_021e5a2c[];

void func_020736bc(unsigned int, void *, int);
void func_020789f4(unsigned int *, unsigned int *, void *);
int func_0207cec0(void *, unsigned int);
int func_020807c0(int, unsigned int);
void func_02081a80(int, unsigned char);

void func_0207695c(void)
{
    unsigned int val = data_020ccf94;
    struct {
        unsigned char b0;
        unsigned char b1;
        unsigned char pad[2];
        unsigned int word1;
        unsigned int word2;
    } buf;
    int ret;

    func_020736bc(val, &buf, 1);
    func_020789f4(&buf.word1, &buf.word2, &buf);
    ret = func_0207cec0(data_021e5a2c, buf.word1);
    if (ret != 0) {
        int res;
        res = func_020807c0(ret, buf.word2);
        if (res != 0) {
            func_020736bc(val, &buf.b1, 1);
            func_02081a80(res, buf.b1);
        }
    }
}
