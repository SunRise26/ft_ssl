/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:35:33 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/23 18:08:20 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_SSL_H
# define __FT_SSL_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readpassphrase.h>
# include <errno.h>
# include <string.h>
# define MIME "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
# define HEXN "0123456789ABCDEF"
# define HEXD "0123456789abcdef"
# define PC1A "\71\61\51\41\31\21\11\1\72\62\52\42\32\22\12\2\73"
# define PC1B "\63\53\43\33\23\13\3\74\64\54\44\77\67\57\47\37\27\17\7\76\66"
# define PC1C "\56\46\36\26\16\6\75\65\55\45\35\25\15\5\34\24\14\4"
# define PC1 PC1A PC1B PC1C
# define PC2A "\16\21\13\30\1\5\3\34\17\6\25\12\27\23\14\4\32\10"
# define PC2B "\20\7\33\24\15\2\51\64\37\45\57\67\36\50\63\55\41\60\54\61\47"
# define PC2C "\70\42\65\56\52\62\44\35\40"
# define PC2 PC2A PC2B PC2C
# define IPA "\72\62\52\42\32\22\12\2\74\64\54\44\34\24\14\4\76\66\56\46\36\26"
# define IPB "\16\6\100\70\60\50\40\30\20\10\71\61\51\41\31\21\11\1\73\63\53\43"
# define IPC "\33\23\13\3\75\65\55\45\35\25\15\5\77\67\57\47\37\27\17\7"
# define IP IPA IPB IPC
# define EBITA "\40\1\2\3\4\5\4\5\6\7\10\11\10\11\12\13\14\15\14"
# define EBITB "\15\16\17\20\21\20\21\22\23\24\25\24\25\26\27\30\31\30\31\32\33"
# define EBITC "\34\35\34\35\36\37\40\1"
# define EBIT EBITA EBITB EBITC
# define S1A "\16\4\15\1\2\17\13\10\3\12\6\14\5\11\0\7\0\17\7\4\16"
# define S1B "\2\15\1\12\6\14\13\11\5\3\10\4\1\16\10\15\6\2\13\17\14\11\7\3\12"
# define S1C "\5\0\17\14\10\2\4\11\1\7\5\13\3\16\12\0\6\15"
# define S1 S1A S1B S1C
# define S2A "\17\1\10\16\6\13\3\4\11\7\2\15\14\0\5\12\3\15\4\7\17"
# define S2B "\2\10\16\14\0\1\12\6\11\13\5\0\16\7\13\12\4\15\1\5\10\14\6\11\3"
# define S2C "\2\17\15\10\12\1\3\17\4\2\13\6\7\14\0\5\16\11"
# define S2 S2A S2B S2C
# define S3A "\12\0\11\16\6\3\17\5\1\15\14\7\13\4\2\10\15\7\0\11"
# define S3B "\3\4\6\12\2\10\5\16\14\13\17\1\15\6\4\11\10\17\3\0\13\1"
# define S3C "\2\14\5\12\16\7\1\12\15\0\6\11\10\7\4\17\16\3\13\5\2\14"
# define S3 S3A S3B S3C
# define S4A "\7\15\16\3\0\6\11\12\1\2\10\5\13\14\4\17\15\10\13\5"
# define S4B "\6\17\0\3\4\7\2\14\1\12\16\11\12\6\11\0\14\13\7\15\17\1\3\16\5\2"
# define S4C "\10\4\3\17\0\6\12\1\15\10\11\4\5\13\14\7\2\16"
# define S4 S4A S4B S4C
# define S5A "\2\14\4\1\7\12\13\6\10\5\3\17\15\0\16\11\16\13\2\14"
# define S5B "\4\7\15\1\5\0\17\12\3\11\10\6\4\2\1\13\12\15\7\10\17\11\14\5\6\3"
# define S5C "\0\16\13\10\14\7\1\16\2\15\6\17\0\11\12\4\5\3"
# define S5 S5A S5B S5C
# define S6A "\14\1\12\17\11\2\6\10\0\15\3\4\16\7\5\13\12\17\4\2\7\14\11"
# define S6B "\5\6\1\15\16\0\13\3\10\11\16\17\5\2\10\14\3\7\0\4\12\1\15\13"
# define S6C "\6\4\3\2\14\11\5\17\12\13\16\1\7\6\0\10\15"
# define S6 S6A S6B S6C
# define S7A "\4\13\2\16\17\0\10\15\3\14\11\7\5\12\6\1\15\0\13\7\4\11\1\12"
# define S7B "\16\3\5\14\2\17\10\6\1\4\13\15\14\3\7\16\12\17\6\10\0\5\11"
# define S7C "\2\6\13\15\10\1\4\12\7\11\5\0\17\16\2\3\14"
# define S7 S7A S7B S7C
# define S8A "\15\2\10\4\6\17\13\1\12\11\3\16\5\0\14\7\1\17\15\10\12\3\7\4"
# define S8B "\14\5\6\13\0\16\11\2\7\13\4\1\11\14\16\2\0\6\12\15\17\3\5\10"
# define S8C "\2\1\16\7\4\12\10\15\17\14\11\0\3\5\6\13"
# define S8 S8A S8B S8C
# define PERA "\20\7\24\25\35\14\34\21\1\17\27\32\5\22\37\12\2\10\30"
# define PERB "\16\40\33\3\11\23\15\36\6\26\13\4\31"
# define PER PERA PERB
# define FIPA "\50\10\60\20\70\30\100\40\47\7\57\17\67\27\77\37\46\6\56\16\66"
# define FIPB "\26\76\36\45\5\55\15\65\25\75\35\44\4\54\14\64\24\74\34\43\3\53"
# define FIPC "\13\63\23\73\33\42\2\52\12\62\22\72\32\41\1\51\11\61\21\71\31"
# define FIP FIPA FIPB FIPC
# define RFIPA "\72\62\52\42\32\22\12\2\74\64\54\44\34\24\14\4\76\66\56\46\36"
# define RFIPB "\26\16\6\100\70\60\50\40\30\20\10\71\61\51\41\31\21\11\1\73\63"
# define RFIPC "\53\43\33\23\13\3\75\65\55\45\35\25\15\5\77\67\57\47\37\27\17\7"
# define RFIP RFIPA RFIPB RFIPC
# define RIPA "\50\10\60\20\70\30\100\40\47\7\57\17\67\27\77\37\46\6\56\16"
# define RIPB "\66\26\76\36\45\5\55\15\65\25\75\35\44\4\54\14\64\24\74\34\43\3"
# define RIPC "\53\13\63\23\73\33\42\2\52\12\62\22\72\32\41\1\51\11\61\21\71\31"
# define RIP RIPA RIPB RIPC
# define MD5_A 1732584193
# define MD5_B 4023233417
# define MD5_C 2562383102
# define MD5_D 271733878
# define MD5_SA "\7\14\21\26\7\14\21\26\7\14\21\26\7\14\21\26"
# define MD5_SB "\5\11\16\24\5\11\16\24\5\11\16\24\5\11\16\24"
# define MD5_SC "\4\13\20\27\4\13\20\27\4\13\20\27\4\13\20\27"
# define MD5_SD "\6\12\17\25\6\12\17\25\6\12\17\25\6\12\17\25"
# define MD5_S MD5_SA MD5_SB MD5_SC MD5_SD
# define MD5_KA "\0\1\2\3\4\5\6\7\10\11\12\13\14\15\16\17"
# define MD5_KB "\1\6\13\0\5\12\17\4\11\16\3\10\15\2\7\14"
# define MD5_KC "\5\10\13\16\1\4\7\12\15\0\3\6\11\14\17\2"
# define MD5_KD "\0\7\16\5\14\3\12\1\10\17\6\15\4\13\2\11"
# define MD5_K MD5_KA MD5_KB MD5_KC MD5_KD
# define SHA256_A 0x6a09e667
# define SHA256_B 0xbb67ae85
# define SHA256_C 0x3c6ef372
# define SHA256_D 0xa54ff53a
# define SHA256_E 0x510e527f
# define SHA256_F 0x9b05688c
# define SHA256_G 0x1f83d9ab
# define SHA256_H 0x5be0cd19

