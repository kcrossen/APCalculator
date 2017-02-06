# APCalculator

Arbitrary Precision Calculator (APCalc)
based on “Calc - C-style arbitrary precision calculator” (2.12.4.14)
by Landon Curt Noll et. al.
http://isthe.com/chongo/tech/comp/calc/

The original Calc was modified by eliminating all of the file-based and terminal-based i/o routines. All communication with the resulting Calc library is accomplished by function calls with string arguments and string returned values.

APCalc is implemented as a Qt-based user interface to the Calc library. This user interface approximates a blend of the features of the HP-42s and the HP-48, but without graphics, statistical, or CAS functionality. The current interface was developed in Qt Creator 4.0.1 "based on Qt 5.6.1 (64 bit)" and has been tested on OS-X 10.11.

APCalc menus are File, Mode, Solve, Equation (Algebraic mode only), Unit, and Constant (more below).

APCalc has three basic modes, RPN, Algebraic (Algebraic Interactive), Program, and Solve. By default, an ini file named “APCalculator.ini” in the “~/Documents/APCalculator/” directory is applied to initialize APCalc modes and “built-in” function definitions. In the shortcut’s properties, you may specify another ini file after the path to the executable file.

<p>Initially set to 64 decimal digits internal precision, with 32 decimal digits displayed, this calculator can be set to any desired precision. Initial operating mode is RPN, which approximates the user interface of the HP-48/49 series calculators. Numeric display, even while entering numbers, features standard digit grouping. In RPN mode, there is essentially unlimited undo/redo of the entire stack, so that even late recognition of a mistake does not require a complete restart.</p>

<p>Algebraic mode allows arbitrary expressions to be entered and evaluated. In Algebraic mode, all results are displayed to the internal precision.</p>

<p>Solve mode is similar to the solve feature of HP calculators, for example allowing solution for any variable even when there is no analytic solution, e.g. Time Value of Money.</p>

<p>Features: Unit conversions, common constants, binary and hexadecimal numeric entry/display, choice of US (period) or EU (comma) radix mark, choice of angle entry (degrees or radians), choice of results display (decimal, scientific, binary, hexadecimal, or a combination of these)</p>

<p>Note: The internal precision is only limited for irrational numbers, e.g. Pi, as all integers and rational numbers, e.g one third, are stored as exact rational numbers (exact numerator and exact denominator).</p>

