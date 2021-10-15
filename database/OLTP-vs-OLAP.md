# OLTP vs OLAP 

OLTP and OLAP have a totally different property. OLTP is served for online transaction systems.  While OLAP is served for analytics.

1. Data size. OLTP is to deal with small data set. While OLAP is to deal with very large data set.  
2. Latency. OLTP is sensitive to latency, as it is an interactive system, so it has a high requirement for latency. While OLAP is not sensitive to latency. 
3. Throughput. OLTP is an online system, which usually support large number of user requests. 
4. Query Type. OLTP is usually a simple query, while OLAP is a complex query, including aggregation, sorting, group by. 
   

   

