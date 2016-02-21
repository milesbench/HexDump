#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

void text(unsigned char buffer[], size_t length)
{
	size_t index;
	wchar_t charset[] =
	    L" ☺☻♥♦♣♠•◘○◙♂♀♪♫☼►◄↕‼¶§▬↨↑↓→←∟↔▲▼"
	    " !\"#$%&'()*+,-./0123456789:;<=>"
	    "?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]"
	    "^_`abcdefghijklmnopqrstuvwxyz{|}"
	    "~⌂ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜ¢£¥"
	    "₧ƒáíóúñÑªº¿⌐¬½¼¡«»░▒▓│┤╡╢╖╕╣║╗╝╜"
	    "╛┐└┴┬├─┼╞╟╚╔╩╦╠═╬╧╨╤╥╙╘╒╓╫╪┘┌█▄▌"
	    "▐▀αßΓπΣσµτΦΘΩδ∞φε∩≡±≥≤⌠⌡÷≈°∙·√ⁿ²■ ";

	for (index = 0; index < 16; index++)
		if (index < length)
			putwchar(charset[buffer[index]]);
	putwchar('\n');
}

void hex(unsigned char buffer[], size_t length)
{
	size_t index;

	for (index = 0; index < 16; index++) {
		if (index < length)
			wprintf(L"%02X", buffer[index]);
		else
			wprintf(L"  ");
		if (index % 2)
			putwchar(' ');
	}
	putwchar(' ');
}

int main(int argc, char *argv[])
{
	size_t length;
	unsigned char buffer[16];
	unsigned int address = 0;
	FILE *fp = NULL;

	if (!setlocale(LC_CTYPE, "")) {
		fprintf(stderr, "[-] Can't set locale, Exiting \n");
		return EXIT_FAILURE;
	}

	if (argc > 1)
		fp = fopen(argv[1], "r");

	if (fp == NULL)
		fp = stdin;
	while ((length = fread(buffer, 1, 16, fp)) > 0) {
		wprintf(L"%08X: ", address);
		text(buffer, length);
		hex(buffer, length);
		if (length < 16)
			wprintf(L"%08X:\n", address + (unsigned int)length);
		address += 16;
	}
	fclose(fp);

	return EXIT_SUCCESS;
}
