/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** data ***/

struct termios orig_termios;

/*** terminal ***/

void die(char const* s) {
    perror(s);
    exit(EXIT_FAILURE);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);

    struct termios raw = orig_termios;

    // stops printing keypresses, start reading byte by byte, turn off ^C ^Z, turn off ^V
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); 
    // stops ^S ^Q (used for historical reasons), stops ^M from being parsed as a return! 
    // (carriage return; new line)
    raw.c_iflag &= ~(IXON | ICRNL);
    // stop \r\n-ing when I only want to be \n-ing (v-tabs, basically)
    raw.c_oflag &= ~(OPOST);
    
    // other flags the tutorial told me to do
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_cflag |= (CS8); // sets character size to 8

    raw.c_cc[VMIN] = 0; // min bytes needed before read can return
    raw.c_cc[VTIME] = 1; // time before read returns (in .1 secs) (MAX, still reads as fast as typing)

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

/*** init ***/

int main() {
    enableRawMode();

    while (1) {
        char c = '\0';

        // checking EAGAIN is for windows compatibility (EAGAIN on timeout)
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");

        // is c a control character? (non printable)
        if (iscntrl(c)) {
            printf("%d\r\n", c);
        } else {
            printf("%d (%c)\r\n", c, c);
        }

        if (c == 'q') break;
    }

    return EXIT_SUCCESS;
}
