# OLAP 

OLAP is an online analytical processing system. 

The properties of OLAP are

1. Large data set as input 
2. Not sensitive to latency
3. For analytical purpose, usually computed on aggregation, sorting, group by operations. 

In computer science, data warehouse is used to support OLAP. And for OLAP system, other techniques like data mining is used to support intelligent analysis.  

In data warehouse, there is a data organization for analysis.  One example is we call it star pattern. In star pattern, we have a fact to describe the details about what occurs, for example, if we buy things from supermarket, we should get to know which customer buys what kinds of products supported by which payment operator. Based on the fact, we have dimension table, like product info, operator info, customer info. So we can aggregate many info from fact based on different dimensions. 

With the development of internet, huge data are produced, so there is a high requirement that how we can get insight from big data.  In storage system, many frameworks are produced to support such requirement. For exmaple, GFS is a distributed system used to store large files. Above GFS, they support column based storage, which is a nosql databse. And computing framework like map reduce ,  enables computing on large data set parallelly. 

