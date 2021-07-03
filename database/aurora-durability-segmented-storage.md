# Aurora Durability: Segmented Storage 

Why aurora uses segmented storage? 

Before diving into segmented storage, the prerequisit is to understand the Aurora quorum model [quorum model in aurora](./quorum-model-in-aurora.md). 

After AZ + 1 failure occurs, aurora is to repair the failed replicas. If there is another failure faults occurs before repairment is done, the quorum model will be totally broken. So the basical idea is to reduce repairment window time, and make repairement done before next fault occurring.  

The solution to make repairment done quickly is to parition database volume into small segments. Each replicated segment is the smallest repair unit. And aurora make each segment to be 10GB to make repairment time to be 10s under 10Gbps network. 

Another idea is to isolate segment failures. The solution is Protection Group, each protection group contains 6 segments with 2 segments in each 3 AZs. And the background noise is independent from Protection Groups. 

### Segment Size Trade-off

- Big segment size will cause repairment time increase, but reduce the size of metadata
- Small segment size decreases repariment time, but increases metadata size. 

### Summary of Key Ideas 

1. Use segmented storage to shrink repairment window
2. Use protection group to isolate failures of segmentation. 