void					ft_putstr(char *s);
void					ft_puter(char *s);
void					ft_putendl(char *s);
size_t					ft_strlen(char *s);
char					*word_in_br(char *s);
char					**des_e(unsigned char **s1, char *s2, int *i, int a);
char					**plain16(char **s);
char					**ch_hex(unsigned char *str, char *n, int *k);
unsigned long long int	bl64(char *s, char *hex);
void					hex64(char *s, unsigned long long int n, char *hex);
unsigned int			*pc_one(unsigned long long int n, char *pc1);
unsigned int			lsh1(unsigned int n);
unsigned int			*lshift(unsigned int *n);
unsigned long long int	uint_join(unsigned int i1, unsigned int i2, int n);
unsigned long long		*pc_two(unsigned int *key16, char *pc2);
unsigned int			perm(unsigned int n, char *per);
unsigned long long int	bl_ip(unsigned long long int n, char *ip);
unsigned long long int	pr_ebit(unsigned int right,
						unsigned long long int key, char *ebit);
unsigned int			sbox(unsigned long long int c, char *s, int sh);
unsigned int			sboxes(unsigned long long int n);
unsigned long long int	fin_ip(unsigned long long int n, char *fip);
void					block_e(char **str, unsigned long long int *key);
unsigned char			*des_strj(char **str, int len);
unsigned char			*des_pad(unsigned char **s, int *i);
void					pad_ch(int *i, unsigned char *s);
unsigned int			*llu_div(unsigned long long int n);
char					**des_d(unsigned char **s1, char *s2, int *i, int a);
void					block_d(char **str, unsigned long long int *key);
void					ft_putstr_fd(unsigned char *s, int fd);
int						ft_scmp(char *s1, char *s2);
void					ssl_commands(char *s);
unsigned char			*ft_strj(unsigned char *s1,
						unsigned char *s2, int i1, int j1);
