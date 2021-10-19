# Row Oriented vs Column Oriented Database

Relational database is a row oriented database. Each row is stored on the page. And the row is organnized by data structure B tree. 

While column oriented database, the internal data structure is totally different. It is a nosql database, which stores key and value format. So the column oriented database can be easily scaled up. 

One classical column oriented database is Hbase. Hbase has a very important concept: column family. Under column family, it can have many columns. The purpose of column family is that we want to have similar access pattern for each column family.  Techniquly, the Hbase internal store the column family data into the same Hfile, this serves the purpose of reducing I/Os. 

For the writing , the relational database is usually random write, which will cause random I/O. We know that random I/O is slow because of seeking. While the column based database uses sequential I/O, it uses write ahead log for recovery purpose, and uses mem store for write performance, and then sync the mem store back to disk when mem store is full. 
