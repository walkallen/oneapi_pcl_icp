#include <pcl/oneapi/registration/icp.h>
#include <pcl/console/parse.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/io/pcd_io.h>


using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;

/* ---[ */
int
main (int argc, char** argv)
{
  // Parse the command line arguments for .pcd files
  std::vector<int> p_file_indices;
  p_file_indices = parse_file_extension_argument (argc, argv, ".pcd");
  if (p_file_indices.size () != 2)
  {
    print_error ("Need one input source PCD file and one input target PCD file to continue.\n");
    print_error ("Example: %s source.pcd target.pcd\n", argv[0]);
    return (-1);
  }

  // Load the files
  print_info ("Loading %s as source and %s as target...\n", argv[p_file_indices[0]], argv[p_file_indices[1]]);
  PointCloud<PointXYZ>::Ptr src, tgt;
  src.reset (new PointCloud<PointXYZ>);
  tgt.reset (new PointCloud<PointXYZ>);
  if (loadPCDFile (argv[p_file_indices[0]], *src) == -1 || loadPCDFile (argv[p_file_indices[1]], *tgt) == -1)
  {
    print_error ("Error reading the input files!\n");
    return (-1);
  }

  PointCloud<PointXYZ> output;
  // Compute the best transformtion
  pcl::oneapi::IterativeClosestPoint<PointXYZ, PointXYZ> reg;
  reg.setMaximumIterations(20);
  reg.setTransformationEpsilon(1e-12);
  reg.setMaxCorrespondenceDistance(2);

  reg.setInputSource(src);
  reg.setInputTarget(tgt);

  // Register
  reg.align(output); //point cloud output of alignment i.e source cloud after transformation is applied.

  Eigen::Matrix4f transform = reg.getFinalTransformation();

  std::cerr << "Transform Matrix:" << std::endl;
  std::cerr << transform << std::endl;
  // Write transformed data to disk
  savePCDFileBinary ("source_transformed.pcd", output);
}
/* ]--- */