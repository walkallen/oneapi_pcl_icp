


# oneapi_pcl_icp


本工程是用来表明 oneapi pcl 工程里的一个问题，在使用 oneapi pcl 过程中，如果先链接 pcl native 库，再链接 pcl oneapi 库，那么就会产生错误


```bash
terminate called after throwing an instance of 'flann::FLANNException'
  what():  Unknown index type
Aborted (core dumped)
```


但是如果先链接 pcl oneapi 库，再链接 pcl native 库，那么就不会有问题

```bash

Loading test_P.pcd as source and test_Q.pcd as target...
Transform Matrix:
   0.998886   0.0107214   0.0457269   0.0791013
-0.00950723    0.999591  -0.0266714   0.0252342
 -0.0459948   0.0262073    0.998591   0.0676732
          0           0           0           1

```


# How to Build 编译步骤

```bash
mkdir build
cd build
cmake ..
make
```

# How to run 如何运行

```bash
cd build
make run
```


# How to switch good and bad version 如何切换好坏两个版本

只要修改 CMakeLists.txt 就可切换两个版本

## good version


```bash

target_link_libraries ( oneapi_icp_example

                        #pcl_segmentation
                        pcl_oneapi_registration
                        pcl_oneapi_search
                        pcl_oneapi_kdtree
                        pcl_io
                        pcl_segmentation
)

```




## bad version


```bash

target_link_libraries ( oneapi_icp_example

                        pcl_segmentation
                        pcl_oneapi_registration
                        pcl_oneapi_search
                        pcl_oneapi_kdtree
                        pcl_io
                        #pcl_segmentation
)

```














