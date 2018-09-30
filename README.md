# ft_ssl
usage: ft_ssl command [command opts] [command args]

Standart commands:

Message Digest commands:
	md5
	sha256

Cipher commands:
	base64
	des
	des-ecb
	des-cbc
	des3
	des3-ecb
	des3-cbc

des-ecb options example:

	-i <file>	input file

	-o <file>	output file

	-e		encrypt

	-d		decrypt

	-a		base64 encode/decode

	-k		key in hex is the next argument

(Any other options you check by inputting wrong opt (smth like -z))