unsigned char			*ft_read(int op, int len, int *i);
int						fd_io(int fd_i[2], int fd_o[2], char **argv, int *i);
void					base64_options(char *s);
int						file_er(int i[2], int o[2], char **argv);
void					base64_m(int fd_i, int fd_o, char f);
void					base64(char **argv);
int						ft_base64e_res(unsigned char *str,
						char *res, char *key, int k);
char					*ft_base64e(unsigned char **str, char *key, int *k);
int						ft_base64d_res(unsigned char *str, char *res, int k);
char					*ft_base64d(unsigned char **str, char *key, int *k);
unsigned char			*hex_out(char *str, char *hex);
int						fd_iok(int fd[6], char **argv, int *i);
void					des_ecb_options(char *s);
void					des_ecb_m(int fd[6], char f, char **argv);
void					des_ecb(char **argv);
char					*ft_getpass(void);
void					key_hex_ch(char **key);
void					key_er(char **key, int k);
char					*key_ch(int i, char **argv, char sw, int k);
char					*ft_getp(char sw);
void					des_cbc(char **argv);
void					des_cbc_m(int fd[7], char f, char **argv);
int						fd_iokiv(int fd[7], char **argv, int *i);
void					des_cbc_options(char *s);
void					block_cbc_e(char **str, unsigned long long int *key,
						unsigned long long int iv);
char					**des_cbc_e(unsigned char **s1, char **s2, int *i,
						int a);
void					block_cbc_d(char **str, unsigned long long int *key,
						unsigned long long int iv);
