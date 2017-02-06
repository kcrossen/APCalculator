#ifndef BUTTONDEFINITIONS_H
#define BUTTONDEFINITIONS_H

#define pgmComplex \
(char*)"if(size(rpnstack)>=1) { \r\n" \
" if(isnum(rpnstack[0])) { \r\n" \
"  if(!isreal(rpnstack[0])) {tmp=pop(rpnstack);push(rpnstack,im(tmp));push(rpnstack,re(tmp)); \r\n" \
"  } else if(size(rpnstack)>=2) { \r\n" \
"   if (isreal(rpnstack[1])) push(rpnstack,(pop(rpnstack) + (pop(rpnstack) * 1i))); \r\n" \
"  } \r\n" \
" } \r\n" \
"} "

#define pgmComplexToReal \
(char*)"if(size(rpnstack)>=1) { \r\n" \
" if(isnum(rpnstack[0])) { \r\n" \
"  if(!isreal(rpnstack[0])) {tmp=pop(rpnstack);push(rpnstack,im(tmp));push(rpnstack,re(tmp));} \r\n" \
" } \r\n" \
"} "

#define pgmToPolar \
(char*)"if(size(rpnstack)>=2) { \r\n" \
" if(isnum(rpnstack[0])&&isnum(rpnstack[1])) { \r\n" \
"  if(isreal(rpnstack[0])&&isreal(rpnstack[1])) {insert(rpnstack, 1, pop(rpnstack)); push(rpnstack, polar(pop(rpnstack),fromangle*pop(rpnstack)));} \r\n" \
" } \r\n" \
"} "

#define pgmFromPolar \
(char*)"if(size(rpnstack)>=1) { \r\n" \
" if(isnum(rpnstack[0])) { \r\n" \
"  if(!isreal(rpnstack[0])) {push(rpnstack, rpnstack[0]); {tmp=pop(rpnstack);push(rpnstack,sqrt(im(tmp)^2+re(tmp)^2));}; insert(rpnstack, 1, pop(rpnstack)); push(rpnstack, toangle*arg(pop(rpnstack)));} \r\n" \
" } \r\n" \
"} "

#define pgmArg \
(char*)"if(size(rpnstack)>=1) { \r\n" \
" if(isnum(rpnstack[0])) push(rpnstack, toangle*arg(pop(rpnstack))); \r\n" \
"} "

#define pgmcAbs \
(char*)"if(size(rpnstack)>=1) { \r\n" \
" if(isnum(rpnstack[0])) { \r\n" \
"  if(!isreal(rpnstack[0])) {tmp=pop(rpnstack);push(rpnstack,sqrt(im(tmp)^2+re(tmp)^2));} \r\n" \
"  else push(rpnstack,abs(pop(rpnstack))); \r\n" \
"  } \r\n" \
" } \r\n" \
"} "

static const APCalcClass::ButtonDefinition RPNButtons_A[] =
{
    {1, 1, APCalcClass::btntypBase, (char*)"Hex", (char*)"Alt-click Binary", (char*)"0x", APCalcClass::NoParameter},
    {1, 2, APCalcClass::btntypChar, (char*)"A", (char*)"", (char*)"A", APCalcClass::NoParameter},
    {1, 3, APCalcClass::btntypChar, (char*)"B", (char*)"", (char*)"B", APCalcClass::NoParameter},
    {1, 4, APCalcClass::btntypChar, (char*)"C", (char*)"", (char*)"C", APCalcClass::NoParameter},
    {1, 5, APCalcClass::btntypChar, (char*)"D", (char*)"", (char*)"D", APCalcClass::NoParameter},
    {1, 6, APCalcClass::btntypChar, (char*)"E", (char*)"", (char*)"E", APCalcClass::NoParameter},
    {1, 7, APCalcClass::btntypChar, (char*)"F", (char*)"", (char*)"F", APCalcClass::NoParameter},

    {2, 1, APCalcClass::btntypProgram, (char*)"asin", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, asind(pop(rpnstack)));", APCalcClass::NoParameter},
    {2, 2, APCalcClass::btntypProgram, (char*)"acos", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, acosd(pop(rpnstack)));", APCalcClass::NoParameter},
    {2, 3, APCalcClass::btntypProgram, (char*)"atan", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, atand(pop(rpnstack)));", APCalcClass::NoParameter},

    {3, 1, APCalcClass::btntypProgram, (char*)"sin", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, sind(pop(rpnstack)));", APCalcClass::NoParameter},
    {3, 2, APCalcClass::btntypProgram, (char*)"cos", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, cosd(pop(rpnstack)));", APCalcClass::NoParameter},
    {3, 3, APCalcClass::btntypProgram, (char*)"tan", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, tand(pop(rpnstack)));", APCalcClass::NoParameter},

    {4, 1, APCalcClass::btntypProgram, (char*)"e^x", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, (e^pop(rpnstack)));", APCalcClass::NoParameter},
    {4, 2, APCalcClass::btntypProgram, (char*)"10^x", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, (10^pop(rpnstack)));", APCalcClass::NoParameter},
    {4, 3, APCalcClass::btntypProgram, (char*)"y^x", (char*)"", (char*)"if(size(rpnstack)>=2) {insert(rpnstack, 1, pop(rpnstack)); push(rpnstack, (pop(rpnstack)^pop(rpnstack)));}", APCalcClass::NoParameter},

    {5, 1, APCalcClass::btntypProgram, (char*)"ln", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, ln(pop(rpnstack)));", APCalcClass::NoParameter},
    {5, 2, APCalcClass::btntypProgram, (char*)"log", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, log(pop(rpnstack)));", APCalcClass::NoParameter},
    {5, 3, APCalcClass::btntypProgram, QString("x")+QString(QChar(0x221a))+QString("y"), (char*)"", (char*)"if(size(rpnstack)>=2) {insert(rpnstack, 1, pop(rpnstack)); push(rpnstack, (pop(rpnstack)^inverse(pop(rpnstack))));}", APCalcClass::NoParameter},

    {6, 1, APCalcClass::btntypProgram, QString("x")+QString(QChar(0xb2)), (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)^2));", APCalcClass::NoParameter},
    {6, 2, APCalcClass::btntypProgram, QString(QChar(0x221a))+QString("x"), (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, sqrt(pop(rpnstack)));", APCalcClass::NoParameter},
    {6, 3, APCalcClass::btntypProgram, (char*)"1/x", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, inverse(pop(rpnstack)));", APCalcClass::NoParameter},

    {7, 1, APCalcClass::btntypShift, (char*)"SHFT", (char*)"", (char*)"", APCalcClass::NoParameter},
    {7, 2, APCalcClass::btntypSTO, (char*)"STO", (char*)"", (char*)"", APCalcClass::NoParameter}, /* btntypSTO, btntypNone */
    {7, 3, APCalcClass::btntypRCL, (char*)"RCL", (char*)"", (char*)"", APCalcClass::NoParameter}, /* btntypRCL, btntypNone */

    {2, 4, APCalcClass::btntypDelete, (char*)"Del", (char*)"", (char*)"", APCalcClass::NoParameter},
    {2, 5, APCalcClass::btntypUndo, (char*)"Undo", (char*)"", (char*)"", APCalcClass::NoParameter},
    {2, 6, APCalcClass::btntypRedo, (char*)"Redo", (char*)"", (char*)"", APCalcClass::NoParameter},
    {2, 7, APCalcClass::btntypSwap, (char*)"Swap", (char*)"", (char*)"if(size(rpnstack)>=2) insert(rpnstack, 1, pop(rpnstack));", APCalcClass::NoParameter},

    // {2, 5, btntypInvSign, (char*)"+/-", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, -pop(rpnstack));", APCalcClass::NoParameter},

    {3, 4, APCalcClass::btntypChar, (char*)"-", (char*)"", (char*)"-", APCalcClass::NoParameter},
    {3, 5, APCalcClass::btntypChar, (char*)"Ex", (char*)"", (char*)"E", APCalcClass::NoParameter},
    {3, 6, APCalcClass::btntypChar, (char*)"i", (char*)"", (char*)"i", APCalcClass::NoParameter},
    {3, 7, APCalcClass::btntypPop, (char*)"Drop", (char*)"", (char*)"", APCalcClass::NoParameter},

    {4, 4, APCalcClass::btntypChar, (char*)"7", (char*)"", (char*)"7", APCalcClass::NoParameter},
    {4, 5, APCalcClass::btntypChar, (char*)"8", (char*)"", (char*)"8", APCalcClass::NoParameter},
    {4, 6, APCalcClass::btntypChar, (char*)"9", (char*)"", (char*)"9", APCalcClass::NoParameter},
    {4, 7, APCalcClass::btntypDivide, QString(QChar(0xf7)), (char*)"", (char*)"if(size(rpnstack)>=2) push(rpnstack, (inverse(pop(rpnstack))*pop(rpnstack)));", APCalcClass::NoParameter},

    {5, 4, APCalcClass::btntypChar, (char*)"4", (char*)"", (char*)"4", APCalcClass::NoParameter},
    {5, 5, APCalcClass::btntypChar, (char*)"5", (char*)"", (char*)"5", APCalcClass::NoParameter},
    {5, 6, APCalcClass::btntypChar, (char*)"6", (char*)"", (char*)"6", APCalcClass::NoParameter},
    {5, 7, APCalcClass::btntypMultiply, (char*)"X", (char*)"", (char*)"if(size(rpnstack)>=2) push(rpnstack, (pop(rpnstack)*pop(rpnstack)));", APCalcClass::NoParameter},

    {6, 4, APCalcClass::btntypChar, (char*)"1", (char*)"", (char*)"1", APCalcClass::NoParameter},
    {6, 5, APCalcClass::btntypChar, (char*)"2", (char*)"", (char*)"2", APCalcClass::NoParameter},
    {6, 6, APCalcClass::btntypChar, (char*)"3", (char*)"", (char*)"3", APCalcClass::NoParameter},
    {6, 7, APCalcClass::btntypSubtract, (char*)"-", (char*)"", (char*)"if(size(rpnstack)>=2) push(rpnstack, (-pop(rpnstack)+pop(rpnstack)));", APCalcClass::NoParameter},

    {7, 4, APCalcClass::btntypChar, (char*)"0", (char*)"", (char*)"0", APCalcClass::NoParameter},
    {7, 5, APCalcClass::btntypRadixMark, (char*)".", (char*)"", (char*)".", APCalcClass::NoParameter},
    {7, 6, APCalcClass::btntypPush, (char*)"ENT", (char*)"", (char*)"push(rpnstack, @value@)", APCalcClass::NoParameter},
    {7, 7, APCalcClass::btntypAdd, (char*)"+", (char*)"", (char*)"if(size(rpnstack)>=2) push(rpnstack, (pop(rpnstack)+pop(rpnstack)));", APCalcClass::NoParameter},

    /* must be last button of set */ {-1, -1, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter} /* must be last button of set */
};

