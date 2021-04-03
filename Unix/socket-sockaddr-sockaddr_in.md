# Socket: socketaddr, socketaddr_in and polymorphism

When I implemented a proxy server using socket, I found I am a little confused about socketaddr and socketaddr_in.  The socketaddr_in is frequently used for socket bind and connect, but it always needs to be cast into socketaddr, which makes me a little confused.

The following code is the bind, connect and accept interface, I found that they all only accept sockaddr as address, that's why we always cast sockaddr_in into sockaddr when calling these interfaces. 

```C
int     accept(int, struct sockaddr * __restrict, socklen_t * __restrict)
__DARWIN_ALIAS_C(accept);
int     bind(int, const struct sockaddr *, socklen_t) __DARWIN_ALIAS(bind);
int     connect(int, const struct sockaddr *, socklen_t) __DARWIN_ALIAS_C(connect);
```

## The design principles behind socketaddr: polymorphism

The socket is designed for general network communication, so the kernel has to support multiple address family, such as IPv4, IPv6. So socketaddr is a general type for address representation. This also allows for future evolutionary.

The sa_family is a key field to identify the address family , it could be IPv4, IPv6 or others. 

```C
struct sockaddr {
	__uint8_t       sa_len;         /* total length */
	sa_family_t     sa_family;      /* [XSI] address family */
	char            sa_data[14];    /* [XSI] addr value (actually larger) */
};
```

The socketaddr_in struct as following. sockaddr_in also contains field `sin_family`, so the runtime program is able to identy which address type based on sa_family_t. 
```C
struct sockaddr_in {
	__uint8_t       sin_len;
	sa_family_t     sin_family;
	in_port_t       sin_port;
	struct  in_addr sin_addr;
	char            sin_zero[8];
};
```

So the design principle behind sockaddr is based on polymorphism. When we call the socket connect, bind or accept , we all need to cast the type into sockaddr, and the program is still able to identity the which address type according to sa_family_t field.   

