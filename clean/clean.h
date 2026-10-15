/* Registering a Clean function (docs/runtime.md, "Clean").
 *
 * A Clean function has the same C signature as the matching source of the function it stands
 * for: the same parameters, in the same order and widths, and the same result. Registered with
 *
 *     CLEAN_AS(func_0209de24, Calendar_DaysInMonth)
 *
 * after its definition, it runs in place of that function's Native version in
 * `tools/run.py --native=... --clean`, and `tools/diffcheck.py --native --clean` checks it
 * against the ROM's code on generated states when it calls nothing. The tools read these lines;
 * the macro only makes the compiler check that the function exists.
 */
#ifndef CLEAN_CLEAN_H
#define CLEAN_CLEAN_H

#define CLEAN_AS(symbol, function)                                                                                   \
    static const void *const clean_as_##symbol __attribute__((unused)) = (const void *) (function);

#endif
