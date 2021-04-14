# Docker: Build xv6 Environment.

Initially, I use ubuntu:16.04 as a base image, and error occurs.

Error message is `unable to locate gcc-riscv64-linux-gnu, unable to locate binutils-riscv64-linux-gnu`

So I search on the google , I found some guy used higher version ubuntu image. 

So I try to use ubuntu 20.04 as a base image, and it succeeds.

Docker file for xv6 as following 

```Dockerfile
FROM ubuntu:20.04
MAINTAINER Wenbin Huang <wenbinhuang001@gmail.com>

RUN \
    apt-get update && \
    apt-get -y upgrade && \
    apt-get -y install sudo git && \
    cd ~root && \
    git clone https://github.com/mhlavac/my-zsh.git && \
    cd my-zsh && \
    ./install.sh && \
    /bin/zsh --login -c "/bin/zsh ~/my-zsh/.zshrc" && \
    apt-get clean && \
    apt-get autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/cache/* && \
    rm -rf /var/lib/log/*

    apt-get install git build-essential gdb-multiarch qemu-system-misc
    apt-get install gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu
    apt-get install python
ENTRYPOINT ["/bin/zsh"]
```

Reference 

[Tools Used in 6.S081](https://pdos.csail.mit.edu/6.S081/2020/tools.html)