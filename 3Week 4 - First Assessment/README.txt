Dear sir/madam,

This folder ought to contain, amongst other things, a file called "dla_1.2_main.c" and a file called "dla_1.3_print_grid_colour.c".

Now the first of these, "dla_1.2_main.c", will produce the crystal required by the problem sheet AS A SERIES OF HASHES, and ought to be compiled from the console using:

    gcc dla_1.2_main.c -Wall -Wfloat-equal -Wextra -O2 -pedantic -ansi

Meanwhile the second file, "dla_1.3_print_grid_colour.c", will produce the crystal IN COLOUR, and ought to be compiled using:

    gcc dla_1.3_print_grid_colour.c neillncurses.c -Wall -Wfloat-equal -Wextra -O2 -pedantic -ansi -lncurses -lm

The second file will also require the presence of "neillncurses.c" and "neillncurses.h" in order to compile properly.

Best wishes,
Tom Hosker
