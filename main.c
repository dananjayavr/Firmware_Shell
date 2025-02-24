#include "shell/shell.h"
#include "impl.h"

#define USE_MEMFAULT_SHELL

void console_putc(char c);
void console_puts(const char *s);

int console_gets(char *s, int len);
char console_getc(void);

int main(void) {
#ifndef USE_MEMFAULT_SHELL
    char buf[128];
    int len;
    while (1) {
        console_puts("$ ");
        len = console_gets(buf, 128);  // Read input
        //console_putc('\n');  // Output a newline after input
        if (len) {
            console_puts("OK\n");  // Print confirmation
        }
        //break;  // For this example, we break the loop after one input
    }
#else
    // Configure shell
    sShellImpl shell_impl = {
        .send_char = console_putc,
      };
    shell_boot(&shell_impl);

    // Consume and send characters to shell...forever
    char c;
    while (1) {
        c = console_getc();
        shell_receive_char(c);
    }
#endif
}

void console_puts(const char *s) {
    while (*s != '\0') {
        if (*s == '\r') {
            console_putc('\n');  // Handle carriage return by printing newline
        } else {
            console_putc(*s);  // Otherwise, print the character as is
        }
        s++;
    }
}

void console_putc(char c) {
    app_uart_put(c);  // Forward the character to UART
}

char console_getc(void) {
    uint8_t cr;
    while (app_uart_get(&cr) != SUCCESS);  // Wait for a valid character input
    return (char)cr;  // Return the received character
}

int console_gets(char *s, int len) {
    char *t = s;
    char c;

    *t = '\0';  // Initialize string with null terminator
    while ((c = console_getc()) != '\n') {  // Read until newline
        if (t - s < len - 1) {  // Ensure we don't overflow the buffer
            *t = c;
            //console_putc(c);  // Echo the character
            t++;  // Move to next character in the buffer
        }
    }
    *t = '\0';  // Null-terminate the string after reading
    return t - s;  // Return the length of the string
}
