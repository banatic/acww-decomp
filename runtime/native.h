/* Included first in every matching source compiled for the PC (Native; see docs/runtime.md).
 *
 * The sources are written for mwccarm. `__arm` and `__thumb`, which pick the instruction set
 * of a function, have no meaning on the PC and are dropped here, so the sources stay exactly
 * as they match.
 */
#ifndef RUNTIME_NATIVE_H
#define RUNTIME_NATIVE_H

#define __arm
#define __thumb

#endif
