# ChaCha20

This is an implementation of the ChaCha20 encryption scheme in C and C++.\
To get the full details of both implementations, follow these links:
- [C](C/)
- [C++](C++/)

## Validity of the implementation

Both [test.c](../C/tests/test.c) and [test.cpp](tests/test.cpp) are here to check the validity of this implementation, according to the [RFC 7539](https://tools.ietf.org/html/rfc7539).\
These two programs run the ChaCha20 algorithm using the same parameters as used in the example section [2.4.2](https://tools.ietf.org/html/rfc7539#section-2.4.2) of said RFC:
- key=00:01:02:03:04:05:06:07:08:09:0a:0b:0c:0d:0e:0f:10:11:12:13:14:15:16:17:18:19:1a:1b:1c:1d:1e:1f
- nonce=(00:00:00:00:00:00:00:4a:00:00:00:00)
- initial counter=1
- message="Ladies and Gentlemen of the class of '99: If I could offer you only one tip for the future, sunscreen would be it."

The expected cipher text is:\
6e 2e 35 9a 25 68 f9 80 41 ba 07 28 dd 0d 69 81 e9 7e 7a ec 1d 43 60 c2 0a 27 af cc fd 9f ae 0b f9 1b 65 c5 52 47 33 ab 8f 59 3d ab cd 62 b3 57 16 39 d6 24 e6 51 52 ab 8f 53 0c 35 9f 08 61 d8 07 ca 0d bf 50 0d 6a 61 56 a3 8e 08 8a 22 b6 5e 52 bc 51 4d 16 cc f8 06 81 8c e9 1a b7 79 37 36 5a f9 0b bf 74 a3 5b e6 b4 0b 8e ed f2 78 5e 42 87 4d