char					**des_cbc_d(unsigned char **s1, char **s2, int *i,
						int a);
void					ft_base64wh(unsigned char **in, int i);
void					des3_ecb(char **argv);
void					des3_ecb_m(int fd[6], char f, char **argv);
void					res_free(char **res);
void					free_cbc(char **key);
void					des_cbc_m(int fd[7], char f, char **argv);
void					des3_cbc(char **argv);
char					**des3_cbc_e(unsigned char **s1, char **s2,
						int *i, int a);
char					**des3_cbc_d(unsigned char **s1, char **s2,
						int *i, int a);
void					des3_key48(unsigned long long int **key48, char **s2);
void					block3_cbc_d(char **str, unsigned long long int **key,
						unsigned long long int iv);
void					block3_cbc_e(char **str, unsigned long long int **key,
						unsigned long long int iv);
unsigned long long int	bl3_cbc_d(char *str, unsigned long long *key,
						unsigned long long int iv);
unsigned long long int	bl3_cbc_e(char *str, unsigned long long *key,
						unsigned long long int iv);
int						shift_base64(int *j, char *res,
						unsigned char *str, char *key);
int						new_k(unsigned char *str, int *k);
int						ft_base64ad(unsigned char *str, char *key, int k1);
unsigned int			bits_rot(unsigned int n, unsigned int bits);
void					md_options(char *s);
void					md_out(char *out, int flags, char *md_str,
						char *md_name);
void					md_files(int flags, char **argv, int i,
						char *(*md_e)(char *argv));
void					md_stdin(int *flags, char *(*md_e)(char *argv),
						char *md_name);
void					md_main(char **argv, char *(*md_e)(char *argv));
void					len_pad(unsigned long long len, unsigned char **s,
						int i);
unsigned char			*md5_pad(char *s, int *size);
unsigned int			**words_conv(unsigned char *s, int size);
char					*md5_output_conv(unsigned int abcd[4]);
char					*md5_e(char *s);
void					md5_rounds(unsigned int **word, int x,
						unsigned int *abcd, const unsigned int md5_t[64]);
void					md5_add_buff(unsigned int abcd[4],
						unsigned int buff[4]);
void					md5_process(unsigned int **word, int size,
						unsigned int abcd[4]);
void					free_word(unsigned int **word, int size);
unsigned int			md5_f(unsigned int x, unsigned int y, unsigned int z);
unsigned int			md5_g(unsigned int x, unsigned int y, unsigned int z);
unsigned int			md5_h(unsigned int x, unsigned int y, unsigned int z);
unsigned int			md5_i(unsigned int x, unsigned int y, unsigned int z);
char					*sha256_e(char *s);
unsigned int			**sha256_words_conv(unsigned char *s, int size);
unsigned char			*sha256_pad(char *s, int *size);
void					sha256_len_pad(unsigned long long len,
						unsigned char **s, int i);
void					sha256_process(unsigned int **word, int size,
						unsigned int hash[8]);
void					sha256_add_buff(unsigned int hash[8],
						unsigned int h_cp[8], unsigned int buff[8]);
void					sha256_set_64w(unsigned int sha256_64w[64],
						unsigned int *word32);
void					sha256_set_buff(unsigned int buff[8],
						unsigned int h_cp[8], unsigned int hash[8]);
void					sha256_compression(unsigned int h_cp[8],
						unsigned int sha256_w[64],
						const unsigned int sha256_k[64]);
unsigned int			bits_rot_rev(unsigned int n, unsigned int bits);
unsigned int			sha256_ch(unsigned int x, unsigned int y,
						unsigned int z);
unsigned int			sha256_maj(unsigned int x, unsigned int y,
						unsigned int z);
unsigned int			sha256_sigma(unsigned int x, int t);
unsigned int			sha256_delta(unsigned int x, int t);
void					ft_toupper(char *s);

#endif
