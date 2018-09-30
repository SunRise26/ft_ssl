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
	-i <file>	input file\n
	-o <file>	output file\n
	-e		encrypt\n
	-d		decrypt\n
	-a		base64 encode/decode\n
	-k		key in hex is the next argument\n
(Any other options you check by inputting wrong opt (smth like -z))
