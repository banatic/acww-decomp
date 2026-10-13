/* func_020b38dc @ 0x020b38dc, 0xd6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int n);

void func_020b38dc(unsigned char *arr)
{
    int idx;
    unsigned int j, i;
    unsigned int k, u, t;
    unsigned int limit, cnt, found;
    int base, val;
    int rnd1;
    unsigned int rnd2;

    rnd1 = func_020644cc(5);
    idx = 0;
    rnd2 = (unsigned int) func_020644cc(4);

    j = 0;
    i = j;
    while (i < 5) {
        if (i != (unsigned int) rnd1) {
            if (j == rnd2) {
                idx = (int) i;
                break;
            }
            j++;
        }
        i++;
    }

    for (i = 0; i < 4; i++) {
        arr[i] = 0xff;
    }

    k = 0;
    base = 5 * (rnd1 % 5);
    do {
        limit = func_020644cc(5 - k);
        cnt = 0;
        t = 0;
        while (t < 5) {
            found = 0;
            u = 0;
            val = (int) (t % 5) + base;
            while (u < 4) {
                unsigned char b = arr[u];
                if (b == val) {
                    found = 1;
                    break;
                }
                u++;
            }
            if (!found) {
                if (cnt == limit) {
                    arr[k] = val;
                    break;
                }
                cnt++;
            }
            t++;
        }
        k++;
    } while (k < 3);

    arr[3] = (unsigned char) (5 * (idx % 5) + (int) ((unsigned int) func_020644cc(5) % 5));
}
