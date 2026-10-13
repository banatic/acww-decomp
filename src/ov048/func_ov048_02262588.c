/* func_ov048_02262588 @ 0x02262588, 0x90 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_02015fb0(int, int, int, int, int, int);

void func_ov048_02262588(int a, unsigned long long d)
{
    unsigned long long q1 = d / 100000000ULL;
    unsigned long long p1 = q1 * 100000000ULL;
    unsigned long long rem = d - p1;
    unsigned long long q2 = rem / 10000ULL;

    func_02015fb0(a, (unsigned int) q1, 5, 4, 6, 0);
    func_02015fb0(a, (unsigned int) q2, 8, 4, 6, 0);

    {
        unsigned long long p2 = q2 * 10000ULL;
        unsigned int final = (unsigned int) ((d - p2) - p1);
        func_02015fb0(a, final, 9, 4, 6, 0);
    }
}
