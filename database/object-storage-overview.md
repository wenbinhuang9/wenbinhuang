# Object Storage Overview 

## Describe Object Storage From its Feature 

1. You have to create a bucket before using it
2. Each object is composed by object key, value and its metadata. 
3. Object key is a unique identification of object, it could be a file name, path or random string. 

## Describe Object Storage From its Design and Architecture 

1. It is implemented by a distributed system, like GFS. 
2. It is optimized for large size object. 
3. The performances of reading and writing usually are faster than traditional file system. 
4. The storage size can be scaled out. 

## Industrial Impl

1. AWS S3, the most famous product in AWS
2. Azure Blob Storage 

### S3
1. Simplicity: API is simple, jsut PUT, GET and DELETE .
2. Scalability: it can be scaled out unlimitedly 
3. Durability: it is really in high durability, r 99.999999999%
4. Availability: designed for 99.99%


## Senarios 

### Archive and Backup

Used as archives. For example, it can be used to archive videos, pictures and digital contracts etc. 

As for backup, for example, we can use it to backup database sanpshot.

### Media Host 

If you are to build media based application like video, music and picture  downloads and uploads, S3 is a good choice.

For example, when you press a play on a Netflix video, the netflix will stream the video from AWS S3. 

### Static Web Site Hosting 

For example, S3 supports building a static web site with high availability, scalability and durability. 

## Reference 

[S3 Common use scenarios](https://docs.aws.amazon.com/AmazonS3/latest/userguide/S3-gsg-CommonUseScenarios.html)

[Netflix: What Happens When You Press Play?](http://highscalability.com/blog/2017/12/11/netflix-what-happens-when-you-press-play.html?currentPage=2)