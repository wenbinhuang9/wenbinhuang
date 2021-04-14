# An Example: Create Docker Image

As a unix lover, I like to use ubuntu with zsh.

```Dockerfile 
FROM ubuntu:16.04
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

ENTRYPOINT ["/bin/zsh"]
```

The following is the command to build image and run it 

```shell 
mkdir ubuntu-zsh 
touch Dockerfile
// copy the content into Dockerfile

// start to build image as follows
docker build --no-cache -t wenbinhuang/ubuntu-zsh ./   

// start  to run as follows
docker run -it wenbinhuang/ubuntu-zsh 
```

Reference 

[github docker-ubuntu-zsh](https://github.com/mhlavac/docker-ubuntu-zsh/blob/master/Dockerfile)