static const APCalcClass::ButtonDefinition RPNButtons_B[] =
{
    {1, 1, APCalcClass::btntypProgram, (char*)"asec", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, asecd(pop(rpnstack)));", APCalcClass::NoParameter},
    {1, 2, APCalcClass::btntypProgram, (char*)"acsc", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, acscd(pop(rpnstack)));", APCalcClass::NoParameter},
    {1, 3, APCalcClass::btntypProgram, (char*)"acot", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, acotd(pop(rpnstack)));", APCalcClass::NoParameter},
    {1, 4, APCalcClass::btntypProgram, QString(QChar(0x21E8))+QString(QChar(0x2009))+QString("deg"), (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, (180*pop(rpnstack)/pi));", APCalcClass::NoParameter},

    {2, 1, APCalcClass::btntypProgram, (char*)"sec", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, secd(pop(rpnstack)));", APCalcClass::NoParameter},
    {2, 2, APCalcClass::btntypProgram, (char*)"csc", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, cscd(pop(rpnstack)));", APCalcClass::NoParameter},
    {2, 3, APCalcClass::btntypProgram, (char*)"cot", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, cotd(pop(rpnstack)));", APCalcClass::NoParameter},
    {2, 4, APCalcClass::btntypProgram, QString(QChar(0x21E8))+QString(QChar(0x2009))+QString("rad"), (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, (pi*pop(rpnstack)/180));", APCalcClass::NoParameter},
// 0x21D2 // 0x21E8
    {3, 1, APCalcClass::btntypProgram, (char*)"re", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, re(pop(rpnstack)));", APCalcClass::NoParameter},
    {3, 2, APCalcClass::btntypProgram, (char*)"im", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, im(pop(rpnstack)));", APCalcClass::NoParameter},
    {3, 3, APCalcClass::btntypProgram, QString("r")+QString(QChar(0x2009))+QString(QChar(0x21E8))+QString(QChar(0x2009))+QString("c"), (char*)"", (char*)"if(size(rpnstack)>=2) push(rpnstack, ((pop(rpnstack)+(pop(rpnstack)*1i))));", APCalcClass::NoParameter},
    {3, 4, APCalcClass::btntypProgram, QString("c")+QString(QChar(0x2009))+QString(QChar(0x21E8))+QString(QChar(0x2009))+QString("r"), (char*)"", pgmComplexToReal, APCalcClass::NoParameter},

    {4, 1, APCalcClass::btntypProgram, (char*)"cArg", (char*)"", pgmArg, APCalcClass::NoParameter},
    {4, 2, APCalcClass::btntypProgram, (char*)"cAbs", (char*)"", pgmcAbs, APCalcClass::NoParameter},
    {4, 3, APCalcClass::btntypProgram, (char*)"Polr", (char*)"", pgmToPolar, APCalcClass::NoParameter},
    {4, 4, APCalcClass::btntypProgram, (char*)"cPolr", (char*)"", pgmFromPolar, APCalcClass::NoParameter},

    {5, 1, APCalcClass::btntypProgram, (char*)"bAnd", (char*)"", (char*)"if(size(rpnstack)>=2) push(rpnstack, (pop(rpnstack)&pop(rpnstack)));", APCalcClass::NoParameter},
    {5, 2, APCalcClass::btntypProgram, (char*)"bOr", (char*)"", (char*)"if(size(rpnstack)>=2) push(rpnstack, (pop(rpnstack)|pop(rpnstack)))", APCalcClass::NoParameter},
    {5, 3, APCalcClass::btntypProgram, (char*)"bXor", (char*)"", (char*)"if(size(rpnstack)>=2) push(rpnstack, (xor(pop(rpnstack),pop(rpnstack))));", APCalcClass::NoParameter},
    {5, 4, APCalcClass::btntypProgram, (char*)"bNot", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, (xor(pop(rpnstack),0xFFFFFFFF)));", APCalcClass::NoParameter},

    // {6, 1, APCalcClass::btntypProgram, (char*)"sign", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, sgn(pop(rpnstack)));", APCalcClass::NoParameter},
    {6, 1, APCalcClass::btntypChangeSign, (char*)"+/-", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, -pop(rpnstack));", APCalcClass::NoParameter},
    {6, 2, APCalcClass::btntypProgram, (char*)"abs", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, abs(pop(rpnstack)));", APCalcClass::NoParameter},
    {6, 3, APCalcClass::btntypProgram, (char*)"ip", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, int(pop(rpnstack)));", APCalcClass::NoParameter},
    {6, 4, APCalcClass::btntypProgram, (char*)"fp", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, frac(pop(rpnstack)));", APCalcClass::NoParameter},

    {7, 1, APCalcClass::btntypShift, (char*)"SHFT", (char*)"", (char*)"", APCalcClass::NoParameter},
    {7, 2, APCalcClass::btntypProgram, (char*)"Pi", (char*)"", (char*)"push(rpnstack, pi)", APCalcClass::NoParameter},
    {7, 3, APCalcClass::btntypProgram, (char*)"e", (char*)"", (char*)"push(rpnstack, e)", APCalcClass::NoParameter},
    {7, 4, APCalcClass::btntypProgram, (char*)"i", (char*)"", (char*)"push(rpnstack, 1i)", APCalcClass::NoParameter},

    {1, 5, APCalcClass::btntypProgram, (char*)"asinh", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, asinhd(pop(rpnstack)));", APCalcClass::NoParameter},
    {1, 6, APCalcClass::btntypProgram, (char*)"acosh", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, acoshd(pop(rpnstack)));", APCalcClass::NoParameter},
    {1, 7, APCalcClass::btntypProgram, (char*)"atanh", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, atanhd(pop(rpnstack)));", APCalcClass::NoParameter},

    {2, 5, APCalcClass::btntypProgram, (char*)"sinh", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, sinhd(pop(rpnstack)));", APCalcClass::NoParameter},
    {2, 6, APCalcClass::btntypProgram, (char*)"cosh", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, coshd(pop(rpnstack)));", APCalcClass::NoParameter},
    {2, 7, APCalcClass::btntypProgram, (char*)"tanh", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, tanhd(pop(rpnstack)));", APCalcClass::NoParameter},

    {3, 5, APCalcClass::btntypProgram, (char*)"y // x", (char*)"", (char*)"if(size(rpnstack)>=2) {insert(rpnstack, 1, pop(rpnstack)); push(rpnstack, (pop(rpnstack) // pop(rpnstack)));}", APCalcClass::NoParameter},
    {3, 6, APCalcClass::btntypProgram, (char*)"y % x", (char*)"", (char*)"if(size(rpnstack)>=2) {insert(rpnstack, 1, pop(rpnstack)); push(rpnstack, (pop(rpnstack) % pop(rpnstack)));}", APCalcClass::NoParameter},
    {3, 7, APCalcClass::btntypProgram, (char*)"atan2", (char*)"", (char*)"if(size(rpnstack)>=2) {insert(rpnstack, 1, pop(rpnstack)); push(rpnstack, atan2(pop(rpnstack), pop(rpnstack)));}", APCalcClass::NoParameter},

    {4, 5, APCalcClass::btntypProgram, (char*)"Conj", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, conj(pop(rpnstack)));", APCalcClass::NoParameter},
    {4, 6, APCalcClass::btntypProgram, (char*)"log2", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, (log(pop(rpnstack))/log(2)));", APCalcClass::NoParameter},
    {4, 7, APCalcClass::btntypProgram, (char*)"logx", (char*)"", (char*)"if(size(rpnstack)>=2) push(rpnstack, (inverse(log(pop(rpnstack)))*log(pop(rpnstack))));", APCalcClass::NoParameter},

    {5, 5, APCalcClass::btntypProgram, (char*)"seed", (char*)"", (char*)"if(size(rpnstack)>=1) srand(pop(rpnstack));", APCalcClass::NoParameter},
    {5, 6, APCalcClass::btntypProgram, (char*)"rand", (char*)"", (char*)"push(rpnstack, (rand()/2^64))", APCalcClass::NoParameter},
    {5, 7, APCalcClass::btntypProgram, (char*)"nrnd", (char*)"", (char*)"push(rpnstack, nrand())", APCalcClass::NoParameter},

    {6, 5, APCalcClass::btntypProgram, (char*)"fact", (char*)"", (char*)"if(size(rpnstack)>=1) push(rpnstack, fact(pop(rpnstack)));", APCalcClass::NoParameter},
    {6, 6, APCalcClass::btntypProgram, (char*)"comb", (char*)"", (char*)"if(size(rpnstack)>=2) {insert(rpnstack, 1, pop(rpnstack)); push(rpnstack, comb(pop(rpnstack), pop(rpnstack)));}", APCalcClass::NoParameter},
    {6, 7, APCalcClass::btntypProgram, (char*)"perm", (char*)"", (char*)"if(size(rpnstack)>=2) {insert(rpnstack, 1, pop(rpnstack)); push(rpnstack, perm(pop(rpnstack), pop(rpnstack)));}", APCalcClass::NoParameter},

    {7, 5, APCalcClass::btntypProgram, (char*)"%", (char*)"", (char*)"if(size(rpnstack)>=2) push(rpnstack, ((pop(rpnstack)*rpnstack[0])/100));", APCalcClass::NoParameter},
    {7, 6, APCalcClass::btntypProgram, (char*)"%ch", (char*)"", (char*)"if(size(rpnstack)>=2) push(rpnstack, (((pop(rpnstack)-rpnstack[0])/rpnstack[0])*100));", APCalcClass::NoParameter},
    {7, 7, APCalcClass::btntypProgram, (char*)"%t", (char*)"", (char*)"if(size(rpnstack)>=2) {insert(rpnstack, 1, pop(rpnstack)); push(rpnstack, (100*pop(rpnstack)/pop(rpnstack)));}", APCalcClass::NoParameter},

    /* must be last button of set */ {-1, -1, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter} /* must be last button of set */
};

static const APCalcClass::ButtonDefinition AlgebraicButtons_A[] =
{
    {1, 1, APCalcClass::btntypBase, (char*)"Hex", (char*)"Alt-click Binary", (char*)"0x", APCalcClass::NoParameter},
    {1, 2, APCalcClass::btntypChar, (char*)"A", (char*)"", (char*)"A", APCalcClass::NoParameter},
    {1, 3, APCalcClass::btntypChar, (char*)"B", (char*)"", (char*)"B", APCalcClass::NoParameter},
    {1, 4, APCalcClass::btntypChar, (char*)"C", (char*)"", (char*)"C", APCalcClass::NoParameter},
    {1, 5, APCalcClass::btntypChar, (char*)"D", (char*)"", (char*)"D", APCalcClass::NoParameter},
    {1, 6, APCalcClass::btntypChar, (char*)"E", (char*)"", (char*)"E", APCalcClass::NoParameter},
    {1, 7, APCalcClass::btntypChar, (char*)"F", (char*)"", (char*)"F", APCalcClass::NoParameter},

    {2, 1, APCalcClass::btntypFunction, (char*)"asin", (char*)"", (char*)"asin(?)", APCalcClass::FindParameter},
    {2, 2, APCalcClass::btntypFunction, (char*)"acos", (char*)"", (char*)"acos(?)", APCalcClass::FindParameter},
    {2, 3, APCalcClass::btntypFunction, (char*)"atan", (char*)"", (char*)"atan(?)", APCalcClass::FindParameter},
    {2, 4, APCalcClass::btntypDelete, (char*)"Del", (char*)"", (char*)"", APCalcClass::NoParameter},
    {2, 5, APCalcClass::btntypCursorLeft, QChar(0x25c4), (char*)"Cursor Left", (char*)"", APCalcClass::NoParameter},
    {2, 6, APCalcClass::btntypCursorRight, QChar(0x25ba), (char*)"Cursor Right", (char*)"", APCalcClass::NoParameter},
    {2, 7, APCalcClass::btntypAns, (char*)"Ans", (char*)"Alt-click to ClipBoard", (char*)"", APCalcClass::NoParameter}, /* btntypRCL, btntypNone */

    {3, 1, APCalcClass::btntypFunction, (char*)"sin", (char*)"", (char*)"sin(?)", APCalcClass::FindParameter},
    {3, 2, APCalcClass::btntypFunction, (char*)"cos", (char*)"", (char*)"cos(?)", APCalcClass::FindParameter},
    {3, 3, APCalcClass::btntypFunction, (char*)"tan", (char*)"", (char*)"tan(?)", APCalcClass::FindParameter},
    {3, 4, APCalcClass::btntypChar, (char*)"-", (char*)"", (char*)"-", APCalcClass::NoParameter},
    {3, 5, APCalcClass::btntypChar, (char*)"Ex", (char*)"", (char*)"E", APCalcClass::NoParameter},
    {3, 6, APCalcClass::btntypChar, (char*)"i", (char*)"", (char*)"i", APCalcClass::NoParameter},
    {3, 7, APCalcClass::btntypParens, (char*)"( )", (char*)"", (char*)"(?)", APCalcClass::FindParameter},

    {4, 1, APCalcClass::btntypFunction, (char*)"ln", (char*)"", (char*)"ln(?)", APCalcClass::FindParameter},
    {4, 2, APCalcClass::btntypFunction, (char*)"log", (char*)"", (char*)"log(?)", APCalcClass::FindParameter},
    {4, 3, APCalcClass::btntypFocusParagraph, QChar(0x25b2), (char*)"Focus Equation", (char*)"", APCalcClass::NoParameter},
    {4, 4, APCalcClass::btntypChar, (char*)"7", (char*)"", (char*)"7", APCalcClass::NoParameter},
    {4, 5, APCalcClass::btntypChar, (char*)"8", (char*)"", (char*)"8", APCalcClass::NoParameter},
    {4, 6, APCalcClass::btntypChar, (char*)"9", (char*)"", (char*)"9", APCalcClass::NoParameter},
    {4, 7, APCalcClass::btntypOperator, (char*)"\xf7", (char*)"", (char*)"/", APCalcClass::NoParameter},

    {5, 1, APCalcClass::btntypOperator, (char*)"^", (char*)"", (char*)"^", APCalcClass::NoParameter},
    {5, 2, APCalcClass::btntypOperator, QChar(0x221a), (char*)"", (char*)"^(1/?)", APCalcClass::FindParameter},
    {5, 3, APCalcClass::btntypFocusLine, QChar(0x25bc), (char*)"Focus Numeric", (char*)"", APCalcClass::NoParameter},
    {5, 4, APCalcClass::btntypChar, (char*)"4", (char*)"", (char*)"4", APCalcClass::NoParameter},
    {5, 5, APCalcClass::btntypChar, (char*)"5", (char*)"", (char*)"5", APCalcClass::NoParameter},
    {5, 6, APCalcClass::btntypChar, (char*)"6", (char*)"", (char*)"6", APCalcClass::NoParameter},
    {5, 7, APCalcClass::btntypOperator, (char*)"X", (char*)"", (char*)"*", APCalcClass::NoParameter},

    {6, 1, APCalcClass::btntypClear, (char*)"Clear", (char*)"", (char*)"", APCalcClass::NoParameter}, /* btntypSTO, btntypNone */
    {6, 2, APCalcClass::btntypPrevEval, (char*)"Prev", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 3, APCalcClass::btntypNextEval, (char*)"Next", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 4, APCalcClass::btntypChar, (char*)"1", (char*)"", (char*)"1", APCalcClass::NoParameter},
    {6, 5, APCalcClass::btntypChar, (char*)"2", (char*)"", (char*)"2", APCalcClass::NoParameter},
    {6, 6, APCalcClass::btntypChar, (char*)"3", (char*)"", (char*)"3", APCalcClass::NoParameter},
    {6, 7, APCalcClass::btntypOperator, QChar(0x2212), (char*)"", (char*)"-", APCalcClass::NoParameter},

    {7, 1, APCalcClass::btntypTrigShift, (char*)"Trig", (char*)"", (char*)"", APCalcClass::NoParameter},
    {7, 2, APCalcClass::btntypMathShift, (char*)"Math", (char*)"", (char*)"", APCalcClass::NoParameter},
    {7, 3, APCalcClass::btntypEval, (char*)"Eval", (char*)"", (char*)"", APCalcClass::NoParameter},
    {7, 4, APCalcClass::btntypChar, (char*)"0", (char*)"", (char*)"0", APCalcClass::NoParameter},
    {7, 5, APCalcClass::btntypRadixMark, (char*)".", (char*)"", (char*)".", APCalcClass::NoParameter},
    {7, 6, APCalcClass::btntypEnter, (char*)"ENT", (char*)"", (char*)"push(rpnstack, @value@)", APCalcClass::NoParameter},
    {7, 7, APCalcClass::btntypOperator, (char*)"+", (char*)"", (char*)"+", APCalcClass::NoParameter},

    /* must be last button of set */ {-1, -1, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter} /* must be last button of set */
};

static const APCalcClass::ButtonDefinition AlgebraicButtons_B[] =
{
    {1, 1, APCalcClass::btntypFunction, (char*)"sin", (char*)"", (char*)"sin(?)", APCalcClass::FindParameter},
    {1, 2, APCalcClass::btntypFunction, (char*)"cos", (char*)"", (char*)"cos(?)", APCalcClass::FindParameter},
    {1, 3, APCalcClass::btntypFunction, (char*)"tan", (char*)"", (char*)"tan(?)", APCalcClass::FindParameter},
    {1, 4, APCalcClass::btntypFunction, (char*)"sec", (char*)"", (char*)"sec(?)", APCalcClass::FindParameter},
    {1, 5, APCalcClass::btntypFunction, (char*)"csc", (char*)"", (char*)"csc(?)", APCalcClass::FindParameter},
    {1, 6, APCalcClass::btntypFunction, (char*)"cot", (char*)"", (char*)"cot(?)", APCalcClass::FindParameter},

    {2, 1, APCalcClass::btntypFunction, (char*)"asin", (char*)"", (char*)"asin(?)", APCalcClass::FindParameter},
    {2, 2, APCalcClass::btntypFunction, (char*)"acos", (char*)"", (char*)"acos(?)", APCalcClass::FindParameter},
    {2, 3, APCalcClass::btntypFunction, (char*)"atan", (char*)"", (char*)"atan(?)", APCalcClass::FindParameter},
    {2, 4, APCalcClass::btntypFunction, (char*)"asec", (char*)"", (char*)"asec(?)", APCalcClass::FindParameter},
    {2, 5, APCalcClass::btntypFunction, (char*)"acsc", (char*)"", (char*)"acsc(?)", APCalcClass::FindParameter},
    {2, 6, APCalcClass::btntypFunction, (char*)"acot", (char*)"", (char*)"acot(?)", APCalcClass::FindParameter},

    {3, 1, APCalcClass::btntypFunction, (char*)"sinh", (char*)"", (char*)"sinh(?)", APCalcClass::FindParameter},
    {3, 2, APCalcClass::btntypFunction, (char*)"cosh", (char*)"", (char*)"cosh(?)", APCalcClass::FindParameter},
    {3, 3, APCalcClass::btntypFunction, (char*)"tanh", (char*)"", (char*)"tanh(?)", APCalcClass::FindParameter},
    {3, 4, APCalcClass::btntypFunction, (char*)"sech", (char*)"", (char*)"sech(?)", APCalcClass::FindParameter},
    {3, 5, APCalcClass::btntypFunction, (char*)"csch", (char*)"", (char*)"csch(?)", APCalcClass::FindParameter},
    {3, 6, APCalcClass::btntypFunction, (char*)"coth", (char*)"", (char*)"coth(?)", APCalcClass::FindParameter},

    {4, 1, APCalcClass::btntypFunction, (char*)"asinh", (char*)"", (char*)"asinh(?)", APCalcClass::FindParameter},
    {4, 2, APCalcClass::btntypFunction, (char*)"acosh", (char*)"", (char*)"acosh(?)", APCalcClass::FindParameter},
    {4, 3, APCalcClass::btntypFunction, (char*)"atanh", (char*)"", (char*)"atanh(?)", APCalcClass::FindParameter},
    {4, 4, APCalcClass::btntypFunction, (char*)"asech", (char*)"", (char*)"asech(?)", APCalcClass::FindParameter},
    {4, 5, APCalcClass::btntypFunction, (char*)"acsch", (char*)"", (char*)"acsch(?)", APCalcClass::FindParameter},
    {4, 6, APCalcClass::btntypFunction, (char*)"acoth", (char*)"", (char*)"acoth(?)", APCalcClass::FindParameter},

    {5, 1, APCalcClass::btntypFunction, (char*)"re", (char*)"", (char*)"re(?)", APCalcClass::FindParameter},
    {5, 2, APCalcClass::btntypFunction, (char*)"im", (char*)"", (char*)"im(?)", APCalcClass::FindParameter},
    {5, 3, APCalcClass::btntypFunction, (char*)"arg", (char*)"", (char*)"arg(?)", APCalcClass::FindParameter},
    {5, 4, APCalcClass::btntypFunction, (char*)"conj", (char*)"", (char*)"conj(?)", APCalcClass::FindParameter},
    {5, 5, APCalcClass::btntypFunction, (char*)"polar", (char*)"", (char*)"polar(?r,a)", APCalcClass::FindParameter},
    {5, 6, APCalcClass::btntypFunction, (char*)"atan2", (char*)"", (char*)"atan2(?y,x)", APCalcClass::FindParameter},

    {6, 1, APCalcClass::btntypFunction, (char*)"pi", (char*)"", (char*)"pi", APCalcClass::NoParameter},
    {6, 2, APCalcClass::btntypFunction, (char*)"\xbb" "deg", (char*)"", (char*)"*(180/pi)", APCalcClass::NoParameter},
    {6, 3, APCalcClass::btntypFunction, (char*)"\xbb" "rad", (char*)"", (char*)"*(pi/180)", APCalcClass::NoParameter},
    {6, 4, APCalcClass::btntypFunction, (char*)"ln", (char*)"", (char*)"ln(?)", APCalcClass::FindParameter},
    {6, 5, APCalcClass::btntypFunction, (char*)"log", (char*)"", (char*)"log(?)", APCalcClass::FindParameter},
    {6, 6, APCalcClass::btntypFunction, (char*)"^", (char*)"", (char*)"^", APCalcClass::NoParameter},

    {7, 1, APCalcClass::btntypShift, (char*)"Home", (char*)"", (char*)"", APCalcClass::NoParameter},
    {7, 2, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter}, /* btntypSTO, btntypNone */
    {7, 3, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter}, /* btntypRCL, btntypNone */
    {7, 4, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter},
    {7, 5, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter},
    {7, 6, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter},

    /* must be last button of set */ {-1, -1, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter} /* must be last button of set */
};

static const APCalcClass::ButtonDefinition AlgebraicButtons_C[] =
{
    {1, 1, APCalcClass::btntypFunction, (char*)"ln", (char*)"", (char*)"ln(?)", APCalcClass::FindParameter},
    {1, 2, APCalcClass::btntypFunction, (char*)"log", (char*)"", (char*)"log(?)", APCalcClass::FindParameter},
    {1, 3, APCalcClass::btntypFunction, (char*)"log2", (char*)"", (char*)"(1/log(2))*log(?)", APCalcClass::FindParameter},
    {1, 4, APCalcClass::btntypFunction, (char*)"logx", (char*)"", (char*)"(1/log(x))*log(?)", APCalcClass::FindParameter},
    {1, 5, APCalcClass::btntypFunction, (char*)"pi", (char*)"", (char*)" pi", APCalcClass::NoParameter},
    {1, 6, APCalcClass::btntypFunction, (char*)"i", (char*)"", (char*)" 1i", APCalcClass::NoParameter},

    {2, 1, APCalcClass::btntypFunction, (char*)"e", (char*)"", (char*)"e", APCalcClass::NoParameter},
    {2, 2, APCalcClass::btntypFunction, (char*)"e^", (char*)"", (char*)"e^", APCalcClass::NoParameter},
    {2, 3, APCalcClass::btntypFunction, (char*)"10^", (char*)"", (char*)"10^", APCalcClass::NoParameter},
    {2, 4, APCalcClass::btntypFunction, (char*)"^2", (char*)"", (char*)"^2", APCalcClass::NoParameter},
    {2, 5, APCalcClass::btntypFunction, (char*)"^", (char*)"", (char*)"^", APCalcClass::NoParameter},
    {2, 6, APCalcClass::btntypFunction, (char*)"1/x", (char*)"", (char*)"(1/?)", APCalcClass::FindParameter},

    {3, 1, APCalcClass::btntypFunction, (char*)"gcd", (char*)"", (char*)"gcd(?a,b,c,...)", APCalcClass::FindParameter},
    {3, 2, APCalcClass::btntypFunction, (char*)"lcm", (char*)"", (char*)"lcm(?a,b,c,...)", APCalcClass::FindParameter},
    {3, 3, APCalcClass::btntypFunction, (char*)"mod", (char*)"", (char*)"%", APCalcClass::NoParameter},
    {3, 4, APCalcClass::btntypFunction, (char*)"intDiv", (char*)"", (char*)"//", APCalcClass::NoParameter},
    {3, 5, APCalcClass::btntypFunction, (char*)"round", (char*)"", (char*)"round(?x [,plcs])", APCalcClass::FindParameter},
    {3, 6, APCalcClass::btntypFunction, (char*)"trunc", (char*)"", (char*)"trunc(?x [,plcs])", APCalcClass::FindParameter},

    {4, 1, APCalcClass::btntypFunction, (char*)"sign", (char*)"", (char*)"sgn(?)", APCalcClass::FindParameter},
    {4, 2, APCalcClass::btntypFunction, (char*)"abs", (char*)"", (char*)"abs(?)", APCalcClass::FindParameter},
    {4, 3, APCalcClass::btntypFunction, (char*)"ip", (char*)"", (char*)"int(?)", APCalcClass::FindParameter},
    {4, 4, APCalcClass::btntypFunction, (char*)"fp", (char*)"", (char*)"frac(?)", APCalcClass::FindParameter},
    {4, 5, APCalcClass::btntypFunction, (char*)"ceil", (char*)"", (char*)"ceil(?)", APCalcClass::FindParameter},
    {4, 6, APCalcClass::btntypFunction, (char*)"floor", (char*)"", (char*)"floor(?)", APCalcClass::FindParameter},

    {5, 1, APCalcClass::btntypFunction, (char*)"seed", (char*)"", (char*)"srand()", APCalcClass::NoParameter},
    {5, 2, APCalcClass::btntypFunction, (char*)"rand", (char*)"", (char*)"(rand()/2^64))", APCalcClass::NoParameter},
    {5, 3, APCalcClass::btntypFunction, (char*)"nrand", (char*)"", (char*)"nrnd()", APCalcClass::NoParameter},
    {5, 4, APCalcClass::btntypNone, (char*)"digit", (char*)"", (char*)"digit(?x, n [, b])", APCalcClass::FindParameter},
    {5, 5, APCalcClass::btntypNone, (char*)"num", (char*)"", (char*)"num(?)", APCalcClass::FindParameter},
    {5, 6, APCalcClass::btntypNone, (char*)"den", (char*)"", (char*)"den(?)", APCalcClass::FindParameter},

    {6, 1, APCalcClass::btntypFunction, (char*)"fib", (char*)"", (char*)"fib(?)", APCalcClass::FindParameter},
    {6, 2, APCalcClass::btntypFunction, (char*)"fact", (char*)"", (char*)"fact(?)", APCalcClass::FindParameter},
    {6, 3, APCalcClass::btntypFunction, (char*)"comb", (char*)"", (char*)"comb(?x, y)", APCalcClass::FindParameter},
    {6, 4, APCalcClass::btntypFunction, (char*)"perm", (char*)"", (char*)"perm(?x, y)", APCalcClass::FindParameter},
    {6, 5, APCalcClass::btntypNone, (char*)"min", (char*)"", (char*)"min(?x1,x2,...)", APCalcClass::FindParameter},
    {6, 6, APCalcClass::btntypNone, (char*)"max", (char*)"", (char*)"max(?x1,x2,...)", APCalcClass::FindParameter},

    {7, 1, APCalcClass::btntypShift, (char*)"Home", (char*)"", (char*)"", APCalcClass::NoParameter},
    {7, 2, APCalcClass::btntypFunction, (char*)"ilog", (char*)"", (char*)"ilog(?x,b)", APCalcClass::FindParameter},
    {7, 3, APCalcClass::btntypFunction, (char*)"ilog10", (char*)"", (char*)"ilog10(?)", APCalcClass::FindParameter},
    {7, 4, APCalcClass::btntypFunction, (char*)"ilog2", (char*)"", (char*)"ilog2(?)", APCalcClass::FindParameter},
    {7, 5, APCalcClass::btntypFunction, (char*)"isqrt", (char*)"", (char*)"isqrt(?)", APCalcClass::FindParameter},
    {7, 6, APCalcClass::btntypFunction, (char*)"iroot", (char*)"", (char*)"iroot(?x,n)", APCalcClass::FindParameter},

    /* must be last button of set */ {-1, -1, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter} /* must be last button of set */
};

static const APCalcClass::ButtonDefinition ProgramButtons_A[] =
{
    {1, 1, APCalcClass::btntypProgram, (char*)"define", (char*)"", (char*)"define fname([param_1 [= default_1], ...]) { [statement_1 ... ] }", APCalcClass::NoParameter},
    {1, 2, APCalcClass::btntypProgramImmediate, (char*)"Confg", (char*)"", (char*)"show config", APCalcClass::NoParameter},
    {1, 3, APCalcClass::btntypProgramImmediate, (char*)"BuiltIn", (char*)"", (char*)"show builtins", APCalcClass::NoParameter},
    {1, 4, APCalcClass::btntypProgramImmediate, (char*)"Funct", (char*)"", (char*)"show function", APCalcClass::NoParameter},
    {1, 5, APCalcClass::btntypProgramImmediate, (char*)"Globl", (char*)"", (char*)"show globals", APCalcClass::NoParameter},
    {1, 6, APCalcClass::btntypProgramImmediate, (char*)"Real", (char*)"", (char*)"show realglobals", APCalcClass::NoParameter},

    {2, 1, APCalcClass::btntypProgram, (char*)"defexp", (char*)"", (char*)"define fname([param_1 [= default_1], ...]) = [expr]", APCalcClass::NoParameter},
    {2, 2, APCalcClass::btntypProgram, (char*)"if", (char*)"", (char*)"if (cond) { } else if (cond) { } else { }", APCalcClass::NoParameter},
    {2, 3, APCalcClass::btntypProgram, (char*)"switch", (char*)"", (char*)"switch (expr) { case 1: statement_1 ... }", APCalcClass::NoParameter},
    {2, 4, APCalcClass::btntypProgram, (char*)"while", (char*)"", (char*)"while (cond) { }", APCalcClass::NoParameter},
    {2, 5, APCalcClass::btntypProgram, (char*)"do", (char*)"", (char*)"do { } while (cond);", APCalcClass::NoParameter},
    {2, 6, APCalcClass::btntypProgram, (char*)"for", (char*)"", (char*)"for (i = lo; i <= hi; ++i) { }", APCalcClass::NoParameter},

    {3, 1, APCalcClass::btntypProgram, (char*)"strcat", (char*)"", (char*)"strcat(s1, ...sn)", APCalcClass::NoParameter},
    {3, 2, APCalcClass::btntypProgram, (char*)"strcmp", (char*)"", (char*)"strcmp(s1, s2)", APCalcClass::NoParameter},
    {3, 3, APCalcClass::btntypProgram, (char*)"strcpy", (char*)"", (char*)"strcpy(dst, src)", APCalcClass::NoParameter},
    {3, 4, APCalcClass::btntypProgram, (char*)"strlen", (char*)"", (char*)"strlen(str)", APCalcClass::NoParameter},
    {3, 5, APCalcClass::btntypProgram, (char*)"strpos", (char*)"", (char*)"strpos(str, tgt)", APCalcClass::NoParameter},
    {3, 6, APCalcClass::btntypProgram, (char*)"substr", (char*)"", (char*)"substr(str, pos, len)", APCalcClass::NoParameter},

    {4, 1, APCalcClass::btntypProgram, (char*)"eval", (char*)"", (char*)"eval(\"...expression...\")", APCalcClass::NoParameter},
    {4, 2, APCalcClass::btntypProgram, (char*)"eq", (char*)"", (char*)"==", APCalcClass::NoParameter},
    {4, 3, APCalcClass::btntypProgram, (char*)"ne", (char*)"", (char*)"!=", APCalcClass::NoParameter},
    {4, 4, APCalcClass::btntypProgram, (char*)"and", (char*)"", (char*)"&", APCalcClass::NoParameter},
    {4, 5, APCalcClass::btntypProgram, (char*)"or", (char*)"", (char*)"|", APCalcClass::NoParameter},
    {4, 6, APCalcClass::btntypProgram, (char*)"xor", (char*)"", (char*)"xor(,)", APCalcClass::NoParameter},

    {5, 1, APCalcClass::btntypProgram, (char*)"epsil", (char*)"", (char*)"epsilon(1e-?)", APCalcClass::FindParameter},
    {5, 2, APCalcClass::btntypFunction, (char*)"<<", (char*)"", (char*)"<<", APCalcClass::NoParameter},
    {5, 3, APCalcClass::btntypFunction, (char*)">>", (char*)"", (char*)">>", APCalcClass::NoParameter},
    {5, 4, APCalcClass::btntypProgram, (char*)"logand", (char*)"", (char*)"&&", APCalcClass::NoParameter},
    {5, 5, APCalcClass::btntypProgram, (char*)"logor", (char*)"", (char*)"||", APCalcClass::NoParameter},
    {5, 6, APCalcClass::btntypProgram, (char*)"disp", (char*)"", (char*)"display(?)", APCalcClass::FindParameter},

    {6, 1, APCalcClass::btntypShift, (char*)"Pgm", (char*)"Click Math, Click-Click Trig", (char*)"", APCalcClass::NoParameter},
    {6, 2, APCalcClass::btntypPrevEval, (char*)"Prev", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 3, APCalcClass::btntypNextEval, (char*)"Next", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 4, APCalcClass::btntypAns, (char*)"Ans", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 5, APCalcClass::btntypClear, (char*)"Clear", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 6, APCalcClass::btntypEval, (char*)"Eval", (char*)"", (char*)"", APCalcClass::NoParameter},

    /* must be last butto of set */ {-1, -1, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter} /* must be last button */
};

static const APCalcClass::ButtonDefinition ProgramButtons_B[] =
{
    {1, 1, APCalcClass::btntypFunction, (char*)"ln", (char*)"", (char*)"ln(?)", APCalcClass::FindParameter},
    {1, 2, APCalcClass::btntypFunction, (char*)"log", (char*)"", (char*)"log(?)", APCalcClass::FindParameter},
    {1, 3, APCalcClass::btntypFunction, (char*)"log2", (char*)"", (char*)"(1/log(2))*log(?)", APCalcClass::FindParameter},
    {1, 4, APCalcClass::btntypFunction, (char*)"logx", (char*)"", (char*)"(1/log(x))*log(?)", APCalcClass::FindParameter},
    {1, 5, APCalcClass::btntypFunction, (char*)"pi", (char*)"", (char*)" pi", APCalcClass::NoParameter},
    {1, 6, APCalcClass::btntypFunction, (char*)"i", (char*)"", (char*)" 1i", APCalcClass::NoParameter},

    {2, 1, APCalcClass::btntypFunction, (char*)"e", (char*)"", (char*)"e", APCalcClass::NoParameter},
    {2, 2, APCalcClass::btntypFunction, (char*)"e^", (char*)"", (char*)"e^", APCalcClass::NoParameter},
    {2, 3, APCalcClass::btntypFunction, (char*)"10^", (char*)"", (char*)"10^", APCalcClass::NoParameter},
    {2, 4, APCalcClass::btntypFunction, (char*)"^2", (char*)"", (char*)"^2", APCalcClass::NoParameter},
    {2, 5, APCalcClass::btntypFunction, (char*)"^", (char*)"", (char*)"^", APCalcClass::NoParameter},
    {2, 6, APCalcClass::btntypFunction, (char*)"1/x", (char*)"", (char*)"(1/?)", APCalcClass::FindParameter},

    {3, 1, APCalcClass::btntypFunction, (char*)"re", (char*)"", (char*)"re(?)", APCalcClass::FindParameter},
    {3, 2, APCalcClass::btntypFunction, (char*)"im", (char*)"", (char*)"im(?)", APCalcClass::FindParameter},
    {3, 3, APCalcClass::btntypFunction, (char*)"arg", (char*)"", (char*)"arg(?)", APCalcClass::FindParameter},
    {3, 4, APCalcClass::btntypFunction, (char*)"conj", (char*)"", (char*)"conj(?)", APCalcClass::FindParameter},
    {3, 5, APCalcClass::btntypFunction, (char*)"polar", (char*)"", (char*)"polar(?r,a)", APCalcClass::FindParameter},
    {3, 6, APCalcClass::btntypFunction, (char*)"atan2", (char*)"", (char*)"atan2(?y,x)", APCalcClass::FindParameter},

    {4, 1, APCalcClass::btntypFunction, (char*)"sign", (char*)"", (char*)"sgn(?)", APCalcClass::FindParameter},
    {4, 2, APCalcClass::btntypFunction, (char*)"abs", (char*)"", (char*)"abs(?)", APCalcClass::FindParameter},
    {4, 3, APCalcClass::btntypFunction, (char*)"ip", (char*)"", (char*)"int(?)", APCalcClass::FindParameter},
    {4, 4, APCalcClass::btntypFunction, (char*)"fp", (char*)"", (char*)"frac(?)", APCalcClass::FindParameter},
    {4, 5, APCalcClass::btntypFunction, (char*)"ceil", (char*)"", (char*)"ceil(?)", APCalcClass::FindParameter},
    {4, 6, APCalcClass::btntypFunction, (char*)"floor", (char*)"", (char*)"floor(?)", APCalcClass::FindParameter},

    {5, 1, APCalcClass::btntypFunction, (char*)"fact", (char*)"", (char*)"fact(?)", APCalcClass::FindParameter},
    {5, 2, APCalcClass::btntypFunction, (char*)"seed", (char*)"", (char*)"srand()", APCalcClass::NoParameter},
    {5, 3, APCalcClass::btntypFunction, (char*)"rand", (char*)"", (char*)"(rand()/2^64))", APCalcClass::NoParameter},
    {5, 4, APCalcClass::btntypFunction, (char*)"mod", (char*)"", (char*)"%", APCalcClass::NoParameter},
    {5, 5, APCalcClass::btntypFunction, (char*)"intDiv", (char*)"", (char*)"//", APCalcClass::NoParameter},
    {5, 6, APCalcClass::btntypFunction, (char*)"round", (char*)"", (char*)"round(?x [,plcs [, rnd]])", APCalcClass::FindParameter},

    {6, 1, APCalcClass::btntypShift, (char*)"Math", (char*)"Click Trig, Click-Click Program", (char*)"", APCalcClass::NoParameter},
    {6, 2, APCalcClass::btntypPrevEval, (char*)"Prev", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 3, APCalcClass::btntypNextEval, (char*)"Next", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 4, APCalcClass::btntypAns, (char*)"Ans", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 5, APCalcClass::btntypClear, (char*)"Clear", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 6, APCalcClass::btntypEval, (char*)"Eval", (char*)"", (char*)"", APCalcClass::NoParameter},

    /* must be last button of set */ {-1, -1, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter} /* must be last button of set */
 };

static const APCalcClass::ButtonDefinition ProgramButtons_C[] =
{
    {1, 1, APCalcClass::btntypFunction, (char*)"sin", (char*)"", (char*)"sin(?)", APCalcClass::FindParameter},
    {1, 2, APCalcClass::btntypFunction, (char*)"cos", (char*)"", (char*)"cos(?)", APCalcClass::FindParameter},
    {1, 3, APCalcClass::btntypFunction, (char*)"tan", (char*)"", (char*)"tan(?)", APCalcClass::FindParameter},
    {1, 4, APCalcClass::btntypFunction, (char*)"sec", (char*)"", (char*)"sec(?)", APCalcClass::FindParameter},
    {1, 5, APCalcClass::btntypFunction, (char*)"csc", (char*)"", (char*)"csc(?)", APCalcClass::FindParameter},
    {1, 6, APCalcClass::btntypFunction, (char*)"cot", (char*)"", (char*)"cot(?)", APCalcClass::FindParameter},

    {2, 1, APCalcClass::btntypFunction, (char*)"asin", (char*)"", (char*)"asin(?)", APCalcClass::FindParameter},
    {2, 2, APCalcClass::btntypFunction, (char*)"acos", (char*)"", (char*)"acos(?)", APCalcClass::FindParameter},
    {2, 3, APCalcClass::btntypFunction, (char*)"atan", (char*)"", (char*)"atan(?)", APCalcClass::FindParameter},
    {2, 4, APCalcClass::btntypFunction, (char*)"asec", (char*)"", (char*)"asec(?)", APCalcClass::FindParameter},
    {2, 5, APCalcClass::btntypFunction, (char*)"acsc", (char*)"", (char*)"acsc(?)", APCalcClass::FindParameter},
    {2, 6, APCalcClass::btntypFunction, (char*)"acot", (char*)"", (char*)"acot(?)", APCalcClass::FindParameter},

    {3, 1, APCalcClass::btntypFunction, (char*)"sinh", (char*)"", (char*)"sinh(?)", APCalcClass::FindParameter},
    {3, 2, APCalcClass::btntypFunction, (char*)"cosh", (char*)"", (char*)"cosh(?)", APCalcClass::FindParameter},
    {3, 3, APCalcClass::btntypFunction, (char*)"tanh", (char*)"", (char*)"tanh(?)", APCalcClass::FindParameter},
    {3, 4, APCalcClass::btntypFunction, (char*)"sech", (char*)"", (char*)"sech(?)", APCalcClass::FindParameter},
    {3, 5, APCalcClass::btntypFunction, (char*)"csch", (char*)"", (char*)"csch(?)", APCalcClass::FindParameter},
    {3, 6, APCalcClass::btntypFunction, (char*)"coth", (char*)"", (char*)"coth(?)", APCalcClass::FindParameter},

    {4, 1, APCalcClass::btntypFunction, (char*)"asinh", (char*)"", (char*)"asinh(?)", APCalcClass::FindParameter},
    {4, 2, APCalcClass::btntypFunction, (char*)"acosh", (char*)"", (char*)"acosh(?)", APCalcClass::FindParameter},
    {4, 3, APCalcClass::btntypFunction, (char*)"atanh", (char*)"", (char*)"atanh(?)", APCalcClass::FindParameter},
    {4, 4, APCalcClass::btntypFunction, (char*)"asech", (char*)"", (char*)"asech(?)", APCalcClass::FindParameter},
    {4, 5, APCalcClass::btntypFunction, (char*)"acsch", (char*)"", (char*)"acsch(?)", APCalcClass::FindParameter},
    {4, 6, APCalcClass::btntypFunction, (char*)"acoth", (char*)"", (char*)"acoth(?)", APCalcClass::FindParameter},

    {5, 1, APCalcClass::btntypFunction, (char*)"pi", (char*)"", (char*)"pi", APCalcClass::NoParameter},
    {5, 2, APCalcClass::btntypFunction, (char*)"\xbb" "deg", (char*)"", (char*)"*(180/pi)", APCalcClass::NoParameter},
    {5, 3, APCalcClass::btntypFunction, (char*)"\xbb" "rad", (char*)"", (char*)"*(pi/180)", APCalcClass::NoParameter},
    {5, 4, APCalcClass::btntypFunction, (char*)"ln", (char*)"", (char*)"ln(?)", APCalcClass::FindParameter},
    {5, 5, APCalcClass::btntypFunction, (char*)"log", (char*)"", (char*)"log(?)", APCalcClass::FindParameter},
    {5, 6, APCalcClass::btntypFunction, (char*)"^", (char*)"", (char*)"^", APCalcClass::NoParameter},

    {6, 1, APCalcClass::btntypShift, (char*)"Trig", (char*)"Click Program, Click-Click Math", (char*)"", APCalcClass::NoParameter},
    {6, 2, APCalcClass::btntypPrevEval, (char*)"Prev", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 3, APCalcClass::btntypNextEval, (char*)"Next", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 4, APCalcClass::btntypAns, (char*)"Ans", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 5, APCalcClass::btntypClear, (char*)"Clear", (char*)"", (char*)"", APCalcClass::NoParameter},
    {6, 6, APCalcClass::btntypEval, (char*)"Eval", (char*)"", (char*)"", APCalcClass::NoParameter},

    /* must be last button of set */ {-1, -1, APCalcClass::btntypNone, (char*)"", (char*)"", (char*)"", APCalcClass::NoParameter} /* must be last button of set */
 };

#endif // BUTTONDEFINITIONS_H
