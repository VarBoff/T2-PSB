/* gerarIndicesRemissivos 

   Copyright (C) 1990-2022 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <stdio.h>

#define PROGRAM_NAME "ig"
#define AUTHORS proper_name ("Eduardo d'Alençon, Pedro Machado, Vinícius Boff")


/* The value to return to the calling program.  */
static int exit_status;

void
usage (int status)
{
    printf (_(
"\
Usage: %s FORMAT [ARGUMENT]...\n\
or:  %s OPTION\n\
"),PROGRAM_NAME, PROGRAM_NAME);

      fputs (_("\
Print ARGUMENT(s) according to FORMAT, or execute according to OPTION:\n\
\n\
"), stdout);
      fputs (HELP_OPTION_DESCRIPTION, stdout);
      fputs (VERSION_OPTION_DESCRIPTION, stdout);
      fputs (_("\
\n\
FORMAT controls the output as in C printf.  Interpreted sequences are:\n\
\n\
  \\\"      double quote\n\
"), stdout);
      fputs (_("\
  \\\\      backslash\n\
  \\a      alert (BEL)\n\
  \\b      backspace\n\
  \\c      produce no further output\n\
  \\e      escape\n\
  \\f      form feed\n\
  \\n      new line\n\
  \\r      carriage return\n\
  \\t      horizontal tab\n\
  \\v      vertical tab\n\
"), stdout);
      fputs (_("\
  \\NNN    byte with octal value NNN (1 to 3 digits)\n\
  \\xHH    byte with hexadecimal value HH (1 to 2 digits)\n\
  \\uHHHH  Unicode (ISO/IEC 10646) character with hex value HHHH (4 digits)\n\
  \\UHHHHHHHH  Unicode character with hex value HHHHHHHH (8 digits)\n\
"), stdout);
      fputs (_("\
  %%      a single %\n\
  %b      ARGUMENT as a string with '\\' escapes interpreted,\n\
          except that octal escapes are of the form \\0 or \\0NNN\n\
  %q      ARGUMENT is printed in a format that can be reused as shell input,\n\
          escaping non-printable characters with the proposed POSIX $'' syntax.\
\n\n\
and all C format specifications ending with one of diouxXfeEgGcs, with\n\
ARGUMENTs converted to proper type first.  Variable widths are handled.\n\
"), stdout);
      printf (USAGE_BUILTIN_WARNING, PROGRAM_NAME);
      emit_ancillary_info (PROGRAM_NAME);
    }
  exit (status);
}

int main(){
    printf("Página principal");
    return 0;
}
