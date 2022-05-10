#include "base64.h"

const char enc_table[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
							'H', 'I', 'J', 'K', 'L', 'M', 'N',
							'O', 'P', 'Q', 'R', 'S', 'T', 'U',
							'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
							'c', 'd', 'e', 'f', 'g', 'h', 'i',
							'j', 'k', 'l', 'm', 'n', 'o', 'p',
							'q', 'r', 's', 't', 'u', 'v', 'w',
							'x', 'y', 'z', '0', '1', '2', '3',
							'4', '5', '6', '7', '8', '9', '+',
							'/', '=' };

const int dec_table[] = {
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
	52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-1,-1,-1,
	-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
	15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
	-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
	41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
};

char* base64_encode(const char* plain) {
	int i = 0, j = 0;
	int len = strlen(plain);
	int bs = len - (len % 3);
	int remain_size = len - bs;
	char buffer[MAX_SIZE];

	for (; i < bs; i += 3) {
		buffer[j++] = enc_table[(plain[i] >> 2) & 0x3f];

		buffer[j++] = enc_table[((plain[i] & 0x03) << 4) + ((plain[i + 1] >> 4) & 0x0f)];

		buffer[j++] = enc_table[((plain[i + 1] & 0x0f) << 2) + ((plain[i + 2] >> 6) & 0x03)];

		buffer[j++] = enc_table[plain[i + 2] & 0x3f];
	}

	if (remain_size != 0) {
		buffer[j++] = enc_table[plain[i] >> 2 & 0x3f];

		if (len - i == 2) {
			buffer[j++] = enc_table[((plain[i] & 0x03) << 4) + ((plain[i + 1] >> 4) & 0x0f)];
			buffer[j++] = enc_table[(plain[i + 1] & 0x0f) << 2];
		}
		else {
			buffer[j++] = enc_table[(plain[i] & 0x03) << 4];
			buffer[j++] = enc_table[PADDING];
		}


		buffer[j++] = enc_table[PADDING];
	}

	buffer[j++] = NULL;

	int size = sizeof(char) * j;

	char* result = (char*)malloc(size);
	memset(result, NULL, size);
	memmove(result, buffer, size);

	return result;
}

char* base64_decode(const char* encoded) {
	int i = 0, j = 0;
	int len = strlen(encoded);

	char buffer[MAX_SIZE];
	for (; i < len; i += 4) {
		int c0 = dec_table[encoded[i]];
		int c1 = dec_table[encoded[i + 1]];
		int c2 = dec_table[encoded[i + 2]];
		int c3 = dec_table[encoded[i + 3]];

		buffer[j++] = (c0 << 2) | (c1 >> 4);
		buffer[j++] = (c1 << 4) | (c2 >> 2);
		buffer[j++] = (c2 << 6) | c3;
	}

	buffer[j++] = NULL;

	int size = sizeof(char) * j;
	char* result = (char*)malloc(size);
	memset(result, NULL, size);
	memmove(result, buffer, size);

	return result;
}
