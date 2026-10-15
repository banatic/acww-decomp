/* func_0205352c @ 0x0205352c, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02053c68(int);
extern int func_0204bc50(int, int);
extern int func_0204bc64(void *);
extern int func_0204bcdc(void *);
extern int func_02053c88(int);

unsigned char func_0205352c(unsigned short *a0)
{
    int flagA = 0;
    int argB = 0;
    int flagC = 0;
    int wanted = func_02053c68((int) a0);
    int count = 0;
    unsigned int i;
    int found;

    for (i = 0; i < 0x6e9; i++) {
        unsigned short local;

        local = func_0204bc50(i, argB);
        if (func_0204bcdc(&local)) {
            int x = func_0204bc64(&local);
            int y = func_0204bc64(a0);
            found = (x == y) ? 1 : flagA;
        } else {
            found = (local == *a0) ? 1 : flagC;
        }
        if (found) {
            return count;
        }
        if (wanted == func_02053c88(i)) {
            count++;
        }
    }
    return 0;
}
