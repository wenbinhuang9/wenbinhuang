
# Docker Notes

## Manage Images 

```
docker images // list all images

docker image rm <imageID> // delete a image 

docker commit <ContainerID>  <ImageName> // create a image based on  a container 
```

## Manage Container 

```
docker run -it  --name xv6  <imageID> // create a container from a image with name xv6

docker exec -it xv6 /bin/zsh   //exec /bin/zsh in xv6 container

```
