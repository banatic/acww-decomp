/* func_020b47fc @ 0x020b47fc, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b4930(char *s, unsigned int len, int at, int n);

void func_020b47fc(char *s, unsigned int len, int group)
{
    int i;
    int cnt;
    char *q;
    int reset;
    int fill;

    i = 0;
    cnt = 0;
    fill = 0;
    reset = 0;
    while (s[i] != 0) {

        if (s[i] >= '0' && s[i] <= '9') {
            cnt++;
            if (cnt >= group) {
                unsigned int j;
                cnt = reset;
                j = i + 2;
                if (j < len) {
                    q = s + j;
                    if (s[j] >= '0' && s[j] <= '9') {
                        func_020b4930(s, len, i, 2);
                        *q = ',';
                        s[j + 1] = (char) fill;
                    }
                }
            }
        }
        i += 2;
    }
}
